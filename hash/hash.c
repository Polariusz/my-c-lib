typedef struct HashOpt {
	unsigned int initial_value;
	unsigned int sub_divider;
	unsigned int divider;
} HashOpt;

HashOpt hash_new(unsigned int d)
{
	unsigned int sd = (d * 2 - d / 10);
	unsigned int iv = sd * 9;

	return (HashOpt) {iv, sd, d};
}

HashOpt hash_build(unsigned int initial_value, unsigned int sub_divider, unsigned int divider)
{
	return (HashOpt) {initial_value, sub_divider, divider};
}

unsigned int hash_str(HashOpt *opt, void *key, unsigned int len)
{
	(void)len;
	unsigned int res = opt->initial_value;

	while(*(char*)key != '\0') {
		res = (res + (*(char*)key)) % opt->sub_divider;
		++key;
	}

	return res % opt->divider;
}

unsigned int hash_strn(HashOpt *opt, void *key, unsigned int len)
{
	unsigned int res = opt->initial_value;
	while(len > 0) {
		res = (res + (*(char*)key)) % opt->sub_divider;
		--len;
		++key;
	}

	return res % opt->divider;
}
