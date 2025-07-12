enum HashType {
	HASH_CHAR,
	HASH_SHORT,
	HASH_INT,
	HASH_LONG,
	HASH_LONG_LONG,
	HASH_CSTRING,
};

typedef struct HashOpt {
	unsigned int initial_value; unsigned int sub_divider;
	unsigned int divider;
	enum HashType hash_type;
} HashOpt;

unsigned int hash_as_char(HashOpt *opt, unsigned char key)
{
	return ((opt->initial_value + key) % opt->sub_divider) % opt->divider;
}

unsigned int hash_as_short(HashOpt *opt, unsigned short key)
{
	return ((opt->initial_value + key) % opt->sub_divider) % opt->divider;
}

unsigned int hash_as_int(HashOpt *opt, unsigned int key)
{
	return ((opt->initial_value + key) % opt->sub_divider) % opt->divider;
}

unsigned int hash_as_long(HashOpt *opt, unsigned long key)
{
	return ((opt->initial_value + key) % opt->sub_divider) % opt->divider;
}

unsigned int hash_as_long_long(HashOpt *opt, unsigned long long key)
{
	return ((opt->initial_value + key) % opt->sub_divider) % opt->divider;
}

unsigned int hash_as_cstring(HashOpt *opt, char* key, unsigned int len)
{
	unsigned int res = opt->initial_value;

	while(*key != '\0' && len > 0) {
		res = (res + (*key)) % opt->sub_divider;
		--len;
		++key;
	}

	return res % opt->divider;
}

unsigned int hash_value(HashOpt *opt, void *key, unsigned int len)
{
	switch(opt->hash_type) {
		case HASH_CHAR:
			return hash_as_char(opt, *(unsigned char*)key);
		case HASH_SHORT:
			return hash_as_short(opt, *(unsigned short*)key);
		case HASH_INT:
			return hash_as_int(opt, *(unsigned int*)key);
		case HASH_LONG:
			return hash_as_long(opt, *(unsigned long*)key);
		case HASH_LONG_LONG:
			return hash_as_long_long(opt, *(unsigned long long*)key);
		case HASH_CSTRING:
			return hash_as_cstring(opt, (char*)key, len);
	}

	return -1;
}
