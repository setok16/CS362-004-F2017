#include "dominion.h"
#include "dominion_helpers.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>


int main() {

	printf("Testing village\n");
	struct gameState state;
	int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};
	int randSeed = 10;
	int numPlayers = 2;
	int handPos = 0;
	int currentPlayer = 0;
	int i = 0;

	initializeGame(numPlayers, k, randSeed, &state);

	// Village lets player draw a card and have two additional actions
	int handCountPrev = state.handCount[0];
	int deckCountPrev = state.deckCount[0];
	int actionCountPrev = state.numActions;
	int result = villageCard(&state, currentPlayer, handPos);
	int handCountPost = state.handCount[0];
	int deckCountPost = state.deckCount[0];
	int actionCountPost = state.numActions;
 
	// Checking player hand (Player draws a card and discards village)
	if (handCountPost - handCountPrev == 0) {
		printf("village: PASS hand count unchanged.\n");
	} else {
		printf("village: FAIL hand count should be unchanged. Changed by %d.\n",handCountPost-handCountPrev);
	}

	// Checking player deck 
	if (deckCountPrev - deckCountPost == 1) {
		printf("village: PASS deck count was decreased by 1.\n");
	} else {
		printf("village: FAIL deck count should decrease by 1. Changed by %d.\n",deckCountPrev-deckCountPost);
	}

	// Checking action count
	if (actionCountPost - actionCountPrev == 2) {
		printf("village: PASS action count was increased by 2.\n");
	} else {
		printf("village: FAIL action count should increase by 2. Changed by %d.\n",actionCountPost-actionCountPrev);
	}

	// Checking return value
	if (!result) {
		printf("village: PASS villlage function returns a 0.\n");
	} else {
		printf("village: FAIL village function returns a %d.\n",result);
	}

	return 0;
}
