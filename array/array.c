#include <stdlib.h>

typedef struct Array {
	void *items;
	unsigned int cnt;
	unsigned int size;
} Array;

enum ERR_LVL {
	NO_ERR,
	NULL_ERR,
	MEM_ERR,
	ARG_ERR,
	OUT_OF_BOUNDS_ERR,
};

/* ---| CREATE |--- */
#define SIZE 16

int array_new(Array *array)
{
	if(array == NULL)
		return NULL_ERR;

	array->items = malloc(SIZE * sizeof(void*));
	if(array->items == NULL) {
		return MEM_ERR;
	}

	array->cnt = 0;
	array->size = SIZE;

	return NO_ERR;
}

/* ---| CREATE |--- */
int array_build(Array *array, unsigned int size)
{
	if(array == NULL)
		return NULL_ERR;

	if(size < 1)
		return ARG_ERR;

	array->items = malloc(size * sizeof(void*));
	if(array->items == NULL) {
		return MEM_ERR;
	}

	array->cnt = 0;
	array->size = size;

	return NO_ERR;
}

/* ---| READ |--- */
int array_get(void **dest, Array *src, int idx)
{
	if(dest == NULL)
		return NULL_ERR;

	if(src == NULL)
		return NULL_ERR;

	if(idx > src->cnt)
		return OUT_OF_BOUNDS_ERR;

	*dest = src->items[idx];

	return NO_ERR;
}

/* ---| UPDATE |--- */
Array array_add_suffix(void);
Array array_add_prefix(void);
Array array_insert(void);
Array array_replace(void);

/* ---| DELETE |--- */

Array array_delete(void);
