#ifndef ARRAY_LIST_H_
#define ARRAY_LIST_H_

typedef struct ArrayList {
	void **items;
	unsigned int cnt;
	unsigned int size;
} ArrayList;

/* ---| CREATE |--- */
int al_new(ArrayList *array);
int al_new_ptr(ArrayList **array);
int al_build(ArrayList *array, unsigned int size);
int al_build_ptr(ArrayList **array, unsigned int size);

/* ---| READ |--- */
int al_get(void **dest, ArrayList *src, unsigned int idx);

/* ---| UPDATE |--- */
int al_add_suffix(ArrayList *src, void *item);
int al_add_prefix(ArrayList *src, void *item);
int al_insert(ArrayList *src, void *item, unsigned int idx);
int al_replace(ArrayList *src, void *item, unsigned int index);

/* ---| DELETE |--- */
int al_delete(void **dest, ArrayList *src, unsigned int idx);

/* ---| CUSTOM |--- */
int al_dump(ArrayList *src, void(*dump_item)(void* item));
int al_destroy(ArrayList *src);
int al_destroy_ptr(ArrayList **src);

#endif
