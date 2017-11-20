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
	
	// Compare treasure cards in hand
	int prevTreasureHandCount = 0, postTreasureHandCount = 0;
	for (i = 0; i < prevState->handCount[player1]; i++) {
		if (prevState->hand[player1][i] == copper || prevState->hand[player1][i] == silver || prevState->hand[player1][i] == gold) {
			prevTreasureHandCount++;
		}
	}
	for (i = 0; i < postState->handCount[player1]; i++) {
		if (postState->hand[player1][i] == copper || postState->hand[player1][i] == silver || postState->hand[player1][i] == gold) {
			postTreasureHandCount++;
		}
	}
	if (postTreasureHandCount - prevTreasureHandCount != 2) {
		printf("FAILED: Treasure count in hand increased by %d\n", postTreasureHandCount - prevTreasureHandCount);
		passed = 0;
	}

	// Compare treasure card in deck
	int prevTreasureDeckCount = 0, postTreasureDeckCount = 0;
	for (i = 0; i < prevState->deckCount[player1]; i++) {
		if (prevState->deck[player1][i] == copper || prevState->deck[player1][i] == silver || prevState->deck[player1][i] == gold) {
			prevTreasureDeckCount++;
		}
	}
	for (i = 0; i < postState->deckCount[player1]; i++) {
		if (postState->deck[player1][i] == copper || postState->deck[player1][i] == silver || postState->deck[player1][i] == gold) {
			postTreasureDeckCount++;
		}
	}
	if (prevTreasureDeckCount - postTreasureDeckCount != 2) {
		printf("FAILED: Treasure count in hand decreased by %d\n", prevTreasureDeckCount - postTreasureDeckCount);
		passed = 0;
	}
	
	return passed;
}


int main() {
	
	// Initializing seed for Random()
	SelectStream(2);
	PutSeed(3);
	
	printf("ADVENTURER RANDOM TEST:\n\n");
	struct gameState postState;
	struct gameState prevState;
	int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};
	int randSeed = 0;
	int numPlayers = 2;
	int currentPlayer = 0;
	int  player1, player2;
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
		// Adding adventurer in player1's hand
		postState.hand[player1][0] = adventurer;

		// Saving initial game state as prevState
		memcpy(&prevState, &postState, sizeof(struct gameState));

		adventurerCard(&postState, currentPlayer);

		allPassed = compareStates(&prevState, &postState);
	
		if (allPassed) printf("All tests passed\n\n");
	}


	
	return 0;
}
