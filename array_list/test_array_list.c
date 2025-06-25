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
	res = al_get(&yoinker, array, 0); cr_expect(res == 0);
	cr_assert_eq(yoinker, &arr[0]);

	res = al_add_suffix(array, &arr[1]); cr_expect(res == 0);
	res = al_get(&yoinker, array, 0); cr_expect(res == 0);
	cr_assert_eq(yoinker, &arr[0]);
	res = al_get(&yoinker, array, 1); cr_expect(res == 0);
	cr_assert_eq(yoinker, &arr[1]);

	res = al_add_suffix(array, &arr[2]); cr_expect(res == 0);
	res = al_get(&yoinker, array, 0); cr_expect(res == 0);
	cr_assert_eq(yoinker, &arr[0]);
	res = al_get(&yoinker, array, 1); cr_expect(res == 0);
	cr_assert_eq(yoinker, &arr[1]);
	res = al_get(&yoinker, array, 2); cr_expect(res == 0);
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
	res = al_get(&yoinker, array, 0); cr_expect(res == 0);
	cr_assert_eq(yoinker, &arr[0]);

	res = al_add_prefix(array, &arr[1]); cr_expect(res == 0);
	res = al_get(&yoinker, array, 0); cr_expect(res == 0);
	cr_assert_eq(yoinker, &arr[1]);
	res = al_get(&yoinker, array, 1); cr_expect(res == 0);
	cr_assert_eq(yoinker, &arr[0]);

	res = al_add_prefix(array, &arr[2]); cr_expect(res == 0);
	res = al_get(&yoinker, array, 0); cr_expect(res == 0);
	cr_assert_eq(yoinker, &arr[2]);
	res = al_get(&yoinker, array, 1); cr_expect(res == 0);
	cr_assert_eq(yoinker, &arr[1]);
	res = al_get(&yoinker, array, 2); cr_expect(res == 0);
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

	res = al_insert(array, &arr[10], 0); cr_expect(res =! 0);
	res = al_get(&yoinker, array, 0); cr_expect(res == 0);
	cr_assert_eq(yoinker, &arr[10]);

	res = al_insert(array, &arr[11], 3); cr_expect(res =! 0);
	res = al_get(&yoinker, array, 3); cr_expect(res == 0);
	cr_assert_eq(yoinker, &arr[11]);

	res = al_insert(array, &arr[12], 9); cr_expect(res =! 0);
	res = al_get(&yoinker, array, 9); cr_expect(res == 0);
	cr_assert_eq(yoinker, &arr[12]);

	res = al_insert(array, &arr[13], 9); cr_expect(res =! 0);
	res = al_get(&yoinker, array, 9); cr_expect(res == 0);
	cr_assert_eq(yoinker, &arr[13]);

	al_get(&yoinker, array, 0); cr_assert_eq(yoinker, &arr[10]);
	al_get(&yoinker, array, 1); cr_assert_eq(yoinker, &arr[0]);
	al_get(&yoinker, array, 2); cr_assert_eq(yoinker, &arr[1]);
	al_get(&yoinker, array, 3); cr_assert_eq(yoinker, &arr[11]);
	al_get(&yoinker, array, 4); cr_assert_eq(yoinker, &arr[2]);
	al_get(&yoinker, array, 5); cr_assert_eq(yoinker, &arr[3]);
	al_get(&yoinker, array, 6); cr_assert_eq(yoinker, &arr[4]);
	al_get(&yoinker, array, 7); cr_assert_eq(yoinker, &arr[5]);
	al_get(&yoinker, array, 8); cr_assert_eq(yoinker, &arr[6]);
	al_get(&yoinker, array, 9); cr_assert_eq(yoinker, &arr[13]);
	al_get(&yoinker, array, 10); cr_assert_eq(yoinker, &arr[12]);
	al_get(&yoinker, array, 11); cr_assert_eq(yoinker, &arr[7]);
	al_get(&yoinker, array, 12); cr_assert_eq(yoinker, &arr[8]);
	al_get(&yoinker, array, 13); cr_assert_eq(yoinker, &arr[9]);

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

	res = al_insert(array, &arr[10], 0); cr_expect(res =! 0);
	res = al_insert(array, &arr[11], 3); cr_expect(res =! 0);
	res = al_insert(array, &arr[12], 9); cr_expect(res =! 0);
	res = al_insert(array, &arr[13], 9); cr_expect(res =! 0);

	res = al_add_prefix(array, &arr[14]); cr_expect(res =! 0);
	res = al_add_prefix(array, &arr[15]); cr_expect(res =! 0);
	res = al_add_prefix(array, &arr[16]); cr_expect(res =! 0);

	res = al_add_suffix(array, &arr[17]); cr_expect(res =! 0);
	res = al_add_suffix(array, &arr[18]); cr_expect(res =! 0);

	res = al_replace(array, &arr[19], 10); cr_expect(res =! 0);
	res = al_replace(array, &arr[20], 6); cr_expect(res =! 0);

	al_get(&yoinker, array, 0); cr_assert_eq(yoinker, &arr[16]);
	al_get(&yoinker, array, 1); cr_assert_eq(yoinker, &arr[15]);
	al_get(&yoinker, array, 2); cr_assert_eq(yoinker, &arr[14]);
	al_get(&yoinker, array, 3); cr_assert_eq(yoinker, &arr[10]);
	al_get(&yoinker, array, 4); cr_assert_eq(yoinker, &arr[0]);
	al_get(&yoinker, array, 5); cr_assert_eq(yoinker, &arr[1]);
	al_get(&yoinker, array, 6); cr_assert_eq(yoinker, &arr[20]);
	al_get(&yoinker, array, 7); cr_assert_eq(yoinker, &arr[2]);
	al_get(&yoinker, array, 8); cr_assert_eq(yoinker, &arr[3]);
	al_get(&yoinker, array, 9); cr_assert_eq(yoinker, &arr[4]);
	al_get(&yoinker, array, 10); cr_assert_eq(yoinker, &arr[19]);
	al_get(&yoinker, array, 11); cr_assert_eq(yoinker, &arr[6]);
	al_get(&yoinker, array, 12); cr_assert_eq(yoinker, &arr[13]);
	al_get(&yoinker, array, 13); cr_assert_eq(yoinker, &arr[12]);
	al_get(&yoinker, array, 14); cr_assert_eq(yoinker, &arr[7]);
	al_get(&yoinker, array, 15); cr_assert_eq(yoinker, &arr[8]);
	al_get(&yoinker, array, 16); cr_assert_eq(yoinker, &arr[9]);
	al_get(&yoinker, array, 17); cr_assert_eq(yoinker, &arr[17]);
	al_get(&yoinker, array, 18); cr_assert_eq(yoinker, &arr[18]);

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

	res = al_get(&yoink, array, 0); cr_expect(res != 0);
	res = al_get(&yoink, array, 1); cr_expect(res != 0);

	al_add_suffix(array, &a);
	res = al_get(&yoink, array, 0); cr_expect(res == 0);
	res = al_get(&yoink, array, 1); cr_expect(res != 0);
	res = al_get(&yoink, array, 2); cr_expect(res != 0);

	al_add_suffix(array, &b);
	res = al_get(&yoink, array, 0); cr_expect(res == 0);
	res = al_get(&yoink, array, 1); cr_expect(res == 0);
	res = al_get(&yoink, array, 2); cr_expect(res != 0);
	res = al_get(&yoink, array, 3); cr_expect(res != 0);

	al_add_suffix(array, &c);
	res = al_get(&yoink, array, 0); cr_expect(res == 0);
	res = al_get(&yoink, array, 1); cr_expect(res == 0);
	res = al_get(&yoink, array, 2); cr_expect(res == 0);
	res = al_get(&yoink, array, 3); cr_expect(res != 0);
	res = al_get(&yoink, array, 4); cr_expect(res != 0);

	al_destroy_ptr(&array);
}

Test(al_delete, complex) {
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

	res = al_delete(NULL, array, 3); cr_expect(res != 0);
	res = al_delete(NULL, array, 2); cr_expect(res == 0);
	res = al_delete(NULL, array, 0); cr_expect(res == 0);
	res = al_delete(&yoink, array, 0); cr_expect(res == 0);
	cr_assert_eq(yoink, &b);
	res = al_delete(&yoink, array, 0); cr_expect(res != 0);

	al_destroy_ptr(&array);
}
