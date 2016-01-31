/*
 * Spell-Checker v0.1
 * Copyright (C) 2016 Pejman Ghorbanzade
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#include "spell-checker.h"

/**
 *
 *
 *
 */
int main(int argc, char *argv[])
{
    int ret = EXIT_FAILURE;
    char *names[FILE_COUNT];
    names[FILE_DOC] = "dat/document";
    names[FILE_DIC] = "lib/dict";
    names[FILE_OUT] = "bin/document";
    if (spell_check(names))
        goto ERROR;
    print_content(FILE_BANNER);
    ret = EXIT_SUCCESS;
ERROR:

    return ret;
}

/**
 *
 *
 *
 */
int spell_check(char *names[])
{
    int i = 0;
    int ret = -1;
    char ch;
    char buf[MAX_WORD_LENGTH];
    FILE *files[FILE_COUNT];
    if (open_files(names, files))
        goto ERROR;
    while ((ch = getc(files[FILE_DOC])) != EOF) {
        if (isspace(ch)) {
            buf[i] = '\0';
            if (i != 0) {
                if (handle_word(buf, files, names))
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
int handle_word(char buf[], FILE *files[], char *names[])
{
    int ret = -1;
    char tmp[strlen(buf)];
    char inp[MAX_WORD_LENGTH];
    trim_word(buf, tmp);
    if (word_exists(files[FILE_DIC], tmp)) {
        fprintf(files[FILE_OUT], "%s", buf);
    } else {
        clear_screen();
        print_header(names[FILE_DOC]);
        print_hr();
        print_preview(files[FILE_DOC]);
        print_progress(files[FILE_DOC]);
        printf("word \"%s\" not found in dict\n", tmp);
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
        }
    }
    ret = 0;
    return ret;
}

/**
 *
 *
 *
 */
int open_files(char *names[], FILE *files[])
{
    int ret = -1;
    files[FILE_DOC] = fopen(names[FILE_DOC], "r");
    files[FILE_DIC] = fopen(names[FILE_DIC], "r+");
    files[FILE_OUT] = fopen(names[FILE_OUT], "w");
    for (int i = 0; i < FILE_COUNT; i++) {
        if (files[i] == NULL) {
            print_error("unable to open file %s.", names[i]);
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
int word_exists(FILE *dict, char *word)
{
    int ret = 0;
    char line[80];
    fseek(dict, 0, SEEK_SET);
    while (fgets(line, 80, dict) != NULL) {
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
    printf("(a) add to dictionary\n");
    printf("(s) substitute word\n");
    printf("(c) ignore word\n");
    while (1) {
        input = getch();
        if (input == 'a' || input == 's' || input == 'c')
            break;
    }
    return input;
}
