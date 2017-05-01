#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <string.h>
#include <stdio.h>
#include <time.h>

//test for adventurer

const char* getCardName(enum CARD);
int assertTrue(int, int);

int main() {
	int i, deckCount;
    int seed = 1000, advFlag = 0, testHolder = 1, testScore = 1;
    int numPlayer = 2, currentPlayer = 0;
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    struct gameState G, testG;

	// initialize a new game state
    initializeGame(numPlayer, k, seed, &G); 

    //put adventurer into hand
    G.hand[currentPlayer][0] = adventurer;

    printf("TESTING adventurer card\n");

  /*  printf("deckCount: %d\n", G.deckCount[currentPlayer]);
    printf("handCount: %d\n", G.handCount[currentPlayer]);
    printf("discardCount: %d\n", G.discardCount[currentPlayer]);*/

/************************/

    printf("\nTest 1 : shuffle needed\n");
    printf("Test 1a : >2 treasure cards in deck\n");

    //copy game state to test game
    memcpy(&testG, &G, sizeof(struct gameState));

    deckCount = testG.deckCount[currentPlayer];
    
    testG.deckCount[currentPlayer] = 0;

    // fill discard to same level as deck with coppers
    for(i = 0; i < deckCount; i++){
    	testG.discard[currentPlayer][i] = 4;
    	testG.discardCount[currentPlayer]++;
    }

  /*  printf("deckCount: %d\n", testG.deckCount[currentPlayer]);
    printf("handCount: %d\n", testG.handCount[currentPlayer]);
    printf("discardCount: %d\n", testG.discardCount[currentPlayer]);*/

  /*  for(i = 0; i < testG.discardCount[currentPlayer];i++){
    	printf("%d\n", testG.discard[currentPlayer][i]);
    }*/
    
    playAdventurer(&testG, currentPlayer);

    if(!assertTrue(testG.handCount[currentPlayer], G.handCount[currentPlayer]+1)){
    	printf("\tTEST 1a FAILURE: hand size: %d\texpected: %d\n", testG.handCount[currentPlayer], G.handCount[currentPlayer]+1);
    	testHolder=0;
    }
    if(!assertTrue(testG.hand[currentPlayer][testG.handCount[0]-2], 4)){
    	printf("\tTEST 1a FAILURE: next to last hand card: %d\texpected: 4\n", testG.hand[currentPlayer][testG.handCount[0]-2]);
    	testHolder=0;
    }
    if(!assertTrue(testG.hand[currentPlayer][testG.handCount[0]-1], 4)){
    	printf("\tTEST 1a FAILURE: last hand card: %d\texpected: 4\n", testG.hand[currentPlayer][testG.handCount[0]-1]);
    	testHolder=0;
    }
/*    printf("hand size: %d\texpected: %d\n", testG.handCount[currentPlayer], G.handCount[currentPlayer]+1);
    printf("next to last card: %d\texpected: 4, 5, or 6\n", testG.hand[currentPlayer][testG.handCount[0]-2]);
    printf("last card: %d\texpected: 4, 5, or 6\n", testG.hand[currentPlayer][testG.handCount[0]-1]);*/

    for(i = 0; i < testG.handCount[currentPlayer]-1; i++){
    	if (testG.hand[currentPlayer][i] == adventurer){
    		advFlag = 1;
    	}
    }
    //printf("contains adventurer card? %d\texpected: 0\n", advFlag);
    if(!assertTrue(advFlag, 0)){
		printf("\tTEST 1a FAILURE: hand contains adventurer card: %d\texpected: 0\n", advFlag);
    	testHolder=0;
    }

    if(testHolder){printf("TEST 1a SUCCESS\n");}
   		else{printf("TEST 1a FAILURE\n");testScore=0;}

   		testHolder = 1;

/************************/

    printf("\nTest 1b : 2 treasure cards in deck\n");

    //copy game state to test game
    memcpy(&testG, &G, sizeof(struct gameState));

    deckCount = testG.deckCount[currentPlayer];
    
    testG.deckCount[currentPlayer] = 0;

    // fill discard to same level - 2 as deck with estate
    for(i = 0; i < deckCount-2; i++){
    	testG.discard[currentPlayer][i] = 4;
    	testG.discardCount[currentPlayer]++;
    }

    testG.discard[currentPlayer][i] = 4;
    testG.discard[currentPlayer][i+1] = 4;
    testG.discardCount[currentPlayer] += 2;

    playAdventurer(&testG, currentPlayer);

     // printf("hand size: %d\texpected: %d\n", testG.handCount[currentPlayer], G.handCount[currentPlayer]+1);
    // printf("next to last card: %d\texpected: 4, 5, or 6\n", testG.hand[currentPlayer][testG.handCount[0]-2]);
    // printf("last card: %d\texpected: 4, 5, or 6\n", testG.hand[currentPlayer][testG.handCount[0]-1]);

    if(!assertTrue(testG.handCount[currentPlayer], G.handCount[currentPlayer]+1)){
    	printf("\tTEST 1b FAILURE: hand size: %d\texpected: %d\n", testG.handCount[currentPlayer], G.handCount[currentPlayer]+1);
    	testHolder=0;
    }
    if(!assertTrue(testG.hand[currentPlayer][testG.handCount[0]-2], 4)){
    	printf("\tTEST 1b FAILURE: next to last hand card: %d\texpected: 4\n", testG.hand[currentPlayer][testG.handCount[0]-2]);
    	testHolder=0;
    }
    if(!assertTrue(testG.hand[currentPlayer][testG.handCount[0]-1], 4)){
    	printf("\tTEST 1b FAILURE: last hand card: %d\texpected: 4\n", testG.hand[currentPlayer][testG.handCount[0]-1]);
    	testHolder=0;
    }

    for(i = 0; i < testG.handCount[currentPlayer]-1; i++){
    	if (testG.hand[currentPlayer][i] == adventurer){
    		advFlag = 1;
    	}
    }
    //printf("contains adventurer card? %d\texpected: 0\n", advFlag);
    if(!assertTrue(advFlag, 0)){
		printf("\tTEST 1b FAILURE: hand contains adventurer card: %d\texpected: 0\n", advFlag);
    	testHolder=0;
    }

    if(testHolder){printf("TEST 1b SUCCESS\n");}
   		else{printf("TEST 1b FAILURE\n");testScore=0;}

   		testHolder = 1;

/************************/

    printf("\nTest 1c : 1 treasure cards in deck\n");
    //copy game state to test game
    memcpy(&testG, &G, sizeof(struct gameState));

    deckCount = testG.deckCount[currentPlayer];
    
    testG.deckCount[currentPlayer] = 0;

    // fill discard to same level - 1 as deck with estate cards
    for(i = 0; i < deckCount-1; i++){
    	testG.discard[currentPlayer][i] = 1;
    	testG.discardCount[currentPlayer]++;
    }

    testG.discard[currentPlayer][i] = 4;
    testG.discardCount[currentPlayer]++;

    playAdventurer(&testG, currentPlayer);

    /*printf("hand size: %d\texpected: %d\n", testG.handCount[currentPlayer], G.handCount[currentPlayer]+1);
    printf("next to last card: %d\texpected: 4, 5, or 6\n", testG.hand[currentPlayer][testG.handCount[0]-2]);
    printf("last card: %d\texpected: 4, 5, or 6\n", testG.hand[currentPlayer][testG.handCount[0]-1]);*/

    if(!assertTrue(testG.handCount[currentPlayer], G.handCount[currentPlayer])){
    	printf("\tTEST 1c FAILURE: hand size: %d\texpected: %d\n", testG.handCount[currentPlayer], G.handCount[currentPlayer]);
    	testHolder=0;
    }
    if(!assertTrue(testG.hand[currentPlayer][testG.handCount[0]-2], 1)){
    	printf("\tTEST 1c FAILURE: next to last hand card: %d\texpected: 1\n", testG.hand[currentPlayer][testG.handCount[0]-2]);
    	testHolder=0;
    }
    if(!assertTrue(testG.hand[currentPlayer][testG.handCount[0]-1], 4)){
    	printf("\tTEST 1c FAILURE: last hand card: %d\texpected: 4\n", testG.hand[currentPlayer][testG.handCount[0]-1]);
    	testHolder=0;
    }

    for(i = 0; i < testG.handCount[currentPlayer]-1; i++){
    	if (testG.hand[currentPlayer][i] == adventurer){
    		advFlag = 1;
    	}
    }
    //printf("contains adventurer card? %d\texpected: 0\n", advFlag);
    if(!assertTrue(advFlag, 0)){
    	printf("\tTEST 1c FAILURE: hand contains adventurer card: %d\texpected: 0\n", advFlag);
    	testHolder=0;
    }

    if(testHolder){printf("TEST 1c SUCCESS\n");}
   		else{printf("TEST 1c FAILURE\n");testScore=0;}

   		testHolder = 1;

/************************/

    printf("\nTest 1d : 0 treasure cards in deck\n");
    //copy game state to test game
    memcpy(&testG, &G, sizeof(struct gameState));

    deckCount = testG.deckCount[currentPlayer];
    
    testG.deckCount[currentPlayer] = 0;

    // fill discard to same level as deck with estate cards
    for(i = 0; i < deckCount; i++){
    	testG.discard[currentPlayer][i] = 1;
    	testG.discardCount[currentPlayer]++;
    }

     playAdventurer(&testG, currentPlayer);  

    //printf("hand size: %d\texpected: %d\n", testG.handCount[currentPlayer], G.handCount[currentPlayer]-1);
    if(!assertTrue(testG.handCount[currentPlayer], G.handCount[currentPlayer]-1)){
    	printf("\tTEST 1d FAILURE: hand size: %d\texpected: %d\n", testG.handCount[currentPlayer], G.handCount[currentPlayer]-1);
    	testHolder=0;
    }

    for(i = 0; i < testG.handCount[currentPlayer];i++){
    	if(!assertTrue(testG.hand[currentPlayer][i], G.hand[currentPlayer][i])){
    		printf("\tTEST 1d FAILURE: handPos %d: %d\texpected: %d\n", i+1, testG.hand[currentPlayer][i], G.hand[currentPlayer][i]);
    		testHolder=0;
    	}
    	//printf("handPos %d: %d\texpected: %d\n", i+1, testG.hand[currentPlayer][i], G.hand[currentPlayer][i]);
    }

    for(i = 0; i < testG.handCount[currentPlayer]-1; i++){
    	if (testG.hand[currentPlayer][i] == adventurer){
    		advFlag = 1;
    	}
    }
    //printf("contains adventurer card? %d\texpected: 0\n", advFlag);
    if(!assertTrue(advFlag, 0)){
    	printf("\tTEST 1d FAILURE: hand contains adventurer card: %d\texpected: 0\n", advFlag);
    	testHolder=0;
    }

    if(testHolder){printf("TEST 1d SUCCESS\n");}
   		else{printf("TEST 1d FALURE\n");testScore=0;}

   		testHolder = 1;


/************************/

    printf("\nTest 2 : shuffle not needed\n");
    //copy game state to test game
    memcpy(&testG, &G, sizeof(struct gameState));

    /*printf("deckCount: %d\n", testG.deckCount[currentPlayer]);
    printf("handCount: %d\n", testG.handCount[currentPlayer]);
    printf("discardCount: %d\n", testG.discardCount[currentPlayer]);*/

    printf("Test 2a : >2 treasure cards in deck\n");
    playAdventurer(&testG, currentPlayer);

    /*printf("hand size: %d\texpected: %d\n", testG.handCount[currentPlayer], G.handCount[currentPlayer]+1);
    printf("next to last card: %d\texpected: 4, 5, or 6\n", testG.hand[currentPlayer][testG.handCount[0]-2]);
    printf("last card: %d\texpected: 4, 5, or 6\n", testG.hand[currentPlayer][testG.handCount[0]-1]);*/

    if(!assertTrue(testG.handCount[currentPlayer], G.handCount[currentPlayer]+1)){
    	printf("\tTEST 2a FAILURE: hand size: %d\texpected: %d\n", testG.handCount[currentPlayer], G.handCount[currentPlayer]+1);
    	testHolder=0;
    }
    if(!assertTrue(testG.hand[currentPlayer][testG.handCount[0]-2], 4)){
    	printf("\tTEST 2a FAILURE: next to last hand card: %d\texpected: 4\n", testG.hand[currentPlayer][testG.handCount[0]-2]);
    	testHolder=0;
    }
    if(!assertTrue(testG.hand[currentPlayer][testG.handCount[0]-1], 4)){
    	printf("\tTEST 2a FAILURE: last hand card: %d\texpected: 4\n", testG.hand[currentPlayer][testG.handCount[0]-1]);
    	testHolder=0;
    }

    for(i = 0; i < testG.handCount[currentPlayer]-1; i++){
    	if (testG.hand[currentPlayer][i] == adventurer){
    		advFlag = 1;
    	}
    }
    //printf("contains adventurer card? %d\texpected: 0\n", advFlag);
    if(!assertTrue(advFlag, 0)){
		printf("\tTEST 2a FAILURE: hand contains adventurer card: %d\texpected: 0\n", advFlag);
    	testHolder=0;
    }

    if(testHolder){printf("TEST 2a SUCCESS\n");}
   		else{printf("TEST 2a FALURE\n");testScore=0;}

   		testHolder = 1;

/************************/

    printf("\nTest 2b : 2 treasure cards in deck\n");

    //copy game state to test game
    memcpy(&testG, &G, sizeof(struct gameState));

	deckCount = testG.deckCount[currentPlayer];
    //replace deck with just estates plus two treasure cards
    for(i = 0; i < deckCount-2; i++){
    	testG.deck[currentPlayer][i] = 1;
    }

    testG.deck[currentPlayer][i] = 4;
    testG.deck[currentPlayer][i+1] = 4;


    playAdventurer(&testG, currentPlayer);

   /* printf("hand size: %d\texpected: %d\n", testG.handCount[currentPlayer], G.handCount[currentPlayer]+1);
    printf("next to last card: %d\texpected: 4, 5, or 6\n", testG.hand[currentPlayer][testG.handCount[0]-2]);
    printf("last card: %d\texpected: 4, 5, or 6\n", testG.hand[currentPlayer][testG.handCount[0]-1]);*/

    if(!assertTrue(testG.handCount[currentPlayer], G.handCount[currentPlayer]+1)){
    	printf("\tTEST 2b FAILURE: hand size: %d\texpected: %d\n", testG.handCount[currentPlayer], G.handCount[currentPlayer]+1);
    	testHolder=0;
    }
    if(!assertTrue(testG.hand[currentPlayer][testG.handCount[0]-2], 4)){
    	printf("\tTEST 2b FAILURE: next to last hand card: %d\texpected: 4\n", testG.hand[currentPlayer][testG.handCount[0]-2]);
    	testHolder=0;
    }
    if(!assertTrue(testG.hand[currentPlayer][testG.handCount[0]-1], 4)){
    	printf("\tTEST 2b FAILURE: last hand card: %d\texpected: 4\n", testG.hand[currentPlayer][testG.handCount[0]-1]);
    	testHolder=0;
    }

    for(i = 0; i < testG.handCount[currentPlayer]-1; i++){
    	if (testG.hand[currentPlayer][i] == adventurer){
    		advFlag = 1;
    	}
    }
    //printf("contains adventurer card? %d\texpected: 0\n", advFlag);
    if(!assertTrue(advFlag, 0)){
    	printf("TEST 2b FAILURE: hand contains adventurer card: %d\texpected: 0\n", advFlag);
    	testHolder=0;
    }

    if(testHolder){printf("TEST 2b SUCCESS\n");}
   		else{printf("TEST 2b FALURE\n");testScore=0;}

   		testHolder = 1;

/************************/

    printf("\nTest 2c : 1 treasure card in deck\n");
    //copy game state to test game
    memcpy(&testG, &G, sizeof(struct gameState));

    deckCount = testG.deckCount[currentPlayer];

    // fill deck with estate cards
    for(i = 0; i < deckCount; i++){
    	testG.deck[currentPlayer][i] = 1;
    }

    //make last card in deck a copper
    testG.deck[currentPlayer][i] = 4;

    playAdventurer(&testG, currentPlayer);

    if(!assertTrue(testG.handCount[currentPlayer], G.handCount[currentPlayer])){
    	printf("\tTEST 2c FAILURE: hand size: %d\texpected: %d\n", testG.handCount[currentPlayer], G.handCount[currentPlayer]);
    	testHolder=0;
    }
    if(!assertTrue(testG.hand[currentPlayer][testG.handCount[0]-2], 1)){
    	printf("\tTEST 2c FAILURE: next to last hand card: %d\texpected: 1\n", testG.hand[currentPlayer][testG.handCount[0]-2]);
    	testHolder=0;
    }
    if(!assertTrue(testG.hand[currentPlayer][testG.handCount[0]-1], 4)){
    	printf("\tTEST 2c FAILURE: last hand card: %d\texpected: 4\n", testG.hand[currentPlayer][testG.handCount[0]-1]);
    	testHolder=0;
    }

    for(i = 0; i < testG.handCount[currentPlayer]-1; i++){
    	if (testG.hand[currentPlayer][i] == adventurer){
    		advFlag = 1;
    	}
    }
    //printf("contains adventurer card? %d\texpected: 0\n", advFlag);
    if(!assertTrue(advFlag, 0)){
    	printf("\tTEST 2c FAILURE: hand contains adventurer card: %d\texpected: 0\n", advFlag);
    	testHolder=0;
    }

    if(testHolder){printf("TEST 2c SUCCESS\n");}
   		else{printf("TEST 2c FALURE\n");testScore=0;}

   		testHolder = 1;

/************************/

 printf("\nTest 2d : 0 treasure cards in deck\n");
    //copy game state to test game
    memcpy(&testG, &G, sizeof(struct gameState));


    // fill deck with estate cards
    for(i = 0; i < deckCount; i++){
    	testG.deck[currentPlayer][i] = 1;
    }

     playAdventurer(&testG, currentPlayer);  

    //printf("hand size: %d\texpected: %d\n", testG.handCount[currentPlayer], G.handCount[currentPlayer]-1);
    if(!assertTrue(testG.handCount[currentPlayer], G.handCount[currentPlayer]-1)){
    	printf("\tTEST 2d FAILURE: hand size: %d\texpected: %d\n", testG.handCount[currentPlayer], G.handCount[currentPlayer]-1);
    	testHolder=0;
    }

    for(i = 0; i < testG.handCount[currentPlayer];i++){
    	if(!assertTrue(testG.hand[currentPlayer][i], G.hand[currentPlayer][i])){
    		printf("\tTEST 2d FAILURE: handPos %d: %d\texpected: %d\n", i+1, testG.hand[currentPlayer][i], G.hand[currentPlayer][i]);
    		testHolder=0;
    	}
    	//printf("handPos %d: %d\texpected: %d\n", i+1, testG.hand[currentPlayer][i], G.hand[currentPlayer][i]);
    }

    for(i = 0; i < testG.handCount[currentPlayer]-1; i++){
    	if (testG.hand[currentPlayer][i] == adventurer){
    		advFlag = 1;
    	}
    }
    //printf("contains adventurer card? %d\texpected: 0\n", advFlag);
    if(!assertTrue(advFlag, 0)){
    	printf("\tTEST 2d FAILURE: hand contains adventurer card: %d\texpected: 0\n", advFlag);
    	testHolder=0;
    }

    if(testHolder){printf("TEST 2d SUCCESS\n");}
   		else{printf("TEST 2c FALURE\n");testScore=0;}

   		testHolder = 1;

 
  if(testScore){printf("adventurer card: PASS\n");}
   		else{printf("adventurer card: FAIL\n");}   

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
