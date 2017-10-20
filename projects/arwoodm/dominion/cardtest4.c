/************************************************
 * Name: Molly Arwood
 * Date: 10-11-17
 * Class: CS_362_SE2
 * cardtest1.c - Council Room Test
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
#define TESTCARD = "council_room"
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
	int k[10] = {adventurer, great_hall, council_room, village, remodel, mine, 
		   		cutpurse, sea_hag, tribute, smithy};

	//initialize game
	initializeGame(numPlayers, k, r, &G);
	memcpy(&Gconst, &G, sizeof(struct gameState));
	printf("\n\n-------------Testing Council Room--------------\n\n");



	/*********************************************
	//variables before council room played
	*********************************************/
	int currPlayer = whoseTurn(&G);
	int numBuys = G.numBuys;
	int cardsInHand = G.handCount[currPlayer];
	int deckCount = G.deckCount[currPlayer];



	//play great hall card
	cardEffect(council_room, -1, -1, -1, &G, 0, &coin_bonus);



	/********************************************
	//variables after council room played
	********************************************/
	//hand count decreases by 3 (one discarded, 4 drawn)
	if (G.handCount[currPlayer] == cardsInHand + 3) {
		printf("PASSED: current hand count increased by 3 \n\n");
	} 
	else {
		printf("FAILED: current hand count increased by 3 \n\n");
	}


	//deck count decreased by 4
	if (G.deckCount[currPlayer] == deckCount - 4) {
		printf("PASSED: deck count decreased by 4\n\n");
	}
	else {
		printf("FAILED: deck count decreased by 4\n\n");
	}


	//player's buys increased by one
	if (G.numBuys == numBuys + 1) {
		printf("PASSED: number of abuys increased by 1\n\n");
	}
	else {
		printf("FAILED: dnumber of abuys increased by 1\n\n");
	}


	//checking other player's state
	currPlayer = whoseTurn(&G) + 1;

	int flag2 = structComparer(&Gconst, &G, currPlayer);
	if (flag2 == 1) {
		printf("PASSED: other player's handCount increased by 1\n\n");
		printf("PASSED: other player's deck decreased by 1\n\n");
		printf("PASSED: other player's discard count unchanged\n\n");
	}



	return 0;
}



int structComparer(struct gameState *state1, struct gameState *state2, int player2) {
	int i = 0;
	int flag = 1;


	//handCount comparison
	if (state1->handCount[player2] == state2->handCount[player2]) {
		flag = 0;
		printf("FAILED ohter player's handCount altered\n");
	}
	
	//deck comparision
	if (state1->deckCount[player2] == state2->deckCount[player2]) {
		printf("state1: %d \t state2: %d \n", state1->deckCount[player2], state2->deckCount[player2]);
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