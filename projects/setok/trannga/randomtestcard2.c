#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h> // floor()
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"

int compareStates(struct gameState *prevState, struct gameState *postState, int returnValue, int choice1, int choice2) {
	int passed = 1;
	int player1 = whoseTurn(postState);
	int player2 = whoseTurn(postState) + 1;
	int i;
	

	

	/* If card is unaffordable with remodel */
	if ((getCost(postState->hand[player1][choice1])+2) > getCost(choice2)) { 

		// Compare hand count (should not decrease, since remodel was unable to be used)
		if (prevState->handCount[player1] - postState->handCount[player1] != 0) {
			printf("FAILED: Player hand count decreased by %d. Should be 0.\n", prevState->handCount[player1] - postState->handCount[player1]);
			passed = 0;
		}

		// Compare discard pile (should increase by 0)
		if (postState->discardCount[player1] - prevState->discardCount[player1] != 0) {
			printf("FAILED: Player discard count increased by %d. Should be 0.\n", postState->handCount[player1] - prevState->handCount[player1]);
			passed = 0;
		}

		if (returnValue == 0) {
			printf("FAILED: remodel function returns a 0 when card is unafforadable.\n");
			passed = 0;
		}

	/* If card is affordable with remodel */
	} else { 

		// Compare hand count (should decrease by 2: remodel card, chosen card)
		if (prevState->handCount[player1] - postState->handCount[player1] != 2) {
			printf("FAILED: Player hand count decreased by %d. Should be 2.\n", prevState->handCount[player1] - postState->handCount[player1]);
			passed = 0;
		}

		// Compare discard pile (should increase by 2: remodel card, chosen card from game)
		if (postState->discardCount[player1] - prevState->discardCount[player1] != 2) {
			printf("FAILED: Player discard count increased by %d. Should be 2.\n", postState->handCount[player1] - prevState->handCount[player1]);
			passed = 0;
		}

		// Checking if new card was acquired
		int newCardFound = 0;
		for ( i = 0; i < postState->discardCount[player1]; i++) {
			if (postState->discard[player1][i] == choice2){ 
				newCardFound = 1;
				break;
			}
		}
		if (!newCardFound) {
			printf("FAILED: newly acquired card not found in discard pile\n");
			passed = 0;
		}
	}
	
	return passed;
}


int main() {
	
	// Initializing seed for Random()
	SelectStream(2);
	PutSeed(3);
	
	printf("REMODEL RANDOM TEST:\n\n");
	struct gameState postState;
	struct gameState prevState;
	int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};
	int randSeed = 0;
	int numPlayers = 2;
	int currentPlayer = 0;
	int handPos, choice1, choice2, player1, player2;
	handPos, choice1, choice2 = 0;
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

		// Randomizing choice
		int choice1pos = floor(Random() * (postState.handCount[player1]-1) + 1);
		choice1 = postState.hand[player1][choice1pos];
		choice2 = floor(Random() * 26);

		// Adding remodel in player1's hand
		postState.hand[player1][0] = remodel;

		// Saving initial game state as prevState
		memcpy(&prevState, &postState, sizeof(struct gameState));

		int returnValue = remodelCard(&postState, currentPlayer, handPos, choice1, choice2);

		allPassed = compareStates(&prevState, &postState, returnValue, choice1, choice2);
	
		if (allPassed) printf("All tests passed\n\n");
	}


	
	return 0;
}
