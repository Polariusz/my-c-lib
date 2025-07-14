#include <stdlib.h>

#include "../err_lvl/err_lvl.h"
#include "../hash/hash.h"

typedef struct GenericFunctions {
	unsigned int (*hash)(HashOpt *opt, void *key, unsigned int len);
	int (*cmp)(void *left, void *right);
	int (*to_cstring)(void *src, char *dest, unsigned int len);
} GenericFunctions;

int gf_new(
	GenericFunctions *gf,
	unsigned int (*hash)(HashOpt *opt, void *key, unsigned int len);
	int (*cmp)(void *left, void *right);
	int (*to_cstring)(void *src, char *dest, unsigned int len);
) {
	if(gf == NULL)
		return NULL_ERR;

	gf->hash = hash;
	gf->cmp = cmp;
	gf->to_cstring = to_cstring;

	return NO_ERR;
}

int gf_new_ptr (
	GenericFunctions **gf,
	unsigned int (*hash)(HashOpt *opt, void *key, unsigned int len);
	int (*cmp)(void *left, void *right);
	int (*to_cstring)(void *src, char *dest, unsigned int len);
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

	gf->hash = NULL;
	gf->cmp = NULL;
	gf->to_cstring = NULL;

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
