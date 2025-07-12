#include <stdlib.h>
#include "../linked_list/linked_list.h"
#include "../hash/hash.h"
#include "../err_lvl/err_lvl.h"

typedef struct HashMap2Pair {
	void *key;
	unsigned int key_len;

	void *val;
	unsigned int val_len;
} HashMap2Pair;

typedef struct HashMap2 {
	HashOpt opt;
	LinkedList *buckets;
} HashMap2;

int hm2_verify_hash_opt(HashOpt *opt)
{
	if(opt == NULL)
		return NULL_ERR;

	if(opt->sub_divider < opt->divider)
		return ARG_ERR;

	if(opt->hash_type == HASH_CUSTOM && opt->hash_custom == NULL)
		return ARG_ERR;

	return NO_ERR;
}

int hm2_init_buckets(HashMap2 *hm2)
{
	unsigned int cnt = hm2->opt.divider;
	while(cnt > 0) {
		--cnt;
		if(ll_new(&hm2->buckets[cnt], NULL) != 0)
			return INT_PANIC;
	}

	return NO_ERR;
}

/* ---| CREATE |--- */
int hm2_new(HashMap2 *hm2, HashOpt opt)
{
	if(hm2 == NULL)
		return NULL_ERR;

	int verify_res = hm2_verify_hash_opt(&opt);
	if(verify_res != NO_ERR)
		return verify_res;

	hm2->opt = opt;
	hm2->buckets = malloc(opt.divider * sizeof(LinkedList));
	if(hm2->buckets == NULL)
		return MEM_ERR;

	return hm2_init_buckets(hm2);
}

int hm2_new_ptr(HashMap2 **hm2, HashOpt opt)
{
	if(hm2 == NULL)
		return NULL_ERR;

	return hm2_new(*hm2, opt);
}

/* ---| READ |--- */
int hm2_get(HashMap2 *hm2, void *key, unsigned int key_len, HashMap2Pair *dest)
{
	if(hm2 == NULL)
		return NULL_ERR;

	if(key == NULL)
		return NULL_ERR;

	if(dest == NULL)
		return NULL_ERR;

	LinkedList *ll = &hm2->buckets[hash_value(&hm2->opt, key, key_len)];
	int cnt = 0;
	void *yoink = NULL;
	while(cnt < ll->cnt) {
		if(ll_get(ll, &yoink, cnt) != NO_ERR) {
			return INT_PANIC;
		}

		if(((HashMap2Pair*)yoink)->key == key && ((HashMap2Pair*)yoink)->key_len == key_len) {
			dest->key = key;
			dest->key_len = key_len;
			dest->val = ((HashMap2Pair*)yoink)->val;
			dest->val_len = ((HashMap2Pair*)yoink)->val_len;

			return NO_ERR;
		}
		cnt++;
	}

	return ARG_ERR;
}

/* ---| UPDATE |--- */
int hm2_add(HashMap2 *hm2, HashMap2Pair *item)
{
	if(!hm2)
		return NULL_ERR;

	if(!item)
		return NULL_ERR;

	LinkedList *ll = &hm2->buckets[hash_value(&hm2->opt, item->key, item->key_len)];
	LinkedListNode *node = ll->root;
	while(node != NULL) {
		if(((HashMap2Pair*)node->item)->key == item->key)
			return ARG_ERR;
	}

	if(ll_push(ll, (void*)item) != NO_ERR)
		return INT_PANIC;

	return NO_ERR;
}

/* ---| DELETE |--- */
int hm2_remove(HashMap2 *hm2, void *key, HashMap2Pair *dest);

int hm2_destroy(HashMap2 *hm2)
{
	if(hm2 == NULL)
		return NULL_ERR;

	while(hm2->opt.divider > 0) {
		--hm2->opt.divider;
		if(ll_destroy(&hm2->buckets[hm2->opt.divider]) != 0)
			return INT_PANIC;
	}

	free(hm2->buckets);

	return NO_ERR;
}

int hm2_destroy_ptr(HashMap2 **hm2)
{
	if(hm2 == NULL)
		return NULL_ERR;

	int res = hm2_destroy(*hm2);
	if(res != NO_ERR)
		return res;

	*hm2 = NULL;

	return NO_ERR;
}

/* ---| CUSTOM |--- */
