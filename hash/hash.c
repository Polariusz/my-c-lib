enum HashType {
	HASH_CHAR,
	HASH_SHORT,
	HASH_INT,
	HASH_LONG,
	HASH_LONG_LONG,
	HASH_STR,
	HASH_STRN,
};

typedef struct HashOpt {
	unsigned int initial_value; unsigned int sub_divider;
	unsigned int divider;
	enum HashType hash_type;
} HashOpt;

unsigned int hash_char(HashOpt *opt, unsigned char key)
{
	return ((opt->initial_value + key) % opt->sub_divider) % opt->divider;
}

unsigned int hash_short(HashOpt *opt, unsigned short key)
{
	return ((opt->initial_value + key) % opt->sub_divider) % opt->divider;
}

unsigned int hash_int(HashOpt *opt, unsigned int key)
{
	return ((opt->initial_value + key) % opt->sub_divider) % opt->divider;
}

unsigned int hash_long(HashOpt *opt, unsigned long key)
{
	return ((opt->initial_value + key) % opt->sub_divider) % opt->divider;
}

unsigned int hash_long_long(HashOpt *opt, unsigned long long key)
{
	return ((opt->initial_value + key) % opt->sub_divider) % opt->divider;
}

unsigned int hash_str(HashOpt *opt, unsigned char* key)
{
	unsigned int res = opt->initial_value;

	while(*key != '\0') {
		res = (res + (*key)) % opt->sub_divider;
		++key;
	}

	return res % opt->divider;
}

unsigned int hash_strn(HashOpt *opt, unsigned char* key, unsigned int len)
{
	unsigned int res = opt->initial_value;
	while(len > 0) {
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
			return hash_char(opt, *(unsigned char*)key);
		case HASH_SHORT:
			return hash_short(opt, *(unsigned short*)key);
		case HASH_INT:
			return hash_int(opt, *(unsigned int*)key);
		case HASH_LONG:
			return hash_long(opt, *(unsigned long*)key);
		case HASH_LONG_LONG:
			return hash_long_long(opt, *(unsigned long long*)key);
		case HASH_STR:
			return hash_str(opt, (unsigned char*)key);
		case HASH_STRN:
			return hash_strn(opt, (unsigned char*)key, len);
	}

	return -1;
}
