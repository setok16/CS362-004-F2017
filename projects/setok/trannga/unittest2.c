#include "dominion.h"
#include "dominion_helpers.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>


int main() {

	printf("Testing endTurn()\n");
	struct gameState state;
	int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};
	int randSeed = 10;
	int numPlayers = 2;
	int i;
	int cardDiscarded = 1;
	int stateReset = 1;

	initializeGame(numPlayers, k, randSeed, &state);
	
	// Adding cards to hand for player 0
	for (i = 0; i < 5; i++) {
		state.hand[0][i] = k[i];
	}
	state.handCount[0] = 5;
	
	assert(state.handCount[0] == 5);

	// Altering game state
	state.outpostPlayed = 1;
	state.phase = 1;
	state.numActions = 0;
	state.coins = 0;
	state.playedCardCount = 3;
	state.handCount[1] = 1;
	
	endTurn(&state);

	// Testing whether hand count was reset
	if (state.handCount[0] == 0) {
		printf("endTurn(): PASS player's hand count was reset.\n");
	} else {
		printf("endTurn(): FAIL player's hand count was not reset.\n");
	}

	// Testing whether cards were discarded from hand
	for (i = 0; i < 5; i++) {
		if (state.hand[0][i] != -1) {
			cardDiscarded = 0;
			break;
		}
	}
	if (cardDiscarded) {
		printf("endTurn(): PASS all of the player's cards were discarded.\n");
	} else {
		printf("endTurn(): FAIL not all of the player's cards were discarded.\n");
	}

	// Testing whether player turn was changed
	if (state.whoseTurn) {
		printf("endTurn(): PASS player turn was successfully changed.\n");
	} else {
		printf("endTurn(): FAIL player turn was not changed.\n");
	}

	// Testing whether all states were reset (e.g. outpostPlayed, phase, numActions)
	if (state.outpostPlayed != 0) {
		stateReset = 0;
	}
	if (state.phase != 0) {
		printf("state.phase = %d\n", state.phase);
		stateReset = 0;
	}
	if (state.numActions != 1) {
		stateReset = 0;
	}
	if (state.coins != 3) {
		stateReset = 0;
	}
	if (state.numBuys != 1) {
		stateReset = 0;
	}
	if (state.playedCardCount != 0) {
		//stateReset = 0;
	}
	if (state.numBuys != 1) {
		//stateReset = 0;
	}
	if (state.playedCardCount != 0) {
		//stateReset = 0;
	}
	if (state.handCount[1] != 0) {
		//stateReset = 0;
	}
	if (stateReset) {
		printf("endTurn(): PASS game state was successfully reset.\n");
	} else {
		printf("endTurn(): FAIL gameState was not reset.\n");
	}



	return 0;
}
