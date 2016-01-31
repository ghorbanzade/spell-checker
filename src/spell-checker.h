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

#ifndef SPELL_CHECKER_H
#define SPELL_CHECKER_H

#include <ctype.h>
#include <string.h>
#include <unistd.h>

#include "util.h"

#define FILE_BANNER "cfg/banner"
#define FILE_DICTIONARY "lib/dictionary"
#define FILE_DOCUMENT "dat/document"
#define FILE_OUTPUT "bin/document"

void add_word(FILE *file, char *format, ...);
int get_word(FILE *doc, char *word);
void intro(void);
char show_menu(void);
void spell_check(char *doc, char *dict, char *out);
void trim_word(char *word, char *out);
int word_exists(FILE *dict, char *word);
void get_line_input(char *out, size_t size);

#endif //SPELL_CHECKER_H
