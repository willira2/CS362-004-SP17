#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <string.h>
#include <stdio.h>
#include <time.h>

#define TEST_NUMBER 50

//random test for adventurer card

int assertTrue(int, int);
int randomGame(struct gameState*);
int containsCard(int, int, int[]);

int main(){
	int testHolder = 1, testScore = 1, advCount1 = 0, advCount2 = 0;
	int i, j, m;
	struct gameState masterG, controlG, testG;

	srand(time(NULL));

	//run test 50 times
	for(i = 0; i < TEST_NUMBER; i++){
		//initialize random master game
		memset(&masterG, 23, sizeof(struct gameState));
		while(randomGame(&masterG)!=0){};

		//play adventurer for each player in random game
		for(j = 0; j < masterG.numPlayers; j++){
			//copy master game to control game
			memcpy(&controlG, &masterG, sizeof(struct gameState));
			
			controlG.whoseTurn = j;

			for (m = 0; m < 5; m++){
		   		drawCard(j, &controlG);
		 	}
		  	updateCoins(controlG.whoseTurn, &controlG, 0);

		  	controlG.hand[j][0] = adventurer;

		  	for(m = 0; m < controlG.handCount[j]; m++){
				if (controlG.hand[j][m] == adventurer){
					advCount1++;
				}
		    }

		    printf("handCount: %d\n", controlG.handCount[j]);
		    printf("deckCount: %d\n", controlG.deckCount[j]);
			
			//copy control game to test game
			memcpy(&testG, &controlG, sizeof(struct gameState));


			//play adventurer card
			playAdventurer(&testG, j);

		    for(m = 0; m < controlG.handCount[m]-1; m++){
		    	if (testG.hand[m][i] == adventurer){
		    		advCount2++;
		    	}
		    }

			//compare control and test games
			if(!assertTrue(testG.handCount[j], controlG.handCount[j]+1)){
		    	printf("\tTEST FAILURE: hand size: %d\texpected: %d\n", testG.handCount[j], controlG.handCount[j]+1);
		    	testHolder=0;
		    }
		    
		    if(!assertTrue(advCount1-1, advCount2)){
		    	printf("\tTEST FAILURE: adventurer cards in hand: %d\texpected: %d\n", advCount2, advCount1-1);
		    	testHolder=0;
		    }

		    if(testHolder){printf("TEST SUCCESS\n");}
   			else{printf("TEST FAILURE\n");testScore=0;}

   			testHolder = 1;
   			advCount1 = 0;
   			advCount2 = 0;
		}
	}

  if(testScore){printf("smithy card: PASS\n");}
   		else{printf("smithy card: FAIL\n");}  
	
	return 0;
}

/****************************************
Function: assertTrue
*****************************************/
int assertTrue(int a, int b){
	if(a == b){return 1;}
	else{return 0;}
}

/****************************************
Function: randomGame
*****************************************/
int randomGame(struct gameState* controlG){
	//random number of players
	//9 random kingdom cards + adventurer card
	//give deck random size then fill with random cards (pull from kingdom card list + treasure cards)
	//repeat for hand and discard, but make sure adventurer is in hand

	int p, m, i, j, r, s, addCard;
	int seed = 1000;
	int k[10] = {-1};
	k[0] = adventurer;

	p = rand() % MAX_PLAYERS + 1;
	m = 1;
	while(m < 10){
		r = rand() % 19 + 8;

		if(!containsCard(r, 10, k)){
			k[m] = r;
			m++;
		}
	}

	//set up random number generator
	SelectStream(1);
	PutSeed((long)seed);

	//check number of players
	if (p > MAX_PLAYERS || p < 2){return -1;}

  	//set number of players
  	controlG->numPlayers = p;

	//check selected kingdom cards are different
	for (i = 0; i < 10; i++){
	  for (j = 0; j < 10; j++){
	  	if (j != i && k[j] == k[i]){return -1;}
	  }
	}


  //initialize supply
  ///////////////////////////////

  //set number of Curse cards
  if (p == 2)
    {
      controlG->supplyCount[curse] = 10;
    }
  else if (p == 3)
    {
      controlG->supplyCount[curse] = 20;
    }
  else
    {
      controlG->supplyCount[curse] = 30;
    }

  //set number of Victory cards
  if (p == 2)
    {
      controlG->supplyCount[estate] = 8;
      controlG->supplyCount[duchy] = 8;
      controlG->supplyCount[province] = 8;
    }
  else
    {
      controlG->supplyCount[estate] = 12;
      controlG->supplyCount[duchy] = 12;
      controlG->supplyCount[province] = 12;
    }

  //set number of Treasure cards
  controlG->supplyCount[copper] = 60 - (7 * p);
  controlG->supplyCount[silver] = 40;
  controlG->supplyCount[gold] = 30;

  //set number of Kingdom cards
  for (i = adventurer; i <= treasure_map; i++)       	//loop all cards
    {
      for (j = 0; j < 10; j++)           		//loop chosen cards
    	{
    	  if (k[j] == i)
    	    {
    	      //check if card is a 'Victory' Kingdom card
    	      if (k[j] == great_hall || k[j] == gardens){
          		  if (p == 2){ 
          		    controlG->supplyCount[i] = 8; 
          		  }
          		  else{controlG->supplyCount[i] = 12; }
    		      }
    	      
            else{
        		  controlG->supplyCount[i] = 10;
        		}
    	      break;
  	       }
    	  else    //card is not in the set choosen for the game
    	    {
    	      controlG->supplyCount[i] = -1;
    	    }
  	}

    }

	//set player decks
	for (m = 0; m < p; m++)
	{
	  controlG->deckCount[m] = 0;
	  s = rand() % MAX_DECK + 1;

	  while(controlG->deckCount[m] < s){
	  	r = rand() % 15 + 1;
	  	if(r > 10){
	  		switch (r){
	  			case 11:
	  				addCard = copper;
	  				break;
	  			case 12:
	  				addCard = silver;
	  				break;
	  			case 13:
	  				addCard = gold;
	  				break;
	  			case 14:
	  				addCard = estate;
	  				break;
	  			case 15:
	  				addCard = duchy;
	  				break;
	  			case 16:
	  				addCard = province;
	  				break;
	  		}
	  	}
	  	else{
	  		addCard = k[r];
	  	}
	  	
  		controlG->deck[m][controlG->deckCount[m]] = addCard;
  		controlG->deckCount[m]++;
	  	
	  }
	}

	//shuffle player decks
	for (i = 0; i < p; i++)
	{
	  if ( shuffle(i, controlG) < 0 )
		{
		  return -1;
		}
	}

	//set player hand counts
	for (i = 0; i < p; i++)
	{  
	  //initialize hand size to zero
	  controlG->handCount[i] = 0;
	  controlG->discardCount[i] = 0;
	}
  
  //set embargo tokens to 0 for all supply piles
  for (i = 0; i <= treasure_map; i++)
    {
      controlG->embargoTokens[i] = 0;
    }

  //initialize first player's turn
  controlG->outpostPlayed = 0;
  controlG->phase = 0;
  controlG->numActions = 1;
  controlG->numBuys = 1;
  controlG->playedCardCount = 0;
  controlG->whoseTurn = 0;
  controlG->handCount[controlG->whoseTurn] = 0;

  return 0;
}


/****************************************
Function: containsCard
*****************************************/
int containsCard(int c, int s, int arr[]){
	int i;
	for(i = 0; i < s; i++){
		if(arr[i] == c)
			return 1;
	}
	return 0;
}

