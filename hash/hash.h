#ifndef HASH_H_
#define HASH_H_

typedef struct HashOpt {
	unsigned int initial_value;
	unsigned int sub_divider;
	unsigned int divider;
} HashOpt;

HashOpt hash_new(unsigned int divider);
HashOpt hash_build(unsigned int initial_value, unsigned int sub_divider, unsigned int divider);

// The argument len is not used, but is in the function to conform to the argument structure. The hashing will stop if the char will encounter a NUL Terminator.
__attribute__ ((nonnull (1, 2), access (read_only, 2)))
	unsigned int hash_str(HashOpt *opt, void *key, unsigned int len);

// NUL Terminator is ignored in the void *. Instead, the hash is generated from the pointer to len with chars.
__attribute__ ((nonnull (1, 2), access (read_only, 2, 3)))
	unsigned int hash_strn(HashOpt *opt, void *key, unsigned int len);

__attribute__ ((nonnull (1, 2), access (read_only, 2)))
	unsigned int hash_str_v2(HashOpt *opt, void *key, unsigned int len);

__attribute__ ((nonnull (1, 2), access (read_only, 2, 3)))
	unsigned int hash_strn_v2(HashOpt *opt, void *key, unsigned int len);

#endif
