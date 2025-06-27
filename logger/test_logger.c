#include "logger.h"
#include "string.h"
#include <criterion/criterion.h>

Test(get_log_type_as_str, equal_size_not_coloured)
{
	size_t header_len = strlen(get_log_type_as_str(DEBUG, 0));

	cr_assert_eq(header_len, strlen(get_log_type_as_str(FINE, 0)));
	cr_assert_eq(header_len, strlen(get_log_type_as_str(WARN, 0)));
	cr_assert_eq(header_len, strlen(get_log_type_as_str(ERROR, 0)));
	cr_assert_eq(header_len, strlen(get_log_type_as_str(PANIC, 0)));
	cr_assert_eq(header_len, strlen(get_log_type_as_str(PANIC+1, 0)));
}

Test(get_log_type_as_str, equal_size_coloured)
{
	size_t header_len = strlen(get_log_type_as_str(DEBUG, 1));

	cr_assert_eq(header_len, strlen(get_log_type_as_str(FINE, 1)));
	cr_assert_eq(header_len, strlen(get_log_type_as_str(WARN, 1)));
	cr_assert_eq(header_len, strlen(get_log_type_as_str(ERROR, 1)));
	cr_assert_eq(header_len, strlen(get_log_type_as_str(PANIC, 1)));
	cr_assert_eq(header_len, strlen(get_log_type_as_str(PANIC+1, 1)));
}
