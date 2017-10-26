/************************************************
 * Name: Molly Arwood
 * Date: 10-25-17
 * Class: CS_362_SE2
 * randomtestcard2.c - Great Hall Test
************************************************/


#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#include <time.h>
#include <math.h>

//constants and prototypes
#define TESTCARD = "great_hall"
#define ADDBUGS 0

void checkResults(struct gameState *, struct gameState *, int *);
void addbugs(int player, struct gameState *);



int main() {

	/*********************************************
	//Initial Setup
	*********************************************/
	struct gameState G;
	struct gameState Gconst;
	srand(time(NULL));
	int currPlayer = 0;
	int coin_bonus = 0;	
	int i = 0;
	int j = 0;
	int passed = 1;
	int k[10] = {adventurer, great_hall, council_room, village, minion, mine, 
		   		cutpurse, sea_hag, tribute, smithy};


	/*********************************************
	//testing great hall
	*********************************************/
	printf("\n\n-------------Testing Great Hall--------------\n\n");

	//initialize game
	for (i = 0; i < 2000; i++) {
		for (j=0; j < sizeof(struct gameState); j++) {
			((char*)&G)[i] = floor(rand() % 256);
		}
	
		//General
		G.playedCardCount = floor(rand() % 500);

		//player 1
		G.whoseTurn = currPlayer;
		G.handCount[currPlayer] = floor(rand() % 500);
		G.deckCount[currPlayer] = floor(rand() % 500);
		G.discardCount[currPlayer] = floor(rand() % 500);

		//player 2
		G.handCount[currPlayer + 1] = floor(rand() % 500);
		G.deckCount[currPlayer + 1] = floor(rand() % 500);
		G.discardCount[currPlayer + 1] = floor(rand() % 500);

		//play great hall card
		memcpy(&Gconst, &G, sizeof(struct gameState));
		cardEffect(great_hall, -1, -1, -1, &G, 0, &coin_bonus);

		if (ADDBUGS) {

			//direct bugs
			addbugs(currPlayer, &G);

			//side effect bugs
			addbugs(currPlayer + 1, &G);
		}

		checkResults(&G, &Gconst, &passed);	
	}
	if (passed) {
		printf("All Tests Passed \n\n");
	}


	return 0;
}


void checkResults(struct gameState *G, struct gameState *Gconst, int *passed) {

	int currPlayer = whoseTurn(G);
	int player2 = currPlayer + 1;
	int victorySupply[3] = {Gconst->supplyCount[1], Gconst->supplyCount[2], Gconst->supplyCount[3]};
	int kingdomSupply[20];
	int i;
	for (i = 0; i < 20; i++) {
		kingdomSupply[i] = Gconst->supplyCount[i+7];
	}



	/**********************************
	 *Direct Tests
	 *********************************/

	//hand count stays same (one discarded and one drawn)
	if (G->handCount[currPlayer] != Gconst->handCount[currPlayer]) {
		printf("FAILED: one card drawn to hand \n\n");
		*passed = 0;
	}


	//deck count decreased (card discarded into separate pile)
	if (G->deckCount[currPlayer] != Gconst->deckCount[currPlayer] - 1 && Gconst->deckCount[currPlayer] > 0) {
		printf("FAILED: deck count decreased by 1\n\n");
		*passed = 0;
	}


	//player's actions increased by one
	if (G->numActions != Gconst->numActions + 1) {
		printf("FAILED: number of actions increased by 1\n\n");
		*passed = 0;
	}


	//checking victory card pile
	for (i = 0; i < sizeof(victorySupply) / sizeof(int); i++) {
		if (victorySupply[i] != G->supplyCount[i+1]) {
			printf("FAILED: victory cards unchanged\n\n");
			*passed = 0;
		}
	}


	//checking kingdom card pile
	for (i = 0; i < sizeof(kingdomSupply) / sizeof(int); i++) {
		if (kingdomSupply[i] != G->supplyCount[i+7]) {
			printf("FAILED: kingdom cards unchanged\n\n");
			*passed = 0;
		}
	}

	/**********************************
	 *Side Effect Tests
	 *********************************/

	//handCount comparison
	if (G->handCount[player2] != Gconst->handCount[player2]) {
		printf("FAILED other player's handCount altered\n");
		*passed = 0;
	}
	
	//deck comparision
	if (G->deckCount[player2] != Gconst->deckCount[player2]) {
		printf("FAILED: other player's deckCount altered\n");
		*passed = 0;
	}

	//discard count
	if (G->discardCount[player2] != Gconst->discardCount[player2]) {
		printf("FAILED: other player's discardCount altered\n");
		*passed = 0;
	}

}



void addbugs(int player, struct gameState *G) {

	//kingdomCard check
	G->supplyCount[8] = rand() % 10;

	//handCount check
	G->handCount[player] = G->handCount[player] - 1;

	//deckCount check
	G->deckCount[player] = G->deckCount[player] -5;

	//numActions check
	G->numActions++;

}
