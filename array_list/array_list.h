#ifndef ARRAY_LIST_H_
#define ARRAY_LIST_H_

typedef struct ArrayList {
	void **items;
	unsigned int cnt;
	unsigned int size;
} ArrayList;

/* ---| CREATE |--- */
int al_new(ArrayList *al);
int al_new_ptr(ArrayList **al);
int al_build(ArrayList *al, unsigned int size);
int al_build_ptr(ArrayList **al, unsigned int size);

/* ---| READ |--- */
int al_get(ArrayList *al, void **dest, unsigned int idx);

/* ---| UPDATE |--- */
int al_add_suffix(ArrayList *al, void *item);
int al_add_prefix(ArrayList *al, void *item);
int al_insert(ArrayList *al, unsigned int idx, void *item);
int al_replace(ArrayList *al, void *item, unsigned int index);

/* ---| DELETE |--- */
int al_delete(ArrayList *al, void **dest, unsigned int idx);

/* ---| CUSTOM |--- */
int al_dump(ArrayList *al, void(*dump_item)(void* item));
int al_destroy(ArrayList *al);
int al_destroy_ptr(ArrayList **al);

#endif
