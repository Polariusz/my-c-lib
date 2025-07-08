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
