#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <string.h>
#include <stdio.h>

//test for smithy

int assertTrue(int, int);

int main() {
	int i, j, m, deck1, deck2, deck3, deckCounter, val1, val2;
    int seed = 1000, smitFlag = 0, testHolder = 1, testScore = 1;
    int numPlayer = 2;
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    struct gameState G, testG, controlG;

	// initialize a new game state
    initializeGame(numPlayer, k, seed, &G); 

    printf("TESTING smithy card\n");

    //number of cards in hand before/after
    //cycle through which cards
    //is smithy not in hand and in discard pile

    //get last three cards in deck
    deckCounter = G.deckCount[0];
    deck1 = G.deck[0][deckCounter - 1];
    deck2 = G.deck[0][deckCounter - 2];
	deck3 = G.deck[0][deckCounter - 3];

	//test for all handPos
	for(i = 0; i < G.handCount[0]; i++){
		//copy game state to control game
    	memcpy(&controlG, &G, sizeof(struct gameState));

		//set current handPos to smithy
		controlG.hand[0][i] = smithy;

		//copy game state to test game
    	memcpy(&testG, &controlG, sizeof(struct gameState));

    	playSmithy(0, &testG, i);

    	//printf("handCount: %d\texpected: %d\n", testG.handCount[0], controlG.handCount[0]+2); //plus 2 because 3 cards are drawn and one is discarded
    	if(!assertTrue(testG.handCount[0], controlG.handCount[0]+2)){
    		testHolder=0;
    		printf("\tTEST handPos[%d] FAILURE: handCount: %d\texpected: %d\n", i, testG.handCount[0], controlG.handCount[0]+2);
    	}


    	for(j = 0, m = 0; j < testG.handCount[0]; j++){
    		//testG hand
    		//printf("%d\t", testG.hand[0][m]);
    		val1 = testG.hand[0][m];
    		m++;

    		if(j == i){
    			if(j != controlG.handCount[0]-1) // not at end
    			{
    				//printf("%d\n", deck3);
    				val2 = deck3;
    			}

    			else if (j == controlG.handCount[0]-1) // at end
    			{
    				//printf("%d\n", deck3);
    				val2 = deck3;
    			}	
    		}
    		else{
    			if(j == controlG.handCount[0]){
    				//printf("%d\n", deck1); 
    				val2 = deck1;}
    			else if(j == controlG.handCount[0]+1){
    				//printf("%d\n", deck2); 
    				val2 = deck2;}
    			else{
    				//printf("%d\n", controlG.hand[0][j]); 
    				val2 = controlG.hand[0][j];}
    		}

    		if(!assertTrue(val1, val2)){testHolder=0;}
    	}

    	//check for smithy card
    	for(j = 0; j < testG.handCount[0]-1; j++){
    		if (testG.hand[0][j] == smithy){
    			smitFlag = 1;
    		}
    	}
    	
    	//printf("AFTER: contains smithy card? %d\texpected: 0\n\n******\n", smitFlag);
   		if(assertTrue(smitFlag, 1)){
   			testHolder=0;
   			printf("\tTEST handPos[%d] FAILURE: hand contains smithy card after call: %d\texpected: 0\n", i, smitFlag);

   		}
   		smitFlag = 0;

    	for(j = 0; j < testG.playedCardCount; j++){
    		if (testG.playedCards[j] == smithy){
    			smitFlag = 1;
    		}
    	}

    	if(assertTrue(smitFlag, 0)){
    		testHolder=0;
    		printf("\tTEST handPos[%d] FAILURE: playedCards contains smithy card after call: %d\texpected: 0\n", i, smitFlag);
    	}
    	
    	if(assertTrue(testG.playedCardCount, controlG.playedCardCount)){
    		testHolder=0;
    		printf("\tTEST handPos[%d] FAILURE: playedCardCount: %d\texpected: %d\n", i, testG.playedCardCount, controlG.playedCardCount);
    	}
   		

   		if(testHolder){printf("TEST handpos[%d] SUCCESS\n", i);}
   		else{printf("TEST handPos[%d] FALURE\n", i); testScore=0;}
	}

	if(testScore){printf("smithy card: PASS\n");}
   		else{printf("smithy card: FAIL\n");}


    return 0;
}

int assertTrue(int a, int b){
	if(a == b){return 1;}
	else{return 0;}
}
