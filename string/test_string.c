#include <criterion/criterion.h>
#include "string.h"

Test(init_and_destroy, good_simple)
{
	int res = 0;
	String str;
	res = string_new(&str, "", 0); cr_assert(res == 0);
	
	res = string_destroy(&str); cr_assert(res == 0);
}

Test(init_ptr_and_destroy, good_simple)
{
	int res = 0;
	String *str;
	res = string_new_ptr(&str, "", 0); cr_assert(res == 0);
	
	res = string_destroy_ptr(&str); cr_assert(res == 0);
	cr_assert(str == NULL);
}

Test(get_char, good_simple)
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

Test(get_char, bad_out_of_bounds)
{
	/* INIT */
	int res = 0;
	String *str;
	res = string_new_ptr(&str, "Hello", 5); cr_assert(res == 0);

	/* Main thing */
	char minus = '-';
	// Index 5 is out of bounds. Normal char* would have a NUL terminator there. The string that I've implemented does not have it.
	// If you need it, use the string_get_chars_with_nul() function or the string_get_chars_slice_with_nul() function for more control.
	res = string_get_char(str, 5, &minus); cr_assert(res != 0);
	cr_assert_eq(minus, '-');

	/* DETROY */
	res = string_destroy_ptr(&str); cr_assert(res == 0);
	cr_assert(str == NULL);
}

Test(get_chars_slice, good_slice)
{
	// The slice that the string_get_chars_slice() writes into the *dest does not have a NUL.
	/* INIT */
	int res = 0;
	String *str;
	res = string_new_ptr(&str, "Hello", 5); cr_assert(res == 0);

	/* Main thing */
	char dest[32] = {0};
	res = string_get_chars_slice(str, 0, 4, dest); cr_assert(res == 0);
	cr_assert_eq(dest[0], 'H');
	cr_assert_eq(dest[1], 'e');
	cr_assert_eq(dest[2], 'l');
	cr_assert_eq(dest[3], 'l');
	// The '4' is exclusive. I zero the memory for the dest with {0} (I think that this works this way), so dest[4] should never be 'o'.
	cr_assert_neq(dest[4], 'o');

	/* DETROY */
	res = string_destroy_ptr(&str); cr_assert(res == 0);
	cr_assert(str == NULL);
}

Test(get_chars_slice, good_full)
{
	/* INIT */
	int res = 0;
	String *str;
	res = string_new_ptr(&str, "Hello", 5); cr_assert(res == 0);

	/* Main thing */
	char dest[32] = {0};
	res = string_get_chars_slice(str, 0, 5, dest); cr_assert(res == 0);
	cr_assert_eq(dest[0], 'H');
	cr_assert_eq(dest[1], 'e');
	cr_assert_eq(dest[2], 'l');
	cr_assert_eq(dest[3], 'l');
	cr_assert_eq(dest[4], 'o');

	/* DETROY */
	res = string_destroy_ptr(&str); cr_assert(res == 0);
	cr_assert(str == NULL);
}

Test(get_chars_slice, bad_arg_to_out_of_bounds)
{
	/* INIT */
	int res = 0;
	String *str;
	res = string_new_ptr(&str, "Hello", 5); cr_assert(res == 0);

	/* Main thing */
	char dest[32] = {0};
	res = string_get_chars_slice(str, 0, 6, dest); cr_assert(res != 0);
	cr_assert_neq(dest[0], 'H');
	cr_assert_neq(dest[1], 'e');
	cr_assert_neq(dest[2], 'l');
	cr_assert_neq(dest[3], 'l');
	cr_assert_neq(dest[4], 'o');

	/* DETROY */
	res = string_destroy_ptr(&str); cr_assert(res == 0);
	cr_assert(str == NULL);
}

Test(get_chars_slice, bad_arg_from_out_of_bounds)
{
	/* INIT */
	int res = 0;
	String *str;
	res = string_new_ptr(&str, "Hello", 5); cr_assert(res == 0);

	/* Main thing */
	char dest[32] = {0};
	res = string_get_chars_slice(str, 6, 8, dest); cr_assert(res != 0);
	cr_assert_neq(dest[0], 'H');
	cr_assert_neq(dest[1], 'e');
	cr_assert_neq(dest[2], 'l');
	cr_assert_neq(dest[3], 'l');
	cr_assert_neq(dest[4], 'o');

	/* DETROY */
	res = string_destroy_ptr(&str); cr_assert(res == 0);
	cr_assert(str == NULL);
}

Test(get_chars_slice, bad_arg_from_equal_with_arg_to)
{
	/* INIT */
	int res = 0;
	String *str;
	res = string_new_ptr(&str, "Hello", 5); cr_assert(res == 0);

	/* Main thing */
	char dest[32] = {0};
	res = string_get_chars_slice(str, 3, 3, dest); cr_assert(res != 0);
	cr_assert_neq(dest[0], 'H');
	cr_assert_neq(dest[1], 'e');
	cr_assert_neq(dest[2], 'l');
	cr_assert_neq(dest[3], 'l');
	cr_assert_neq(dest[4], 'o');

	/* DETROY */
	res = string_destroy_ptr(&str); cr_assert(res == 0);
	cr_assert(str == NULL);
}

Test(get_chars_slice, good_single_char)
{
	/* INIT */
	int res = 0;
	String *str;
	res = string_new_ptr(&str, "Hello", 5); cr_assert(res == 0);

	/* Main thing */
	char dest[32] = {0};
	res = string_get_chars_slice(str, 1, 2, dest); cr_assert(res == 0);
	cr_assert_eq(dest[0], 'e');
	cr_assert_neq(dest[1], 'l');

	/* DETROY */
	res = string_destroy_ptr(&str); cr_assert(res == 0);
	cr_assert(str == NULL);
}
