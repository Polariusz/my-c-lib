#ifndef ARRAY_H_
#define ARRAY_H_

typedef struct Array {
	void *items;
	int cnt;
	int size;
} Array;

/* ---| CREATE |--- */
int array_new(Array *array);
int array_build(Array *array, unsigned int size);

/* ---| READ |--- */
int array_get(void **dest, Array *src, unsigned int idx);

/* ---| UPDATE |--- */
int array_add_suffix(Array *src, void *item);
int array_add_prefix(Array *src, void *item);
int array_insert(Array *src, void *item, unsigned int idx);
int array_replace(Array *src, void *item, unsigned int index);

/* ---| DELETE |--- */

int array_delete(Array *src, unsigned int idx);

#endif
