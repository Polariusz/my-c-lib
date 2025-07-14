#include <stdlib.h>

#include "../err_lvl/err_lvl.h"
#include "../hash/hash.h"

typedef struct GenericFunctions {
	int (*to_cstring)(void *src, char *dest, unsigned int len);
	int (*hash)(HashOpt *opt, void *key, unsigned int len);
	int (*cmp)(void *left, void *right);
} GenericFunctions;

int gf_new(
	GenericFunctions *gf,
	int (*to_cstring)(void *src, char *dest, unsigned int len),
	int (*hash)(HashOpt *opt, void *key, unsigned int len),
	int (*cmp)(void *left, void *right)
) {
	if(gf == NULL)
		return NULL_ERR;

	gf->to_cstring = to_cstring;
	gf->hash = hash;
	gf->cmp = cmp;

	return NO_ERR;
}

int gf_new_ptr (
	GenericFunctions **gf,
	int (*to_cstring)(void *src, char *dest, unsigned int len),
	int (*hash)(HashOpt *opt, void *key, unsigned int len),
	int (*cmp)(void *left, void *right)
) {
	if(gf == NULL)
		return NULL_ERR;

	*gf = malloc(sizeof(GenericFunctions));
	if(gf == NULL)
		return MEM_ERR;

	return gf_new(*gf, to_cstring, hash, cmp);
}

int gf_destroy(GenericFunctions *gf)
{
	if(gf == NULL)
		return NULL_ERR;

	gf->to_cstring = NULL;
	gf->hash = NULL;
	gf->cmp = NULL;

	return NO_ERR;
}

int gf_destroy_ptr(GenericFunctions **gf)
{
	if(gf == NULL)
		return NULL_ERR;

	int res = gf_destroy(*gf);
	if(res != NO_ERR)
		return res;

	free(*gf);
	*gf = NULL;

	return NO_ERR;
}
