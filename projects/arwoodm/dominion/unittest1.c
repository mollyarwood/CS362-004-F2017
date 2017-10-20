/************************************************
 * Name: Molly Arwood
 * Date: 10-11-17
 * Class: CS_362_SE2
 * unittest1.c - gainCard Test
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
void supplyCheck(int cardSupply[], int cardChosen[], struct gameState *G);



int main() {

	/*********************************************
	//Initial Setup
	*********************************************/
	struct gameState G;
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
	printf("\n\n-------------Testing gainCard--------------\n\n");

	/*********************************************
	//variables setup for tests
	*********************************************/
	int cardChosen[5] = {0, 1, 4, 7, 26};
	int toFlag[5] = {0, 1, 2, -1, 5};
	int currPlayer = whoseTurn(&G);
	int funcReturn[5];
	int errFlag = 0;
	int cardsInHand = G.handCount[currPlayer];
	int deckCount = G.deckCount[currPlayer];
	int discardCount = G.discardCount[currPlayer];
	int cardSupply[5] = {supplyCount(cardChosen[0], &G), supplyCount(cardChosen[1], &G),
						supplyCount(cardChosen[2], &G), supplyCount(cardChosen[3], &G),
						supplyCount(cardChosen[4], &G), supplyCount(cardChosen[5], &G)};


	/*********************************************
	//for each card type,  test the different flag options.
	*********************************************/

	/******** first: toFlag = 0 (to discard) ****************/
	printf("--Testing toFlag == 0 \n\n");
	for (i = 0; i < 5; i++) {
		funcReturn[i] = gainCard(cardChosen[i], &G, toFlag[0], currPlayer);
	}	


	//check for -1 in funcReturn
	for (i = 0; i < sizeof(funcReturn) / sizeof(int); i++) {
		if (funcReturn[i] == -1) {
			errFlag = 1;
		}
	}
	if (errFlag) {
		printf("FAILED: function caught card error when no error exists\n\n");
	}
	else {
		printf("PASSED: No supplyCount errors caught \n\n");
	}


	//check discard pile after
	if (discardCount < G.discardCount[currPlayer]) {
		printf("PASSED: discard count increased to: %d\n\n", G.discardCount[currPlayer]);
		discardCount = G.discardCount[currPlayer]; //updating for next tests
	}
	else {
		printf("FAILED: discard count did not increase\n\n");
	}
	//check hand pile after
	if (cardsInHand < G.handCount[currPlayer]) {
		printf("FAILED: hand count increased to: %d\n\n", G.handCount[currPlayer]);
	}
	else {
		printf("PASSED: hand count did not increase\n\n");
	}
	//check deck pile after
	if (deckCount < G.deckCount[currPlayer]) {
		printf("FAILED: deck count increased to: %d\n\n", G.deckCount[currPlayer]);
	}
	else {
		printf("PASSED: deck count did not increase\n\n");
	}

	//check supply of cards
	supplyCheck(cardSupply, cardChosen, &G);
	

	/******** second: toFlag = 1 (to deck) ****************/
	printf("--Testing toFlag == 1 \n\n");
	for (i = 0; i < 5; i++) {
		funcReturn[i] = gainCard(cardChosen[i], &G, toFlag[1], currPlayer);
	}	


	//check deck pile after
	if (deckCount < G.deckCount[currPlayer]) {
		printf("PASSED: deck count increased to: %d\n\n", G.deckCount[currPlayer]);
		deckCount = G.deckCount[currPlayer]; //updating for next tests
	}
	else {
		printf("FAILED: deck count did not increase\n\n");
	}
	//check hand pile after
	if (cardsInHand < G.handCount[currPlayer]) {
		printf("FAILED: hand count increased to: %d\n\n", G.handCount[currPlayer]);
	}
	else {
		printf("PASSED: hand count did not increase\n\n");
	}
	//check discard pile after
	if (discardCount < G.discardCount[currPlayer]) {
		printf("FAILED: discard count increased to: %d\n\n", G.discardCount[currPlayer]);
	}
	else {
		printf("PASSED: discard count did not increase\n\n");
	}

	//check supply of cards
	supplyCheck(cardSupply, cardChosen, &G);


	/******** third: toFlag = 2 (to hand) ****************/
	printf("--Testing toFlag == 2 \n\n");
	for (i = 0; i < 5; i++) {
		funcReturn[i] = gainCard(cardChosen[i], &G, toFlag[2], currPlayer);
	}	


	//check hand pile after
	if (cardsInHand < G.handCount[currPlayer]) {
		printf("PASSED: hand count increased to: %d\n\n", G.handCount[currPlayer]);
		cardsInHand = G.handCount[currPlayer]; //updating for next tests
	}
	else {
		printf("FAILED: hand count did not increase\n\n");
	}
	//check discard pile after
	if (discardCount < G.discardCount[currPlayer]) {
		printf("FAILED: discard count increased to: %d\n\n", G.discardCount[currPlayer]);
	}
	else {
		printf("PASSED: discard count did not increase\n\n");
	}
	//check deck pile after
	if (deckCount < G.deckCount[currPlayer]) {
		printf("FAILED: deck count increased to: %d\n\n", G.deckCount[currPlayer]);
	}
	else {
		printf("PASSED: deck count did not increase\n\n");
	}

	//check supply of cards
	supplyCheck(cardSupply, cardChosen, &G);




	/******** fourth: toFlag = -1 (to discard) ****************/
	printf("--Testing toFlag == -1 \n\n");
	for (i = 0; i < 5; i++) {
		funcReturn[i] = gainCard(cardChosen[i], &G, toFlag[3], currPlayer);
	}	


	//check discard pile after
	if (discardCount < G.discardCount[currPlayer]) {
		printf("PASSED: discard count increased to: %d\n\n", G.discardCount[currPlayer]);
		discardCount = G.discardCount[currPlayer]; //updating for next tests
	}
	else {
		printf("FAILED: discard count did not increase\n\n");
	}
	//check hand pile after
	if (cardsInHand < G.handCount[currPlayer]) {
		printf("FAILED: hand count increased to: %d\n\n", G.handCount[currPlayer]);
	}
	else {
		printf("PASSED: hand count did not increase\n\n");
	}
	//check deck pile after
	if (deckCount < G.deckCount[currPlayer]) {
		printf("FAILED: deck count increased to: %d\n\n", G.deckCount[currPlayer]);
	}
	else {
		printf("PASSED: deck count did not increase\n\n");
	}

	//check supply of cards
	supplyCheck(cardSupply, cardChosen, &G);




	/*********************************************
	//function should catch empty supply of card error
	*********************************************/
	printf("--Testing supplyCount Error Catching \n\n");
	G.supplyCount[1] = 0;
	funcReturn[0] = gainCard(cardChosen[1], &G, toFlag[1], currPlayer);
	funcReturn[1] = gainCard(15, &G, toFlag[1], currPlayer);

	//empty card supply
	if (funcReturn[0] == -1) {
		printf("PASSED: function caught empty card supply error\n\n");
	}
	else {
		printf("FAILED: function did not catch empty card supply error\n\n");
	}

	//card not used in game
	if (funcReturn[1] == -1) {
		printf("PASSED: function caught unused card in game error\n\n");
	}
	else {
		printf("FAILED: function did not catch unused card in game error\n\n");
	}


	printf("\n\n");
	return 0;
}



//checks supply of cards after gainCards function runs
void supplyCheck(int cardSupply[], int cardChosen[], struct gameState *G)
{
	int i;

	//check supplyCount of card after
	for (i = 0; i < 5; i++) {
		if (cardSupply[i] > supplyCount(cardChosen[i], G)) {
			printf("PASSED: supply of %d card has lowered from %d to %d\n\n", cardChosen[i], cardSupply[i], supplyCount(cardChosen[i], G));
		}
		else {
			printf("FAILED: supply of %d cards did not lower. \n\n", cardChosen[i]);
		}
	}
}