/************************************************
 * Name: Molly Arwood
 * Date: 10-25-17
 * Class: CS_362_SE2
 * randomtestcard3.c - Council Room Test
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
#define TESTCARD = "council_room"
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
	//testing council room
	*********************************************/
	printf("\n\n-------------Testing Council Room--------------\n\n");

	//initialize game
	for (i = 0; i < 11000; i++) {
		for (j=0; j < sizeof(struct gameState); j++) {
			((char*)&G)[i] = floor(rand() % 256);
		}
	
		//General
		G.playedCardCount = floor(rand() % 500);
		G.numPlayers = 2;

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
		//councilRoomEffect(currPlayer, &G, 0);
		cardEffect(council_room, -1, -1, -1, &G, 0, &coin_bonus);

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

	/**********************************
	 *Direct Tests
	 *********************************/

	//hand count decreases by 3 (one discarded, 4 drawn)
	if (G->handCount[currPlayer] != Gconst->handCount[currPlayer] + 3) {
		printf("G handCount: %d \t Gconst: %d \n", G->handCount[currPlayer], Gconst->handCount[currPlayer]);
		printf("FAILED: current hand count increased by 3 \n\n");
		*passed = 0;
	}


	//deck count decreased by 4
	if (G->deckCount[currPlayer] != Gconst->deckCount[currPlayer] - 4 && Gconst->deckCount[currPlayer] > 3) {
		printf("FAILED: deck count decreased by 4\n\n");
		*passed = 0;
	}


	//player's buys increased by one
	if (G->numBuys != Gconst->numBuys + 1) {
		printf("FAILED: number of buys increased by 1\n\n");
		*passed = 0;
	}


	/**********************************
	 *Side Effect Tests
	 *********************************/
	
	//handCount comparison
	if (G->handCount[player2] != Gconst->handCount[player2] + 1) {
		printf("FAILED other player's handCount did not increase\n");
		*passed = 0;
	}


	//deck comparision
	if (G->deckCount[player2] == Gconst->deckCount[player2] && Gconst->deckCount[player2] != 0) {
		printf("FAILED: other player's deckCount altered\n");
		*passed = 0;
	}

	//discard count
	if (G->discardCount[player2] != Gconst->discardCount[player2] && Gconst->deckCount[player2] != 0) {
		printf("FAILED: other player's discardCount altered\n");
		*passed = 0;
	}

}


void addbugs(int player, struct gameState *G) {

	//handCount check
	G->handCount[player] = G->handCount[player] - 1;

	//deckCount check
	G->deckCount[player] = G->deckCount[player] -2;

	//numActions check
	G->numBuys++;

}