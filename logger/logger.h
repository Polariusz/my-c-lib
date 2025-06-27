#ifndef LOGGER_H_
#define LOGGER_H_

#include <stdio.h>

typedef enum LOG_TYPE {
	LOG_DEBUG,
	LOG_FINE,
	LOG_WARN,
	LOG_ERROR,
	LOG_PANIC,
} LOG_TYPE;

char *get_log_type_as_str(LOG_TYPE type, int is_coloured);

typedef struct Logger {
	FILE *fd;
	LOG_TYPE log_from;
	int colour;
	int console_log;
} Logger;

int logger_message(Logger *l, LOG_TYPE type, char *msg);
int logger_debug(Logger *l, char *msg);
int logger_fine(Logger *l, char *msg);
int logger_warn(Logger *l, char *msg);
int logger_error(Logger *l, char *msg);
int logger_panic(Logger *l, char *msg);

int logger_new(Logger *l, char *log_path, LOG_TYPE log_from, int colour, int console_log);
int logger_new_ptr(Logger **l, char *log_path, LOG_TYPE log_from, int colour, int console_log);

int logger_destroy(Logger *l);
int logger_destroy_ptr(Logger **l);

#endif
