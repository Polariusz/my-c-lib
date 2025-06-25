#ifndef ARRAY_H_
#define ARRAY_H_

typedef struct Array {
	void **items;
	unsigned int cnt;
	unsigned int size;
} Array;

/* ---| CREATE |--- */
int array_new(Array *array);
int array_new_ptr(Array **array);
int array_build(Array *array, unsigned int size);
int array_build_ptr(Array **array, unsigned int size);

/* ---| READ |--- */
int array_get(void **dest, Array *src, unsigned int idx);

/* ---| UPDATE |--- */
int array_add_suffix(Array *src, void *item);
int array_add_prefix(Array *src, void *item);
int array_insert(Array *src, void *item, unsigned int idx);
int array_replace(Array *src, void *item, unsigned int index);

/* ---| DELETE |--- */
int array_delete(void **dest, Array *src, unsigned int idx);

/* ---| CUSTOM |--- */
int array_dump(Array *src, void(*dump_item)(void* item));
int array_destroy(Array *src);
int array_destroy_ptr(Array **src);

#endif
