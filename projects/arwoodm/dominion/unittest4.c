/************************************************
 * Name: Molly Arwood
 * Date: 10-11-17
 * Class: CS_362_SE2
 * unittest3.c - supplyCount Test
************************************************/


#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#include <time.h>

//constants and prototypes
//void supplyCheck(int cardSupply[], int cardChosen[], struct gameState *G);
void checkState(int stateReturned);


int main() {

	/*********************************************
	//Initial Setup
	*********************************************/
	struct gameState G;
	srand(time(NULL));
	int r = rand() % 100000000;
	int numPlayers = 2;
	int i = 0;
	int k[10] = {adventurer, great_hall, council_room, village, minion, mine, 
		   		cutpurse, sea_hag, treasure_map, smithy};

	//initialize game
	initializeGame(numPlayers, k, r, &G);
	printf("\n\n-------------Testing supplyCheck --------------\n\n");



	/*********************************************
	//variables setup for tests
	*********************************************/
	int cardChosen[5] = {0, 1, 4, 7, 26};
	int randNums[5] = {4, 0, -1, 22, 100};
	int currPlayer = whoseTurn(&G);


	/*********************************************
	//Testing
	*********************************************/
	for (i = 0; i < sizeof(cardChosen) / sizeof(int); i++) {
		G.supplyCount[cardChosen[i]] = randNums[i];
	}


	for (i = 0; i < 5; i++) {
		if (randNums[i] == supplyCount(cardChosen[i], &G)) {
			printf("PASSED: supply of %d card is same: %d to %d\n\n", cardChosen[i], randNums[i], supplyCount(cardChosen[i], &G));
		}
		else {
			printf("FAILED: supply of %d cards is not same: %d to %d \n\n", cardChosen[i], randNums[i], supplyCount(cardChosen[i], &G));
		}
	}



	printf("\n\n");
	return 0;


}