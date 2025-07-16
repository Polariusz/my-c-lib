CC		= gcc
CFLAGS	= -Wall -Wextra
CLIBS	= -lcriterion
CPATHS	= ./hash_map.c ../hash/hash.c ../generic_functions/generic_functions.c ../linked_list/linked_list.c ../err_lvl/err_lvl.c
TSRC	= ./test_hash_map.c
TOUT	= test.out
MSRC	= ./main.c
MOUT	= main.out
ESRC	= ./example.c
EOUT	= example.out

test:
	$(CC) $(TSRC) $(CFLAGS) $(CLIBS) $(CPATHS) -o $(TOUT)

example:
	$(CC) $(ESRC) $(CFLAGS) $(CPATHS) -o $(EOUT)

main:
	$(CC) $(MSRC) $(CFLAGS) $(CPATHS) -o $(MOUT)
