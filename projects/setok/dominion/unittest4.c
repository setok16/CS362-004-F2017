#include "dominion.h"
#include "dominion_helpers.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>


int main() {

	printf("Testing isGameOver()\n");
	struct gameState state;
	int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};
	int randSeed = 10;
	int numPlayers = 2;

	initializeGame(numPlayers, k, randSeed, &state);

	// If numPlayers == 2, all victory cards have a count of 8
	printf("province count: %d\n", state.supplyCount[province]);

	// Testing for game over state right after initialization
	if (!isGameOver(&state)) {
		printf("isGameOver(): PASS successfully indicated that the game is not over.\n");
	} else {
		printf("numHandCards(): FAIL indicated that game is over with a full supply of victory cards.\n");
	}
	
	// Testing for game over state after one victory pile is depleated
	state.supplyCount[province] = 0;
	if (isGameOver(&state)) {
		printf("isGameOver(): PASS indicated that game is over when a victory card pile is depleted\n");
	} else {
		printf("isGameOver(): FAIL indicated that game is not over when a victory card pile is depleted\n");
	}

	// Testing for game over state after three supply piles have depleted
	state.supplyCount[province] = 8; // Resupplying province pile
	state.supplyCount[adventurer] = 0;
	state.supplyCount[village] = 0;
	state.supplyCount[mine] = 0;
	if (isGameOver(&state)) {
		printf("isGameOver(): PASS indicated that game is over when three supply piles are depleted\n");
	} else {
		printf("isGameOver(): FAIL indicated that game is not over when three supply piles are depleted\n");
	}

	// Testing for game over state after supply piles have depleted
	state.supplyCount[adventurer] = 3; // Replenishing one of the previously depleted supply piles
	if (!isGameOver(&state)) {
		printf("isGameOver(): PASS indicated that game is not over when only two supply piles are depleted\n");
	} else {
		printf("isGameOver(): FAIL indicated that game is over when only two supply piles are depleted\n");
	}
	return 0;
}
