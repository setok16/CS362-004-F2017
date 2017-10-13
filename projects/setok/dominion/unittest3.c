#include "dominion.h"
#include "dominion_helpers.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>


int main() {

	printf("Testing scoreFor()\n");
	struct gameState state;
	int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};
	int randSeed = 10;
	int numPlayers = 2;
	int i;

	initializeGame(numPlayers, k, randSeed, &state);

	// Player should have 5 in hand, 5 in deck, and 0 in discard

	// Testing initial score of 3
	if (scoreFor(0, &state) == 3) {
		printf("scoreFor(): PASS got correct score after initializing game.\n");
	} else {
		printf("scoreFor(): FAIL initial score incorrect. Should be 3. Got %d.\n", scoreFor(0,&state));
	}

	// Testing for score after player acquires some victory cards 
	state.hand[0][0] = province;	// +6
	state.discard[0][0] = estate;	// +1
	state.discard[0][1] = duchy;	// +3
	state.deck[0][0] = province;	// +6
	state.deck[0][1] = duchy;		// +3
	state.deck[0][2] = duchy;		// +3
									// TOTAL: 22
	state.handCount[0] = 1;
	state.discardCount[0] = 2;
	state.deckCount[0] = 3;
	if (scoreFor(0, &state) == 20) {
		printf("scoreFor(): PASS got correct score after adding victory cards.\n");
	} else {
		printf("scoreFor(): FAIL got incorrect score after adding victory cards. Should be 20. Got %d\n", scoreFor(0,&state));
	}
	// P.S. These tests fail because the implementation is incorrect when looping from deck to check for victory cards

	return 0;
}
