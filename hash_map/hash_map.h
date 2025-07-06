#ifndef HASH_MAP_H_
#define HASH_MAP_H_

#include "../linked_list/linked_list.h"

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

int hm_new(HashMap *hm, void(*dump_item)(char *buf, void *item));
int hm_new_ptr(HashMap **hm, void(*dump_item)(char *buf, void *item));

int hm_get(HashMap *hm, unsigned int key, HashMapPair *dest);
int hm_add(HashMap *hm, HashMapPair *item);
int hm_remove(HashMap *hm, unsigned int key, HashMapPair *dest);

/* ---| CUSTOM |--- */
int hm_dump(HashMap *hm);
int hm_destroy(HashMap *hm);
int hm_destroy_ptr(HashMap **hm);

#endif
