#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h> // floor()
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"

int compareStates(struct gameState *prevState, struct gameState *postState) {
	int passed = 1;
	int player1 = whoseTurn(postState);
	int player2 = whoseTurn(postState) + 1;
	int i;
	
	// Compare hand count
	if (postState->handCount[player1] - prevState->handCount[player1] != 2) {
		printf("FAILED: Player hand count increased by %d\n", postState->handCount[player1] - prevState->handCount[player1]);
		passed = 0;
	}

	// Compare deck count
	if (prevState->deckCount[player1] - postState->deckCount[player1] != 3) {
		printf("FAILED: Player hand count decreased by %d\n", prevState->deckCount[player1] - postState->deckCount[player1]);
		passed = 0;
	}
	
	return passed;
}


int main() {
	
	// Initializing seed for Random()
	SelectStream(2);
	PutSeed(3);
	
	printf("SMITHY RANDOM TEST:\n\n");
	struct gameState postState;
	struct gameState prevState;
	int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};
	int randSeed = 0;
	int numPlayers = 2;
	int handPos, choice1, choice2, choice3, choice4, bonus, player1, player2;
	handPos, choice1, choice2, choice3, choice4, bonus = 0;
	int i, n, p, j;
	int allPassed;



	for (n = 0; n < 2000; n++) {

		randSeed = floor(Random() * 500 + 1);

		// Initializing game state
		initializeGame(numPlayers, k, randSeed, &postState);

		// Randomizing current player
		player1 = floor(Random() * 2);
		if (player1) player2 = 0; 
		else player2 = 1;

		// Randomizing game state
		p = floor(Random() * 2);
		postState.numPlayers = 2;
		postState.deckCount[p] = floor(Random() * MAX_DECK);
		postState.discardCount[p] = floor(Random() * MAX_DECK);
		postState.handCount[p] = floor(Random() * MAX_HAND);
		postState.supplyCount[copper] = floor(Random() * 60 + 1);
		postState.supplyCount[silver] = floor(Random() * 40 + 1);
		postState.supplyCount[gold] = floor(Random() * 30 + 1);
		postState.whoseTurn = player1;
		postState.handCount[player1] = 5;
		postState.deckCount[player1] = floor(Random() * 30 + 1);
		postState.discardCount[player1] = floor(Random() * 30 + 1);
		postState.handCount[player2] = floor(Random() * 3 + 1) + 2;
		postState.deckCount[player2] = floor(Random() * 30 + 1);
		postState.discardCount[player2] = floor(Random() * 30 + 1);

		// Randomizing cards in hand
		for (j = 0; j < 5; j++) {
			postState.hand[player1][j] = floor(Random() * 26);
			postState.hand[player2][j] = floor(Random() * 26);
		}
		// Adding smithy in player1's hand
		postState.hand[player1][0] = smithy;

		// Saving initial game state as prevState
		memcpy(&prevState, &postState, sizeof(struct gameState));

		smithy_card(choice1, choice2, choice3, &postState, handPos, &bonus);

		allPassed = compareStates(&prevState, &postState);
	
		if (allPassed) printf("All tests passed\n\n");
	}


	
	return 0;
}
