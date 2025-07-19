#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#include "../err_lvl/err_lvl.h"
#include "../generic_functions/generic_functions.h"

typedef struct LinkedListNode {
	void *item;
	struct LinkedListNode *next;
} LinkedListNode;

typedef struct LinkedList {
	GenericFunctions gf;
	LinkedListNode *root;
	unsigned int cnt;
} LinkedList;

/* ---| CREATE |--- */
int ll_new(LinkedList *ll, GenericFunctions *gf)
{
	if(ll == NULL)
		return NULL_ERR;

	if(gf == NULL) {
		ll->gf.hash = NULL;
		ll->gf.cmp = NULL;
		ll->gf.to_cstring = NULL;
	} else {
		ll->gf.hash = gf->hash;
		ll->gf.cmp = gf->cmp;
		ll->gf.to_cstring = gf->to_cstring;
	}

	ll->root = NULL;
	ll->cnt = 0;

	return NO_ERR;
}

int ll_new_ptr(LinkedList **ll, GenericFunctions *gf)
{
	if(ll == NULL)
		return NULL_ERR;

	*ll = malloc(sizeof(LinkedList));
	if(ll == NULL)
		return MEM_ERR;

	int res = ll_new(*ll, gf);
	if(res != NO_ERR) {
		free(*ll);
		return res;
	}

	return NO_ERR;
}

/* ---| READ |--- */
int ll_get(LinkedList *ll, unsigned int idx, void **dest)
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

int ll_insert(LinkedList *ll, unsigned int idx, void *item)
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
	ll->cnt += 1;

	return NO_ERR;
}

int ll_replace(LinkedList *ll, unsigned int idx, void *item)
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

int ll_remove(LinkedList *ll, unsigned int idx, void **dest)
{
	if(ll == NULL)
		return NULL_ERR;

	if(idx > ll->cnt)
		return OUT_OF_BOUNDS_ERR;

	if(idx == 0)
		return ll_pop(ll, NULL);

	LinkedListNode *node = ll->root;

	while((idx - 1) > 0) {
		node = node->next;
		--idx;
	}

	if(dest != NULL)
		*dest = node->next->item;

	LinkedListNode *to_free = node->next;
	to_free->item = NULL;

	node->next = node->next->next;
	ll->cnt -= 1;

	free(to_free);

	return NO_ERR;
}

void purge_nodes(LinkedListNode *node)
{
	if(node == NULL)
		return;

	if(node->next != NULL)
		purge_nodes(node->next);

	node->item = NULL;
	node->next = NULL;
	free(node);
}

int ll_dump(LinkedList *ll)
{
	if(ll == NULL)
		return NULL_ERR;

	if(ll->gf.to_cstring == NULL)
		return ARG_ERR;

	LinkedListNode *node = ll->root;
	char buf[64];
	while(node != NULL) {
		ll->gf.to_cstring(node->item, buf, 64);
		write(1, "[", 1);
		write(1, buf, strlen(buf));
		write(1, "]", 1);
		write(1, "->", 2);

		node = node->next;
	}
	write(1, "[NULL]\n", 7);

	return NO_ERR;
}

int ll_destroy(LinkedList *ll)
{
	purge_nodes(ll->root);
	ll->gf.hash = NULL;
	ll->gf.cmp = NULL;
	ll->gf.to_cstring = NULL;
	ll->root = NULL;
	ll->cnt = 0;

	return NO_ERR;
}

int ll_destroy_ptr(LinkedList **ll)
{
	if(ll == NULL)
		return NULL_ERR;

	ll_destroy(*ll);

	free(*ll);
	*ll = NULL;

	return NO_ERR;
}
