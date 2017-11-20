#include "dominion.h"
#include "dominion_helpers.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>


int main() {

	printf("Testing remodel\n");
	struct gameState state;
	int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};
	int randSeed = 10;
	int numPlayers = 2;
	int handPos = 0, choice1 = copper, choice2 = mine;
	int currentPlayer = 0;
	int i = 0;

	initializeGame(numPlayers, k, randSeed, &state);

	// Remodl lets player discard a card from hand and gain one that costs two more
	int handCountPrev = state.handCount[0];
	int discardCountPrev = state.discardCount[0];
	int result = remodelCard(&state, currentPlayer, handPos, choice1, choice2);
	int handCountPost = state.handCount[0];
	int discardCountPost = state.discardCount[0];
 
	// Checking player hand
	if (handCountPrev - handCountPost == 2) {
		printf("remodel: PASS hand count decreased by 2.\n");
	} else {
		printf("remodel: FAIL hand count should decrease by 2. Changed by %d.\n",handCountPrev-handCountPost);
	}

	// Checking player discard pile
	if (discardCountPost - discardCountPrev == 1) {
		printf("remodel: PASS discard pile count was increased by 1.\n");
	} else {
		printf("remodel: FAIL discard pile count should increase by 1. Changed by %d.\n",discardCountPost-discardCountPrev);
	}

	// Checking return value
	if (!result) {
		printf("remodel: PASS remodel function returns a 0.\n");
	} else {
		printf("remodel: FAIL remodel function returns a %d.\n",result);
	}
	
	// Checking if new card was acquired
	int newCardFound = 0;
	for (i = 0; i < state.discardCount[0]; i++) {
		if (state.discard[0][i] == choice2) {
			newCardFound = 1;
			break;
		}
	}
	if (newCardFound) {
		printf("remodel: PASS newly acquired card found in discard pile.\n");
	} else {
		printf("remodel: FAIL newly acquired card not found in discard pile.\n");
	}

	// Checking for correct failure if cost of choice2 is too high
	choice1 = copper; // cost = 0
	choice2 = mine; // cost = 8
	initializeGame(numPlayers, k, randSeed, &state);
	result = remodelCard(&state, currentPlayer, handPos, choice1, choice2);
	if (result) {
		printf("remodel: PASS remodel function returns a -1 when card is unaffordable.\n");
	} else {
		printf("remodel: FAIL remodel function returns a 0 when card is unaffordable.\n");
	}

	return 0;
}
