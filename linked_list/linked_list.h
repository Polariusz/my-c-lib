#ifndef LINKED_LIST_H_
#define LINKED_LIST_H_

typedef struct LinkedListNode {
	void *item;
	struct LinkedListNode *next;
} LinkedListNode;

typedef struct LinkedList {
	LinkedListNode *root;
	unsigned int cnt;
} LinkedList;

/* ---| CREATE |--- */
int ll_new(LinkedList *ll);
int ll_new_ptr(LinkedList **ll);

/* ---| READ |--- */
int ll_get(LinkedList *ll, unsigned int idx, void **dest);

/* ---| UPDATE |--- */
int ll_push(LinkedList *ll, void *item);
int ll_insert(LinkedList *ll, unsigned int idx, void *item);
int ll_replace(LinkedList *ll, unsigned int idx, void *item);

/* ---| DELETE |--- */
int ll_pop(LinkedList *ll, void **dest);
int ll_delete(LinkedList *ll, unsigned int idx, void **dest);

/* ---| CUSTOM |--- */
int ll_dump(LinkedList *ll, void(*dump_item)(void *src));
int ll_destroy(LinkedList *ll);
int ll_destroy_ptr(LinkedList **ll);

#endif
