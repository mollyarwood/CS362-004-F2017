/************************************************
 * Name: Molly Arwood
 * Date: 10-11-17
 * Class: CS_362_SE2
 * cardtest1.c - Smithy Test
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
#define TESTCARD = "smithy"
int structComparer(struct gameState *, struct gameState *, int);




int main() {

	/*********************************************
	//Initial Setup
	*********************************************/
	struct gameState G;
	struct gameState Gconst;
	srand(time(NULL));
	int r = rand() % 100000000;
	int numPlayers = 2;
	int coin_bonus = 0;	
	int i = 0;
	int k[10] = {adventurer, gardens, council_room, village, minion, mine, 
		   		cutpurse, sea_hag, tribute, smithy};

	//initialize game
	initializeGame(numPlayers, k, r, &G);
	memcpy(&Gconst, &G, sizeof(struct gameState));
	printf("\n\n-------------Testing Smithy--------------\n\n");



	/*********************************************
	//variables before smithy played
	*********************************************/
	int currPlayer = whoseTurn(&G);
	int cardsInHand = G.handCount[currPlayer];
	int deckCount = G.deckCount[currPlayer];
	int victorySupply[3] = {G.supplyCount[1], G.supplyCount[2], G.supplyCount[3]};
	int kingdomSupply[20];
	for (i = 0; i < 20; i++) {
		kingdomSupply[i] = G.supplyCount[i+7];
	}


	//play Smithy card
	cardEffect(smithy, -1, -1, -1, &G, 0, &coin_bonus);



	/********************************************
	//variables after smithy played
	********************************************/

	//hand count increase
	if (G.handCount[currPlayer] == cardsInHand + 3) {
		printf("PASSED: current hand count increase\n\n");
	} 
	else {
		printf("FAILED: current hand count increase\n\n");
	}


	//deck count decrease
	if (G.deckCount[currPlayer] == deckCount - 3) {
		printf("PASSED: deck count decrease\n\n");
	}
	else {
		printf("FAILED: deck count decrease\n\n");
	}


	//checking victory card pile
	int flag = 1;
	for (i = 0; i < sizeof(victorySupply) / sizeof(int); i++) {
		if (victorySupply[i] != G.supplyCount[i+1]) {
			flag = 0;
		}
	}
	if (flag) {
		printf("PASSED: victory cards unchanged\n\n");
	}
	else {
		printf("FAILED: victory cards unchanged\n\n");
	}


	//checking kingdom card pile
	flag = 1;
	for (i = 0; i < sizeof(kingdomSupply) / sizeof(int); i++) {
		if (kingdomSupply[i] != G.supplyCount[i+7]) {
			flag = 0;
		}
	}
	if (flag) {
		printf("PASSED: kingdom cards unchanged\n\n");
	}
	else {
		printf("FAILED: kingdom cards unchanged\n\n");
	}


	//checking other player's state
	currPlayer = whoseTurn(&G) + 1;

	int flag2 = structComparer(&Gconst, &G, currPlayer);
	if (flag2 == 1) {
		printf("PASSED: other player's handCount unchanged\n\n");
		printf("PASSED: other player's deck unchanged\n\n");
		printf("PASSED: other player's discard count unchanged\n\n");
	}



	printf("\n\n");

	return 0;
}




int structComparer(struct gameState *state1, struct gameState *state2, int player2) {
	int i = 0;
	int flag = 1;


	//handCount comparison
	if (state1->handCount[player2] != state2->handCount[player2]) {
		flag = 0;
		printf("FAILED ohter player's handCount altered\n");
	}
	
	//deck comparision
	if (state1->deckCount[player2] != state2->deckCount[player2]) {
		flag = 0;
		printf("FAILED: other player's deckCount altered\n");
	}

	//discard count
	if (state1->discardCount[player2] != state2->discardCount[player2]) {
		flag = 0;
		printf("FAILED: other player's discardCount altered\n");
	}

	return flag;
}