#include <stdio.h>
#include <stdlib.h>
#include "../err_lvl/err_lvl.h"

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
int ll_new(LinkedList* ll, void(*dump_item)(void* item))
{
	if(ll == NULL)
		return NULL_ERR;

	LinkedList new_ll;
	new_ll.root = NULL;
	new_ll.cnt = 0;
	new_ll.dump_item = dump_item;

	*ll = new_ll;

	return NO_ERR;
}

int ll_new_ptr(LinkedList** ll, void(*dump_item)(void* item))
{
	if(ll == NULL)
		return NULL_ERR;

	LinkedList *new_ll = malloc(sizeof(LinkedList));
	if(new_ll == NULL)
		return MEM_ERR;

	new_ll->root = NULL;
	new_ll->cnt = 0;
	new_ll->dump_item = dump_item;

	*ll = new_ll;

	return NO_ERR;
}

/* ---| READ |--- */
int ll_get(LinkedList *ll, void **dest, unsigned int idx)
{
	if(ll == NULL)
		return NULL_ERR;

	if(dest == NULL)
		return NULL_ERR;

	if(idx >= ll->cnt)
		return OUT_OF_BOUNDS_ERR;

	LinkedListNode *node = ll->root;
	while(idx > 0) {
		node = node->next;
		--idx;
	}

	*dest = node->item;

	return NO_ERR;
}

/* ---| UPDATE |--- */
int ll_push(LinkedList *ll, void *item)
{
	if(ll == NULL)
		return NULL_ERR;

	if(item == NULL)
		return NULL_ERR;

	LinkedListNode *new_node = malloc(sizeof(LinkedListNode));
	if(new_node == NULL)
		return MEM_ERR;

	new_node->item = item;
	new_node->next = ll->root;
	ll->root = new_node;

	ll->cnt += 1;

	return NO_ERR;
}

int ll_insert(LinkedList *ll, void *item, unsigned int idx)
{
	if(ll == NULL)
		return NULL_ERR;

	if(item == NULL)
		return NULL_ERR;

	if(idx > ll->cnt)
		return OUT_OF_BOUNDS_ERR;

	if(idx == 0)
		return ll_push(ll, item);

	LinkedListNode *new_node = malloc(sizeof(LinkedListNode));
	if(new_node == NULL)
		return MEM_ERR;

	new_node->item = item;
	new_node->next = NULL;

	LinkedListNode *node = ll->root;
	while((idx - 1) > 0) {
		node = node->next;
		--idx;
	}

	new_node->next = node->next;
	node->next = new_node;

	return NO_ERR;
}

int ll_replace(LinkedList *ll, void *item, unsigned int idx)
{
	if(ll == NULL)
		return NULL_ERR;

	if(item == NULL)
		return NULL_ERR;

	if(idx > ll->cnt)
		return OUT_OF_BOUNDS_ERR;

	LinkedListNode *node = ll->root;

	while(idx > 0) {
		node = node->next;
		--idx;
	}

	node->item = item;

	return NO_ERR;
}

/* ---| DELETE |--- */
int ll_pop(LinkedList *ll, void **dest)
{
	if(ll == NULL)
		return NULL_ERR;

	if(ll->cnt <= 0)
		return OUT_OF_BOUNDS_ERR;
	
	LinkedListNode *node = ll->root;
	ll->root = ll->root->next;
	ll->cnt -= 1;

	node->next = NULL;
	if(dest != NULL)
		*dest = node->item;

	free(node);
	node = NULL;

	return NO_ERR;
}

int ll_delete(LinkedList *ll, void **dest, unsigned int idx)
{
	if(ll == NULL)
		return NULL_ERR;

	if(idx > ll->cnt)
		return OUT_OF_BOUNDS_ERR;

	if(idx == 0)
		return ll_pop(ll, dest);

	LinkedListNode *node = ll->root;

	while((idx - 1) > 0) {
		node = node->next;
		--idx;
	}

	LinkedListNode *to_free = node->next;
	if(dest != 0)
		*dest = to_free->item;

	node->next = node->next->next;
	free(to_free);

	return NO_ERR;
}

/* ---| CUSTOM |--- */
int ll_dump(LinkedList *ll)
{
	if(ll == NULL)
		return NULL_ERR;

	if(ll->dump_item == NULL)
		return ARG_ERR;

	LinkedListNode *node = ll->root;
	while(node != NULL) {
		ll->dump_item(node->item);
		printf(" ");
		node = node->next;
	}
	printf("\n");

	return NO_ERR;
}

int ll_destroy(LinkedList *ll);
int ll_destroy_ptr(LinkedList **ll);
