#ifndef STRING_H_
#define STRING_H_

#include "../generic_functions/generic_functions.h"
#include "../hash/hash.h"

typedef struct String {
	GenericFunctions gf;
	char *chars;
	unsigned int c_chars;
} String;

/* ---| CREATE |--- */
__attribute__ ((access (read_only, 2, 3)))
int string_new(String *str, char *chars, unsigned int c_chars);

__attribute__ ((access (read_only, 2, 3)))
int string_new_ptr(String **str, char *chars, unsigned int c_chars);

/* ---| READ |--- */
int string_get_char(String *str, unsigned int idx, char *dest);
int string_get_chars_slice(String *str, unsigned int from, unsigned int to, char *dest);
int string_get_chars_slice_with_nul(String *str, unsigned int from, unsigned int to, char *dest);
int string_get_string_slice(String *str, unsigned int from, unsigned int to, String *dest);
int string_get_chars(String *str, char *dest);
int string_get_chars_with_nul(String *str, char *dest);

/* ---| UPDATE |--- */
int string_set_char_at(String *str, unsigned int idx, char character);

__attribute__ ((access (read_only, 3, 4)))
int string_set_chars_at(String *str, unsigned int idx, char *chars, unsigned int c_chars);

/* ---| DELETE |--- */
int string_destroy(String *str);
int string_destroy_ptr(String **str);

/* ---| CUSTOM |--- */
__attribute__ ((nonnull (1, 2)))
	unsigned int string_hash(HashOpt *opt, String *key, unsigned int len);
int string_cmp(String *left, String *right);
int string_to_cstring(String *src, char *dest, unsigned int len);

int string_dump(String *str);

#endif
