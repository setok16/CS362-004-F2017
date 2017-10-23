#include "dominion.h"
#include "dominion_helpers.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>


int main() {

	printf("Testing smithy\n");
	struct gameState state;
	int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};
	int randSeed = 10;
	int numPlayers = 2;
	int handPos, choice1, choice2, choice3, choice4, bonus;
	handPos = choice1 = choice2 = choice3 = choice4 = bonus = 0;
	int i = 0;

	initializeGame(numPlayers, k, randSeed, &state);

	// Smithy lets player draw 3 cards from deck
	int handCountPrev = state.handCount[0];
	int deckCountPrev = state.deckCount[0];
	smithy_card(choice1, choice2, choice3, &state, handPos, &bonus);
	int handCountPost = state.handCount[0];
	int deckCountPost = state.deckCount[0];
	//printf("handCount: %d\n", state.handCount[0]);
 
	// Checking player hand
	if (handCountPost - handCountPrev == 2) {
		printf("smithy: PASS hand count was increased by 2.\n");
	} else {
		printf("smithy: FAIL hand count should increase by 2. Increased by %d.\n",handCountPost-handCountPrev);
	}

	// Checking player deck
	if (deckCountPrev - deckCountPost == 3) {
		printf("smithy: PASS deck count was decreased by 3.\n");
	} else {
		printf("smithy: FAIL deck count should decrease by 3. Decreased by %d.\n",deckCountPrev-deckCountPost);
	}

	return 0;
}
