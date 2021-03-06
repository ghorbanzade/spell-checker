/**
 * splchk: interactive command-line tool to find and fix spelling errors
 * Copyright 2016 Pejman Ghorbanzade <pejman@ghorbanzade.com>
 * Released under the terms of MIT License
 * https://github.com/ghorbanzade/splchk/blob/master/LICENSE
 */

#include "util.h"

static struct termios old, new;

/**
 *
 *
 *
 */
char getch(void)
{
    char ch;
    tcgetattr(0, &old);
    new = old;
    new.c_lflag &= ~ICANON;
    new.c_lflag &= ~ECHO;
    tcsetattr(0, TCSANOW, &new);
    ch = getchar();
    tcsetattr(0, TCSANOW, &old);
    return ch;
}

/**
 *
 *
 *
 */
void input_line(char *out, size_t size)
{
    size_t i = 0;
    char ch;
    char tmp[size];
    while ((ch = getch()) != '\n') {
        if (ch == 127) {
            if (i == 0) continue;
            tmp[i--] = '\0';
            printf("\b \b");
        } else if (i < sizeof(tmp) - 1) {
            putchar(ch);
            tmp[i++] = ch;
        }
    }
    tmp[i] = '\0';
    putchar('\n');
    strncpy(out, tmp, size);
}

/**
 *
 *
 *
 */
int get_word(FILE *file, char *word)
{
    int ret = 0;
    if (fscanf(file, "%s", word) == EOF)
        goto ERROR;
    ret = 1;

ERROR:
    return ret;
}

/**
 *
 *
 *
 */
void print_help()
{
    char const * const msg =
        "\n  usage: splchk [-hv] [[-i] input_file] [-p | -o output_file]"
        "\n                [-d dictionary_file]"
        "\n"
        "\n  -d dictionary_file    file to be used as dictionary"
        "\n  -h                    prints this message and exits"
        "\n  -i input_file         file to check"
        "\n  -o output_file        file to write corrected text into"
        "\n  -p                    makes document to be modified in-place"
        "\n  -v                    prints version and exits"
        "\n\n";
    printf(msg);
}

/**
 *
 *
 *
 */
void print_banner()
{
    char const * const msg =
        "\n\n"
        "\n        splchk v1.1, Copyright (C) 2016 Pejman Ghorbanzade"
        "\n        This software comes with ABSOLUTELY NO WARRANTY."
        "\n        This is free software, and you are welcome to redistribute it"
        "\n        under certain conditions; refer to `license' for details."
        "\n\n";
    printf(msg);
}

/**
 *
 *
 *
 */
void print_version()
{
    printf("%s version %s\n", "splchk", "v1.1");
}

/**
 *
 *
 *
 */
void print_header(char const * const doc)
{
    printf("%-39s%40s\n", "splchk", doc);
}

/**
 *
 *
 *
 */
int print_content(char const *const filename)
{
    int ret = -1;
    char line[LINE_WIDTH];
    FILE *file = NULL;
    file = fopen(filename, "r");
    if (file == NULL) {
        log_error("unable to open file %s.", filename);
        goto ERROR;
    }
    while (fgets(line, LINE_WIDTH, file) != NULL) {
        int i = 0;
        while (line[i] == ' ')
            i++;
        if (line[i] != '#')
            fprintf(stdout, "%s", line);
    }
    ret = 0;

 ERROR:
    if (file != NULL)
        fclose(file);

    return ret;
}

/**
 *
 *
 *
 */
void print_hr(void)
{
    int i;
    for (i = 0; i < LINE_WIDTH; i++)
        putchar('-');
    putchar('\n');
}

/**
 *
 *
 *
 */
void print_preview(FILE *file, char const word[])
{
    long pre, len;
    long cur, end;
    size_t size = 300;

    cur = ftell(file);
    pre = ((size_t) cur < size) ? 0 : cur - size - strlen(word);
    len = ((size_t) cur < size) ? cur - strlen(word) : size;
    print_snippet(file, pre, len);

    printf("%s%s%s ", KRED, word, KNRM);

    fseek(file, 0, SEEK_END);
    end = ftell(file);
    fseek(file, cur, SEEK_SET);
    len = ((size_t) end < cur + size) ? end - cur : (long) size;
    print_snippet(file, cur, len);

    printf("\n");
    fseek(file, cur, SEEK_SET);
}

/**
 *
 *
 *
 */
void print_snippet(FILE *file, long int const str, size_t const len)
{
    char tmp[len];
    long int cur = ftell(file);
    fseek(file, str, SEEK_SET);
    fread(tmp, sizeof(char), len, file);
    fseek(file, cur, SEEK_SET);
    tmp[len-1] = '\0';
    printf("%s", tmp);
}

/**
 *
 *
 *
 */
void print_progress(FILE *file)
{
    int i;
    long int cur, end, progress;
    cur = ftell(file);
    fseek(file, 0, SEEK_END);
    end = ftell(file);
    fseek(file, cur, SEEK_SET);
    progress = cur * LINE_WIDTH / end;
    for (i = 0; i < progress; i++)
        putchar('-');
    putchar('\n');
}
