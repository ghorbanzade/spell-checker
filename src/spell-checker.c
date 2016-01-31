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
    intro();
	spell_check(FILE_DOCUMENT, FILE_DICTIONARY, FILE_OUTPUT);
}

/**
 *
 *
 *
 */
void intro(void)
{
    clear_screen();
	print_content(FILE_BANNER);
    for (int i = 0; i < 3; i++) {
        fprintf(stdout, ".");
        fflush(stdout);
        sleep(1);
    }
}

/**
 *
 *
 *
 */
void spell_check(char *doc, char *dic, char *out) {
    char wrd[100];
    char tmp[100];
    char word[100];

    FILE *fdoc = NULL;
    FILE *fdic = NULL;
    FILE *fout = NULL;

    fdic = fopen(dic, "r+");
    if (fdic == NULL) {
        print_error("unable to open file %s.", dic);
        goto ERROR;
    }
    fdoc = fopen(doc, "r");
    if (fdoc == NULL) {
        print_error("unable to open file %s.", doc);
        goto ERROR;
    }
    fout = fopen(out, "w");
    if (fout == NULL) {
        print_error("unable to open file %s.", out);
        goto ERROR;
    }

    while (get_word(fdoc, word)) {
        trim_word(word, wrd);
        if (word_exists(fdic, wrd)) {
            add_word(fout, "%s ", word);
        }
        else {
            clear_screen();
            print_header(doc);
            print_hr();
            print_preview(fdoc);
            print_hr();
            printf("word \"%s\" not found in dict\n", wrd);
            switch (show_menu()) {
            case 'a':
                add_word(fdic, "%s\n", wrd);
                add_word(fout, "%s ", wrd);
                break;
            case 's':
                printf("substitute %s: ", wrd);
                get_line_input(tmp, sizeof(tmp));
                printf("entered: %s\n", tmp);
                add_word(fout, "%s ", tmp);
                break;
            case 'c':
                add_word(fout, "%s ", word);
                break;
            }
        }
    }

ERROR:
    if (fdic != NULL)
        fclose(fdic);
    if (fdoc != NULL)
        fclose(fdoc);
    if (fout != NULL)
        fclose(fout);
}

/**
 *
 *
 *
 */
int get_word(FILE *doc, char *word)
{
    int ret = 0;
    if (fscanf(doc, "%s", word) == EOF)
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

/**
 *
 *
 *
 */
void add_word(FILE *file, char *format, ...)
{
    va_list args;
    va_start(args, format);
    fseek(file, 0, SEEK_END);
    vfprintf(file, format, args);
    va_end(args);
}
