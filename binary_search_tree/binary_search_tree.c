#include <stdio.h>
#include <stdlib.h>

#include "../err_lvl/err_lvl.h"

typedef struct BinarySearchTreeNode {
	void *item;
	struct BinarySearchTreeNode *left;
	struct BinarySearchTreeNode *right;
} BinarySearchTreeNode;

typedef struct BinarySearchTree {
	BinarySearchTreeNode *root;
	unsigned int cnt;
	int (*cmp)(void *left, void *right);
} BinarySearchTree;

/* ---| CONSTRUCTOR |--- */
int bst_new(BinarySearchTree *bst, int (*cmp)(void *left, void *right))
{
	if(bst == NULL)
		return NULL_ERR;

	bst->root = NULL;
	bst->cnt = 0;
	bst->cmp = cmp;

	return NO_ERR;
}

int bst_new_ptr(BinarySearchTree **bst, int (*cmp)(void *left, void *right))
{
	if(bst == NULL)
		return NULL_ERR;

	return bst_new(*bst, cmp);
}

/* ---| DESTRUCTOR |--- */
int bst_destroy_nodes_r(BinarySearchTreeNode *bstn)
{
	if(bstn == NULL)
		return NO_ERR;

	if(bstn->left != NULL)
		bst_destroy_nodes_r(bstn->left);

	if(bstn->right != NULL)
		bst_destroy_nodes_r(bstn->right);

	bstn->item = NULL;
	free(bstn);

	return NO_ERR;
}

int bst_destroy(BinarySearchTree *bst)
{
	if(bst == NULL)
		return NULL_ERR;

	bst_destroy_nodes_r(bst->root);
	bst->cnt = 0;
	bst->cmp = NULL;

	return NO_ERR;
}

int bst_destroy_ptr(BinarySearchTree **bst)
{
	if(bst == NULL)
		return NULL_ERR;

	return bst_destroy(*bst);
}

int bst_dump_r(BinarySearchTreeNode *bstn, void(*dump_item)(void *src))
{
	if(bstn->left != NULL)
		bst_dump_r(bstn->left, dump_item);

	printf("[");
	dump_item(bstn->item);
	printf("] ");

	if(bstn->right != NULL)
		bst_dump_r(bstn->right, dump_item);

	return NO_ERR;
}

/* ---| CUSTOM |--- */
int bst_dump(BinarySearchTree *bst, void(*dump_item)(void *src))
{
	bst_dump_r(bst->root, dump_item);
	printf("\n");
	return NO_ERR;
}

/* ---| CREATE |--- */
int bst_add_r(BinarySearchTreeNode **bstn, void *item, int (*cmp)(void *left, void *right))
{
	if(*bstn == NULL) {
		*bstn = malloc(sizeof(BinarySearchTreeNode));
		if(*bstn == NULL)
			return MEM_ERR;

		(*bstn)->item = item;
		(*bstn)->left = NULL;
		(*bstn)->right = NULL;

		return NO_ERR;
	}

	if(cmp((*bstn)->item, item) > 0) {
		int err = bst_add_r(&(*bstn)->left, item, cmp);
		if(err != NO_ERR)
			return err;
	} else if(cmp((*bstn)->item, item) < 0) {
		int err = bst_add_r(&(*bstn)->right, item, cmp);
		if(err != NO_ERR)
			return err;
	} else {
		return ARG_ERR;
	}

	return NO_ERR;
}

int bst_add(BinarySearchTree *bst, void *item)
{
	return bst_add_r(&bst->root, item, bst->cmp);
}

/* ---| READ |--- */
int bst_search_r(BinarySearchTreeNode **bstn, void *src, BinarySearchTreeNode **dest, int (*cmp)(void *left, void *right))
{
	if(bstn == NULL)
		return ARG_ERR;

	if(*bstn == NULL)
		return NULL_ERR;

	int res = cmp((*bstn)->item, src);

	if(res > 0) {
		return bst_search_r(&(*bstn)->left, src, dest, cmp);
	} else if(res < 0) {
		return bst_search_r(&(*bstn)->right, src, dest, cmp);
	} else {
		*dest = *bstn;
		return NO_ERR;
	}
}

int bst_search(BinarySearchTree *bst, void *src, BinarySearchTreeNode **dest)
{
	return bst_search_r(&bst->root, src, dest, bst->cmp);
}

/* ---| DELETE |--- */
int bst_delete_node(BinarySearchTree *bst, void *item);
int bst_delete_nodes(BinarySearchTree *bst, void *item);
