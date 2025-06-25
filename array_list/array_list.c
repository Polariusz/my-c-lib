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

int al_new(ArrayList *al)
{
	if(al == NULL)
		return NULL_ERR;

	al->items = malloc(SIZE * sizeof(void*));
	if(al->items == NULL) {
		return MEM_ERR;
	}

	al->cnt = 0;
	al->size = SIZE;

	return NO_ERR;
}

int al_new_ptr(ArrayList **al)
{
	if(al == NULL)
		return NULL_ERR;

	*al = malloc(sizeof(ArrayList));

	(*al)->items = malloc(SIZE * sizeof(void*));
	if((*al)->items == NULL) {
		return MEM_ERR;
	}

	(*al)->cnt = 0;
	(*al)->size = SIZE;

	return NO_ERR;
}

int al_build(ArrayList *al, unsigned int size)
{
	if(al == NULL)
		return NULL_ERR;

	if(size < 1)
		return ARG_ERR;

	al->items = malloc(size * sizeof(void*));
	if(al->items == NULL) {
		return MEM_ERR;
	}

	al->cnt = 0;
	al->size = size;

	return NO_ERR;
}

int al_build_ptr(ArrayList **al, unsigned int size)
{
	if(al == NULL)
		return NULL_ERR;

	if(size < 1)
		return ARG_ERR;

	*al = malloc(sizeof(ArrayList));

	(*al)->items = malloc(size * sizeof(void*));
	if((*al)->items == NULL) {
		return MEM_ERR;
	}

	(*al)->cnt = 0;
	(*al)->size = size;

	return NO_ERR;
}

/* ---| READ |--- */
int al_get(ArrayList *al, void **dest, unsigned int idx)
{
	if(dest == NULL)
		return NULL_ERR;

	if(al == NULL)
		return NULL_ERR;

	if(al->cnt <= idx)
		return OUT_OF_BOUNDS_ERR;

	*dest = al->items[idx];

	return NO_ERR;
}

/* ---| UPDATE |--- */
int al_add_suffix(ArrayList *al, void *item)
{
	if(al == NULL)
		return NULL_ERR;

	if(item == NULL)
		return NULL_ERR;

	if(al->cnt >= al->size)
	{
		void **new_items = malloc(al->size * 2 * sizeof(void*));
		if(new_items == NULL)
			return MEM_ERR;

		al->size *= 2;
		for(unsigned int i = 0; i < al->cnt; i++) {
			new_items[i] = al->items[i];
		}
		free(al->items);
		al->items = new_items;
	}

	al->items[al->cnt] = item;
	++al->cnt;

	return NO_ERR;
}

int al_add_prefix(ArrayList *al, void *item)
{
	if(al == NULL)
		return NULL_ERR;

	if(item == NULL)
		return NULL_ERR;

	if(al->cnt >= al->size)
	{
		void **new_items = malloc(al->size * 2 * sizeof(void*));
		if(new_items == NULL)
			return MEM_ERR;

		al->size *= 2;
		for(unsigned int i = 0; i < al->cnt; i++) {
			new_items[1 + i] = al->items[i];
		}
		free(al->items);

		new_items[0] = item;
		al->items = new_items;
		++al->cnt;

		return NO_ERR;
	}

	for(unsigned int i = al->cnt; i > 0; i--) {
		al->items[i] = al->items[i-1];
	}

	al->items[0] = item;
	++al->cnt;

	return NO_ERR;
}

int al_insert(ArrayList *al, void *item, unsigned int idx)
{
	if(al == NULL)
		return NULL_ERR;

	if(item == NULL)
		return NULL_ERR;

	if(al->cnt < idx)
		return OUT_OF_BOUNDS_ERR;

	if(al->cnt >= al->size) {
		al->size *= 2;
		void **new_items = malloc(al->size * sizeof(void*));
		if(new_items == NULL)
			return MEM_ERR;

		for(unsigned int i = 0; i < al->cnt; i++) {
			new_items[i] = al->items[i];
		}
		free(al->items);
		al->items = new_items;
	}

	++al->cnt;
	for(unsigned int i = al->cnt; i > idx; i--) {
		al->items[i] = al->items[i-1];
	}

	al->items[idx] = item;

	return NO_ERR;
}

int al_replace(ArrayList *al, void *item, unsigned int idx)
{
	if(al == NULL)
		return NULL_ERR;

	if(item == NULL)
		return NULL_ERR;

	if(al->cnt <= idx)
		return OUT_OF_BOUNDS_ERR;

	al->items[idx] = item;

	return NO_ERR;
}

/* ---| DELETE |--- */
int al_delete(ArrayList *al, void **dest, unsigned int idx)
{
	if(al == NULL)
		return NULL_ERR;

	if(al->cnt <= idx)
		return OUT_OF_BOUNDS_ERR;

	if(dest != NULL)
		*dest = al->items[idx];

	for(unsigned int i = idx; i < al->cnt; i++) {
		al->items[i] = al->items[i+1];
	}
	al->items[al->cnt] = NULL;
	--al->cnt;

	return NO_ERR;
}

/* ---| CUSTOM |--- */
int al_dump(ArrayList *al, void(*dump_item)(void* item))
{
	if(al == NULL)
		return NULL_ERR;

	printf("CNT  : %d\n", al->cnt);
	printf("SIZE : %d\n", al->size);
	for(unsigned int i = 0; i < al->cnt; i++) {
		printf("%p: ", al->items[i]);
		dump_item(al->items[i]);
		printf("\n");
	}

	return NO_ERR;
}

int al_destroy(ArrayList *al)
{
	if(al == NULL)
		return NULL_ERR;

	if(al->items == NULL)
		return NULL_ERR;

	free(al->items);
	al->items = NULL;
	al->cnt = 0;
	al->size = 0;

	return NO_ERR;
}

int al_destroy_ptr(ArrayList **al)
{
	if(al == NULL)
		return NULL_ERR;

	if(*al == NULL)
		return NULL_ERR;

	if((*al)->items == NULL)
		return NULL_ERR;

	free((*al)->items);
	(*al)->items = NULL;
	(*al)->cnt = 0;
	(*al)->size = 0;
	free(*al);
	*al = NULL;

	return NO_ERR;
}
