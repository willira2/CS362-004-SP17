#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <string.h>
#include <stdio.h>

//test for outpost card

int assertTrue(int, int);

int main() {
	int i, j;
    int seed = 1000;
    int choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0, outFlag = 0, testHolder = 1, testScore = 1;
    int numPlayer = 2;
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    struct gameState G, testG;

	// initialize a new game state
    initializeGame(numPlayer, k, seed, &G); 

    printf("TESTING outpost card\n");

    /******************** TEST 1 : outpostPlayed flag value ********************/
    printf("TEST 1: check outpostPlayed flag\n");

    //copy to test game
	memcpy(&testG, &G, sizeof(struct gameState));

	testG.hand[0][0] = outpost;

	cardEffect(outpost, choice1, choice2, choice3, &testG, testG.hand[0][0], &bonus);

	//printf("outpostPlayed flag: %d\texpected: %d\n", testG.outpostPlayed, G.outpostPlayed +1);
	//check value of outpostPlayed
	if(!assertTrue(testG.outpostPlayed, G.outpostPlayed+1)){
		printf("TEST 1 FALURE: outpostPlayed flag: %d\texpected: %d\n", testG.outpostPlayed, G.outpostPlayed+1);
		testScore=0;
	}
	else{printf("TEST 1 SUCCESS\n");}
   

    /******************** TEST 2 : outpost card discarded ********************/
    printf("TEST 2: outpost card discarded\n");

    for(i = 0; i < G.handCount[0]; i++){
    	//copy game state to test game
    	memcpy(&testG, &G, sizeof(struct gameState));

    	testG.hand[0][i] = outpost;

    	cardEffect(outpost, choice1, choice2, choice3, &testG, i, &bonus);

    	if(!assertTrue(testG.playedCards[testG.playedCardCount-1], 23)){
    		testHolder=0;
    		printf("\tTEST 2a handPos[%d] FAILURE: last card in playedCards = %d\texpected = 23\n", i, testG.playedCards[testG.playedCardCount-1]);
    	}
    	if(!assertTrue(testG.playedCardCount, G.playedCardCount+1)){
    		testHolder=0;
    		printf("\tTEST 2b handPos[%d] FAILURE: playedCardCount = %d\texpected = %d\n", i, testG.playedCardCount, G.playedCardCount+1);
    	}
    	if(!assertTrue(testG.handCount[0], G.handCount[0]-1)){
    		testHolder=0;
    		printf("\tTEST 2c handPos[%d] FAILURE: handCount: %d\texpected: %d\n", i, testG.handCount[0], G.handCount[0]-1);
    	}
    	/*printf("Last card in playedCards = %d\texpected = 23\n", testG.playedCards[testG.playedCardCount-1]);
    	printf("playedCardCount = %d\texpected = %d\n", testG.playedCardCount, G.playedCardCount+1);
    	printf("handCount: %d\texpected: %d\n", testG.handCount[0], G.handCount[0]-1);*/

    	for(j = 0; j < testG.handCount[0]-1; j++){
    		if (testG.hand[0][j] == outpost){
    			outFlag = 1;
    		}
    	}
   		if(!assertTrue(outFlag, 0)){
   			testHolder=0;
   			printf("\tTEST 2d handPos[%d] FAILURE: hand contains outpost card? %d\texpected: 0\n\n", i, outFlag);
   		}
   		/*printf("hand contains outpost card? %d\texpected: 0\n\n", outFlag);*/

   		if(testHolder){printf("TEST 2 handPos[%d]: SUCCESS\n", i);}
   		else{printf("TEST 2 handPos[%d]: FALURE\n", i);testScore=0;}
   }

   if(testScore){printf("outpost card: PASS\n");}
   		else{printf("outpost card: FAIL\n");testScore=0;}

return 0;

}

int assertTrue(int a, int b){
	if(a == b){return 1;}
	else{return 0;}
}
