#include "spell-check.h"

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
            print_content(SC_FILE_HELP);
            return EXIT_SUCCESS;
        case 'i':
            config.file[FILE_DOC] = optarg;
            break;
        case 'o':
            config.file[FILE_OUT] = optarg;
            break;
        case 'p':
            config.in_place = 1;
            break;
        case 'v':
            print_content(SC_FILE_VERSION);
            return EXIT_SUCCESS;
        default:
            print_content(SC_FILE_HELP);
            return EXIT_FAILURE;
        }
    }

    if (spell_check(&config))
        goto ERROR;
    print_content(SC_FILE_BANNER);
    ret = EXIT_SUCCESS;

 ERROR:
    return ret;
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
    int i, j = 0;
    for (i = 0; i < strlen(word); i++) {
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
    for (int i = 0; i < strlen(tmp); i++)
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
    int i;
    char input;
    char *tmp = "ascq";
    printf("(a) add to dictionary\n");
    printf("(s) substitute word\n");
    printf("(c) ignore word\n");
    printf("(q) abort program\n");
    while (1) {
        input = getch();
        for (i = 0; i < strlen(tmp); i++)
            if (input == tmp[i])
                goto FOUND;
    }

FOUND:
    return input;
}
