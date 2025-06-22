#include <stdlib.h>

typedef struct Array {
	void **items;
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
int array_get(void **dest, Array *src, unsigned int idx)
{
	if(dest == NULL)
		return NULL_ERR;

	if(src == NULL)
		return NULL_ERR;

	if(src->cnt <= idx)
		return OUT_OF_BOUNDS_ERR;

	*dest = src->items[idx];

	return NO_ERR;
}

/* ---| UPDATE |--- */
int array_add_suffix(Array *src, void *item)
{
	if(src == NULL)
		return NULL_ERR;

	if(item == NULL)
		return NULL_ERR;

	if(src->cnt >= src->size)
	{
		void **new_items = malloc(src->size * 2 * sizeof(void*));
		if(new_items == NULL)
			return MEM_ERR;

		src->size *= 2;
		for(unsigned int i = 0; i < src->cnt; i++) {
			new_items[i] = src->items[i];
		}
		free(src->items);
		src->items = new_items;
	}

	src->items[src->cnt] = item;
	++src->cnt;

	return NO_ERR;
}

int array_add_prefix(Array *src, void *item)
{
	if(src == NULL)
		return NULL_ERR;

	if(item == NULL)
		return NULL_ERR;

	if(src->cnt >= src->size)
	{
		void **new_items = malloc(src->size * 2 * sizeof(void*));
		if(new_items == NULL)
			return MEM_ERR;

		src->size *= 2;
		for(unsigned int i = 0; i < src->cnt; i++) {
			new_items[1 + i] = src->items[i];
		}
		free(src->items);

		new_items[0] = item;
		src->items = new_items;
		++src->cnt;

		return NO_ERR;
	}

	for(unsigned int i = src->cnt; i > 0; i--) {
		src->items[i] = src->items[i-1];
	}

	src->items[0] = item;
	++src->cnt;

	return NO_ERR;
}

int array_insert(Array *src, void *item, unsigned int idx)
{
	if(src == NULL)
		return NULL_ERR;

	if(item == NULL)
		return NULL_ERR;

	if(src->cnt <= idx)
		return OUT_OF_BOUNDS_ERR;

	if(src->cnt >= src->size)
	{
		void **new_items = malloc(src->size * 2 * sizeof(void*));
		if(new_items == NULL)
			return MEM_ERR;

		src->size *= 2;
		for(unsigned int i = 0; i < idx; i++) {
			new_items[i] = src->items[i];
		}
		for(unsigned int i = src->cnt; i >= idx; i--) {
			new_items[i+1] = src->items[i];
		}
		new_items[idx] = item;

		free(src->items);
		src->items = new_items;
		++src->cnt;

		return NO_ERR;
	}

	for(unsigned int i = src->cnt; i >= idx; i--) {
		src->items[i+1] = src->items[i];
	}
	src->items[idx] = item;
	++src->cnt;

	return NO_ERR;
}

int array_replace(Array *src, void *item, unsigned int idx)
{
	if(src == NULL)
		return NULL_ERR;

	if(item == NULL)
		return NULL_ERR;

	if(src->cnt <= idx)
		return OUT_OF_BOUNDS_ERR;

	src->items[idx] = item;

	return NO_ERR;
}

/* ---| DELETE |--- */
int array_delete(Array *src, unsigned int idx)
{
	if(src == NULL)
		return NULL_ERR;

	if(src->cnt <= idx)
		return OUT_OF_BOUNDS_ERR;

	for(unsigned int i = idx; i < src->cnt; i++) {
		src->items[i] = src->items[i+1];
	}
	src->items[src->cnt] = NULL;
	--src->cnt;

	return NO_ERR;
}
