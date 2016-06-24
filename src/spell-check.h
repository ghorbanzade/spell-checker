#ifndef SPELL_CHECKER_H
#define SPELL_CHECKER_H

#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "util.h"
#include "logger.h"

#define FILE_BANNER "cfg/banner"
#define FILE_HELP "cfg/help"
#define FILE_VERSION "cfg/version"

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
