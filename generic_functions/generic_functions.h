#ifndef GENERIC_FUNCTIONS_H_
#define GENERIC_FUNCTIONS_H_

#include "../hash/hash.h"

typedef struct GenericFunctions {
	unsigned int (*hash)(HashOpt *opt, void *key, unsigned int len);
	int (*cmp)(void *left, void *right);
	int (*to_cstring)(void *src, char *dest, unsigned int len);
} GenericFunctions;

__attribute__ ((nonnull (1)))
	int gf_new(
		GenericFunctions *gf,
		unsigned int (*hash)(HashOpt *opt, void *key, unsigned int len),
		int (*cmp)(void *left, void *right),
		int (*to_cstring)(void *src, char *dest, unsigned int len)
	);

__attribute__ ((nonnull (1)))
	int gf_new_ptr (
		GenericFunctions **gf,
		unsigned int (*hash)(HashOpt *opt, void *key, unsigned int len),
		int (*cmp)(void *left, void *right),
		int (*to_cstring)(void *src, char *dest, unsigned int len)
	);

__attribute__ ((nonnull (1)))
	int gf_destroy(GenericFunctions *gf);

__attribute__ ((nonnull (1)))
	int gf_destroy_ptr(GenericFunctions **gf);

#endif
