#include "EquityCalculator.hpp"

using namespace std;

EquityCalculator::EquityCalculator() {

}

vector<float> EquityCalculator::evaluateHand(const vector<Card>& hand, const vector<Card>& communityCards, Deck deck, int numPlayers) {

	int iterations = 3000;
	int wins = 0;
	int draws = 0;
	int losses = 0;
	for (int iteration = 0; iteration < iterations; iteration++) {
		bool lose = false;
		bool draw = false;
		Deck deckCopy(deck);
		deckCopy.shuffle();
		vector<Card> communityCardsFull(communityCards);
		while (communityCardsFull.size() < 5) {
			communityCardsFull.push_back(deckCopy.deal());
		}
		for (int player = 0; player < numPlayers; player++) {
			if (lose) { continue; }
			// create random hand for opponent
			vector<Card> otherHand;
			for (int i = 0; i < 2; i++) { otherHand.push_back(deckCopy.deal()); }
			// check if we beat opponent's hand
			int outcome = handEvaluator.compareHands(hand, otherHand, communityCardsFull);
			lose = outcome == LOSE;
			if (!draw) {
				draw = outcome == DRAW;
			}
		}
		if (lose) { losses++; continue; }
		if (draw) { draws++; continue; }
		wins++;
	}

	return { 1.0f * wins / iterations, 1.0f * draws / iterations,  1.0f * (iterations - (wins + draws)) / iterations };
}