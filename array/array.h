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
Array array_insert(void);
Array array_replace(void);

/* ---| DELETE |--- */

Array array_delete(void);

#endif
