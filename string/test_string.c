#include <criterion/criterion.h>
#include <string.h>
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
	// The '4' is exclusive. The dest array is zeroed automatically so dest[4] should never be 'o'.
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

Test(get_chars_slice_with_nul, good_slice)
{
	// Since the function behaves almost the same way as get_chars_slice (it literally uses it and then appends the NUL terminator), the test will look similar.

	/* INIT */
	int res = 0;
	String *str;
	res = string_new_ptr(&str, "Hello", 5); cr_assert(res == 0);

	/* Main thing */
	char dest[32] = {10};
	memset(dest, '\n', 32);
	res = string_get_chars_slice_with_nul(str, 0, 4, dest); cr_assert(res == 0);
	cr_assert_eq(dest[0], 'H');
	cr_assert_eq(dest[1], 'e');
	cr_assert_eq(dest[2], 'l');
	cr_assert_eq(dest[3], 'l');
	cr_assert_neq(dest[4], 'o'); // Shouldn't be 'o', because we exclude it with the arg 'to' set to 4
	cr_assert_neq(dest[4], '\n'); // Shouldn't be '\n', because the function overwrites this position to be NUL.
	cr_assert_eq(dest[4], '\0'); // Should be '\0', because the function appends the char '\0' at the end.
	cr_assert_eq(dest[5], '\n'); // Should be '\n', as it is not touched.

	/* DETROY */
	res = string_destroy_ptr(&str); cr_assert(res == 0);
	cr_assert(str == NULL);
}

Test(get_chars_slice_with_nul, good_full)
{
	/* INIT */
	int res = 0;
	String *str;
	res = string_new_ptr(&str, "Hello", 5); cr_assert(res == 0);

	/* Main thing */
	char dest[32] = {10};
	memset(dest, '\n', 32);
	res = string_get_chars_slice_with_nul(str, 0, 5, dest); cr_assert(res == 0);
	cr_assert_eq(dest[0], 'H');
	cr_assert_eq(dest[1], 'e');
	cr_assert_eq(dest[2], 'l');
	cr_assert_eq(dest[3], 'l');
	cr_assert_eq(dest[4], 'o');
	cr_assert_eq(dest[5], '\0');
	cr_assert_eq(dest[6], '\n');

	/* DETROY */
	res = string_destroy_ptr(&str); cr_assert(res == 0);
	cr_assert(str == NULL);
}

Test(get_chars_slice_with_nul, bad_arg_to_out_of_bounds)
{
	/* INIT */
	int res = 0;
	String *str;
	res = string_new_ptr(&str, "Hello", 5); cr_assert(res == 0);

	/* Main thing */
	char dest[32] = {0};
	res = string_get_chars_slice_with_nul(str, 0, 6, dest); cr_assert(res != 0);
	cr_assert_neq(dest[0], 'H');
	cr_assert_neq(dest[1], 'e');
	cr_assert_neq(dest[2], 'l');
	cr_assert_neq(dest[3], 'l');
	cr_assert_neq(dest[4], 'o');

	/* DETROY */
	res = string_destroy_ptr(&str); cr_assert(res == 0);
	cr_assert(str == NULL);
}

Test(get_chars_slice_with_nul, bad_arg_from_out_of_bounds)
{
	/* INIT */
	int res = 0;
	String *str;
	res = string_new_ptr(&str, "Hello", 5); cr_assert(res == 0);

	/* Main thing */
	char dest[32] = {0};
	res = string_get_chars_slice_with_nul(str, 6, 8, dest); cr_assert(res != 0);
	cr_assert_neq(dest[0], 'H');
	cr_assert_neq(dest[1], 'e');
	cr_assert_neq(dest[2], 'l');
	cr_assert_neq(dest[3], 'l');
	cr_assert_neq(dest[4], 'o');

	/* DETROY */
	res = string_destroy_ptr(&str); cr_assert(res == 0);
	cr_assert(str == NULL);
}

Test(get_chars_slice_with_nul, bad_arg_from_equal_with_arg_to)
{
	/* INIT */
	int res = 0;
	String *str;
	res = string_new_ptr(&str, "Hello", 5); cr_assert(res == 0);

	/* Main thing */
	char dest[32] = {0};
	res = string_get_chars_slice_with_nul(str, 3, 3, dest); cr_assert(res != 0);
	cr_assert_neq(dest[0], 'H');
	cr_assert_neq(dest[1], 'e');
	cr_assert_neq(dest[2], 'l');
	cr_assert_neq(dest[3], 'l');
	cr_assert_neq(dest[4], 'o');

	/* DETROY */
	res = string_destroy_ptr(&str); cr_assert(res == 0);
	cr_assert(str == NULL);
}

Test(get_chars_slice_with_nul, good_single_char_with_nul)
{
	/* INIT */
	int res = 0;
	String *str;
	res = string_new_ptr(&str, "Hello", 5); cr_assert(res == 0);

	/* Main thing */
	char dest[32] = {10};
	memset(dest, '\n', 32);
	res = string_get_chars_slice_with_nul(str, 1, 2, dest); cr_assert(res == 0);
	cr_assert_eq(dest[0], 'e');
	cr_assert_neq(dest[1], 'l');
	cr_assert_eq(dest[1], '\0');
	cr_assert_eq(dest[2], '\n');

	/* DETROY */
	res = string_destroy_ptr(&str); cr_assert(res == 0);
	cr_assert(str == NULL);
}

Test(get_chars_slice_with_nul, bad_no_stray_nul)
{
	/* INIT */
	int res = 0;
	String *str;
	res = string_new_ptr(&str, "Hello", 5); cr_assert(res == 0);

	/* Main thing */
	char dest[32] = {10};
	memset(dest, '\n', 32);
	res = string_get_chars_slice_with_nul(str, 1, 1, dest); cr_assert(res != 0);
	cr_assert_neq(dest[0], '\0');
	cr_assert_neq(dest[1], '\0');
	cr_assert_neq(dest[2], '\0');
	cr_assert_neq(dest[3], '\0');
	cr_assert_neq(dest[4], '\0');
	cr_assert_neq(dest[5], '\0');

	/* DETROY */
	res = string_destroy_ptr(&str); cr_assert(res == 0);
	cr_assert(str == NULL);
}

Test(get_string_slice, good_simple)
{
	// The string_get_string_slice() function uses the string_get_chars_slice() inside to get the slice of characters to store in char *chars.

	/* INIT */
	int res = 0;
	String *str;
	res = string_new_ptr(&str, "Hello", 5); cr_assert(res == 0);

	/* Main thing */
	String str2;
	res = string_get_string_slice(str, 0, 5, &str2); cr_assert(res == 0);

	res = string_cmp(str, &str2); cr_assert(res == 0);

	/* DETROY */
	res = string_destroy_ptr(&str); cr_assert(res == 0);
	res = string_destroy(&str2); cr_assert(res == 0);
	cr_assert(str == NULL);
}

Test(get_string_slice, good_from_one_two)
{
	/* INIT */
	int res = 0;
	String *str;
	res = string_new_ptr(&str, "Just Monika, I love Monika", 26); cr_assert(res == 0);

	/* Main thing */
	String str2;
	res = string_get_string_slice(str, 5, 11, &str2); cr_assert(res == 0);

	String str3;
	res = string_get_string_slice(str, 20, 26, &str3); cr_assert(res == 0);

	res = string_cmp(&str2, &str3); cr_assert(res == 0);

	/* DETROY */
	res = string_destroy_ptr(&str); cr_assert(res == 0);
	cr_assert(str == NULL);
}

Test(get_string_slice, bad_different_same_len_slices)
{
	/* INIT */
	int res = 0;
	String *str;
	res = string_new_ptr(&str, "Monika is monikawaii", 20); cr_assert(res == 0);

	/* Main thing */
	String str2; // 'onika '
	res = string_get_string_slice(str, 1, 7, &str2); cr_assert(res == 0);

	String str3; // 'onikaw'
	res = string_get_string_slice(str, 11, 17, &str3); cr_assert(res == 0);

	res = string_cmp(&str2, &str3); cr_assert(res != 0);

	/* DETROY */
	res = string_destroy_ptr(&str); cr_assert(res == 0);
	cr_assert(str == NULL);
}

Test(get_string_slice, bad_different_len)
{
	/* INIT */
	int res = 0;
	String *str;
	res = string_new_ptr(&str, "Monika is so beautiful", 22); cr_assert(res == 0);

	/* Main thing */
	String str2; // 'Monika'
	res = string_get_string_slice(str, 0, 6, &str2); cr_assert(res == 0);

	String str3; // ' is so '
	res = string_get_string_slice(str, 6, 13, &str3); cr_assert(res == 0);

	res = string_cmp(&str2, &str3); cr_assert(res != 0);

	/* DETROY */
	res = string_destroy_ptr(&str); cr_assert(res == 0);
	cr_assert(str == NULL);
}

Test(get_string_slice, bad_args)
{
	/* INIT */
	int res = 0;
	String str;
	res = string_new(&str, "Monika is so beautiful", 22); cr_assert(res == 0);

	/* Main thing */
	String str2;
	res = string_get_string_slice(&str, 0, 666, NULL); cr_assert(res != 0);
	res = string_get_string_slice(&str, 777, 666, &str2); cr_assert(res != 0);
	res = string_get_string_slice(&str, 4, 4, &str2); cr_assert(res != 0);
	res = string_get_string_slice(&str, 21, 22, &str2); cr_assert(res == 0);
	cr_assert_eq(str2.chars[0], 'l');
	cr_assert_eq(str2.c_chars, 1);

	/* DETROY */
	res = string_destroy(&str); cr_assert(res == 0);
}

Test(get_chars, good_simple)
{
	// The function string_get_chars literally only uses string_get_chars_slice() where it sets arguments 'from' to be 0 and 'to' to be c_chars

	/* INIT */
	int res = 0;
	String str;
	res = string_new(&str, "Monika is very sweet", 20); cr_assert(res == 0);

	/* Main thing */
	char buf[32] = {10};
	memset(buf, '\n', 32);

	res = string_get_chars(&str, buf); cr_assert(res == 0);
	cr_assert_neq(buf[0], '\n');
	cr_assert_eq(buf[0], 'M');

	cr_assert_neq(buf[19], '\n');
	cr_assert_eq(buf[19], 't');

	cr_assert_eq(buf[20], '\n');

	/* DETROY */
	res = string_destroy(&str); cr_assert(res == 0);
}

Test(get_chars_with_nul, good_simple)
{
	// The function string_get_chars literally only uses string_get_chars_slice_with_nul() where it sets arguments 'from' to be 0 and 'to' to be c_chars

	/* INIT */
	int res = 0;
	String str;
	res = string_new(&str, "Monika is so cute", 17); cr_assert(res == 0);

	/* Main thing */
	char buf[32] = {10};
	memset(buf, '\n', 32);

	res = string_get_chars_with_nul(&str, buf); cr_assert(res == 0);
	cr_assert_neq(buf[0], '\n');
	cr_assert_eq(buf[0], 'M');

	cr_assert_neq(buf[16], '\n');
	cr_assert_eq(buf[16], 'e');

	cr_assert_eq(buf[17], '\0');
	cr_assert_eq(buf[18], '\n');

	/* DETROY */
	res = string_destroy(&str); cr_assert(res == 0);
}

Test(set_char_at, good_simple)
{
	// Because we are not dealing with a string literal, we can easily modify what is inside of the char array!

	/* INIT */
	int res = 0;
	String str;
	res = string_new(&str, "Monika is amazing!", 18); cr_assert(res == 0);

	/* Main thing */
	res = string_set_char_at(&str, 10, 'A'); cr_assert(res == 0);
	// => 'Monika is Amazing!'

	cr_assert_neq(str.chars[10], 'a');
	cr_assert_eq(str.chars[10], 'A');

	/* DETROY */
	res = string_destroy(&str); cr_assert(res == 0);
}

Test(set_char_at, bad_oob)
{
	/* INIT */
	int res = 0;
	String str;
	res = string_new(&str, "Just Monika", 11); cr_assert(res == 0);

	/* Main thing */
	res = string_set_char_at(&str, 11, 'A'); cr_assert(res != 0);

	/* DETROY */
	res = string_destroy(&str); cr_assert(res == 0);
}
