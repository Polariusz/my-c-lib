#ifndef HASH_H_
#define HASH_H_

typedef struct HashOpt {
	unsigned int initial_value;
	unsigned int sub_divider;
	unsigned int divider;
} HashOpt;

__attribute__((nonnull (1)))
	unsigned int hash_char(HashOpt *opt, unsigned char key);

__attribute__((nonnull (1)))
	unsigned int hash_short(HashOpt *opt, unsigned short key);

__attribute__((nonnull (1)))
	unsigned int hash_int(HashOpt *opt, unsigned int key);

__attribute__((nonnull (1)))
	unsigned int hash_long(HashOpt *opt, unsigned long key);

__attribute__((nonnull (1)))
	unsigned int hash_long_long(HashOpt *opt, unsigned long long key);

__attribute__ ((nonnull (1), access (read_only, 2, 3)))
	unsigned int hash_cstring(HashOpt *opt, char *key, unsigned int len);

#endif
