#include <stdlib.h>
#include <stdio.h>
#include "../err_lvl/err_lvl.h"

typedef struct ArrayList {
	void **items;
	unsigned int cnt;
	unsigned int size;
} ArrayList;

/* ---| CREATE |--- */
#define SIZE 16

int al_new(ArrayList *array)
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

int al_new_ptr(ArrayList **array)
{
	if(array == NULL)
		return NULL_ERR;

	*array = malloc(sizeof(ArrayList));

	(*array)->items = malloc(SIZE * sizeof(void*));
	if((*array)->items == NULL) {
		return MEM_ERR;
	}

	(*array)->cnt = 0;
	(*array)->size = SIZE;

	return NO_ERR;
}

int al_build(ArrayList *array, unsigned int size)
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

int al_build_ptr(ArrayList **array, unsigned int size)
{
	if(array == NULL)
		return NULL_ERR;

	if(size < 1)
		return ARG_ERR;

	*array = malloc(sizeof(ArrayList));

	(*array)->items = malloc(size * sizeof(void*));
	if((*array)->items == NULL) {
		return MEM_ERR;
	}

	(*array)->cnt = 0;
	(*array)->size = size;

	return NO_ERR;
}

/* ---| READ |--- */
int al_get(void **dest, ArrayList *src, unsigned int idx)
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
int al_add_suffix(ArrayList *src, void *item)
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

int al_add_prefix(ArrayList *src, void *item)
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

int al_insert(ArrayList *src, void *item, unsigned int idx)
{
	if(src == NULL)
		return NULL_ERR;

	if(item == NULL)
		return NULL_ERR;

	if(src->cnt < idx)
		return OUT_OF_BOUNDS_ERR;

	if(src->cnt >= src->size) {
		src->size *= 2;
		void **new_items = malloc(src->size * sizeof(void*));
		if(new_items == NULL)
			return MEM_ERR;

		for(unsigned int i = 0; i < src->cnt; i++) {
			new_items[i] = src->items[i];
		}
		free(src->items);
		src->items = new_items;
	}

	++src->cnt;
	for(unsigned int i = src->cnt; i > idx; i--) {
		src->items[i] = src->items[i-1];
	}

	src->items[idx] = item;

	return NO_ERR;
}

int al_replace(ArrayList *src, void *item, unsigned int idx)
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
int al_delete(void **dest, ArrayList *src, unsigned int idx)
{
	if(src == NULL)
		return NULL_ERR;

	if(src->cnt <= idx)
		return OUT_OF_BOUNDS_ERR;

	if(dest != NULL)
		*dest = src->items[idx];

	for(unsigned int i = idx; i < src->cnt; i++) {
		src->items[i] = src->items[i+1];
	}
	src->items[src->cnt] = NULL;
	--src->cnt;

	return NO_ERR;
}

/* ---| CUSTOM |--- */
int al_dump(ArrayList *src, void(*dump_item)(void* item))
{
	if(src == NULL)
		return NULL_ERR;

	printf("CNT  : %d\n", src->cnt);
	printf("SIZE : %d\n", src->size);
	for(unsigned int i = 0; i < src->cnt; i++) {
		printf("%p: ", src->items[i]);
		dump_item(src->items[i]);
		printf("\n");
	}

	return NO_ERR;
}

int al_destroy(ArrayList *src)
{
	if(src == NULL)
		return NULL_ERR;

	if(src->items == NULL)
		return NULL_ERR;

	free(src->items);
	src->items = NULL;
	src->cnt = 0;
	src->size = 0;

	return NO_ERR;
}

int al_destroy_ptr(ArrayList **src)
{
	if(src == NULL)
		return NULL_ERR;

	if(*src == NULL)
		return NULL_ERR;

	if((*src)->items == NULL)
		return NULL_ERR;

	free((*src)->items);
	(*src)->items = NULL;
	(*src)->cnt = 0;
	(*src)->size = 0;
	free(*src);
	*src = NULL;

	return NO_ERR;
}
