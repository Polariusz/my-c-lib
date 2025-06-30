#include <stdio.h>
#include <criterion/criterion.h>
#include "linked_list.h"

void dump_item(void *item)
{
	printf("%d", *(int*)item);
}

Test(init_destroy, simple)
{
	int res = 0;
	LinkedList ll;

	res = ll_new(&ll, &dump_item); cr_assert(res == 0);

	res = ll_destroy(&ll); cr_assert(res == 0);
	cr_assert(ll.root == NULL);
	cr_assert(ll.cnt == 0);
	cr_assert(ll.dump_item == NULL);
}

Test(init_ptr_destroy, simple)
{
	int res = 0;
	LinkedList *ll;

	res = ll_new_ptr(&ll, &dump_item); cr_assert(res == 0);

	res = ll_destroy_ptr(&ll); cr_assert(res == 0);
	cr_assert(NULL == ll);
}

Test(push, simple)
{
	int res = 0;
	LinkedList *ll;
	int a = 0;

	res = ll_new_ptr(&ll, &dump_item); cr_assert(res == 0);
	res = ll_push(ll, &a); cr_assert(res == 0);

	cr_assert_eq(ll->cnt, 1);

	res = ll_destroy_ptr(&ll); cr_assert(res == 0);
	cr_assert(NULL == ll);
}

Test(get, simple)
{
	int res = 0;
	LinkedList *ll;

	int a = 0;

	res = ll_new_ptr(&ll, &dump_item); cr_assert(res == 0);
	res = ll_push(ll, &a); cr_assert(res == 0);

	void *yoink = NULL;
	res = ll_get(ll, &yoink, 0); cr_assert(res == 0);
	cr_assert_eq(yoink, &a);

	cr_assert_eq(ll->cnt, 1);

	res = ll_destroy_ptr(&ll); cr_assert(res == 0);
	cr_assert(NULL == ll);
}

Test(insert, simple)
{
	int res = 0;
	LinkedList *ll;

	int a = 0;

	res = ll_new_ptr(&ll, &dump_item); cr_assert(res == 0);
	res = ll_insert(ll, &a, 0); cr_assert(res == 0);

	cr_assert_eq(ll->cnt, 1);

	res = ll_destroy_ptr(&ll); cr_assert(res == 0);
	cr_assert(NULL == ll);
}

Test(replace, simple)
 {
	int res = 0;
	LinkedList *ll;

	int a = 0;
	int b = 0;

	res = ll_new_ptr(&ll, &dump_item); cr_assert(res == 0);
	res = ll_push(ll, &a); cr_assert(res == 0);

	cr_assert_eq(ll->cnt, 1);

	res = ll_replace(ll, &b, 0); cr_assert(res == 0);
	cr_assert_eq(ll->cnt, 1);

	res = ll_destroy_ptr(&ll); cr_assert(res == 0);
	cr_assert(NULL == ll);
 }

Test(pop, simple)
{
	int res = 0;
	LinkedList *ll;

	int a = 0;

	res = ll_new_ptr(&ll, &dump_item); cr_assert(res == 0);
	res = ll_push(ll, &a); cr_assert(res == 0);

	void *yoink = NULL;
	res = ll_pop(ll, &yoink); cr_assert(res == 0);
	cr_assert_eq(yoink, &a);

	cr_assert_eq(ll->cnt, 0);

	res = ll_destroy_ptr(&ll); cr_assert(res == 0);
	cr_assert(NULL == ll);
}

Test(delete, simple)
{
	int res = 0;
	LinkedList *ll;

	int a = 0;

	res = ll_new_ptr(&ll, &dump_item); cr_assert(res == 0);
	res = ll_push(ll, &a); cr_assert(res == 0);

	void *yoink = NULL;
	res = ll_delete(ll, &yoink, 0); cr_assert(res == 0);
	cr_assert_eq(yoink, &a);

	cr_assert_eq(ll->cnt, 0);

	res = ll_destroy_ptr(&ll); cr_assert(res == 0);
	cr_assert(NULL == ll);
}
