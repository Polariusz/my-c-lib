#include <stdio.h>
#include <stdlib.h>
#include "../linked_list/linked_list.h"
#include "../err_lvl/err_lvl.h"

typedef struct KeyVal {
	void *key;
	void *val;
} KeyVal;

typedef struct HashMap {
	GenericFunctions gf;
	HashOpt hash_opt;
	LinkedList *buckets;
	unsigned int c_buckets;
} HashMap;

/* ---| CREATE |--- */
int hm_new(HashMap *hm, GenericFunctions gf);
int hm_new_custom(HashMap *hm, GenericFunctions gf, HashOpt hash_opt);

int hm_new_ptr(HashMap **hm, GenericFunctions gf);
int hm_new_custom_ptr(HashMap **hm, GenericFunctions gf, HashOpt hash_opt);

/* ---| READ |--- */
int hm_get(HashMap *hm, void *key);

/* ---| UPDATE |--- */
int hm_add(HashMap *hm, void *key, void *val);

/* ---| DESTROY |--- */
int hm_delete(HashMap *hm, void *key, void *val);
int hm_destroy(HashMap *hm);
int hm_destroy_ptr(HashMap **hm);

/* ---| CUSTOM |--- */

#endif
