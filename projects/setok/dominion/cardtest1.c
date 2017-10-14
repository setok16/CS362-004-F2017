#include "dominion.h"
#include "dominion_helpers.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>


int main() {

	printf("Testing adventurer\n");
	struct gameState state;
	int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};
	int randSeed = 8;
	int numPlayers = 2;
	int handPos, choice1, choice2, choice3, choice4, bonus;
	handPos = choice1 = choice2 = choice3 = choice4 = bonus = 0;
	int i = 0;

	initializeGame(numPlayers, k, randSeed, &state);

	// Adventurer adds two treasure cards into your hand from the dec
	int treasureCountPrev = 0;
	int treasureCountPost = 0;
	int playerHandPrev = state.handCount[0];
	for (i = 0; i < state.handCount[0]; i++) { // Counting treasure cards in hand
		if (state.hand[0][i] == copper || state.hand[0][i] == silver || state.hand[0][i] == gold) {
			treasureCountPrev++;
		}
	}
	adventurer_card(choice1, choice2, choice3, &state, handPos, &bonus);
	int playerHandPost = state.handCount[0];
	for (i = 0; i < state.handCount[0]; i++) { // Counting treasure cards in hand after call to adventurer
		if (state.hand[0][i] == copper || state.hand[0][i] == silver || state.hand[0][i] == gold) {
			treasureCountPost++;
		}
	}
	//printf("handCount: %d\n", state.handCount[0]);
	//printf("prev:\t%d\npost\t%d\n", treasureCountPrev, treasureCountPost);
	//printf("prev:\t%d\npost\t%d\n", playerHandPrev, playerHandPost);

	if (treasureCountPost - treasureCountPrev == 2) {
		printf("adventurer: PASS added exactly two treasure cards into player's hand.\n");
	} else {
		printf("adventurer: FAIL failed to add exactly two treasure cards into player's hand.\n");
	}

	// Testing whether player hand increased by two
	if (playerHandPost - playerHandPrev == 2) {
		printf("adventurer: PASS player hand increased by 2.\n");
	} else {
		printf("adventurer: FAIL expected player hand to increase by 2. It increased by %d.\n", playerHandPost - playerHandPrev);
	}

	return 0;
}
