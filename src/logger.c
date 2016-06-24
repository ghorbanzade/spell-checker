#include "logger.h"

enum log_level {
	LOG_DEBUG,
	LOG_INFO,
	LOG_WARN,
	LOG_ERROR,
	LOG_FATAL,
	LOG_LEVEL // to get number of enum items
};

static FILE *fp;
static char fmt[LOG_MSG_LEN];
static char const *levels[LOG_LEVEL];
static int started = 0;

/**
 *
 */
void logit_start()
{
	started = 1;
	// the advantage of this kind of initialization is that the
	// values will be independant from the order of enum items.
	levels[LOG_DEBUG] = "debug";
	levels[LOG_INFO] = "info";
	levels[LOG_WARN] = "warning";
	levels[LOG_ERROR] = "error";
	levels[LOG_FATAL] = "fatal";
	log_debug("logger initialized");
}

/**
 *
 */
void logit(enum log_level const level, char const *format, va_list args)
{
	if (!started)
		logit_start();
	sprintf(fmt, "%s: %s\n", levels[level], format);
	// TODO: log all messages into a log file

	switch (level) {
	case LOG_DEBUG:
		break;
	case LOG_INFO:
	case LOG_WARN:
		vfprintf(stdout, fmt, args);
		break;
	case LOG_ERROR:
	case LOG_FATAL:
		vfprintf(stderr, fmt, args);
		break;
	default:
		log_fatal("invalid log level given to logger");
		break;
	}
}

/**
 * Wrapper API function to log debug messages.
 */
void log_debug(char const *format, ...) {
	va_list args;
	va_start(args, format);
	logit(LOG_DEBUG, format, args);
	va_end(args);
}

/**
 * Wrapper API function to log info messages.
 */
void log_info(char const *format, ...) {
	va_list args;
	va_start(args, format);
	logit(LOG_INFO, format, args);
	va_end(args);
}

/**
 * Wrapper API function to log warnings.
 */
void log_warning(char const *format, ...) {
	va_list args;
	va_start(args, format);
	logit(LOG_WARN, format, args);
	va_end(args);
}

/**
 * Wrapper API functions to log errors.
 */
void log_error(char const *format, ...) {
	va_list args;
	va_start(args, format);
	logit(LOG_ERROR, format, args);
	va_end(args);
}

/**
 * Wrapper API function to log fatal errors.
 */
void log_fatal(char const *format, ...) {
	va_list args;
	va_start(args, format);
	logit(LOG_FATAL, format, args);
	va_end(args);
}
