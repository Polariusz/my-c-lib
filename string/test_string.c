#include <criterion/criterion.h>
#include "string.h"

Test(init_and_destroy, simple)
{
	int res = 0;
	String str;
	res = string_new(&str, "", 0); cr_assert(res == 0);
	
	res = string_destroy(&str); cr_assert(res == 0);
}

Test(init_ptr_and_destroy, simple)
{
	int res = 0;
	String *str;
	res = string_new_ptr(&str, "", 0); cr_assert(res == 0);
	
	res = string_destroy_ptr(&str); cr_assert(res == 0);
	cr_assert(str == NULL);
}

Test(get_char, should_succeed)
{
	/* INIT */
	int res = 0;
	String *str;
	res = string_new_ptr(&str, "Hello", 5); cr_assert(res == 0);

	/* Main thing */
	char h;
	res = string_get_char(str, 0, &h); cr_assert(res == 0);
	cr_assert_eq(h, 'H');
	char e;
	res = string_get_char(str, 1, &e); cr_assert(res == 0);
	cr_assert_eq(e, 'e');
	char l1;
	res = string_get_char(str, 2, &l1); cr_assert(res == 0);
	cr_assert_eq(l1, 'l');
	char l2;
	res = string_get_char(str, 3, &l2); cr_assert(res == 0);
	cr_assert_eq(l2, 'l');
	char o;
	res = string_get_char(str, 4, &o); cr_assert(res == 0);
	cr_assert_eq(o, 'o');

	/* DETROY */
	res = string_destroy_ptr(&str); cr_assert(res == 0);
	cr_assert(str == NULL);
}

Test(get_char, should_fail)
{
	/* INIT */
	int res = 0;
	String *str;
	res = string_new_ptr(&str, "Hello", 5); cr_assert(res == 0);

	/* Main thing */
	char minus = '-';
	res = string_get_char(str, 5, &minus); cr_assert(res != 0);
	cr_assert_eq(minus, '-');

	/* DETROY */
	res = string_destroy_ptr(&str); cr_assert(res == 0);
	cr_assert(str == NULL);
}
