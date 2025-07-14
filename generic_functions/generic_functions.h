#ifndef GENERIC_FUNCTIONS_H_
#define GENERIC_FUNCTIONS_H_

#include "../hash/hash.h"

typedef struct GenericFunctions {
	int (*to_cstring)(void *src, char *dest, unsigned int len);
	unsigned int (*hash)(HashOpt *opt, void *key, unsigned int len);
	int (*cmp)(void *left, void *right);
} GenericFunctions;

__attribute__ ((nonnull (1)))
	int gf_new(
		GenericFunctions *gf,
		int (*to_cstring)(void *src, char *dest, unsigned int len),
		unsigned int (*hash)(HashOpt *opt, void *key, unsigned int len),
		int (*cmp)(void *left, void *right)
	);

__attribute__ ((nonnull (1)))
	int gf_new_ptr (
		GenericFunctions **gf,
		int (*to_cstring)(void *src, char *dest, unsigned int len),
		unsigned int (*hash)(HashOpt *opt, void *key, unsigned int len),
		int (*cmp)(void *left, void *right)
	);

__attribute__ ((nonnull (1)))
	int gf_destroy(GenericFunctions *gf);

__attribute__ ((nonnull (1)))
	int gf_destroy_ptr(GenericFunctions **gf);

#endif
