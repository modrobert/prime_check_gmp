CC = gcc
CFLAGS = -O3 -Wpedantic
CLINK = -lgmp

default: prime_check_gmp

debug: CFLAGS = -g -Wpedantic -lgmp
debug: prime_check_gmp

prime_check_gmp.o: prime_check_gmp.c
	$(CC) $(CFLAGS) -c prime_check_gmp.c -o prime_check_gmp.o

prime_check_gmp: prime_check_gmp.o
	$(CC) $(CFLAGS) prime_check_gmp.o -o prime_check_gmp $(CLINK)

clean:
	-rm -f prime_check_gmp.o
	-rm -f prime_check_gmp
	
