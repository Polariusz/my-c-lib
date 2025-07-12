#ifndef HASH_MAP_2_H
#define HASH_MAP_2_H

#include "../linked_list/linked_list.h"
#include "../hash/hash.h"

typedef struct HashMap2Pair {
	void *key;
	unsigned int sizeof_key;

	void *val;
	unsigned int sizeof_val;
} HashMap2Pair;

typedef struct HashMap2Bucket {
	LinkedList bucket;
} HashMapBucket;

typedef struct HashMap2 {
	HashOpt opt;
	HashMapBucket2 *buckets;
	unsigned int c_buckets;
} HashMap2;

/* ---| CREATE |--- */
__attribute__ ((nonnull (1)))
	int hm2_new(HashMap2 *hm2, HashOpt opt);

__attribute__ ((nonnull (1)))
	int hm2_new_ptr(HashMap2 **hm2, HashOpt opt);

/* ---| READ |--- */
__attribute__ ((nonnull (1, 2, 3)))
	int hm2_get(HashMap2 *hm2, void *key, HashMap2Pair *dest);

__attribute__ ((nonnull (1, 2, 3)))
	int hm2_get_ptr(HashMap2 *hm2, void *key, HashMap2Pair **dest);

/* ---| UPDATE |--- */
__attribute__ ((nonnull (1, 2)))
	int hm2_add(HashMap2 *hm2, HashMapPair *item);

/* ---| DELETE |--- */
__attribute__ ((nonnull (1, 2, 3)))
	int hm2_remove(HashMap2 *hm2, void *key, HashMapPair *dest);

__attribute__ ((nonnull (1, 2, 3)))
	int hm2_remove_ptr(HashMap2 *hm2, void *key, HashMapPair **dest);

__attribute__ ((nonnull (1)))
	int hm2_destroy(HashMap2 *hm2);

__attribute__ ((nonnull (1)))
	int hm2_destroy_ptr(HashMap2 **hm2);

/* ---| CUSTOM |--- */

#endif
