#ifndef HASH_H_
#define HASH_H_

enum HashType {
	HASH_CHAR,
	HASH_SHORT,
	HASH_INT,
	HASH_LONG,
	HASH_LONG_LONG,
	HASH_STR,
	HASH_STRN,
	HASH_CUSTOM,
};

typedef struct HashOpt {
	unsigned int initial_value;
	unsigned int sub_divider;
	unsigned int divider;
	enum HashType hash_type;
	unsigned int (*hash_custom)(struct HashOpt *opt, void *key, unsigned int len);
} HashOpt;


__attribute__ ((nonnull (1)))
	unsigned int hash_char(HashOpt *opt, unsigned char key);

__attribute__ ((nonnull (1)))
	unsigned int hash_short(HashOpt *opt, unsigned short key);

__attribute__ ((nonnull (1)))
	unsigned int hash_int(HashOpt *opt, unsigned int key);

__attribute__ ((nonnull (1)))
	unsigned int hash_long(HashOpt *opt, unsigned long key);

__attribute__ ((nonnull (1)))
	unsigned int hash_long_long(HashOpt *opt, unsigned long long key);

__attribute__ ((nonnull (1, 2)))
	unsigned int hash_str(HashOpt *opt, unsigned char* key);

__attribute__ ((nonnull (1, 2), access (read_only, 2, 3)))
	unsigned int hash_strn(HashOpt *opt, unsigned char* key, unsigned int len);

__attribute__ ((nonnull (1, 2), access (read_only, 2, 3)))
	unsigned int hash_value(HashOpt *opt, void *key, unsigned int len);

#endif
