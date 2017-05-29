#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <string.h>
#include <stdio.h>

//test for gainCard()

const char* getCardName(enum CARD);
int assertTrue(int, int);

int main() {
    int seed = 1000;
    int numPlayer = 2, testHolder = 1, testScore = 1;
    int i, p, result, expected;
    int supplyPos, toFlag;
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    struct gameState G, testG;

    // initialize a new game state
    initializeGame(numPlayer, k, seed, &G); 

    //test return value where supply pile of chosen card is empty
    //choose adventurer as supplyPos
    printf("TEST 1: supplyPos pile is empty\n");
    
        //copy game state to test game
        memcpy(&testG, &G, sizeof(struct gameState));
     
        supplyPos = adventurer;
        toFlag = 0;
        p = 1;
        testG.supplyCount[supplyPos] = 0; // set adventurer count to empty

        result = gainCard(supplyPos, &testG, toFlag, p);
        if(!assertTrue(result, -1)){
            testHolder=0; 
            testScore=0; 
            printf("\tTEST 1a FAILURE: result: %d\texpected: -1\n", result);
        }

        if(!assertTrue(testG.discardCount[0], G.discardCount[0])){
            printf("\tTEST 1b FAILURE: discard count: %d\texpected: %d\n", testG.discardCount[0], G.discardCount[0]);
            testHolder=0;
            testScore=0;
        }

        if(!assertTrue(testG.deckCount[0], G.deckCount[0])){
            printf("\tTEST 1c FAILURE: deck count: %d\texpected: %d\n", testG.deckCount[0], G.deckCount[0]);
            testHolder=0;
            testScore=0;
        }


        if(!assertTrue(testG.handCount[0], G.handCount[0])){
            printf("\tTEST 1d FAILURE: hand count: %d\texpected: %d\n", testG.handCount[0], G.handCount[0]);
            testHolder=0;
            testScore=0;
        }

        for(i = 0; i < treasure_map+1; i++){
            if(i == supplyPos){expected = 0;}
            else{expected = G.supplyCount[i];}

            if(!assertTrue(testG.supplyCount[i], expected)){
                printf("\tTEST 1e FAILURE: supplyCount: %d\texpected: %d\n", testG.supplyCount[i], expected);
                testHolder=0;
                testScore=0;
            }
        }

        if(assertTrue(testHolder, 1)){printf("TEST 1 SUCCESS\n");}
        else{printf("TEST 1 FAILURE\n");}
            
    testHolder = 1;    

    //test return value where supply pile of chosen card is not in game
    //choose sea_hag as supplyPos
    printf("TEST 2: supplyPos not in game\n");
        
        //copy game state to test game
        memcpy(&testG, &G, sizeof(struct gameState));

        supplyPos = sea_hag;
        toFlag = 0;
        p = 1;

        result = gainCard(supplyPos, &testG, toFlag, p);
        
        if(!assertTrue(result, -1)){
            printf("\tTEST 2a FAILURE: result: %d\texpected: -1\n", result);
            testHolder=0; 
            testScore=0;  
        }

        if(!assertTrue(testG.discardCount[0], G.discardCount[0])){
            printf("\tTEST 2b FAILURE: discard count: %d\texpected: %d\n", testG.discardCount[0], G.discardCount[0]);
            testHolder=0;
            testScore=0;
        }

        if(!assertTrue(testG.deckCount[0], G.deckCount[0])){
            printf("\tTEST 2c FAILURE: deck count: %d\texpected: %d\n", testG.deckCount[0], G.deckCount[0]);
            testHolder=0;
            testScore=0;
        }

        if(!assertTrue(testG.handCount[0], G.handCount[0])){
            printf("\tTEST 2d FAILURE: hand count: %d\texpected: %d\n", testG.handCount[0], G.handCount[0]);
            testHolder=0;
            testScore=0;
        }

        for(i = 0; i < treasure_map+1; i++){
            if(!assertTrue(G.supplyCount[i],testG.supplyCount[i])){
                printf("\tTEST 2e FAILURE: supplyCount: %d\texpected: %d\n", testG.supplyCount[i], G.supplyCount[i]);
                testHolder=0;
                testScore=0;
            }
        }

        if(assertTrue(testHolder, 1)){printf("TEST 2 SUCCESS\n");}
        else{printf("TEST 2 FAILURE\n");}
    
    // test when toFlag == 0 (discard)
    printf("TEST 3: toFlag = 0\n");

        //copy game state to test game
        memcpy(&testG, &G, sizeof(struct gameState));

        toFlag = 0;
        supplyPos = adventurer;
        gainCard(supplyPos, &testG, toFlag, 0);

        if(!assertTrue(testG.discard[0][(testG.discardCount[0])-1], adventurer)){
            printf("TEST 3a FAILURE: last card is discard: %d\texpected: %d\n", testG.discard[0][(testG.discardCount[0])-1], adventurer);
            testHolder=0;
            testScore=0;
        }

        if(!assertTrue(testG.discardCount[0], G.discardCount[0]+1)){
            printf("\tTEST 3b FAILURE: discard count: %d\texpected: %d\n", testG.discardCount[0], G.discardCount[0]+1);
            testHolder=0;
            testScore=0;
        }

        if(!assertTrue(testG.deckCount[0], G.deckCount[0])){
            printf("\tTEST 3c FAILURE: deck count: %d\texpected: %d\n", testG.deckCount[0], G.deckCount[0]);
            testHolder=0;
            testScore=0;
        }

        if(!assertTrue(testG.handCount[0], G.handCount[0])){
            printf("\tTEST 3d FAILURE: hand count: %d\texpected: %d\n", testG.handCount[0], G.handCount[0]);
            testHolder=0;
            testScore=0;
        }

        for(i = 0; i < treasure_map+1; i++){
            if(i == supplyPos){expected = G.supplyCount[i]-1;}
            else{expected = G.supplyCount[i];}

            if(!assertTrue(testG.supplyCount[i], expected)){
                printf("\tTEST 3e FAILURE: supplyCount: %d\texpected: %d\n", testG.supplyCount[i], expected);
                testHolder=0;
                testScore=0;
            }
        }

        if(assertTrue(testHolder, 1)){
            printf("TEST 3 SUCCESS\n");
        }
        else{printf("TEST 3 FAILURE\n");}

        testHolder = 1;


    // test gainCard when toFlag == 1 (deck)
     printf("TEST 4: toFlag = 1\n");
        //copy game state to test game
        memcpy(&testG, &G, sizeof(struct gameState));

        toFlag = 1;
        supplyPos = adventurer;
        gainCard(supplyPos, &testG, toFlag, 0);

        if(!assertTrue(testG.deck[0][(testG.deckCount[0])-1], adventurer)){
            printf("TEST 4a FAILURE: last card is deck: %d\texpected: %d\n", testG.deck[0][(testG.deckCount[0])-1], adventurer);
            testHolder=0;
            testScore=0;
        }

       if(!assertTrue(testG.discardCount[0], G.discardCount[0])){
            printf("\tTEST 4b FAILURE: discard count: %d\texpected: %d\n", testG.discardCount[0], G.discardCount[0]+1);
            testHolder=0;
            testScore=0;
        }

        if(!assertTrue(testG.deckCount[0], G.deckCount[0]+1)){
            printf("\tTEST 4c FAILURE: deck count: %d\texpected: %d\n", testG.deckCount[0], G.deckCount[0]);
            testHolder=0;
            testScore=0;
        }

        if(!assertTrue(testG.handCount[0], G.handCount[0])){
            printf("\tTEST 4d FAILURE: hand count: %d\texpected: %d\n", testG.handCount[0], G.handCount[0]);
            testHolder=0;
            testScore=0;
        }

        for(i = 0; i < treasure_map+1; i++){
            if(i == supplyPos){expected = G.supplyCount[i]-1;}
            else{expected = G.supplyCount[i];}

            if(!assertTrue(testG.supplyCount[i], expected)){
                printf("\tTEST 4e FAILURE: supplyCount: %d\texpected: %d\n", testG.supplyCount[i], expected);
                testHolder=0;
                testScore=0;
            }
        }

        if(assertTrue(testHolder, 1)){
            printf("TEST 4 SUCCESS\n");
        }
        else{printf("TEST 4 FAILURE\n");}

        testHolder = 1;

    // test gainCard when toFlag == 2 (hand)
    printf("TEST 5: toFlag = 2\n");
        //copy game state to test game
        memcpy(&testG, &G, sizeof(struct gameState));

        toFlag = 2;
        supplyPos = adventurer;
        gainCard(supplyPos, &testG, toFlag, 0);

        if(!assertTrue(testG.hand[0][(testG.handCount[0])-1], adventurer)){
            printf("TEST 5a FAILURE: last card is hand: %d\texpected: %d\n", testG.hand[0][(testG.handCount[0])-1], adventurer);
            testHolder=0;
            testScore=0;
        }

        if(!assertTrue(testG.discardCount[0], G.discardCount[0])){
            printf("\tTEST 5b FAILURE: discard count: %d\texpected: %d\n", testG.discardCount[0], G.discardCount[0]+1);
            testHolder=0;
            testScore=0;
        }

        if(!assertTrue(testG.deckCount[0], G.deckCount[0])){
            printf("\tTEST 5c FAILURE: deck count: %d\texpected: %d\n", testG.deckCount[0], G.deckCount[0]);
            testHolder=0;
            testScore=0;
        }

        if(!assertTrue(testG.handCount[0], G.handCount[0]+1)){
            printf("\tTEST 5d FAILURE: hand count: %d\texpected: %d\n", testG.handCount[0], G.handCount[0]);
            testHolder=0;
            testScore=0;
        }

        for(i = 0; i < treasure_map+1; i++){
            if(i == supplyPos){expected = G.supplyCount[i]-1;}
            else{expected = G.supplyCount[i];}

            if(!assertTrue(testG.supplyCount[i], expected)){
                printf("\tTEST 5e FAILURE: supplyCount: %d\texpected: %d\n", testG.supplyCount[i], expected);
                testHolder=0;
                testScore=0;
            }
        }

        if(assertTrue(testHolder, 1)){
            printf("TEST 5 SUCCESS\n");
        }
        else{printf("TEST 5 FAILURE\n");}

        testHolder = 1;


        if(assertTrue(testScore, 1)){
            printf("gainCard() PASS\n");
        }
        else{printf("gainCard() FAIL\n");}

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
