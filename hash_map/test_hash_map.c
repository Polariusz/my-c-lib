#include <criterion/criterion.h>
#include <string.h>

#include "hash_map.h"

Test(hm_new__hm_destroy, simple)
{
	int err = 0;
	HashMap hm;

	err = hm_new(&hm, 1000, NULL, NULL); cr_assert(err != 0);
	err = hm_new(&hm, 1000, &hash_strn_v2, (int(*)(void*, void*))&strcmp); cr_assert(err == 0);

	err = hm_destroy(&hm); cr_assert(err == 0); }

Test(hm_new__ptr_hm_destroy_ptr, simple)
{
	int err = 0;
	HashMap *hm;

	err = hm_new_ptr(&hm, 1000, NULL, NULL); cr_assert(err != 0);
	err = hm_new_ptr(&hm, 1000, &hash_strn_v2, (int(*)(void*, void*))&strcmp); cr_assert(err == 0);

	err = hm_destroy_ptr(&hm); cr_assert(err == 0);
	cr_assert_eq(hm, NULL);
}

Test(hm_new_custom, simple)
{
	int err = 0;
	HashMap hm;
	HashOpt opt = {133, 99, 69};

	err = hm_new_custom(&hm, opt, 1000, NULL, NULL); cr_assert(err != 0);
	err = hm_new_custom(&hm, opt, 1000, &hash_strn_v2, (int(*)(void*, void*))&strcmp); cr_assert(err == 0);

	err = hm_destroy(&hm); cr_assert(err == 0);
}

Test(hm_new_custom_ptr, simple)
{
	int err = 0;
	HashMap *hm;
	HashOpt opt = {133, 99, 69};

	err = hm_new_custom_ptr(&hm, opt, 1000, NULL, NULL); cr_assert(err != 0);
	err = hm_new_custom_ptr(&hm, opt, 1000, &hash_strn_v2, (int(*)(void*, void*))&strcmp); cr_assert(err == 0);

	err = hm_destroy_ptr(&hm); cr_assert(err == 0);
	cr_assert_eq(hm, NULL);
}

Test(hm_add, simple)
{
	int err = 0;
	HashMap hm;

	hm_new(&hm, 1000, &hash_strn_v2, (int(*)(void*, void*))&strcmp);

	int a = 10;
	KeyVal kv1 = {"Book", &a, 5, sizeof(int)};
	err = hm_add(&hm, &kv1); cr_assert_eq(err, 0);

	int b = 6;
	KeyVal kv2 = {"Tome", &b, 5, sizeof(int)};
	err = hm_add(&hm, &kv2); cr_assert_eq(err, 0);

	int c = 16;
	KeyVal kv3 = {"Table", &c, 6, sizeof(int)};
	err = hm_add(&hm, &kv3); cr_assert_eq(err, 0);

	hm_destroy(&hm);
}

int u32cmp(void *left, void *right)
{
	return *(unsigned int*)left - *(unsigned int*)right;
}

Test(hm_get, simple)
{
	int err = 0;
	HashMap hm;

	hm_new(&hm, 1000, &hash_strn_v2, (int(*)(void*, void*))&strcmp);

	unsigned int a = 4294967295;
	KeyVal kv1 = {"Love", &a, 5, sizeof(int)};
	hm_add(&hm, &kv1);

	KeyVal yoink = {"Love", NULL, 5, 0};
	err = hm_get(&hm, &yoink); cr_assert_eq(err, 0);
	cr_assert_eq(&a, yoink.val);
	cr_assert_eq(sizeof(int), yoink.val_len);

	hm_destroy(&hm);
}

Test(hm_replace, simple)
{
	int err = 0;
	HashMap hm;

	hm_new(&hm, 1000, &hash_strn_v2, (int(*)(void*, void*))&strcmp);

	unsigned int a = 4294967295;
	KeyVal kv1 = {"Love", &a, 5, sizeof(int)};
	hm_add(&hm, &kv1);

	unsigned long b = 18446744073709551615UL;
	KeyVal kv2 = {"Love", &b, 5, sizeof(long)};
	err = hm_replace(&hm, &kv2); cr_assert_eq(err, 0);

	KeyVal yoink = {"Love", NULL, 5, 0};
	hm_get(&hm, &yoink);
	cr_assert_eq(&b, yoink.val);
	cr_assert_eq(sizeof(long), yoink.val_len);

	hm_destroy(&hm);
}

Test(hm_delete, simple)
{
	int err = 0;
	HashMap hm;

	hm_new(&hm, 1000, &hash_strn_v2, (int(*)(void*, void*))&strcmp);

	unsigned long a = 18446744073709551615UL;
	KeyVal kv1 = {"Love", &a, 5, sizeof(long)};
	hm_add(&hm, &kv1);

	KeyVal yoink = {"Love", NULL, 5, 0};
	err = hm_delete(&hm, &yoink); cr_assert_eq(err, 0);
	cr_assert_eq(&a, yoink.val);
	cr_assert_eq(sizeof(long), yoink.val_len);

	hm_destroy(&hm);
}

Test(hm, complex)
{
	int err = 0;
	HashMap hm;

	err = hm_new(&hm, 1000, &hash_strn_v2, (int(*)(void*, void*))&strcmp); cr_assert_eq(err, 0);

	KeyVal kv1 = {"Monika is Monikawaii", "Very Kawaii", 29, 11};
	KeyVal kv2 = {"Chocolate", "Caramel", 10, 8};
	KeyVal kv3 = {"Keyboard", "Keys", 9, 4};
	unsigned long a = 18446744073709551615UL;
	KeyVal kv4 = {"Love", &a, 5, sizeof(long)};
	char k5[] = "Zooming";
	KeyVal kv5 = {k5, "pretty fast", 8, 12};

	err = hm_add(&hm, &kv1); cr_assert_eq(err, 0);
	err = hm_add(&hm, &kv2); cr_assert_eq(err, 0);
	err = hm_add(&hm, &kv3); cr_assert_eq(err, 0);
	err = hm_add(&hm, &kv4); cr_assert_eq(err, 0);
	err = hm_add(&hm, &kv5); cr_assert_eq(err, 0);

	KeyVal kv2New = {"Chocolate", "Milk", 10, 5};
	KeyVal kvNone = {"Electric", "a", 9, 2};
	err = hm_replace(&hm, &kv2New); cr_assert_eq(err, 0);
	err = hm_replace(&hm, &kvNone); cr_assert_neq(err, 0);
	err = hm_delete(&hm, &kv3); cr_assert_eq(err, 0);
	err = hm_add(&hm, &kv3); cr_assert_eq(err, 0);
	err = hm_add(&hm, &kv3); cr_assert_neq(err, 0);
	err = hm_delete(&hm, &kv3); cr_assert_eq(err, 0);

	KeyVal yoink1 = {"Monika is Monikawaii", NULL, 29, 0};
	err = hm_get(&hm, &yoink1); cr_assert_eq(err, 0);
	cr_assert_eq(strcmp(yoink1.val, kv1.val), 0);

	KeyVal yoink2 = {"Chocolate", NULL, 10, 0};
	err = hm_get(&hm, &yoink2); cr_assert_eq(err, 0);
	cr_assert_neq(strcmp(yoink2.val, kv2.val), 0);
	cr_assert_eq(strcmp(yoink2.val, kv2New.val), 0);

	KeyVal yoink3 = {"Keyboard", NULL, 9, 0};
	err = hm_get(&hm, &yoink3); cr_assert_neq(err, 0);

	KeyVal yoink4 = {"Love", NULL, 5, 0};
	err = hm_get(&hm, &yoink4); cr_assert_eq(err, 0);
	cr_assert_eq(yoink4.val, &a);

	KeyVal yoink5 = {k5, NULL, 8, 0};
	err = hm_get(&hm, &yoink5); cr_assert_eq(err, 0);
	cr_assert_eq(strcmp(yoink5.val, kv5.val), 0);

	err = hm_destroy(&hm); cr_assert_eq(err, 0);
}
