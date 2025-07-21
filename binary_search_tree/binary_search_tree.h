#ifndef BINARY_TREE_H
#define BINARY_TREE_H

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
int bt_new(BinaryTree *bt, int (*cmp)(void *left, void *right));
int bt_new_ptr(BinaryTree **bt, int (*cmp)(void *left, void *right));

/* ---| DESTRUCTOR |--- */
int bt_destroy(BinaryTree *bt);
int bt_destroy_ptr(BinaryTree **bt);

/* ---| CUSTOM |--- */
int bt_dump(BinaryTree *bt, void(*dump_item)(void *src));

/* ---| CREATE |--- */
int bt_add(BinaryTree *bt, void *item);

/* ---| READ |--- */
int bt_get(BinaryTree *bt, unsigned int idx, void **dest);

/* ---| UPDATE |--- */
int bt_swap_nodes(BinaryTree *bt, unsigned int idx);
int bt_replace(BinaryTree *bt, unsigned int idx, void *item);

/* ---| DELETE |--- */
int bt_delete_node(BinaryTree *bt, void *item);
int bt_delete_nodes(BinaryTree *bt, void *item);

#endif
