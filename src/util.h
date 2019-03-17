/**
 * splchk: interactive command-line tool to find and fix spelling errors
 * Copyright 2016 Pejman Ghorbanzade <pejman@ghorbanzade.com>
 * Released under the terms of MIT License
 * https://github.com/ghorbanzade/splchk/blob/master/LICENSE
 */

#ifndef UTIL_H
#define UTIL_H

#include <ctype.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>

#include "config.h"
#include "logger.h"

#define KNRM  "\x1B[0m"
#define KRED  "\x1B[31m"
#define CLSCRN "\e[1;1H\e[2J"
#define LINE_WIDTH 80

char getch(void);
void input_line(char *out, size_t size);
int get_word(FILE *file, char *word);
int print_content(char const *const filename);
void print_header(char const *const doc);
void print_hr(void);
void print_preview(FILE *file, char const word[]);
void print_snippet(FILE *file, long int const str, size_t const len);
void print_progress(FILE *file);

#endif //UTIL_H
