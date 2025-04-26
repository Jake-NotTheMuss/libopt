examples= fnv1a

I=-I..

CFLAGS=-g -Wall -Wpedantic -Wextra -ansi

test: fnv1a echo
	sh test.sh

fnv1a: fnv1a.c ../libopt.a
	$(CC) $(I) $(CFLAGS) -o $@ fnv1a.c ../libopt.a

echo: echo.c ../liboptf.a
	$(CC) $(I) $(CFLAGS) -o $@ echo.c ../liboptf.a

.PHONY: test
