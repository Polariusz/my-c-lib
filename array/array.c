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
Array array_get(void);

/* ---| UPDATE |--- */
Array array_add_suffix(void);
Array array_add_prefix(void);
Array array_insert(void);
Array array_replace(void);

/* ---| DELETE |--- */

Array array_delete(void);
