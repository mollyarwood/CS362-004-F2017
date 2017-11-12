CFLAGS = -Wall -fpic -coverage -lm

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

cardUnitTest1: dominion.o cardtest1.c
	gcc -o cardtest1 cardtest1.c -g dominion.o rngs.o $(CFLAGS)

cardUnitTest2: dominion.o cardtest2.c
	gcc -o cardtest2 cardtest2.c -g dominion.o rngs.o $(CFLAGS)

cardUnitTest3: dominion.o cardtest3.c
	gcc -o cardtest3 cardtest3.c -g dominion.o rngs.o $(CFLAGS)

cardUnitTest4: dominion.o cardtest4.c
	gcc -o cardtest4 cardtest4.c -g dominion.o rngs.o $(CFLAGS)

funcUnitTest1: dominion.o unittest1.c
	gcc -o unittest1 unittest1.c -g dominion.o rngs.o $(CFLAGS)

funcUnitTest2: dominion.o unittest2.c
	gcc -o unittest2 unittest2.c -g dominion.o rngs.o $(CFLAGS)

funcUnitTest3: dominion.o unittest3.c
	gcc -o unittest3 unittest3.c -g dominion.o rngs.o $(CFLAGS)

funcUnitTest4: dominion.o unittest4.c
	gcc -o unittest4 unittest4.c -g dominion.o rngs.o $(CFLAGS)

cardRandTestAd: dominion.o randomtestadventurer.c
	gcc -o randomtestadventurer randomtestadventurer.c -g dominion.o rngs.o $(CFLAGS)

cardRandTest1: dominion.o randomtestcard1.c
	gcc -o randomtestcard1 randomtestcard1.c -g dominion.o rngs.o $(CFLAGS)

cardRandTest2: dominion.o randomtestcard2.c
	gcc -o randomtestcard2 randomtestcard2.c -g dominion.o rngs.o $(CFLAGS)

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)
#To run playdom you need to entere: ./playdom <any integer number> like ./playdom 10*/

testDrawCard: testDrawCard.c dominion.o rngs.o
	gcc  -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

badTestDrawCard: badTestDrawCard.c dominion.o rngs.o
	gcc -o badTestDrawCard -g  badTestDrawCard.c dominion.o rngs.o $(CFLAGS)

testBuyCard: testDrawCard.c dominion.o rngs.o
	gcc -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

testAll: dominion.o testSuite.c
	gcc -o testSuite testSuite.c -g  dominion.o rngs.o $(CFLAGS)

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

runtests: testDrawCard 
	./testDrawCard &> unittestresult.out
	gcov dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out

unittestresults.out: cardUnitTest1 cardUnitTest2 cardUnitTest3 cardUnitTest4 funcUnitTest1 funcUnitTest2 funcUnitTest3 funcUnitTest4
	cardtest1 > unittestresults.out
	gcov cardtest1.c >> unittestresults.out
	cardtest2 >> unittestresults.out
	gcov cardtest2.c >> unittestresults.out
	cardtest3 >> unittestresults.out
	gcov cardtest3.c >> unittestresults.out
	cardtest4 >> unittestresults.out
	gcov cardtest4.c >> unittestresults.out
	unittest1 >> unittestresults.out
	gcov unittest1 >> unittestresults.out
	unittest2 >> unittestresults.out
	gcov unittest2 >> unittestresults.out
	unittest3 >> unittestresults.out
	gcov unittest3 >> unittestresults.out
	unittest4 >> unittestresults.out
	gcov unittest4 >> unittestresults.out
	gcov -f -b dominion.c >> unittestresults.out
	cat dominion.c.gcov >> unittestresults.out

randtestresults.out: cardRandTest1 cardRandTest2 cardRandTestAd
	randomtestadventurer > randomtestadventurer.out
	gcov randomtestadventurer.c >> randomtestadventurer.out
	gcov -f -b dominion.c >> randomtestadventurer.out
	cat dominion.c.gcov >> randomtestadventurer.out
	randomtestcard1 > randomtestcard1.out
	gcov randomtestcard1.c >> randomtestcard1.out
	gcov -f -b dominion.c >> randomtestcard1.out
	cat dominion.c.gcov >> randomtestcard1.out
	randomtestcard2 > randomtestcard2.out
	gcov randomtestcard2.c >> randomtestcard2.out
	gcov -f -b dominion.c >> randomtestcard2.out
	cat dominion.c.gcov >> randomtestcard2.out



player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

all: cardUnitTest1 cardUnitTest2 cardUnitTest3 cardUnitTest4 funcUnitTest1 funcUnitTest2 funcUnitTest3 funcUnitTest4 cardRandTest1 cardRandTest2 cardRandTestAd playdom player testDrawCard testBuyCard badTestDrawCard randtestresults.out unittestresults.out

clean:
	rm -f *.o player player.exe  *.gcov *.gcda *.gcno *.so *.out testDrawCard testDrawCard.exe
