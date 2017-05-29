#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <string.h>
#include <stdio.h>

#define ARRLEN(x) (sizeof(x)/sizeof(x[0]))

// test getCost()

int assertTrue(int, int);

int main(){
  enum CARD cost0[2] = {curse, copper};
  enum CARD cost2[2] = {estate, embargo};
  enum CARD cost3[5] = {silver, village, great_hall, steward, ambassador};
  enum CARD cost4[9] = {feast, gardens, remodel, smithy, baron, cutpurse, salvager, sea_hag, treasure_map};
  enum CARD cost5[6] = {duchy, council_room, mine, minion, tribute, outpost};
  enum CARD cost6[2] = {gold, adventurer};
  enum CARD cost8[1] = {province};

  int i, result, testHolder = 1, testScore = 1;

  //TEST 1 : 0 cost cards
  printf("TEST 1: 0 cost cards\n");
  for(i = 0; i < ARRLEN(cost0); i++){
    result = getCost(cost0[i]);
    if(!assertTrue(result, 0)){
      printf("\tTEST 1 CARD %d FAILURE: result: %d\texpected: 0\n", i, result);
      testHolder = 0;
    }
  }

  if(testHolder){printf("TEST 1 SUCCESS\n");}
  else{printf("TEST 1 FAILURE\n"); testScore = 0;}

  testHolder = 1;

  //TEST 2 : 2 cost cards
  printf("TEST 2: 2 cost cards\n");
  for(i = 0; i < ARRLEN(cost2); i++){
    result = getCost(cost2[i]);
    if(!assertTrue(result, 2)){
      printf("\tTEST 2 CARD %d FAILURE: result: %d\texpected: 2\n", i, result);
      testHolder = 0;
    }
  }

  if(testHolder){printf("TEST 2 SUCCESS\n");}
  else{printf("TEST 2 FAILURE\n"); testScore = 0;}

  testHolder = 1;

  //TEST 3 : 3 cost cards
  printf("TEST 3: 3 cost cards\n");
  for(i = 0; i < ARRLEN(cost3); i++){
    result = getCost(cost3[i]);
    if(!assertTrue(result, 3)){
      printf("\tTEST 3 CARD %d FAILURE: result: %d\texpected: 3\n", i, result);
      testHolder = 0;
    }
  }

  if(testHolder){printf("TEST 3 SUCCESS\n");}
  else{printf("TEST 3 FAILURE\n"); testScore = 0;}

  testHolder = 1;

  //TEST 4 : 4 cost cards
  printf("TEST 4: 4 cost cards\n");
  for(i = 0; i < ARRLEN(cost4); i++){
    result = getCost(cost4[i]);
    if(!assertTrue(result, 4)){
      printf("\tTEST 4 CARD %d FAILURE: result: %d\texpected: 4\n", i, result);
      testHolder = 0;
    }
  }

  if(testHolder){printf("TEST 4 SUCCESS\n");}
  else{printf("TEST 4 FAILURE\n"); testScore = 0;}

  testHolder = 1;

  //TEST 5 : 5 cost cards
  printf("TEST 5: 5 cost cards\n");
  for(i = 0; i < ARRLEN(cost5); i++){
    result = getCost(cost5[i]);
    if(!assertTrue(result, 5)){
      printf("\tTEST 5 CARD %d FAILURE: result: %d\texpected: 5\n", i, result);
      testHolder = 0;
    }
  }

  if(testHolder){printf("TEST 5 SUCCESS\n");}
  else{printf("TEST 5 FAILURE\n"); testScore = 0;}

  testHolder = 1;

  //TEST 6 : 6 cost cards
  printf("TEST 6: 6 cost cards\n");
  for(i = 0; i < ARRLEN(cost6); i++){
    result = getCost(cost6[i]);
    if(!assertTrue(result, 6)){
      printf("\tTEST 6 CARD %d FAILURE: result: %d\texpected: 6\n", i, result);
      testHolder = 0;
    }
  }

  if(testHolder){printf("TEST 6 SUCCESS\n");}
  else{printf("TEST 6 FAILURE\n"); testScore = 0;}

  testHolder = 1;

  //TEST 7 : 8 cost cards
  printf("TEST 7: 8 cost cards\n");
  for(i = 0; i < ARRLEN(cost8); i++){
    result = getCost(cost8[i]);
    if(!assertTrue(result, 8)){
      printf("\tTEST 7 CARD %d FAILURE: result: %d\texpected: 8\n", i, result);
      testHolder = 0;
    }
  }

  if(testHolder){printf("TEST 7 SUCCESS\n");}
  else{printf("TEST 7 FAILURE\n"); testScore = 0;}

  testHolder = 1;

}

int assertTrue(int a, int b){
  if(a == b){return 1;}
  else{return 0;}
}
