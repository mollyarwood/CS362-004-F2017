/************************************************
 * Name: Molly Arwood
 * Date: 10-25-17
 * Class: CS_362_SE2
 * randomtestcard1.c - Adventurer Test
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
#define TESTCARD = "Adventurer"
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
	int r = rand() % 100000000;
	int numPlayers = 2;
	int currPlayer = 0;
	int coin_bonus = 0;	
	int i = 0;
	int j = 0;
	int passed = 1;
	int k[10] = {adventurer, gardens, council_room, village, minion, mine, 
		   		cutpurse, sea_hag, tribute, smithy};


	/*********************************************
	//testing adventurer
	*********************************************/
	printf("\n\n-------------Testing Adventurer--------------\n\n");

	//initialize game
	for (i = 0; i < 500; i++) {
	//	for (j=0; j < sizeof(struct gameState); j++) {
	//		((char*)&G)[i] = floor(rand() % 256);
	//	}
		initializeGame(numPlayers, k, r, &G);

		//player 1
		G.whoseTurn = currPlayer;
		G.handCount[currPlayer] = floor(rand() % 500);
		G.deckCount[currPlayer] = floor(rand() % 500);
		G.discardCount[currPlayer] = floor(rand() % 500);
		G.supplyCount[4] = 60;
		G.supplyCount[5] = 40;
		G.supplyCount[6] = 30;

		//player 2
		G.handCount[currPlayer + 1] = floor(rand() % 500);
		G.deckCount[currPlayer + 1] = floor(rand() % 500);
		G.discardCount[currPlayer + 1] = floor(rand() % 500);

		//play adventurer card
		memcpy(&Gconst, &G, sizeof(struct gameState));
		cardEffect(adventurer, -1, -1, -1, &G, 0, &coin_bonus);

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
	int initialTreasure = 0; 
	int newTreasure = 0;
	int victorySupply[3] = {Gconst->supplyCount[1], Gconst->supplyCount[2], Gconst->supplyCount[3]};
	int kingdomSupply[20];
	int i;


	for (i = 0; i < 20; i++) {
		kingdomSupply[i] = Gconst->supplyCount[i+7];
	}

	//calculating new treasure cards in deck
	for (i = 0; i < G->deckCount[currPlayer]; i++) {
		if (G->deck[currPlayer][i] == copper || G->deck[currPlayer][i] == silver || G->deck[currPlayer][i] == gold) {
			newTreasure++;
		}
	}

	//calculating initial treasure cards in deck
	for (i = 0; i < Gconst->deckCount[currPlayer]; i++) {
		if (Gconst->deck[currPlayer][i] == copper || Gconst->deck[currPlayer][i] == silver || Gconst->deck[currPlayer][i] == gold) {
			initialTreasure++;
		}
	}


	/**********************************
	 *Direct Tests
	 *********************************/

	//hand count increase
	if (G->handCount[currPlayer] != Gconst->handCount[currPlayer] + 2) {
		printf("FAILED: current hand count increase\n\n");
		*passed = 0;
	} 


	//current hand's money increase. if player's deck has not decreased in treasures, it fails (cuz treasure should now be in hands). 
	if (newTreasure != initialTreasure - 2) {
		printf("G supplyCount: %d \t Gconst: %d \n", newTreasure, initialTreasure);
		printf("FAILED: current hand treasure differs from expected\n\n");
		*passed = 0;
	}


	//deck count decrease
	if ((G->deckCount[currPlayer] >= Gconst->deckCount[currPlayer]) && Gconst->deckCount[currPlayer] > 1) {
		printf("FAILED: deck count decrease test\n\n");
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

	//victoryCard check
	G->supplyCount[1] = rand() % 10;

	//handCount check
	G->handCount[player] = G->handCount[player] - 1;

	//deckCount check
	G->deckCount[player] = G->deckCount[player] -5;

}


