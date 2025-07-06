#include <stdio.h>
#include <stdlib.h>
#include "../linked_list/linked_list.h"
#include "../err_lvl/err_lvl.h"

typedef struct HashMapPair {
	unsigned int key;
	void *value;
} HashMapPair;

typedef struct HashMapBucket {
	LinkedList bucket;
} HashMapBucket;

typedef struct HashMap {
	HashMapBucket *buckets;
	unsigned int c_buckets;
	unsigned int size;
	void(*dump_item)(char *buf, void *item);
} HashMap;

#define HM_DEFAULT_SIZE 10

int hm_hash_key(HashMap *hm, unsigned int key)
{
	return key % hm->size;
}

int hm_init_buckets(HashMap *hm, void(*dump_item)(char *buf, void *item))
{
	int cnt = hm->size;
	while(cnt > 0) {
		--cnt;
		if(ll_new(&hm->buckets[cnt].bucket, dump_item) != 0)
			return INT_PANIC;
	}

	return NO_ERR;
}

int hm_new(HashMap *hm, void(*dump_item)(char *buf, void *item))
{
	if(!hm)
		return NULL_ERR;

	hm->buckets = malloc(HM_DEFAULT_SIZE * sizeof(HashMapBucket));
	if(hm->buckets == NULL)
		return MEM_ERR;

	hm->c_buckets = 0;
	hm->size = HM_DEFAULT_SIZE;
	hm->dump_item = dump_item;

	return hm_init_buckets(hm, dump_item);
}

int hm_new_ptr(HashMap **hm, void(*dump_item)(char *buf, void *item))
{
	if(!hm)
		return NULL_ERR;

	(*hm)->buckets = malloc(HM_DEFAULT_SIZE * sizeof(HashMapBucket));
	if((*hm)->buckets == NULL)
		return MEM_ERR;

	(*hm)->c_buckets = 0;
	(*hm)->size = HM_DEFAULT_SIZE;
	(*hm)->dump_item = dump_item;

	return hm_init_buckets(*hm, dump_item);
}

int hm_get(HashMap *hm, unsigned int key, HashMapPair *dest)
{
	if(!hm)
		return NULL_ERR;

	if(!dest)
		return NULL_ERR;

	LinkedList *ll = &(hm->buckets[hm_hash_key(hm, key)].bucket);

	void *yoink = NULL;
	int cnt = ll->cnt;
	while(cnt > 0) {
		--cnt;
		if(ll_get(ll, &yoink, cnt) != NO_ERR) {
			return INT_PANIC;
		}
		if(((HashMapPair*)yoink)->key == key) {
			dest->key = key;
			dest->value = ((HashMapPair*)yoink)->value;

			return NO_ERR;
		}
	}

	return ARG_ERR;
}

int hm_add(HashMap *hm, HashMapPair *item)
{
	if(!hm)
		return NULL_ERR;

	if(!item)
		return NULL_ERR;

	if(ll_push(&hm->buckets[hm_hash_key(hm, item->key)].bucket, (void*)item) != NO_ERR)
		return INT_PANIC;

	return NO_ERR;
}

int hm_remove(HashMap *hm, unsigned int key, HashMapPair *dest)
{
	if(!hm)
		return NULL_ERR;

	LinkedList *ll = &(hm->buckets[hm_hash_key(hm, key)].bucket);

	void *yoink = NULL;
	int cnt = ll->cnt;
	while(cnt > 0) {
		--cnt;
		if(ll_get(ll, &yoink, cnt) != NO_ERR)
			return INT_PANIC;

		if(((HashMapPair*)yoink)->key == key) {
			if(dest != NULL) {
				dest->key = key;
				dest->value = ((HashMapPair*)yoink)->value;
			}

			if(ll_delete(ll, cnt) != NO_ERR)
				return INT_PANIC;

			return NO_ERR;
		}
	}

	return ARG_ERR;
}

/* ---| CUSTOM |--- */
int hm_dump(HashMap *hm);
int hm_destroy(HashMap *hm)
{
	if(!hm)
		return NULL_ERR;

	int cnt = hm->size;
	while(cnt > 0) {
		--cnt;
		if(ll_destroy(&hm->buckets[cnt].bucket) != 0)
			return INT_PANIC;
	}

	free(hm->buckets);
	hm->c_buckets = 0;

	return NO_ERR;
}

int hm_destroy_ptr(HashMap **hm)
{
	if(!hm)
		return NULL_ERR;

	hm_destroy(*hm);
	*hm = NULL;

	return NO_ERR;
}
