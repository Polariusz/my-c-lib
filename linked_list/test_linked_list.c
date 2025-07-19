#include <stdio.h>
#include <criterion/criterion.h>
#include "linked_list.h"

void dump_item(char *buf, void *item)
{
	int foo = *(int*)item;
	sprintf(buf, "%d", foo);
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
	res = ll_get(ll, 0, &yoink); cr_assert(res == 0);
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
	res = ll_insert(ll, 0, &a); cr_assert(res == 0);

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

	res = ll_delete(ll, 0); cr_assert(res == 0);

	cr_assert_eq(ll->cnt, 0);

	res = ll_destroy_ptr(&ll); cr_assert(res == 0);
	cr_assert(NULL == ll);
}

Test(crud, complex)
{
	int res = 0;
	LinkedList *ll;
	int a = 0;
	int b = 10;
	int c = 20;
	int d = 30;
	int e = 40;

	res = ll_new_ptr(&ll, &dump_item); cr_assert(res == 0);
	res = ll_push(ll, &a); cr_assert(res == 0);      // 0 -> NULL
	res = ll_insert(ll, 1, &b); cr_assert(res == 0); // 0 -> 10 -> NULL
	res = ll_push(ll, &c); cr_assert(res == 0);      // 20 -> 0 -> 10 -> NULL
	res = ll_insert(ll, 2, &d); cr_assert(res == 0); // 20 -> 0 -> 30 -> 10 -> NULL

	void *yoink = NULL;
	res = ll_get(ll, 0, &yoink); cr_assert(res == 0);
	cr_assert_eq(yoink, &c);

	res = ll_get(ll, 1, &yoink); cr_assert(res == 0);
	cr_assert_eq(yoink, &a);

	res = ll_get(ll, 2, &yoink); cr_assert(res == 0);
	cr_assert_eq(yoink, &d);

	res = ll_get(ll, 3, &yoink); cr_assert(res == 0);
	cr_assert_eq(yoink, &b);

	res = ll_replace(ll, &e, 3); cr_assert(res == 0); // 20 -> 0 -> 30 -> 40 -> NULL
	res = ll_get(ll, 3, &yoink); cr_assert(res == 0);
	cr_assert_neq(yoink, &b);
	cr_assert_eq(yoink, &e);

	res = ll_pop(ll, NULL); cr_assert(res == 0); // 0 -> 30 -> 40 -> NULL
	res = ll_delete(ll, 1); cr_assert(res == 0); // 0 -> 40 -> NULL

	res = ll_destroy_ptr(&ll); cr_assert(res == 0);
	cr_assert(NULL == ll);
}

Test(delete, curious)
{
	int res = 0;
	LinkedList *ll; res = ll_new_ptr(&ll, &dump_item); cr_assert(res == 0);
	int a = 0;
	int b = 10;
	int c = 20;

	res = ll_push(ll, &a); cr_assert(res == 0);
	res = ll_push(ll, &b); cr_assert(res == 0);
	res = ll_push(ll, &c); cr_assert(res == 0);

	void *yoink = NULL;
	res = ll_get(ll, 1, &yoink); cr_assert(res == 0);
	cr_assert_eq(yoink, &b);

	res = ll_delete(ll, 1); cr_assert(res == 0);
	res = ll_delete(ll, 1); cr_assert(res == 0);
	res = ll_delete(ll, 0); cr_assert(res == 0);

	cr_assert_eq(yoink, &b);

	res = ll_destroy_ptr(&ll); cr_assert(res == 0);
	cr_assert(NULL == ll);
}

Test(remove, simple)
{
	int res = 0;
	LinkedList *ll; res = ll_new_ptr(&ll, &dump_item); cr_assert(res == 0);
	int a = 0;
	int b = 10;
	int c = 20;

	res = ll_push(ll, &a); cr_assert(res == 0);
	res = ll_push(ll, &b); cr_assert(res == 0);
	res = ll_push(ll, &c); cr_assert(res == 0);

	void *yoink = NULL;
	res = ll_remove(ll, &yoink, 1);

	cr_assert_eq(&b, yoink);

	res = ll_destroy_ptr(&ll); cr_assert(res == 0);
	cr_assert(NULL == ll);
}
