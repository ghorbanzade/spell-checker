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

#ifndef UTIL_H
#define UTIL_H

#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <termios.h>

#define PROGRAM_NAME "spell-checker"

void clear_screen(void);
char getch(void);
void input_line(char *out, size_t size);
int get_word(FILE *file, char *word);
int print_content(char const *const filename);
void print_error(char *format, ...);
void print_header(char const *const doc);
void print_hr(void);
void print_preview(FILE *file);
void print_progress(FILE *file);

#endif //UTIL_H
