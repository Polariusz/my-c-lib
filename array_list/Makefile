CC		= gcc
CFLAGS	= -Wall -Wextra
CLIBS	= -lcriterion
CPATHS	= ./array_list.c ../err_lvl/err_lvl.c
TSRC	= ./test_array_list.c
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
