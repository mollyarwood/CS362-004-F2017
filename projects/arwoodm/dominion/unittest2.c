/************************************************
 * Name: Molly Arwood
 * Date: 10-11-17
 * Class: CS_362_SE2
 * unittest2.c - isGameOver Test
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
void checkState(int stateReturned);


int main() {

	/*********************************************
	//Initial Setup
	*********************************************/
	struct gameState G;
	//struct gameState *Gpoint = &G;
	//struct gameState Gconst;
	srand(time(NULL));
	int r = rand() % 100000000;
	int numPlayers = 2;
	int coin_bonus = 0;	
	int i = 0;
	int j = 0;
	int k[10] = {adventurer, great_hall, council_room, village, minion, mine, 
		   		cutpurse, sea_hag, treasure_map, smithy};

	//initialize game
	initializeGame(numPlayers, k, r, &G);
	//memcpy(&Gconst, &G, sizeof(struct gameState));
	printf("\n\n-------------Testing isGameOver--------------\n\n");

	/*********************************************
	//variables setup for tests
	*********************************************/
	int province = 3;
	int stateReturned;
	int origProvince = G.supplyCount[province];
	int origSupplies[10];

	for (i = 0; i < sizeof(k) / sizeof(int); i++) {
		origSupplies[i] = G.supplyCount[k[i]];
	}

	/*********************************************
	//Testing
	*********************************************/

	//no cards at 0 - game should not end
	printf("-- No card supplies at 0: \n\n");
	stateReturned = isGameOver(&G);
	checkState(!stateReturned);



	//set Province card supply equal to 0
	printf("-- Set province supply to 0: \n\n");
	G.supplyCount[province] = 0;
	stateReturned = isGameOver(&G);
	checkState(stateReturned);

	//reset
	G.supplyCount[province] = origProvince;



	//three supply piles are at 0
	printf("-- Set 3 card supplies to 0: \n\n");
	for (i = 0; i < 3; i++) {
		G.supplyCount[k[i]] = 0;
	}
	stateReturned = isGameOver(&G);
	checkState(stateReturned);

	//reset
	for (i = 0; i < 3; i++) {
		G.supplyCount[k[i]] = origSupplies[i];
	}



	// >3 supply piles are at 0
	printf("-- Set 5 card supplies to 0: \n\n");
	for (i = 0; i < 5; i++) {
		G.supplyCount[k[i]] = 0;
	}
	stateReturned = isGameOver(&G);
	checkState(stateReturned);

	//reset
	for (i = 0; i < 5; i++) {
		G.supplyCount[k[i]] = origSupplies[i];
	}




	//set 2 supply piles to 0
	printf("-- Set 2 card supplies to 0: \n\n");
	for (i = 0; i < 2; i++) {
		G.supplyCount[k[i]] = 0;
	}
	stateReturned = isGameOver(&G);
	checkState(!stateReturned);

	//reset
	for (i = 0; i < 2; i++) {
		G.supplyCount[k[i]] = origSupplies[i];
	}



	printf("\n\n");
	return 0;
}




void checkState(int stateReturned) {
	if (stateReturned == 1) {
		printf("PASSED: game results as expected\n\n");
	}
	else {
		printf("FAILED: game results not as expected\n\n");
	}
}
