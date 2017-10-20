CFLAGS = -Wall -fpic -coverage -lm

testme: 
	gcc testme.c -o testme $(CFLAGS)

execute: testme
	testme

all: testme execute
