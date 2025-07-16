#include <stdlib.h>
#include <stdio.h>

#include "../linked_list/linked_list.h"
#include "../generic_functions/generic_functions.h"
#include "../hash/hash.h"
#include "../err_lvl/err_lvl.h"

typedef struct KeyVal {
	void *key;
	void *val;
	unsigned int key_len;
	unsigned int val_len;
} KeyVal;

typedef struct HashMap {
	GenericFunctions gf;
	HashOpt hash_opt;
	LinkedList *buckets;
	unsigned int c_buckets;
} HashMap;

int hm_init_buckets(HashMap *hm, unsigned int size)
{
	if(hm == NULL)
		return NULL_ERR;

	hm->buckets = malloc(size * sizeof(LinkedList));
	if(hm->buckets == NULL)
		return MEM_ERR;

	while(size-- > 0)
		ll_new(&hm->buckets[size], NULL);

	return NO_ERR;
}

/* ---| CREATE |--- */
int hm_new_custom(HashMap *hm, GenericFunctions gf, HashOpt hash_opt, unsigned int size)
{
	if(hm == NULL)
		return NULL_ERR;

	if(gf.hash == NULL)
		return NULL_ERR;

	if(gf.cmp == NULL)
		return NULL_ERR;

	hm->gf = gf;
	hm->hash_opt = hash_opt;
	int err = hm_init_buckets(hm, size);
	if(err != NO_ERR)
		return err;

	hm->c_buckets = size;

	return NO_ERR;
}

int hm_new_custom_ptr(HashMap **hm, GenericFunctions gf, HashOpt hash_opt, unsigned int size)
{
	if(hm == NULL)
		return NULL_ERR;

	*hm = malloc(sizeof(HashMap));
	if(*hm == NULL)
		return MEM_ERR;

	return hm_new_custom(*hm, gf, hash_opt, size);
}

int hm_new(HashMap *hm, GenericFunctions gf, unsigned int size)
{
	return hm_new_custom(hm, gf, hash_new(size), size);
}

int hm_new_ptr(HashMap **hm, GenericFunctions gf, unsigned int size)
{
	if(hm == NULL)
		return NULL_ERR;

	*hm = malloc(sizeof(HashMap));
	if(*hm == NULL)
		return MEM_ERR;

	return hm_new(*hm, gf, size);
}

/* ---| READ |--- */
int hm_get(HashMap *hm, KeyVal *kv)
{
	if(hm == NULL)
		return NULL_ERR;

	if(kv == NULL)
		return NULL_ERR;

	if(kv->key == NULL)
		return NULL_ERR;

	LinkedList *ll = &hm->buckets[hm->gf.hash(&hm->hash_opt, kv->key, kv->key_len)];
	LinkedListNode *node = ll->root;
	while(node != NULL) {
		if(hm->gf.cmp(((KeyVal*)node->item)->key, ((KeyVal*)kv)->key) == 0) {
			kv->val = ((KeyVal*)node->item)->val;
			kv->val_len = ((KeyVal*)node->item)->val_len;
			return NO_ERR;
		}
		node = node->next;
	}

	return ARG_ERR;
}

/* ---| UPDATE |--- */
int hm_add(HashMap *hm, KeyVal *kv)
{
	if(hm == NULL)
		return NULL_ERR;

	if(kv == NULL)
		return NULL_ERR;

	if(kv->key == NULL)
		return NULL_ERR;

	if(kv->val == NULL)
		return NULL_ERR;

	LinkedList *ll = &hm->buckets[hm->gf.hash(&hm->hash_opt, kv->key, kv->key_len)];
	LinkedListNode *node = ll->root;
	while(node != NULL) {
		if(hm->gf.cmp(((KeyVal*)node->item)->key, ((KeyVal*)kv)->key) == 0)
			return ARG_ERR;
		node = node->next;
	}

	int res = ll_push(ll, kv);
	if(res != NO_ERR)
		return res;

	return NO_ERR;
}

/* ---| DESTROY |--- */
int hm_delete(HashMap *hm, KeyVal *kv)
{
	if(hm == NULL)
		return NULL_ERR;

	if(kv == NULL)
		return NULL_ERR;

	if(kv->key == NULL)
		return NULL_ERR;

	LinkedList *ll = &hm->buckets[hm->gf.hash(&hm->hash_opt, kv->key, kv->key_len)];
	void *yoink;
	int err = 0;

	for(unsigned int i = 0; i < ll->cnt; i++) {
		err = ll_get(ll, &yoink, i);
		if(err != NO_ERR)
			return err;

		if(hm->gf.cmp(((KeyVal*)yoink)->key, kv->key) == 0) {
			kv->val = ((KeyVal*)yoink)->val;
			kv->val_len = ((KeyVal*)yoink)->val_len;

			err = ll_remove(ll, NULL, i);
			if(err != NO_ERR)
				return err;

			return NO_ERR;
		}
	}

	return ARG_ERR;
}

int hm_destroy(HashMap *hm)
{
	if(hm == NULL)
		return NULL_ERR;

	hm->gf.hash = NULL;
	hm->gf.cmp = NULL;
	hm->gf.to_cstring = NULL;

	hm->hash_opt.initial_value = 0;
	hm->hash_opt.sub_divider = 0;
	hm->hash_opt.divider = 0;

	int err = 0;
	while(hm->c_buckets-- > 0) {
		err = ll_destroy(&hm->buckets[hm->c_buckets]);
		if(err != NO_ERR)
			return err;
	}

	free(hm->buckets);
	hm->buckets = NULL;

	return NO_ERR;
}

int hm_destroy_ptr(HashMap **hm)
{
	if(hm == NULL)
		return NULL_ERR;

	int res = hm_destroy(*hm);
	if(res != NO_ERR)
		return res;

	free(*hm);
	*hm = NULL;

	return NO_ERR;
}

/* ---| CUSTOM |--- */
