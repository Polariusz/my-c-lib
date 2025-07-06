#ifndef STRING_H_
#define STRING_H_

typedef struct String {
	char *chars;
	unsigned int c_chars;
} String;

/* ---| CREATE |--- */
int string_new(String *str, char *chars, unsigned int c_chars);
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
int string_set_chars_at(String *str, unsigned int idx, char *chars, unsigned int c_chars);

/* ---| DELETE |--- */
/* ---| CUSTOM |--- */
int string_dump(String *str);
int string_destroy(String *str);
int string_destroy_ptr(String **str);

#endif
