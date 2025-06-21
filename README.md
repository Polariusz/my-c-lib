### TODO:

#### Data Structures:

- Array

```C
/* ---| CREATE |--- */
int array_new(Array *array);
int array_build(Array *array, unsigned int size);

/* ---| READ |--- */
int array_get(void **dest, Array *src, unsigned int idx);

/* ---| UPDATE |--- */
int array_add_suffix(Array *src, void *item);
int array_add_prefix(Array *src, void *item);
int array_insert(Array *src, void *item, unsigned int idx);
Array array_replace(void); // TODO: This

/* ---| DELETE |--- */

Array array_delete(void); // TODO: This
```

- LinkedList
- BinaryTree

