#include <stdlib.h>
#include <unistd.h>

#include "../generic_functions/generic_functions.h"
#include "../hash/hash.h"
#include "../err_lvl/err_lvl.h"

typedef struct String {
	GenericFunctions gf;
	char *chars;
	unsigned int c_chars;
} String;

unsigned int string_hash(HashOpt *opt, void *key, unsigned int len);
int string_cmp(void *left, void *right);
int string_to_cstring(void *src, char *dest, unsigned int len);

/* ---| CREATE |--- */
int string_new(String *str, char *chars, unsigned int c_chars)
{
	if(str == NULL)
		return NULL_ERR;

	if(chars == NULL)
		return NULL_ERR;

	unsigned int len = 0;
	char *chars_ptr = chars;

	while(len < c_chars) {
		++len;
		++chars_ptr;
	}

	str->chars = malloc(len * sizeof(char));
	if(str->chars == NULL)
		return MEM_ERR;

	unsigned int cnt = 0;
	while(cnt < len) {
		str->chars[cnt] = *chars;
		++chars;
		++cnt;
	}

	str->c_chars = len;

	str->gf.hash = &string_hash;
	str->gf.cmp = &string_cmp;
	str->gf.to_cstring = &string_to_cstring;

	return NO_ERR;
}

int string_new_ptr(String **str, char *chars, unsigned int c_chars)
{
	if(str == NULL)
		return NULL_ERR;

	*str = malloc(sizeof(String));
	int res = string_new(*str, chars, c_chars);
	if(res != NO_ERR) {
		free(*str);
		return res;
	}

	return NO_ERR;
}

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

	if(from >= to)
		return ARG_ERR;

	if(to > str->c_chars)
		return ARG_ERR;

	if(dest == NULL)
		return NULL_ERR;

	for(unsigned int i = from; i < to; i++) {
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
	if(dest == NULL)
		return NULL_ERR;

	dest->chars = malloc((to - from) * sizeof(char));
	int res = string_get_chars_slice(str, from, to, dest->chars);
	if(res != NO_ERR) {
		free(dest->chars);
		dest->chars = NULL;

		return res;
	}
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

	for(unsigned int i = idx; i < idx + c_chars; i++) {
		str->chars[i] = chars[i - idx];
	}

	return NO_ERR;
}

/* ---| DELETE |--- */
int string_destroy(String *str)
{
	if(str == NULL)
		return NULL_ERR;

	free(str->chars);
	str->c_chars = 0;
	str->gf.hash = NULL;
	str->gf.cmp = NULL;
	str->gf.to_cstring = NULL;

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

unsigned int string_hash(HashOpt *opt, void *key, unsigned int len)
{
	(void)len;
	char *chars = ((String*)key)->chars;
	unsigned int c_chars = ((String*)key)->c_chars;

	unsigned int res = opt->initial_value;
	while(c_chars > 0) {
		res = (res + (*chars)) % opt->sub_divider;
		--c_chars;
		++chars;
	}

	return res % opt->divider;
}

int string_cmp(void *left, void *right)
{
	// first, check for nulls
	if(left == NULL && right == NULL)
		return 0;
	else if(left == NULL && right != NULL)
		return -1;
	else if(left != NULL && right == NULL)
		return 1;

	// Both aren't null; check for the content

	// c_chars
	if(((String*)left)->c_chars != ((String*)right)->c_chars) {
		return ((String*)left)->c_chars - ((String*)right)->c_chars;
	}
	// Now.. Someone could just modify the c_chars manually to for example 10 times of it's original state for both the arguments. In that case, the for loop below will probably segfault.. or not! If not, it might return unequality or not, depending if the memory past allocated char arrays is zeroed or not.

	// chars
	for(unsigned int i = 0; i < ((String*)left)->c_chars; i++) {
		if(((String*)left)->chars[i] != ((String*)right)->chars[i])
			return ((String*)left)->chars[i] - ((String*)right)->chars[i];
	}

	return 0;
}

/*
 * Why len is ignored? The src, as a String contains c_chars, so the length of the characters is already known.
*/
int string_to_cstring(void *src, char *dest, unsigned int len)
{
	(void)len;
	if(src == NULL)
		return NULL_ERR;

	if(dest == NULL)
		return NULL_ERR;

	if(((String*)src)->c_chars > len)
		return ARG_ERR;

	return string_get_chars_with_nul(((String*)src), dest);
}

int string_dump(String *str)
{
	if(str == NULL)
		return NULL_ERR;

	write(1, str->chars, str->c_chars);
	write(1, "\n", 1);

	return NO_ERR;
}
