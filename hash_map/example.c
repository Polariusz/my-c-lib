#include <stdio.h>
#include <string.h>
#include "hash_map.h"

int main(void)
{
	// Declare and initialise new Hash Map:
	HashMap hm;
	hm_new(&hm, 1000, &hash_strn_v2, (int(*)(void*, void*))&strcmp);

	// Add few key vals
	KeyVal kv1 = {"Key", "one", 4, 4};
	hm_add(&hm, &kv1);

	KeyVal kv2 = {"Oraoraora", "Jot", 10, 4};
	hm_add(&hm, &kv2);

	// We can retrieve values as such:
	KeyVal kvYoink1 = {"Key", NULL, 4, 0};
	hm_get(&hm, &kvYoink1);

	// kvYoink.val == "one"
	printf("Key: '%s', Val: '%s'\n", (char*)kvYoink1.key, (char*)kvYoink1.val);

	KeyVal kvYoink2 = {"Oraoraora", NULL, 10, 0};
	hm_get(&hm, &kvYoink2);

	// kvYoink.val == "Jot"
	printf("Key: '%s', Val: '%s'\n", (char*)kvYoink2.key, (char*)kvYoink2.val);

	// Note that adding the same key will result in an err:
	KeyVal kv3 = {"Key", "foo", 4, 4};
	if(int err = hm_add(&hm, &kv3); err != 0)
		printf("Key: '%s' is already in the hash map.\n", (char*)kv3.key);

	// Note that trying to get a value from a non existing key will result in an err:
	KeyVal kv4 = {"Dio Brando", NULL, 10, 0};
	if(int err = hm_get(&hm, &kv4); err != 0)
		printf("Key: '%s' does not exists.\n", (char*)kv4.key);

	// We can delete an entry as such:
	KeyVal kvYoink3 = {"Key", NULL, 4, 0};
	hm_delete(&hm, &kvYoink3);
	// The deletion writes the val and val_len into the KeyVal argument.

	// Now getting the entry with key "Key" will result in an err:
	if(int err = hm_get(&hm, &kvYoink3); err != 0)
		printf("Key: '%s' does not exists.\n", (char*)kvYoink3.key);

	// HashMap destructor
	hm_destroy(&hm);

	printf("Just Monika\n");
	return 0;
}
