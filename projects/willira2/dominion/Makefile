CFLAGS = -Wall -fpic -coverage -lm -std=c99

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)

testDrawCard: testDrawCard.c dominion.o rngs.o
	gcc -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

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


player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

randomtestcard1: dominion.o randomtestcard1.c rngs.o
	gcc -o randomtestcard1 -g randomtestcard1.c dominion.o rngs.o -ftest-coverage -fprofile-arcs $(CFLAGS)

randomtestcard2: dominion.o randomtestcard2.c rngs.o
	gcc -o randomtestcard2 -g randomtestcard2.c dominion.o rngs.o -ftest-coverage -fprofile-arcs $(CFLAGS)

randomtestadventurer: dominion.o randomtestadventurer.c rngs.o
	gcc -o randomtestadventurer -g randomtestadventurer.c dominion.o rngs.o -ftest-coverage -fprofile-arcs $(CFLAGS)

unittest1: unittest1.c dominion.o rngs.o
	gcc -o unittest1 -g unittest1.c dominion.o rngs.o -ftest-coverage -fprofile-arcs $(CFLAGS)

unittest2: unittest2.c dominion.o rngs.o
	gcc -o unittest2 -g unittest2.c dominion.o rngs.o -ftest-coverage -fprofile-arcs $(CFLAGS)

unittest3: unittest3.c dominion.o rngs.o
	gcc -o unittest3 -g unittest3.c dominion.o rngs.o -ftest-coverage -fprofile-arcs $(CFLAGS)

unittest4: unittest4.c dominion.o rngs.o
	gcc -o unittest4 -g unittest4.c dominion.o rngs.o -ftest-coverage -fprofile-arcs $(CFLAGS)

cardtest1: cardtest1.c dominion.o rngs.o
	gcc -o cardtest1 -g cardtest1.c dominion.o rngs.o -ftest-coverage -fprofile-arcs $(CFLAGS)

cardtest2: cardtest2.c dominion.o rngs.o
	gcc -o cardtest2 -g cardtest2.c dominion.o rngs.o -ftest-coverage -fprofile-arcs $(CFLAGS)

cardtest3: cardtest3.c dominion.o rngs.o
	gcc -o cardtest3 -g cardtest3.c dominion.o rngs.o -ftest-coverage -fprofile-arcs $(CFLAGS)

cardtest4: cardtest4.c dominion.o rngs.o
	gcc -o cardtest4 -g cardtest4.c dominion.o rngs.o -ftest-coverage -fprofile-arcs $(CFLAGS)
	
randomtestcard1.out: randomtestcard1.c dominion.c rngs.c
	echo "Results from randomtestcard1: " > randomtestcard1.out

	make clean
	make randomtestcard1
	./randomtestcard1 >> randomtestcard1.out	
	gcov dominion.c -b -f >> randomtestcard1.out
	cat dominion.c.gcov >> randomtestcard1.out

randomtestcard2.out: randomtestcard2.c dominion.c rngs.c
	echo "Results from randomtestcard2: " > randomtestcard2.out

	make clean
	make randomtestcard2
	./randomtestcard2 >> randomtestcard2.out	
	gcov dominion.c -b -f >> randomtestcard2.out
	cat dominion.c.gcov >> randomtestcard2.out

randomtestadventurer.out: randomtestadventurer.c dominion.c rngs.c
	echo "Results from randomtestadventurer: " > randomtestadventurer.out

	make clean
	make randomtestadventurer
	./randomtestadventurer >> randomtestadventurer.out	
	gcov dominion.c -b -f >> randomtestadventurer.out
	cat dominion.c.gcov >> randomtestadventurer.out

unittestresults.out: unittest1.c unittest2.c unittest3.c unittest4.c cardtest1.c cardtest2.c cardtest3.c cardtest4.c dominion.c rngs.c
	echo "Results from running all tests: " > unittestresults.out

	echo "unittest1.c" >> unittestresults.out
	make clean
	make unittest1
	./unittest1 >> unittestresults.out	
	gcov dominion.c -b -f >> unittestresults.out
	cat dominion.c.gcov >> unittestresults.out
	 
	echo "unittest2.c" >> unittestresults.out
	make clean
	make unittest2
	./unittest2 >> unittestresults.out	
	gcov dominion.c -b -f >> unittestresults.out
	cat dominion.c.gcov >> unittestresults.out
	
	echo "unittest3.c" >> unittestresults.out
	make clean
	make unittest3
	./unittest3 >> unittestresults.out	
	gcov dominion.c -b -f >> unittestresults.out
	cat dominion.c.gcov >> unittestresults.out

	echo "unittest4.c" >> unittestresults.out
	make clean
	make unittest4
	./unittest4 >> unittestresults.out	
	gcov dominion.c -b -f >> unittestresults.out
	cat dominion.c.gcov >> unittestresults.out
	
	echo "cardtest1.c" >> unittestresults.out
	make clean
	make cardtest1
	./cardtest1 >> unittestresults.out	
	gcov dominion.c -b -f >> unittestresults.out
	cat dominion.c.gcov >> unittestresults.out
	
	echo "cardtest2.c" >> unittestresults.out
	make clean
	make cardtest2
	./cardtest2 >> unittestresults.out	
	gcov dominion.c -b -f >> unittestresults.out
	cat dominion.c.gcov >> unittestresults.out
	
	echo "cardtest3.c" >> unittestresults.out
	make clean
	make cardtest3
	./cardtest3 >> unittestresults.out	
	gcov dominion.c -b -f >> unittestresults.out
	cat dominion.c.gcov >> unittestresults.out
	
	echo "cardtest4.c removed from makefile due to segfault" >> unittestresults.out

all: playdom player testDrawCard testBuyCard badTestDrawCard

clean:
	rm -f *.o playdom.exe playdom test.exe test player player.exe testInit testInit.exe *.gcov *.gcda *.gcno *.so
