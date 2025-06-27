#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "../err_lvl/err_lvl.h"

typedef enum LOG_TYPE {
	LOG_DEBUG,
	LOG_FINE,
	LOG_WARN,
	LOG_ERROR,
	LOG_PANIC,
} LOG_TYPE;

char *get_log_type_as_str(LOG_TYPE type, int is_coloured)
{
	// Note: The coloured version is 16 bits long.
	//       Not coloured version is  9 bits long.
	switch(type) {
		case LOG_DEBUG:
			if(is_coloured)
				return "\033[34m|DEBUG|\033[0m";
			else
				return "|DEBUG|";
		case LOG_FINE:
			if(is_coloured)
				return "\033[32m|FINE |\033[0m";
			else
				return "|FINE |";
		case LOG_WARN:
			if(is_coloured)
				return "\033[33m|WARN |\033[0m";
			else
				return "|WARN |";
		case LOG_ERROR:
			if(is_coloured)
				return "\033[91m|ERROR|\033[0m";
			else
				return "|ERROR|";
		case LOG_PANIC:
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

typedef struct Logger {
	FILE *fd;
	LOG_TYPE log_from;
	int colour;
	int console_log;
} Logger;

char *build_message(char *date, char *log_type_str, char *msg)
{
	// The 7 bytes come from the " - " between date and log type, ": " between log type and message and "\n\0" after message.
	char *buffer = malloc(7 + strlen(date) + strlen(log_type_str) + strlen(msg));
	if(buffer == NULL)
		return NULL;

	char *msg_format = "%s - %s: %s\n";
	sprintf(buffer, msg_format, date, log_type_str, msg);

	return buffer;
}

int logger_message(Logger *l, LOG_TYPE type, char *msg)
{
	if(l == NULL)
		return NULL_ERR;

	if(l->log_from > type)
		return ARG_ERR;

	if(msg == NULL)
		return NULL_ERR;

	char *buffer = NULL;
	time_t time_now = time(NULL);
	char time_now_str[20]; strftime(time_now_str, sizeof(time_now_str), "%F %T", localtime(&time_now));
	char *log_type_str = NULL;

	if(l->console_log) {
		log_type_str = get_log_type_as_str(type, l->colour);
		buffer = build_message(time_now_str, log_type_str, msg);
		if(buffer == NULL)
			return MEM_ERR;

		printf("%s", buffer);
		fflush(stdout);
		free(buffer);
		buffer = NULL;
	}

	log_type_str = get_log_type_as_str(type, 0);
	buffer = build_message(time_now_str, log_type_str, msg);
	if(buffer == NULL)
		return MEM_ERR;

	fputs(buffer, l->fd);
	fflush(l->fd);
	free(buffer);
	buffer = NULL;

	return NO_ERR;
}

int logger_debug(Logger *l, char *msg)
{
	return logger_message(l, LOG_DEBUG, msg);
}

int logger_fine(Logger *l, char *msg)
{
	return logger_message(l, LOG_FINE, msg);
}

int logger_warn(Logger *l, char *msg)
{
	return logger_message(l, LOG_WARN, msg);
}

int logger_error(Logger *l, char *msg)
{
	return logger_message(l, LOG_ERROR, msg);
}

int logger_panic(Logger *l, char *msg)
{
	int res = logger_message(l, LOG_PANIC, msg);
	exit(res == 0 ? INT_PANIC : res);
}

int logger_new(Logger *l, char * log_path, LOG_TYPE log_from, int colour, int console_log)
{
	if(l == NULL)
		return NULL_ERR;

	l->fd = fopen(log_path, "a");
	if (l->fd == NULL)
		return ARG_ERR;

	l->log_from = log_from;
	l->colour = colour;
	l->console_log = console_log;

	logger_message(l, LOG_DEBUG, "Logger is active");

	return NO_ERR;
}

int logger_new_ptr(Logger **l, char * log_path, LOG_TYPE log_from, int colour, int console_log)
{
	if(l == NULL)
		return NULL_ERR;

	*l = malloc(sizeof(Logger));

	(*l)->fd = fopen(log_path, "a");
	if ((*l)->fd == NULL) {
		free(*l);
		return ARG_ERR;
	}

	(*l)->log_from = log_from;
	(*l)->colour = colour;
	(*l)->console_log = console_log;

	logger_message(*l, LOG_DEBUG, "Logger is active");

	return NO_ERR;
}

int logger_destroy(Logger *l)
{
	if(l == NULL)
		return NULL_ERR;

	fclose(l->fd);
	l->fd = NULL;
	l->log_from = 0;
	l->console_log = 0;

	return NO_ERR;
}

int logger_destroy_ptr(Logger **l)
{
	if(l == NULL)
		return NULL_ERR;

	logger_destroy(*l);

	free(*l);
	*l = NULL;

	return NO_ERR;
}
