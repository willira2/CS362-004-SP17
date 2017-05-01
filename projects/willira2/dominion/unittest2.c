#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <string.h>
#include <stdio.h>

//test for discardCard()

const char* getCardName(enum CARD);
int assertTrue(int, int);

int main() {
    int i, j;
    int seed = 1000;
    int numPlayer = 2, testHolder = 1, testScore = 1;
    int expected, trashFlag;
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    struct gameState G, testG;

    // initialize a new game state
    initializeGame(numPlayer, k, seed, &G); 

    printf("TESTING discardCard()\n");

    // TEST 1 : trashFlag == 0
    printf("TEST 1: trashFlag = 0\n");
    trashFlag = 0;


    for(i = 0; i < G.handCount[0]; i++){
    	//copy game state to test game
    	memcpy(&testG, &G, sizeof(struct gameState));

    	int handSize = testG.handCount[0];
    	int hand[handSize];
    	for(j = 0; j < testG.handCount[0]; j++){
    		hand[j] = testG.hand[0][j];
    		//printf("hand %d: %d\n", j, hand[j]);
    	}

    	discardCard(i, 0, &testG, trashFlag);

        if(!assertTrue(testG.playedCards[testG.playedCardCount-1], G.hand[0][i])){
            printf("\tTEST 1 CARD %d FAILURE: last card in playedCards: %d\texpected: %d\n", i, testG.playedCards[testG.playedCardCount-1], G.hand[0][i]);
            testHolder = 0;
        }
        
        if(!assertTrue(testG.playedCardCount, G.playedCardCount+1)){
            printf("\tTEST 1 CARD %d FAILURE: playedCard count: %d\texpected: %d\n", i, testG.playedCardCount, G.playedCardCount+1);
            testHolder = 0;
        }
    	//printf("Last card in playedCards = %d\texpected = %d\n", testG.playedCards[testG.playedCardCount-1], G.hand[0][i]);
    	//printf("playedCardCount = %d\texpected = %d\n\n", testG.playedCardCount, G.playedCardCount+1);

    	if(i == testG.handCount[0]){ //not handCount[0] - 1 to account for the handCount being decremented in discardCard()
    		expected = -1;
    		//printf("case 1\n");
    		//printf("testG.handCount[0]: %d\ti: %d\n", testG.handCount[0]-1, i);
    	}

    	else if(testG.handCount[0] == 1){
    		expected = -1;
    		//printf("case 2\n");
    	}

    	else{ //not last card and handcount != 1
    		expected = hand[handSize-1];
    		//printf("case 3\n");
    		//printf("testG.handCount[0]-1: %d\ti: %d\n", testG.handCount[0], i);
    	}

    	if(!assertTrue(testG.hand[0][i], expected)){
            printf("\tTEST 1 CARD %d FAILURE: value at hand[%d]: %d\texpected: %d\n", i, i, testG.hand[0][i], expected);
            testHolder = 0;
        }

        if(!assertTrue(testG.handCount[0], G.handCount[0]-1)){
            printf("\tTEST 1 CARD %d FAILURE: hand count: %d\texpected: %d\n", i, testG.handCount[0], G.handCount[0]-1);
            testHolder = 0;
        }

        //printf("value at handPos in hand: %d\t expected: %d\n", testG.hand[0][i], expected);
    	//printf("\nhand count: %d\texpected: %d\n******\n\n", testG.handCount[0], G.handCount[0]-1);

        if(testHolder){printf("TEST 1 CARD %d SUCCESS\n", i);}
        else {printf("TEST 1 CARD %d FAILURE\n", i); testScore = 0;}

    }

    //TEST 2 : trashFlag = 1
    printf("TEST 2: trashFlag = 1\n");
    trashFlag = 1;

     for(i = 0; i < G.handCount[0]; i++){
    	//copy game state to test game
    	memcpy(&testG, &G, sizeof(struct gameState));

    	int handSize = testG.handCount[0];
    	int hand[handSize];
    	for(j = 0; j < testG.handCount[0]; j++){
    		hand[j] = testG.hand[0][j];
    		//printf("hand %d: %d\n", j, hand[j]);
    	}

    	discardCard(i, 0, &testG, trashFlag);

    	if(!assertTrue(testG.playedCards[testG.playedCardCount-1], G.playedCards[G.playedCardCount-1])){
            printf("\tTEST 2 CARD %d FAILURE: last card in playedCards: %d\texpected: %d\n", i, testG.playedCards[testG.playedCardCount-1], G.playedCards[G.playedCardCount-1]);
            testHolder = 0;
        }
        
        if(!assertTrue(testG.playedCardCount, G.playedCardCount)){
            printf("\tTEST 2 CARD %d FAILURE: playedCard count: %d\texpected: %d\n", i, testG.playedCardCount, G.playedCardCount);
            testHolder = 0;
        }
        //printf("Last card in playedCards = %d\texpected = %d\n", testG.playedCards[testG.playedCardCount-1], G.playedCards[G.playedCardCount-1]);
    	//printf("playedCardCount = %d\texpected = %d\n\n", testG.playedCardCount, G.playedCardCount);

    	if(i == testG.handCount[0]){ //not handCount[0] - 1 to account for the handCount being decremented in discardCard()
    		expected = -1;
    		//printf("case 1\n");
    		//printf("testG.handCount[0]: %d\ti: %d\n", testG.handCount[0]-1, i);
    	}

    	else if(testG.handCount[0] == 1){
    		expected = -1;
    		//printf("case 2\n");
    	}

    	else{ //not last card and handcount != 1
    		expected = hand[handSize-1];
    		//printf("case 3\n");
    		//printf("testG.handCount[0]-1: %d\ti: %d\n", testG.handCount[0], i);
    	}
    	
        if(!assertTrue(testG.hand[0][i], expected)){
            printf("\tTEST 2 CARD %d FAILURE: value at hand[%d]: %d\texpected: %d\n", i, i, testG.hand[0][i], expected);
            testHolder = 0;
        }

        if(!assertTrue(testG.handCount[0], G.handCount[0]-1)){
            printf("\tTEST 2 CARD %d FAILURE: hand count: %d\texpected: %d\n", i, testG.handCount[0], G.handCount[0]-1);
            testHolder = 0;
        }

        //printf("value at handPos in hand: %d\t expected: %d\n", testG.hand[0][i], expected);
    	//printf("\nhand count: %d\texpected: %d\n******\n\n", testG.handCount[0], G.handCount[0]-1);
        
        if(testHolder){printf("TEST 2 CARD %d SUCCESS\n", i);}
        else {printf("TEST 2 CARD %d FAILURE\n", i); testScore = 0;}

    }

    if(testScore){printf("discardCard() PASS\n");}
        else {printf("discardCard() FAIL\n");}


return 0;
}

const char* getCardName(enum CARD card){
    switch(card)
    {
        case curse: return "curse";
        case estate: return "estate";
        case duchy: return "duchy";
        case province: return "province";

        case copper: return "copper";
        case silver: return "silver";
        case gold: return "gold";

        case adventurer: return "adventurer";
        case council_room: return "council_room";
        case feast: return "feast";
        case gardens: return "gardens";
        case mine: return "mine";
        case remodel: return "remodel";
        case smithy: return "smithy";
        case village: return "village";

        case baron: return "baron";
        case great_hall: return "great_hall";
        case minion: return "minion";
        case steward: return "steward";
        case tribute: return "tribute";

        case ambassador: return "ambassador";
        case cutpurse: return "cutpurse";
        case embargo: return "embargo";
        case outpost: return "outpost";
        case salvager: return "salvager";
        case sea_hag: return "sea_hag";
        case treasure_map: return "treasure_map";
    }
}

int assertTrue(int a, int b){
    if(a == b){return 1;}
    else{return 0;}
}