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
int string_get_char(String *str, unsigned int idx, char *dest);
// int string_get_chars_slice(String *str, unsigned int from, unsigned int to, char **dest);
// int string_get_chars_slice_with_nul(String *str, unsigned int from, unsigned int to, char **dest);
// int string_get_string_slice(String *str, unsigned int from, unsigned int to, String *dest);

/* ---| UPDATE |--- */
int string_set_char_at(String *str, unsigned int idx, char character);
// int string_set_chars_at(String *str, unsigned int idx, char *chars, unsigned int c_chars);

/* ---| DELETE |--- */
/* ---| CUSTOM |--- */
int string_dump(String *str)
{
	if(str == NULL)
		return NULL_ERR;

	for(int i = 0; i < str->c_chars; i++)
		write(1, &str->chars[i], 1);
	write(1, "\n", 1);
}

int string_destroy(String *str);
int string_destroy_ptr(String **str);
