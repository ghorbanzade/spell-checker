/**
 * splchk: interactive command-line tool to find and fix spelling errors
 * Copyright 2016 Pejman Ghorbanzade <pejman@ghorbanzade.com>
 * Released under the terms of MIT License
 * https://github.com/ghorbanzade/splchk/blob/master/LICENSE
 */

#ifndef SPELL_CHECKER_H
#define SPELL_CHECKER_H

#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "util.h"
#include "logger.h"

#define DEFAULT_DICTIONARY "dat/dictionary"
#define SC_FILE_BANNER "bin/cfg/banner"
#define SC_FILE_HELP "bin/cfg/help"
#define SC_FILE_VERSION "bin/cfg/version"

#define MAX_WORD_LENGTH 40

enum {
	FILE_DOC,
	FILE_DIC,
	FILE_OUT,
	FILE_COUNT
};

struct sc_config {
    int in_place;
    char const *file[FILE_COUNT];
};

int check_config(struct sc_config *config, int argc, char *argv[]);
int spell_check(struct sc_config const *config);
void close_files(FILE *files[]);
int handle_word(char buf[], FILE *files[], struct sc_config const *config);
int open_files(struct sc_config const *config, FILE *files[]);
char show_menu(void);
void trim_word(char *word, char *out);
int is_number(char tmp[]);
int word_exists(FILE *dict, char *word);

#endif //SPELL_CHECKER_H
