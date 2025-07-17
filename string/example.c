#include <stdio.h>
#include <string.h>
#include "string.h"

int main(void)
{
	// This is how to use the constructor:
	String str;
	string_new(&str, "String is a string yes", 18);
	// Note that the length can be shorter if you want a part of the cstring.
	// With the lenght of only 18, the saved character array is this: "String is a String"

	// This function writes the character array of the &str into the second argument. It also writes the NUL terminator to comply with the cstring.
	// If you don't want the NUL terminator, you can use the 'string_get_chars_with_nul()' function.
	char yoink[32];
	string_get_chars_with_nul(&str, yoink);

	if(int res = strcmp(yoink, "String is a string"); res != 0)
		printf("This will not print");

	// How about a slice? There are several functions for that. Let's use one of them.
	String str2;
	string_get_string_slice(&str, 12, 18, &str2);
	// The str2 now contains chars = "string" with c_chars = 6

	// Do you want to update a character? Sure, let's use this:
	string_set_char_at(&str2, 0, 'S');
	// Now str2 contains chars = "String"

	// Updating one character is fine and all, but if you want to update multipe of them, using this function might be a better option:
	string_set_chars_at(&str2, 2, "RoNk", 4);
	string_dump(&str2);
	// Now str2 contains chars = "StRoNk"

	// Destructors
	string_destroy(&str);
	string_destroy(&str2);

	printf("Just Monika\n");
	return 0;
}
