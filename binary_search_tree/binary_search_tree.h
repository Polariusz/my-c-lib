#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

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
int bt_new(BinarySearchTree *bt, int (*cmp)(void *left, void *right));
int bt_new_ptr(BinarySearchTree **bt, int (*cmp)(void *left, void *right));

/* ---| DESTRUCTOR |--- */
int bt_destroy(BinarySearchTree *bt);
int bt_destroy_ptr(BinarySearchTree **bt);

/* ---| CUSTOM |--- */
int bt_dump(BinarySearchTree *bt, void(*dump_item)(void *src));

/* ---| CREATE |--- */
int bt_add(BinarySearchTree *bt, void *item);

/* ---| READ |--- */
int bt_search(BinarySearchTree *bt, void *src, BinarySearchTreeNode **dest);

/* ---| DELETE |--- */
int bt_delete_node(BinarySearchTree *bt, void *item);
int bt_delete_nodes(BinarySearchTree *bt, void *item);

#endif
