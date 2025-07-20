#include <criterion/criterion.h>
#include "array_list.h"
#include <stdio.h>

int *init_int_arr(int length)
{
	int *arr = malloc(length * sizeof(int));
	while(length > 0) {
		--length;
		arr[length] = length;
	}

	return arr;
}

void dump_item(void *item)
{
	printf("%d", *(int*)item);
}

Test(al_add_suffix, complex)
{
	ArrayList *array = NULL; al_new_ptr(&array);
	int *arr = init_int_arr(3);
	int res = 0;
	void *yoinker = NULL;
	
	res = al_add_suffix(array, &arr[0]); cr_expect(res == 0);
	res = al_get(array, 0, &yoinker); cr_expect(res == 0);
	cr_assert_eq(yoinker, &arr[0]);

	res = al_add_suffix(array, &arr[1]); cr_expect(res == 0);
	res = al_get(array, 0, &yoinker); cr_expect(res == 0);
	cr_assert_eq(yoinker, &arr[0]);
	res = al_get(array, 1, &yoinker); cr_expect(res == 0);
	cr_assert_eq(yoinker, &arr[1]);

	res = al_add_suffix(array, &arr[2]); cr_expect(res == 0);
	res = al_get(array, 0, &yoinker); cr_expect(res == 0);
	cr_assert_eq(yoinker, &arr[0]);
	res = al_get(array, 1, &yoinker); cr_expect(res == 0);
	cr_assert_eq(yoinker, &arr[1]);
	res = al_get(array, 2, &yoinker); cr_expect(res == 0);
	cr_assert_eq(yoinker, &arr[2]);

	res = al_destroy_ptr(&array); cr_expect(res == 0);
	free(arr);
}

Test(al_add_prefix, complex)
{
	ArrayList *array = NULL; al_new_ptr(&array);
	int *arr = init_int_arr(3);
	int res = 0;
	void *yoinker = NULL;

	res = al_add_prefix(array, &arr[0]); cr_expect(res == 0);
	res = al_get(array, 0, &yoinker); cr_expect(res == 0);
	cr_assert_eq(yoinker, &arr[0]);

	res = al_add_prefix(array, &arr[1]); cr_expect(res == 0);
	res = al_get(array, 0, &yoinker); cr_expect(res == 0);
	cr_assert_eq(yoinker, &arr[1]);
	res = al_get(array, 1, &yoinker); cr_expect(res == 0);
	cr_assert_eq(yoinker, &arr[0]);

	res = al_add_prefix(array, &arr[2]); cr_expect(res == 0);
	res = al_get(array, 0, &yoinker); cr_expect(res == 0);
	cr_assert_eq(yoinker, &arr[2]);
	res = al_get(array, 1, &yoinker); cr_expect(res == 0);
	cr_assert_eq(yoinker, &arr[1]);
	res = al_get(array, 2, &yoinker); cr_expect(res == 0);
	cr_assert_eq(yoinker, &arr[0]);

	res = al_destroy_ptr(&array); cr_expect(res == 0);
	free(arr);
}

Test(al_insert, complex)
{
	ArrayList *array = NULL;
	int *arr = init_int_arr(64);
	int res = 0;
	void *yoinker = NULL;

	al_new_ptr(&array);
	
	res = al_add_suffix(array, &arr[0]); cr_expect(res =! 0);
	res = al_add_suffix(array, &arr[1]); cr_expect(res =! 0);
	res = al_add_suffix(array, &arr[2]); cr_expect(res =! 0);
	res = al_add_suffix(array, &arr[3]); cr_expect(res =! 0);
	res = al_add_suffix(array, &arr[4]); cr_expect(res =! 0);
	res = al_add_suffix(array, &arr[5]); cr_expect(res =! 0);
	res = al_add_suffix(array, &arr[6]); cr_expect(res =! 0);
	res = al_add_suffix(array, &arr[7]); cr_expect(res =! 0);
	res = al_add_suffix(array, &arr[8]); cr_expect(res =! 0);
	res = al_add_suffix(array, &arr[9]); cr_expect(res =! 0);

	res = al_insert(array, 0, &arr[10]); cr_expect(res =! 0);
	res = al_get(array, 0, &yoinker); cr_expect(res == 0);
	cr_assert_eq(yoinker, &arr[10]);

	res = al_insert(array, 3, &arr[11]); cr_expect(res =! 0);
	res = al_get(array, 3, &yoinker); cr_expect(res == 0);
	cr_assert_eq(yoinker, &arr[11]);

	res = al_insert(array, 9, &arr[12]); cr_expect(res =! 0);
	res = al_get(array, 9, &yoinker); cr_expect(res == 0);
	cr_assert_eq(yoinker, &arr[12]);

	res = al_insert(array, 9, &arr[13]); cr_expect(res =! 0);
	res = al_get(array, 9, &yoinker); cr_expect(res == 0);
	cr_assert_eq(yoinker, &arr[13]);

	al_get(array, 0, &yoinker); cr_assert_eq(yoinker, &arr[10]);
	al_get(array, 1, &yoinker); cr_assert_eq(yoinker, &arr[0]);
	al_get(array, 2, &yoinker); cr_assert_eq(yoinker, &arr[1]);
	al_get(array, 3, &yoinker); cr_assert_eq(yoinker, &arr[11]);
	al_get(array, 4, &yoinker); cr_assert_eq(yoinker, &arr[2]);
	al_get(array, 5, &yoinker); cr_assert_eq(yoinker, &arr[3]);
	al_get(array, 6, &yoinker); cr_assert_eq(yoinker, &arr[4]);
	al_get(array, 7, &yoinker); cr_assert_eq(yoinker, &arr[5]);
	al_get(array, 8, &yoinker); cr_assert_eq(yoinker, &arr[6]);
	al_get(array, 9, &yoinker); cr_assert_eq(yoinker, &arr[13]);
	al_get(array, 10, &yoinker); cr_assert_eq(yoinker, &arr[12]);
	al_get(array, 11, &yoinker); cr_assert_eq(yoinker, &arr[7]);
	al_get(array, 12, &yoinker); cr_assert_eq(yoinker, &arr[8]);
	al_get(array, 13, &yoinker); cr_assert_eq(yoinker, &arr[9]);

	al_destroy_ptr(&array);
	free(arr);
}

Test(al_update, complex)
{
	ArrayList *array = NULL;
	int *arr = init_int_arr(64);
	int res = 0;
	void *yoinker = NULL;

	al_new_ptr(&array);
	
	res = al_add_suffix(array, &arr[0]); cr_expect(res =! 0);
	res = al_add_suffix(array, &arr[1]); cr_expect(res =! 0);
	res = al_add_suffix(array, &arr[2]); cr_expect(res =! 0);
	res = al_add_suffix(array, &arr[3]); cr_expect(res =! 0);
	res = al_add_suffix(array, &arr[4]); cr_expect(res =! 0);
	res = al_add_suffix(array, &arr[5]); cr_expect(res =! 0);
	res = al_add_suffix(array, &arr[6]); cr_expect(res =! 0);
	res = al_add_suffix(array, &arr[7]); cr_expect(res =! 0);
	res = al_add_suffix(array, &arr[8]); cr_expect(res =! 0);
	res = al_add_suffix(array, &arr[9]); cr_expect(res =! 0);

	res = al_insert(array, 0, &arr[10]); cr_expect(res =! 0);
	res = al_insert(array, 3, &arr[11]); cr_expect(res =! 0);
	res = al_insert(array, 9, &arr[12]); cr_expect(res =! 0);
	res = al_insert(array, 9, &arr[13]); cr_expect(res =! 0);

	res = al_add_prefix(array, &arr[14]); cr_expect(res =! 0);
	res = al_add_prefix(array, &arr[15]); cr_expect(res =! 0);
	res = al_add_prefix(array, &arr[16]); cr_expect(res =! 0);

	res = al_add_suffix(array, &arr[17]); cr_expect(res =! 0);
	res = al_add_suffix(array, &arr[18]); cr_expect(res =! 0);

	res = al_replace(array, 10, &arr[19]); cr_expect(res =! 0);
	res = al_replace(array, 6, &arr[20]); cr_expect(res =! 0);

	al_get(array, 0, &yoinker); cr_assert_eq(yoinker, &arr[16]);
	al_get(array, 1, &yoinker); cr_assert_eq(yoinker, &arr[15]);
	al_get(array, 2, &yoinker); cr_assert_eq(yoinker, &arr[14]);
	al_get(array, 3, &yoinker); cr_assert_eq(yoinker, &arr[10]);
	al_get(array, 4, &yoinker); cr_assert_eq(yoinker, &arr[0]);
	al_get(array, 5, &yoinker); cr_assert_eq(yoinker, &arr[1]);
	al_get(array, 6, &yoinker); cr_assert_eq(yoinker, &arr[20]);
	al_get(array, 7, &yoinker); cr_assert_eq(yoinker, &arr[2]);
	al_get(array, 8, &yoinker); cr_assert_eq(yoinker, &arr[3]);
	al_get(array, 9, &yoinker); cr_assert_eq(yoinker, &arr[4]);
	al_get(array, 10, &yoinker); cr_assert_eq(yoinker, &arr[19]);
	al_get(array, 11, &yoinker); cr_assert_eq(yoinker, &arr[6]);
	al_get(array, 12, &yoinker); cr_assert_eq(yoinker, &arr[13]);
	al_get(array, 13, &yoinker); cr_assert_eq(yoinker, &arr[12]);
	al_get(array, 14, &yoinker); cr_assert_eq(yoinker, &arr[7]);
	al_get(array, 15, &yoinker); cr_assert_eq(yoinker, &arr[8]);
	al_get(array, 16, &yoinker); cr_assert_eq(yoinker, &arr[9]);
	al_get(array, 17, &yoinker); cr_assert_eq(yoinker, &arr[17]);
	al_get(array, 18, &yoinker); cr_assert_eq(yoinker, &arr[18]);

	al_destroy_ptr(&array);
	free(arr);
}

Test(al_get, oob)
{
	int a = 0;
	int b = 1;
	int c = 2;
	ArrayList *array;
	al_new_ptr(&array);
	void *yoink = NULL;
	int res = 0;

	res = al_get(array, 0, &yoink); cr_expect(res != 0);
	res = al_get(array, 1, &yoink); cr_expect(res != 0);

	al_add_suffix(array, &a);
	res = al_get(array, 0, &yoink); cr_expect(res == 0);
	res = al_get(array, 1, &yoink); cr_expect(res != 0);
	res = al_get(array, 2, &yoink); cr_expect(res != 0);

	al_add_suffix(array, &b);
	res = al_get(array, 0, &yoink); cr_expect(res == 0);
	res = al_get(array, 1, &yoink); cr_expect(res == 0);
	res = al_get(array, 2, &yoink); cr_expect(res != 0);
	res = al_get(array, 3, &yoink); cr_expect(res != 0);

	al_add_suffix(array, &c);
	res = al_get(array, 0, &yoink); cr_expect(res == 0);
	res = al_get(array, 1, &yoink); cr_expect(res == 0);
	res = al_get(array, 2, &yoink); cr_expect(res == 0);
	res = al_get(array, 3, &yoink); cr_expect(res != 0);
	res = al_get(array, 4, &yoink); cr_expect(res != 0);

	al_destroy_ptr(&array);
}

Test(al_delete, complex)
{
	int a = 0;
	int b = 1;
	int c = 2;
	ArrayList *array;
	al_new_ptr(&array);
	void *yoink = NULL;
	int res = 0;

	al_add_suffix(array, &a);
	al_add_suffix(array, &b);
	al_add_suffix(array, &c);

	res = al_delete(array, 3, NULL); cr_expect(res != 0);
	res = al_delete(array, 2, NULL); cr_expect(res == 0);
	res = al_delete(array, 0, NULL); cr_expect(res == 0);
	res = al_delete(array, 0, &yoink); cr_expect(res == 0);
	cr_assert_eq(yoink, &b);
	res = al_delete(array, 0, &yoink); cr_expect(res != 0);

	al_destroy_ptr(&array);
}

Test(al_insert, growing)
{
	const int ARR_SIZE = 33;

	int *arr = init_int_arr(ARR_SIZE);
	ArrayList *array;
	al_new_ptr(&array);

	unsigned int cnt = ARR_SIZE;
	int res = 0;
	while(cnt > 0) {
		--cnt;
		res = al_add_suffix(array, &arr[cnt]); cr_expect(res == 0);
	}

	cr_assert_gt(array->size, 32);
	cr_assert_geq(array->size, array->cnt);
	cr_assert_eq(array->items[array->cnt-1], &arr[0]);
	cr_assert_eq(array->items[array->cnt-2], &arr[1]);

	al_destroy_ptr(&array);
	free(arr);
}

Test(al_delete, shrinking)
{
	const int ARR_SIZE = 33;

	int *arr = init_int_arr(ARR_SIZE);
	ArrayList *array;
	al_new_ptr(&array);

	unsigned int cnt = ARR_SIZE;
	int res = 0;
	while(cnt > 0) {
		--cnt;
		res = al_add_suffix(array, &arr[cnt]); cr_expect(res == 0);
	}

	cr_assert_eq(array->size, 64);

	res = al_delete(array, array->cnt-1, NULL); cr_expect(res == 0);
	res = al_delete(array, array->cnt-1, NULL); cr_expect(res == 0);

	cr_assert_eq(array->size, 32);

	for(int i = 0; i < ARR_SIZE/2; i++) {
		res = al_delete(array, array->cnt-1, NULL); cr_expect(res == 0);
	}

	cr_assert_eq(array->size, 16);

	while(res == 0) {
		res = al_delete(array, array->cnt-1, NULL);
	}

	cr_assert_eq(array->size, 16);
	cr_assert_eq(array->cnt, 0);

	al_destroy_ptr(&array);
	free(arr);
}
