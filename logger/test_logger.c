#include "logger.h"
#include "string.h"
#include <criterion/criterion.h>

Test(get_log_type_as_str, equal_size_not_coloured)
{
	size_t header_len = strlen(get_log_type_as_str(LOG_DEBUG, 0));

	cr_assert_eq(header_len, strlen(get_log_type_as_str(LOG_FINE, 0)));
	cr_assert_eq(header_len, strlen(get_log_type_as_str(LOG_WARN, 0)));
	cr_assert_eq(header_len, strlen(get_log_type_as_str(LOG_ERROR, 0)));
	cr_assert_eq(header_len, strlen(get_log_type_as_str(LOG_FATAL, 0)));
	cr_assert_eq(header_len, strlen(get_log_type_as_str(LOG_FATAL+1, 0)));
}

Test(get_log_type_as_str, equal_size_coloured)
{
	size_t header_len = strlen(get_log_type_as_str(LOG_DEBUG, 1));

	cr_assert_eq(header_len, strlen(get_log_type_as_str(LOG_FINE, 1)));
	cr_assert_eq(header_len, strlen(get_log_type_as_str(LOG_WARN, 1)));
	cr_assert_eq(header_len, strlen(get_log_type_as_str(LOG_ERROR, 1)));
	cr_assert_eq(header_len, strlen(get_log_type_as_str(LOG_FATAL, 1)));
	cr_assert_eq(header_len, strlen(get_log_type_as_str(LOG_FATAL+1, 1)));
}

Test(logger, init_and_destroy)
{
	Logger logger;
	int res = 0;
	res = logger_new(&logger, "log.out", LOG_DEBUG, 1, 1); cr_assert(res == 0);

	res = logger_destroy(&logger); cr_assert(res == 0);
}

Test(logger_ptr, init_and_destroy)
{
	Logger *logger;
	int res = 0;
	res = logger_new_ptr(&logger, "log.out", LOG_DEBUG, 1, 1); cr_assert(res == 0);

	res = logger_destroy_ptr(&logger); cr_assert(res == 0);
}
