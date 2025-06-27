#include <stdio.h>
#include <string.h>

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

char *get_log_type_as_str(LOG_TYPE type, int is_coloured)
{
	// Note: The coloured version is 16 bits long.
	//       Not coloured version is  9 bits long.
	switch(type) {
		case DEBUG:
			if(is_coloured)
				return "\033[34m|DEBUG|\033[0m";
			else
				return "|DEBUG|";
		case FINE:
			if(is_coloured)
				return "\033[32m|FINE |\033[0m";
			else
				return "|FINE |";
		case WARN:
			if(is_coloured)
				return "\033[33m|WARN |\033[0m";
			else
				return "|WARN |";
		case ERROR:
			if(is_coloured)
				return "\033[91m|ERROR|\033[0m";
			else
				return "|ERROR|";
		case PANIC:
			if(is_coloured)
				return "\033[31m|PANIC|\033[0m";
			else
				return "|PANIC|";
		default:
			if(is_coloured)
				return "\033[95m|NCLUE|\033[0m";
			else
				return "|NCLUE|";
	}
}

void log_message(Logger *l, LOG_TYPE type, char *msg);
void log_debug(Logger *l, char *msg);
void log_fine(Logger *l, char *msg);
void log_warn(Logger *l, char *msg);
void log_error(Logger *l, char *msg);
void log_panic(Logger *l, char *msg);
