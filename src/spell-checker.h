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
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "util.h"

#define FILE_BANNER "cfg/banner"
#define MAX_WORD_LENGTH 40

enum {
	FILE_DOC,
	FILE_DIC,
	FILE_OUT,
	FILE_COUNT
};

void close_files(FILE *files[]);
int handle_word(char buf[], FILE *files[], char *names[]);
int open_files(char *names[], FILE *files[]);
char show_menu(void);
int spell_check(char *names[]);
void trim_word(char *word, char *out);
int is_number(char tmp[]);
int word_exists(FILE *dict, char *word);

#endif //SPELL_CHECKER_H
