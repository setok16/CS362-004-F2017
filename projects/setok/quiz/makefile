CFLAGS = -Wall -fpic -coverage -lm

default: testme

testme: testme.c
	gcc -o testme testme.c $(CFLAGS)
	./testme

clean:
	rm testme *.gcov *.gcno *.gcda
