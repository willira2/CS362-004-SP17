#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <string.h>
#include <stdio.h>

//test for isGameOver()

int assertTrue(int, int);

int main() {
	int i;
    int seed = 1000;
    int numPlayer = 2, testHolder = 1, testScore = 1;
    int result;
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    struct gameState G, testG;

    // initialize a new game state
    initializeGame(numPlayer, k, seed, &G); 

    printf("TESTING isGameOver()\n");

    printf("TEST 1: supply of province cards = 0\n");
	    //copy game state to test game
	    memcpy(&testG, &G, sizeof(struct gameState));

	    //set province supply to 0 
	    testG.supplyCount[province] = 0;

	    result = isGameOver(&testG);
	    
	    if(!assertTrue(result, 1)){
	    	printf("TEST 1 FAILURE: return value: %d\texpected: 1\n", result);
	    	testHolder = 0;
	    	testScore = 0;
	    }
	    else{printf("TEST 1 SUCCESS\n");}

    printf("TEST 2: supply of province cards = 1, # of empty supply piles < 3\n");
	    //copy game state to test game
	    memcpy(&testG, &G, sizeof(struct gameState));

	    //set all supply piles to 5
	    for(i = 0; i < 25; i++){
	    	testG.supplyCount[i] = 5;
	    }

	    //set province supply to 0 
	    testG.supplyCount[province] = 1;

	    result = isGameOver(&testG);
    	if(!assertTrue(result, 0)){
	    	printf("TEST 2 FAILURE: return value: %d\texpected: 0\n", result);
	    	testHolder = 0;
	    	testScore = 0;
	    }
	    else{printf("TEST 2 SUCCESS\n");}

    printf("TEST 3: supply of province cards = 1, # of empty supply piles = 3\n");
	    //copy game state to test game
	    memcpy(&testG, &G, sizeof(struct gameState));


	    //set all supply piles to 5 starting from 4th supply pile
	    for(i = 3; i < 25; i++){
	    	testG.supplyCount[i] = 5;
	    }

	    //set province supply to 0 
	    testG.supplyCount[province] = 1;

	    //set first three supply piles to empty
	    for(i = 0; i < 3; i++){
	    	testG.supplyCount[i] = 0;
	    }

	    result = isGameOver(&testG);

    	if(!assertTrue(result, 1)){
	    	printf("TEST 3 FAILURE: return value: %d\texpected: 1\n", result);
	    	testHolder = 0;
	    	testScore = 0;
	    }
	    else{printf("TEST 3 SUCCESS\n");}

    printf("TEST 4: supply of province cards = 1, # of empty supply piles > 3\n");
	    //copy game state to test game
	    memcpy(&testG, &G, sizeof(struct gameState));

	    //set all supply piles to 5 starting from 4th supply pile
	    for(i = 4; i < 25; i++){
	    	testG.supplyCount[i] = 5;
	    }

	   	//set province supply to 0 
	    testG.supplyCount[province] = 1;

	    //set first three supply piles to empty
	    for(i = 0; i < 4; i++){
	    	testG.supplyCount[i] = 0;
	    }

	    result = isGameOver(&testG);
    	if(!assertTrue(result, 1)){
	    	printf("TEST 4 FAILURE: return value: 0\texpected: %d\n", result);
	    	testHolder = 0;
	    	testScore = 0;
	    }
	    else{printf("TEST 4 SUCCESS\n");}

	if(testScore){printf("isGameOver() PASS\n");}
	else{printf("isGameOver() FAIL\n");}


return 0;
}

int assertTrue(int a, int b){
	if(a == b){return 1;}
	else{return 0;}
}
