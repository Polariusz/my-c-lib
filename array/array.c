typedef struct Array {
	void *item;
	int cnt;
	int size;
} Array;

Array new_array(void);
Array insert(void);
