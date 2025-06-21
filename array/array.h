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
Array array_get(void);

/* ---| UPDATE |--- */
Array array_add_suffix(void);
Array array_add_prefix(void);
Array array_insert(void);
Array array_replace(void);

/* ---| DELETE |--- */

Array array_delete(void);

#endif
