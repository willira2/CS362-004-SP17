#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <string.h>
#include <stdio.h>

//test for salvager

const char* getCardName(enum CARD);
int assertTrue(int, int);

int main() {
	int i, j, x;
    int seed = 1000, testHolder = 1, testScore = 1;;
    int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0, salvFlag = 0;
    int numPlayer = 2, currentPlayer = 0;
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    struct gameState G, testG;

	// initialize a new game state
    initializeGame(numPlayer, k, seed, &G); 

    printf("TESTING salvager card\n");

 	//value of numbuys before and after
    //send every card to the function and check value of coins against expected
    	//check playedcard count, playedcard pile(shouldn't be in playedcards), handcount, and hand for values
    //send null to function, check playedcard count, playedcard pile(should be in playedcards), handcount, and hand for values

	for(x = 0; x < G.handCount[currentPlayer]; x++){ 
	//copy game state to test game
	memcpy(&testG, &G, sizeof(struct gameState));
	
	//play choice1 using every card and from every hand position 
	choice1 = x;

	//put salvager into hand
	if((x+1)>=G.handCount[currentPlayer]){
		handpos = 0;
		G.hand[currentPlayer][handpos] = salvager;
	}
	else{
		handpos=x+1;
		G.hand[currentPlayer][handpos] = salvager;
	}
    
	    for(i = 0; i < 26; i++){
	    	printf("TEST %d handPos[%d]: choice1 = %s in position %d\n", i+1, handpos, getCardName(i), x);

	    	//copy game state to test game
	    	memcpy(&testG, &G, sizeof(struct gameState));

	    	//put card in hand
	    	testG.hand[currentPlayer][x] = i;

	   		//printf("*Function call*\nResults:\n");
	    	cardEffect(salvager, choice1, choice2, choice3, &testG, handpos, &bonus);

			if(!assertTrue(testG.numBuys, G.numBuys+1)){
				printf("\tTEST %d handPos[%d] FAILURE: numbuys: %d\texpected: %d\n", i+1, x, testG.numBuys, G.numBuys+1);
				testHolder=0;
			}
			if(!assertTrue(testG.coins, G.coins+getCost(i))){
				printf("\tTEST %d handPos[%d] FAILURE: coins: %d\texpected: %d\n", i+1, x, testG.coins, G.coins+getCost(i));
				testHolder=0;
			}
			if(!assertTrue(testG.playedCards[testG.playedCardCount-1], 24)){
				printf("\tTEST %d handPos[%d] FAILURE: last card in playedCards = %d\texpected = 24\n", i+1, x, testG.playedCards[testG.playedCardCount-1]);
				testHolder=0;
			}

			if(!assertTrue(testG.playedCardCount, G.playedCardCount+1)){
				printf("\tTEST %d handPos[%d] FAILURE: hand count: %d\texpected: %d\n", i+1, x, testG.handCount[0], G.handCount[0]-2);
				testHolder=0;
			}

	    	/*printf("numbuys: %d\texpected: %d\n", testG.numBuys, G.numBuys+1);
	    	printf("coins: %d\texpected: %d\n", testG.coins, G.coins+getCost(i));
	    	printf("last card in playedCards = %d\texpected = %d\n", testG.playedCards[testG.playedCardCount-1], G.hand[0][0]);
	    	printf("playedCardCount = %d\texpected = %d\n", testG.playedCardCount, G.playedCardCount+1);
	    	printf("hand count: %d\texpected: %d\n", testG.handCount[0], G.handCount[0]-2);*/

	    	for(j = 0; j < testG.handCount[currentPlayer]-1; j++){
	    		if (testG.hand[currentPlayer][j] == salvager){
	    			salvFlag = 1;
	    		}
	    	}
	   		//printf("AFTER: contains salvager card? %d\texpected: 0\n\n******\n", salvFlag);
	   		if(i == salvager){
	   			if(!assertTrue(salvFlag, 1)){
					printf("\tTEST %d handPos[%d] FAILURE: hand contains salvager card: %d\texpected: 1\n", i+1, x, salvFlag);
	   				testHolder=0;
	   			}
	   		}
	   		else{
	   			if(!assertTrue(salvFlag, 0)){
					printf("\tTEST %d handPos[%d] FAILURE: hand contains salvager card: %d\texpected: 0\n", i+1, x, salvFlag);
	   				testHolder=0;
	   			}
	   		}

	   		if(testHolder){printf("****TEST %d handPos[%d] SUCCESS****\n\n", i+1, x);}
	   		else{printf("*****TEST %d handPos[%d] FAILURE****\n\n", i+1, x);testScore=0;}

	   		testHolder = 1;

	    }
	}

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