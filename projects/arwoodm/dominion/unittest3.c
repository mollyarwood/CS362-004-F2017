/************************************************
 * Name: Molly Arwood
 * Date: 10-11-17
 * Class: CS_362_SE2
 * unittest3.c - whoseTurn Test
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
	srand(time(NULL));
	int r = rand() % 100000000;
	int numPlayers = 2;
	int i = 0;
	int k[10] = {adventurer, great_hall, council_room, village, minion, mine, 
		   		cutpurse, sea_hag, treasure_map, smithy};

	//initialize game
	initializeGame(numPlayers, k, r, &G);
	printf("\n\n-------------Testing whoseTurn --------------\n\n");


	/*********************************************
	//Testing
	*********************************************/
	int errFlag = 0;

	for (i = 0; i < 10; i++) {

		G.whoseTurn = i;

		if (whoseTurn(&G) != i) {
			errFlag = 1;
		}
	}

	if (!errFlag) {
		printf("PASSED: Correct players returned during testing\n\n");
	}
	else {
		printf("FAILED: Incorrect players returned during testing\n\n");
	}



	printf("\n\n");
	return 0;


}