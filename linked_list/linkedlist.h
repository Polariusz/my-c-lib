#ifndef LINKED_LIST_H_
#define LINKED_LIST_H_

typedef struct LinkedListNode {
	void *item;
	struct LinkedListNode *next;
} LinkedListNode;

typedef struct LinkedList {
	LinkedListNode *root;
	unsigned int cnt;
	void(*dump_item)(void* item);
} LinkedList;

/* ---| CREATE |--- */
int ll_new(LinkedList* ll, void(*dump_item)(void* item));
int ll_new_ptr(LinkedList** ll, void(*dump_item)(void* item));

/* ---| READ |--- */
int ll_get(LinkedList *ll, void **dest, unsigned int idx);

/* ---| UPDATE |--- */
int ll_push(LinkedList *ll, void *item);
int ll_insert(LinkedList *ll, void *item, unsigned int idx);
int ll_replace(LinkedList *ll, void *item, unsigned int idx);

/* ---| DELETE |--- */
int ll_pop(LinkedList *ll, void **dest);
int ll_delete(LinkedList *ll, void **dest, unsigned int idx);

/* ---| CUSTOM |--- */
int ll_dump(LinkedList *ll);
int ll_destroy(LinkedList *ll);
int ll_destroy_ptr(LinkedList *ll);

#endif
