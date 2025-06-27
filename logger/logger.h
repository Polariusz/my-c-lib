#include <stdio.h>

typedef enum LOG_TYPE {
	DEBUG,
	FINE,
	WARN,
	ERROR,
	PANIC,
} LOG_TYPE;

typedef struct Logger {
	FILE *fd;
	LOG_TYPE log_from;
} Logger;

void new_logger(Logger *l, LOG_TYPE log_from);

char *get_log_type_as_str(LOG_TYPE type, int is_coloured);

void log_message(Logger *l, LOG_TYPE type, char *msg);
void log_debug(Logger *l, char *msg);
void log_fine(Logger *l, char *msg);
void log_warn(Logger *l, char *msg);
void log_error(Logger *l, char *msg);
void log_panic(Logger *l, char *msg);
