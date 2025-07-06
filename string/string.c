#include <stdlib.h>
#include <unistd.h>
#include "../err_lvl/err_lvl.h"

typedef struct String {
	char *chars;
	unsigned int c_chars;
} String;

/* ---| CREATE |--- */
int string_new(String *str, char *chars, unsigned int c_chars)
{
	if(str == NULL)
		return NULL_ERR;

	if(chars == NULL)
		return NULL_ERR;

	int len = 0;
	char *chars_ptr = chars;

	while(len < c_chars) {
		if(*chars_ptr == '\0')
			break;

		++len;
		++chars_ptr;
	}

	str->chars = malloc(len * sizeof(char));
	if(str->chars == NULL)
		return MEM_ERR;

	int cnt = 0;
	while(cnt < len) {
		str->chars[cnt] = *chars;
		++chars;
		++cnt;
	}

	str->c_chars = len;

	return NO_ERR;
}

int string_new_ptr(String **str, char *chars, unsigned int c_chars);

/* ---| READ |--- */
int string_get_char(String *str, unsigned int idx, char *dest)
{
	if(str == NULL)
		return NULL_ERR;

	if(dest == NULL)
		return NULL_ERR;

	if(idx >= str->c_chars)
		return ARG_ERR;

	*dest = str->chars[idx];

	return NO_ERR;
}

int string_get_chars_slice(String *str, unsigned int from, unsigned int to, char *dest)
{
	if(str == NULL)
		return NULL_ERR;

	if(from > to)
		return ARG_ERR;

	if(to > str->c_chars)
		return ARG_ERR;

	if(dest == NULL)
		return NULL_ERR;

	for(int i = from; i < to; i++) {
		dest[i-from] = str->chars[i];
	}

	return NO_ERR;
}

int string_get_chars_slice_with_nul(String *str, unsigned int from, unsigned int to, char *dest)
{
	int res = string_get_chars_slice(str, from, to, dest);
	if(res != NO_ERR)
		return res;

	dest[to - from] = '\0';

	return NO_ERR;
}

int string_get_string_slice(String *str, unsigned int from, unsigned int to, String *dest)
{
	if(str == NULL)
		return ARG_ERR;

	if(from > to)
		return ARG_ERR;

	if(to > str->c_chars)
		return ARG_ERR;

	if(dest == NULL)
		return NULL_ERR;

	dest->chars = malloc((to - from) * sizeof(char));
	string_get_chars_slice(str, from, to, dest->chars);
	dest->c_chars = to - from;

	return NO_ERR;
}

int string_get_chars(String *str, char *dest)
{
	return string_get_chars_slice(str, 0, str->c_chars, dest);
}

int string_get_chars_with_nul(String *str, char *dest)
{
	return string_get_chars_slice_with_nul(str, 0, str->c_chars, dest);
}

/* ---| UPDATE |--- */
int string_set_char_at(String *str, unsigned int idx, char character)
{
	if(str == NULL)
		return NULL_ERR;

	if(idx >= str->c_chars)
		return ARG_ERR;

	str->chars[idx] = character;

	return NO_ERR;
}

int string_set_chars_at(String *str, unsigned int idx, char *chars, unsigned int c_chars)
{
	if(str == NULL)
		return NULL_ERR;

	if(idx >= str->c_chars)
		return ARG_ERR;

	for(int i = idx; i < idx + c_chars; i++) {
		str->chars[i] = chars[i - idx];
	}

	return NO_ERR;
}

/* ---| DELETE |--- */
/* ---| CUSTOM |--- */
int string_dump(String *str)
{
	if(str == NULL)
		return NULL_ERR;

	write(1, str->chars, str->c_chars);
	write(1, "\n", 1);
}

int string_destroy(String *str)
{
	if(str == NULL)
		return NULL_ERR;

	free(str->chars);
	str->c_chars = 0;

	return NO_ERR;
}

int string_destroy_ptr(String **str)
{
	if(str == NULL)
		return NULL_ERR;

	string_destroy(*str);
	*str = NULL;

	return NO_ERR;
}
