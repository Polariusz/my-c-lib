typedef struct HashOpt {
	unsigned int initial_value;
	unsigned int sub_divider;
	unsigned int divider;
} HashOpt;

unsigned int hash_single(HashOpt *opt, unsigned long long key)
{
	return ((opt->initial_value + key) % opt->sub_divider) % opt->divider;
}

unsigned int hash_char(HashOpt *opt, unsigned char key)
{
	return hash_single(opt, (unsigned long long)key);
}

unsigned int hash_short(HashOpt *opt, unsigned short key)
{
	return hash_single(opt, (unsigned long long)key);
}

unsigned int hash_int(HashOpt *opt, unsigned int key)
{
	return hash_single(opt, (unsigned long long)key);
}

unsigned int hash_long(HashOpt *opt, unsigned long key)
{
	return hash_single(opt, (unsigned long long)key);
}

unsigned int hash_long_long(HashOpt *opt, unsigned long long key)
{
	return hash_single(opt, key);
}

unsigned int hash_cstring(HashOpt *opt, char *key, unsigned int len)
{
	unsigned int res = opt->initial_value;

	while(*key != '\0' && len > 0) {
		res = (res + ((unsigned int)*key)) % opt->sub_divider;
		--len;
		++key;
	}

	return res % opt->divider;
}
