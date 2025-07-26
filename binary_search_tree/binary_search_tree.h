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
int bst_new(BinarySearchTree *bst, int (*cmp)(void *left, void *right));
int bst_new_ptr(BinarySearchTree **bst, int (*cmp)(void *left, void *right));

/* ---| DESTRUCTOR |--- */
int bst_destroy(BinarySearchTree *bst);
int bst_destroy_ptr(BinarySearchTree **bst);

/* ---| CUSTOM |--- */
int bst_dump(BinarySearchTree *bst, void(*dump_item)(void *src));

/* ---| CREATE |--- */
int bst_add(BinarySearchTree *bst, void *item);

/* ---| READ |--- */
int bst_search_node(BinarySearchTree *bst, void *src, BinarySearchTreeNode **dest);
int bst_search_parent(BinarySearchTree *bst, void *item, BinarySearchTreeNode **dest);

/* ---| DELETE |--- */
int bst_delete_node(BinarySearchTree *bst, void *item);
int bst_delete_nodes(BinarySearchTree *bst, void *item);

#endif
