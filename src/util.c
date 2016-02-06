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
    int i = 0;
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
void print_error(char *format, ...)
{
    va_list args;
    char new_format[240];
    va_start(args, format);
    sprintf(new_format, "error: %s\n", format);
    vprintf(new_format, args);
    va_end(args);
}

/**
 *
 *
 *
 */
void print_header(char const *const doc)
{
    printf("%-40s%40s\n", PROGRAM_NAME, doc);
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
        print_error("unable to open file %s.", filename);
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
    long int pre, len;
    long int cur, end;
    size_t size = 300;

    cur = ftell(file);
    pre = (cur < size) ? 0 : cur - size - strlen(word);
    len = (cur < size) ? cur - strlen(word) : size;
    print_snippet(file, pre, len);

    printf("%s%s%s ", KRED, word, KNRM);

    fseek(file, 0, SEEK_END);
    end = ftell(file);
    fseek(file, cur, SEEK_SET);
    len = (end < cur + size) ? end - cur : size;
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
