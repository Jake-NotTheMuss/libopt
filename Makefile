
CFLAGS=-g -Wall -Wpedantic -Wextra -ansi

all: libopt.a liboptf.a

libopt.a: opt.o
	ar rcs $@ opt.o

liboptf.a: opt.c opt.h
	$(CC) -c -DLIBOPT_SOLO -ffreestanding -nolibc $(CFLAGS) -o optf.o opt.c
	ar rcs $@ optf.o

opt.o: opt.c opt.h

clean:
	rm -f libopt.a liboptf.a opt.o optf.o

test:
	cd examples && $(MAKE)

.PHONY: clean test
