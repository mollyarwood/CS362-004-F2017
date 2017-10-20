/************************************************
 *Name: Molly Arwood
 *Date: 10-12-17
 *Class: CS_362_SE2
 *Function: struct comparer for dominion game
 ***********************************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>


int structComparer(struct gameState *state1, struct gameState *state2) {
	int i = 0;
	int flag = 1;

	printf("in structComparer\n");

	for (i = 0; i < sizeof(state1->supplyCount) / sizeof(int); i++) {
		if (state1->supplyCount[i] != state2->supplyCount[1]) {
			flag = 0;
		}
	}


	return flag;
}