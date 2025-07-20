#include <stdio.h>

#include "array_list.h"

void dump_item(void *arg)
{
	printf("%s", (char*)arg);
	return;
}

int main(void)
{
	// Declare and initialise the array list with the constuctor:
	ArrayList al;
	al_new(&al);

	// There is the al_build() function where one can give the size of the array.

	// There are three functions to add items:
	// The al_add_suffix(), which adds to the empty slot after the used ones:
	al_add_suffix(&al, "suffixed item");

	// The al_add_prefix(), which moves all items one index to the right and then adds the argument into the index 0:
	al_add_prefix(&al, "prefixed item");

	// The al_insert(), which moves the items of the index to the right once and then insert the argument:
	al_insert(&al, 1, "inserted item");

	// To get an item, the al_get() function can be used:
	void *yoink;
	al_get(&al, 0, &yoink);
	// The yoink now points to the "prefixed item"

	// Because we add cstrings into the array list, we can easily print them out using the al_dump() function. the function requires a function pointer that ONLY prints the item out.
	al_dump(&al, &dump_item);
	// Note: The function pointer can be NULL, which will make it print the addresses out.
	
	// To delete an item, the al_delete() function can be used:
	al_delete(&al, 2, NULL);

	// Destructor to free allocated memory
	al_destroy(&al);

	printf("Just Monika\n");
	return 0;
}
