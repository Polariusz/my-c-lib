#include <stdio.h>

#include "linked_list.h"

int main(void)
{
	// Declare and initialise with a constructor:
	LinkedList ll;
	ll_new(&ll, NULL);

	// To add an item, you can use the ll_push or ll_insert functions:
	ll_insert(&ll, "First added item", 0);
	ll_push(&ll, "Second added item");
	int a = 10;
	ll_insert(&ll, &a, 1);

	// You can get the item with the ll_get function:
	void *yoink0 = NULL;
	ll_get(&ll, &yoink0, 0);
	// yoink0 points to the "Second added item"

	void *yoink1 = NULL;
	ll_get(&ll, &yoink1, 1);
	// yoink1 points to the variable 'a' address.
	printf("%d\n", *(int*)yoink1);

	// ll_push pushes to HEAD, so it is always O(1).

	// To remove an item, you can use ll_pop function that removes the head, or the ll_remove function that accepts the intex:
	void *yoink2 = NULL;
	ll_remove(&ll, &yoink2, 1);
	ll_pop(&ll, &yoink2);
	// You can ignore the retrieval of the item pointer by passing a NULL into it: ll_pop(&ll, NULL); or ll_remove(&ll, NULL, INDEX);

	// You can get the current count of the items, or nodes in the LinkedList. There is a cnt variable in the LinkedList struct.

	// Destructor:
	ll_destroy(&ll);

	printf("Just Monika\n");
	return 0;
}
