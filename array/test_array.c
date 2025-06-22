#include <criterion/criterion.h>
#include "array.h"
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

Test(array_add_suffix, complex)
{
	Array *array = NULL; array_new_ptr(&array);
	int *arr = init_int_arr(3);
	int res = 0;
	void *yoinker = NULL;
	
	res = array_add_suffix(array, &arr[0]); cr_expect(res == 0);
	res = array_get(&yoinker, array, 0); cr_expect(res == 0);
	cr_assert_eq(yoinker, &arr[0]);

	res = array_add_suffix(array, &arr[1]); cr_expect(res == 0);
	res = array_get(&yoinker, array, 0); cr_expect(res == 0);
	cr_assert_eq(yoinker, &arr[0]);
	res = array_get(&yoinker, array, 1); cr_expect(res == 0);
	cr_assert_eq(yoinker, &arr[1]);

	res = array_add_suffix(array, &arr[2]); cr_expect(res == 0);
	res = array_get(&yoinker, array, 0); cr_expect(res == 0);
	cr_assert_eq(yoinker, &arr[0]);
	res = array_get(&yoinker, array, 1); cr_expect(res == 0);
	cr_assert_eq(yoinker, &arr[1]);
	res = array_get(&yoinker, array, 2); cr_expect(res == 0);
	cr_assert_eq(yoinker, &arr[2]);

	res = array_destroy_ptr(&array); cr_expect(res == 0);
	free(arr);
}

Test(array_add_prefix, complex)
{
	Array *array = NULL; array_new_ptr(&array);
	int *arr = init_int_arr(3);
	int res = 0;
	void *yoinker = NULL;

	res = array_add_prefix(array, &arr[0]); cr_expect(res == 0);
	res = array_get(&yoinker, array, 0); cr_expect(res == 0);
	cr_assert_eq(yoinker, &arr[0]);

	res = array_add_prefix(array, &arr[1]); cr_expect(res == 0);
	res = array_get(&yoinker, array, 0); cr_expect(res == 0);
	cr_assert_eq(yoinker, &arr[1]);
	res = array_get(&yoinker, array, 1); cr_expect(res == 0);
	cr_assert_eq(yoinker, &arr[0]);

	res = array_add_prefix(array, &arr[2]); cr_expect(res == 0);
	res = array_get(&yoinker, array, 0); cr_expect(res == 0);
	cr_assert_eq(yoinker, &arr[2]);
	res = array_get(&yoinker, array, 1); cr_expect(res == 0);
	cr_assert_eq(yoinker, &arr[1]);
	res = array_get(&yoinker, array, 2); cr_expect(res == 0);
	cr_assert_eq(yoinker, &arr[0]);

	res = array_destroy_ptr(&array); cr_expect(res == 0);
	free(arr);
}

Test(array_insert, complex)
{
	Array *array = NULL;
	int *arr = init_int_arr(64);
	int res = 0;
	void *yoinker = NULL;

	array_new_ptr(&array);
	
	res = array_add_suffix(array, &arr[0]); cr_expect(res =! 0);
	res = array_add_suffix(array, &arr[1]); cr_expect(res =! 0);
	res = array_add_suffix(array, &arr[2]); cr_expect(res =! 0);
	res = array_add_suffix(array, &arr[3]); cr_expect(res =! 0);
	res = array_add_suffix(array, &arr[4]); cr_expect(res =! 0);
	res = array_add_suffix(array, &arr[5]); cr_expect(res =! 0);
	res = array_add_suffix(array, &arr[6]); cr_expect(res =! 0);
	res = array_add_suffix(array, &arr[7]); cr_expect(res =! 0);
	res = array_add_suffix(array, &arr[8]); cr_expect(res =! 0);
	res = array_add_suffix(array, &arr[9]); cr_expect(res =! 0);

	res = array_insert(array, &arr[10], 0); cr_expect(res =! 0);
	res = array_get(&yoinker, array, 0); cr_expect(res == 0);
	cr_assert_eq(yoinker, &arr[10]);

	res = array_insert(array, &arr[11], 3); cr_expect(res =! 0);
	res = array_get(&yoinker, array, 3); cr_expect(res == 0);
	cr_assert_eq(yoinker, &arr[11]);

	res = array_insert(array, &arr[12], 9); cr_expect(res =! 0);
	res = array_get(&yoinker, array, 9); cr_expect(res == 0);
	cr_assert_eq(yoinker, &arr[12]);

	res = array_insert(array, &arr[13], 9); cr_expect(res =! 0);
	res = array_get(&yoinker, array, 9); cr_expect(res == 0);
	cr_assert_eq(yoinker, &arr[13]);

	array_get(&yoinker, array, 0); cr_assert_eq(yoinker, &arr[10]);
	array_get(&yoinker, array, 1); cr_assert_eq(yoinker, &arr[0]);
	array_get(&yoinker, array, 2); cr_assert_eq(yoinker, &arr[1]);
	array_get(&yoinker, array, 3); cr_assert_eq(yoinker, &arr[11]);
	array_get(&yoinker, array, 4); cr_assert_eq(yoinker, &arr[2]);
	array_get(&yoinker, array, 5); cr_assert_eq(yoinker, &arr[3]);
	array_get(&yoinker, array, 6); cr_assert_eq(yoinker, &arr[4]);
	array_get(&yoinker, array, 7); cr_assert_eq(yoinker, &arr[5]);
	array_get(&yoinker, array, 8); cr_assert_eq(yoinker, &arr[6]);
	array_get(&yoinker, array, 9); cr_assert_eq(yoinker, &arr[13]);
	array_get(&yoinker, array, 10); cr_assert_eq(yoinker, &arr[12]);
	array_get(&yoinker, array, 11); cr_assert_eq(yoinker, &arr[7]);
	array_get(&yoinker, array, 12); cr_assert_eq(yoinker, &arr[8]);
	array_get(&yoinker, array, 13); cr_assert_eq(yoinker, &arr[9]);

	array_destroy_ptr(&array);
	free(arr);
}

Test(array_update, complex)
{
	Array *array = NULL;
	int *arr = init_int_arr(64);
	int res = 0;
	void *yoinker = NULL;

	array_new_ptr(&array);
	
	res = array_add_suffix(array, &arr[0]); cr_expect(res =! 0);
	res = array_add_suffix(array, &arr[1]); cr_expect(res =! 0);
	res = array_add_suffix(array, &arr[2]); cr_expect(res =! 0);
	res = array_add_suffix(array, &arr[3]); cr_expect(res =! 0);
	res = array_add_suffix(array, &arr[4]); cr_expect(res =! 0);
	res = array_add_suffix(array, &arr[5]); cr_expect(res =! 0);
	res = array_add_suffix(array, &arr[6]); cr_expect(res =! 0);
	res = array_add_suffix(array, &arr[7]); cr_expect(res =! 0);
	res = array_add_suffix(array, &arr[8]); cr_expect(res =! 0);
	res = array_add_suffix(array, &arr[9]); cr_expect(res =! 0);

	res = array_insert(array, &arr[10], 0); cr_expect(res =! 0);
	res = array_insert(array, &arr[11], 3); cr_expect(res =! 0);
	res = array_insert(array, &arr[12], 9); cr_expect(res =! 0);
	res = array_insert(array, &arr[13], 9); cr_expect(res =! 0);

	res = array_add_prefix(array, &arr[14]); cr_expect(res =! 0);
	res = array_add_prefix(array, &arr[15]); cr_expect(res =! 0);
	res = array_add_prefix(array, &arr[16]); cr_expect(res =! 0);

	res = array_add_suffix(array, &arr[17]); cr_expect(res =! 0);
	res = array_add_suffix(array, &arr[18]); cr_expect(res =! 0);

	res = array_replace(array, &arr[19], 10); cr_expect(res =! 0);
	res = array_replace(array, &arr[20], 6); cr_expect(res =! 0);

	array_get(&yoinker, array, 0); cr_assert_eq(yoinker, &arr[16]);
	array_get(&yoinker, array, 1); cr_assert_eq(yoinker, &arr[15]);
	array_get(&yoinker, array, 2); cr_assert_eq(yoinker, &arr[14]);
	array_get(&yoinker, array, 3); cr_assert_eq(yoinker, &arr[10]);
	array_get(&yoinker, array, 4); cr_assert_eq(yoinker, &arr[0]);
	array_get(&yoinker, array, 5); cr_assert_eq(yoinker, &arr[1]);
	array_get(&yoinker, array, 6); cr_assert_eq(yoinker, &arr[20]);
	array_get(&yoinker, array, 7); cr_assert_eq(yoinker, &arr[2]);
	array_get(&yoinker, array, 8); cr_assert_eq(yoinker, &arr[3]);
	array_get(&yoinker, array, 9); cr_assert_eq(yoinker, &arr[4]);
	array_get(&yoinker, array, 10); cr_assert_eq(yoinker, &arr[19]);
	array_get(&yoinker, array, 11); cr_assert_eq(yoinker, &arr[6]);
	array_get(&yoinker, array, 12); cr_assert_eq(yoinker, &arr[13]);
	array_get(&yoinker, array, 13); cr_assert_eq(yoinker, &arr[12]);
	array_get(&yoinker, array, 14); cr_assert_eq(yoinker, &arr[7]);
	array_get(&yoinker, array, 15); cr_assert_eq(yoinker, &arr[8]);
	array_get(&yoinker, array, 16); cr_assert_eq(yoinker, &arr[9]);
	array_get(&yoinker, array, 17); cr_assert_eq(yoinker, &arr[17]);
	array_get(&yoinker, array, 18); cr_assert_eq(yoinker, &arr[18]);

	array_destroy_ptr(&array);
	free(arr);
}
