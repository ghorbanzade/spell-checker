/**
 * splchk: interactive command-line tool to find and fix spelling errors
 * Copyright 2016 Pejman Ghorbanzade <pejman@ghorbanzade.com>
 * Released under the terms of MIT License
 * https://github.com/ghorbanzade/splchk/blob/master/LICENSE
 */

#include "main.h"

/**
 *
 *
 *
 */
int main(int argc, char *argv[])
{
    char ch;
    int ret = EXIT_FAILURE;
    struct sc_config config;

    config.in_place = 0;
    config.file[FILE_DIC] = DEFAULT_DICTIONARY;
    while ((ch = getopt(argc, argv, "d:hi:o:pv")) != -1) {
        switch (ch) {
        case 'd':
            config.file[FILE_DIC] = optarg;
            break;
        case 'h':
            print_help();
            return EXIT_SUCCESS;
        case 'i':
            config.file[FILE_DOC] = optarg;
            break;
        case 'o':
            if (config.in_place) {
                log_fatal("output file cannot be specified "
                          "if in-place edit is asked for");
                return EXIT_FAILURE;
            }
            config.file[FILE_OUT] = optarg;
            break;
        case 'p':
            if (config.file[FILE_OUT]) {
                log_fatal("document cannot be edited in place "
                          "if output file is specified");
                return EXIT_FAILURE;
            }
            config.in_place = 1;
            break;
        case 'v':
            print_version();
            return EXIT_SUCCESS;
        default:
            print_help();
            return EXIT_FAILURE;
        }
    }

    if (check_config(&config, argc, argv)) {
        print_help();
        goto ERROR;
    }

    if (spell_check(&config))
        goto ERROR;
    print_banner();
    ret = EXIT_SUCCESS;

 ERROR:
    if (config.file[FILE_OUT])
        free(config.file[FILE_OUT]);
    return ret;
}

/**
 *
 *
 *
 */
int check_config(struct sc_config *config, int argc, char *argv[])
{

    if (!config->file[FILE_DOC]) {
        if (optind < argc && 1 < argc) {
            config->file[FILE_DOC] = argv[optind];
        } else {
            log_fatal("document not specified");
            return -1;
        }
    }

    if (!config->file[FILE_OUT]) {
        if (!config->in_place) {
            config->file[FILE_OUT] = malloc(
                    strlen(config->file[FILE_DOC]) + sizeof(".out")
            );
            strcpy(config->file[FILE_OUT], config->file[FILE_DOC]);
            strcat(config->file[FILE_OUT], ".out");
        } else {
            config->file[FILE_OUT] = config->file[FILE_DOC];
        }
    }

    log_info("input: %s", config->file[FILE_DOC]);
    log_info("output: %s", config->file[FILE_OUT]);
    log_info("dictionary: %s", config->file[FILE_DIC]);

    return 0;
}

/**
 *
 *
 *
 */
int spell_check(struct sc_config const *config)
{
    int i = 0;
    int ret = -1;
    char ch;
    char buf[MAX_WORD_LENGTH];
    FILE *files[FILE_COUNT];

    if (open_files(config, files))
        goto ERROR;
    while ((ch = getc(files[FILE_DOC])) != EOF) {
        if (isspace(ch)) {
            buf[i] = '\0';
            if (i != 0) {
                if (handle_word(buf, files, config))
                    goto ERROR;
                i = 0;
            }
            fprintf(files[FILE_OUT], "%c", ch);
        } else {
            buf[i++] = ch;
        }
    }
    ret = 0;

 ERROR:
    close_files(files);
    return ret;
}

/**
 *
 *
 *
 */
int handle_word(char buf[], FILE *files[], struct sc_config const *config)
{
    int ret = -1;
    char tmp[strlen(buf)];
    char inp[MAX_WORD_LENGTH];
    trim_word(buf, tmp);
    if (is_number(tmp))
        goto NEXT;
    if (word_exists(files[FILE_DIC], tmp)) {
        fprintf(files[FILE_OUT], "%s", buf);
    } else {
        printf(CLSCRN);
        print_header(config->file[FILE_DOC]);
        print_hr();
        print_preview(files[FILE_DOC], buf);
        print_hr();
        printf("word \"%s\" not found in dict\n", tmp);
        print_progress(files[FILE_DOC]);
        switch (show_menu()) {
        case 'a':
            fprintf(files[FILE_DIC], "%s\n", tmp);
            fprintf(files[FILE_OUT], "%s", tmp);
            break;
        case 's':
            printf("substitute %s: ", buf);
            input_line(inp, sizeof(inp));
            fprintf(files[FILE_OUT], "%s", inp);
            break;
        case 'c':
            fprintf(files[FILE_OUT], "%s", buf);
            break;
        case 'q':
            goto ERROR;
        }
    }

 NEXT:
    ret = 0;

 ERROR:
    return ret;
}

/**
 *
 *
 *
 */
int open_files(struct sc_config const *config, FILE *files[])
{
    int ret = -1;
    files[FILE_DOC] = fopen(config->file[FILE_DOC], "r");
    files[FILE_OUT] = fopen(config->file[FILE_OUT], "w");
    files[FILE_DIC] = fopen(config->file[FILE_DIC], "r+");
    for (int i = 0; i < FILE_COUNT; i++) {
        if (files[i] == NULL) {
            log_error("unable to open file %s.", config->file[i]);
            goto ERROR;
        }
    }
    ret = 0;

 ERROR:
    return ret;
}

/**
 *
 *
 *
 */
void close_files(FILE *files[])
{
    for (int i = 0; i < FILE_COUNT; i++)
        if (files[i] != NULL)
            fclose(files[i]);
}

/**
 *
 *
 *
 */
void trim_word(char *word, char *out)
{
    unsigned j = 0u;
    for (size_t i = 0; i < strlen(word); i++) {
        if (!ispunct(word[i]))
            out[j++] = tolower(word[i]);
    }
    out[j] = '\0';
}

/**
 *
 *
 *
 */
int is_number(char tmp[])
{
    int ret = -1;
    for (size_t i = 0; i < strlen(tmp); i++)
        if (!isdigit(tmp[i]))
            ret = 0;
    return ret;
}

/**
 *
 *
 *
 */
int word_exists(FILE *dict, char *word)
{
    int ret = 0;
    char line[LINE_WIDTH];
    fseek(dict, 0, SEEK_SET);
    while (fgets(line, LINE_WIDTH, dict) != NULL) {
        line[strlen(line) - 1] = '\0';
        if (strcmp(line, word) == 0) {
            ret = 1;
            break;
        }
    }
    return ret;
}

/**
 *
 *
 *
 */
char show_menu(void)
{
    char input;
    char *tmp = "ascq";
    printf("(a) add to dictionary\n");
    printf("(s) substitute word\n");
    printf("(c) ignore word\n");
    printf("(q) abort program\n");
    while (1) {
        input = getch();
        for (size_t i = 0; i < strlen(tmp); i++)
            if (input == tmp[i])
                goto FOUND;
    }

FOUND:
    return input;
}
