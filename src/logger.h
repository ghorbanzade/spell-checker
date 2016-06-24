#ifndef LOGGER_H
#define LOGGER_H

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LOG_MSG_LEN 256

void log_debug(char const *format, ...);
void log_info(char const *format, ...);
void log_warning(char const *format, ...);
void log_error(char const *format, ...);
void log_fatal(char const *format, ...);

#endif /* LOGGER_H */
