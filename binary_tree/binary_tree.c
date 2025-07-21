#include <stdio.h>
#include <stdlib.h>

#include "../err_lvl/err_lvl.h"

typedef struct BinaryTreeNode {
	void *item;
	struct BinaryTreeNode *left;
	struct BinaryTreeNode *right;
} BinaryTreeNode;

typedef struct BinaryTree {
	BinaryTreeNode *root;
	unsigned int cnt;
	int (*cmp)(void *left, void *right);
} BinaryTree;

/* ---| CONSTRUCTOR |--- */
int bt_new(BinaryTree *bt, int (*cmp)(void *left, void *right))
{
	if(bt == NULL)
		return NULL_ERR;

	bt->root = NULL;
	bt->cnt = 0;
	bt->cmp = cmp;

	return NO_ERR;
}

int bt_new_ptr(BinaryTree **bt, int (*cmp)(void *left, void *right))
{
	if(bt == NULL)
		return NULL_ERR;

	return bt_new(*bt, cmp);
}

/* ---| DESTRUCTOR |--- */
int bt_destroy_nodes_r(BinaryTreeNode *btn)
{
	if(btn == NULL)
		return NO_ERR;

	if(btn->left != NULL)
		bt_destroy_nodes_r(btn->left);

	if(btn->right != NULL)
		bt_destroy_nodes_r(btn->right);

	btn->item = NULL;
	free(btn);

	return NO_ERR;
}

int bt_destroy(BinaryTree *bt)
{
	if(bt == NULL)
		return NULL_ERR;

	bt_destroy_nodes_r(bt->root);
	bt->cnt = 0;
	bt->cmp = NULL;

	return NO_ERR;
}

int bt_destroy_ptr(BinaryTree **bt)
{
	if(bt == NULL)
		return NULL_ERR;

	return bt_destroy(*bt);
}

int bt_dump_r(BinaryTreeNode *btn, void(*dump_item)(void *src))
{
	if(btn->left != NULL)
		bt_dump_r(btn->left, dump_item);

	printf("[");
	dump_item(btn->item);
	printf("] ");

	if(btn->right != NULL)
		bt_dump_r(btn->right, dump_item);

	return NO_ERR;
}

/* ---| CUSTOM |--- */
int bt_dump(BinaryTree *bt, void(*dump_item)(void *src))
{
	bt_dump_r(bt->root, dump_item);
	printf("\n");
	return NO_ERR;
}

/* ---| CREATE |--- */
int bt_add_r(BinaryTreeNode **btn, void *item, int (*cmp)(void *left, void *right))
{
	if(*btn == NULL) {
		*btn = malloc(sizeof(BinaryTreeNode));
		if(*btn == NULL)
			return MEM_ERR;

		(*btn)->item = item;
		(*btn)->left = NULL;
		(*btn)->right = NULL;

		return NO_ERR;
	}

	if(cmp((*btn)->item, item) > 0) {
		int err = bt_add_r(&(*btn)->left, item, cmp);
		if(err != NO_ERR)
			return err;
	} else if(cmp((*btn)->item, item) < 0) {
		int err = bt_add_r(&(*btn)->right, item, cmp);
		if(err != NO_ERR)
			return err;
	} else {
		return ARG_ERR;
	}

	return NO_ERR;
}

int bt_add(BinaryTree *bt, void *item)
{
	return bt_add_r(&bt->root, item, bt->cmp);
}

/* ---| READ |--- */
int bt_get(BinaryTree *bt, unsigned int idx, void **dest);

/* ---| UPDATE |--- */
int bt_swap_nodes(BinaryTree *bt, unsigned int idx);
int bt_replace(BinaryTree *bt, unsigned int idx, void *item);

/* ---| DELETE |--- */
int bt_delete_node(BinaryTree *bt, void *item);
int bt_delete_nodes(BinaryTree *bt, void *item);
