#ifndef HASH_MAP_H_
#define HASH_MAP_H_

#include "../linked_list/linked_list.h"
#include "../hash/hash.h"

typedef struct KeyVal {
	void *key;
	void *val;
	unsigned int key_len;
	unsigned int val_len;
} KeyVal;

typedef struct HashMap {
	HashOpt hash_opt;
	LinkedList *buckets;
	unsigned int c_buckets;

	unsigned int (*hash)(HashOpt *opt, void *key, unsigned int len);
	int (*cmp)(void *left, void *right);
} HashMap;

/* ---| CONSTRUCTOR |--- */
int hm_new_custom(
	HashMap *hm,
	HashOpt hash_opt,
	unsigned int size,
	unsigned int (*hash)(HashOpt *opt, void *key, unsigned int len),
	int (*cmp)(void *left, void *right)
);

int hm_new_custom_ptr(
	HashMap **hm,
	HashOpt hash_opt,
	unsigned int size,
	unsigned int (*hash)(HashOpt *opt, void *key, unsigned int len),
	int (*cmp)(void *left, void *right)
);

int hm_new(
	HashMap *hm,
	unsigned int size,
	unsigned int (*hash)(HashOpt *opt, void *key, unsigned int len),
	int (*cmp)(void *left, void *right)
);

int hm_new_ptr(
	HashMap **hm,
	unsigned int size,
	unsigned int (*hash)(HashOpt *opt, void *key, unsigned int len),
	int (*cmp)(void *left, void *right)
);

/* ---| DESTRUCTOR |--- */
int hm_destroy(HashMap *hm);
int hm_destroy_ptr(HashMap **hm);

/* ---| CREATE |--- */
int hm_add(HashMap *hm, KeyVal *kv);

/* ---| READ |--- */
int hm_get(HashMap *hm, KeyVal *kv);

/* ---| UPDATE |--- */
int hm_replace(HashMap *hm, KeyVal *kv);

/* ---| DELETE |--- */
int hm_delete(HashMap *hm, KeyVal *kv);

/* ---| CUSTOM |--- */

#endif
