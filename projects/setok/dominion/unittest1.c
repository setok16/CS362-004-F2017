#include "dominion.h"
#include "dominion_helpers.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>


int main() {

	printf("Testing numHandCards()\n");
	struct gameState state;
	int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};
	int randSeed = 10;
	int numPlayers = 2;

	initializeGame(numPlayers, k, randSeed, &state);

	if (numHandCards(&state) == 5) {
		printf("numHandCards(): PASS player starts off with 5 cards in hand.\n");
	} else {
		printf("numHandCards(): FAIL player starts off with an incorrect number of cards in hand.\n");
	}
	
	// Incrementing handCount
	state.handCount[0]++;
	if (numHandCards(&state) == 6) {
		printf("numHandCards(): PASS returned the correct hand count after incrementing.\n");
	} else {
		printf("numHandCards(): FAIL returned an incorrect hand count after incrementing.\n");
	}
	
	// Decrementing handCount
	state.handCount[0]--;
	if (numHandCards(&state) == 5) {
		printf("numHandCards(): PASS returned the correct hand count after decrementing.\n");
	} else {
		printf("numHandCards(): FAIL returned an incorrect hand count after decrementing.\n");
	}


	//printf("%d\n", whoseTurn(&state));

	return 0;
}
