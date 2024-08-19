#include "HandEvaluator.hpp"

using namespace std;

HandEvaluator::HandEvaluator() {

}


float HandEvaluator::evaluateHand(vector<Card> hand, vector<Card> communityCards, Deck deck, int numPlayers) {
	
	cout << "Hand: " << endl;
	for (Card c : hand) { cout << c.get_card() << endl; }
	cout << "Community Cards: " << endl;
	for (Card c : communityCards) { cout << c.get_card() << endl; }

	int pairIndex = checkPair(hand, communityCards);
	if (pairIndex != -1) { cout << "\npair of " << ranks[pairIndex] << endl; }
	else { cout << "\nno pair found " << endl; }

	int iterations = 10000;
	int wins = 0;
	for (int iteration = 0; iteration < iterations; iteration++) {
		bool win = true;
		Deck deckCopy(deck);
		deckCopy.shuffle();
		for (int player = 0; player < numPlayers; player++) {
			if (!win) { continue; }
			// create random hand for opponent
			vector<Card> otherHand;
			for (int i = 0; i < 2; i++) { otherHand.push_back(deckCopy.deal()); }
			// check if we beat opponent's hand
			win = compareHands(hand, otherHand, communityCards);
		}
		if (win) { wins++; }
	}

	return 1.0f * wins / iterations;
}

bool HandEvaluator::compareHands(vector<Card> hand, vector<Card> opponentHand, vector<Card> communityCards) {
	int handScore = checkPair(hand, communityCards);
	int opponentScore = checkPair(opponentHand, communityCards);
	if (handScore != opponentScore) {
		// Pairs are different, return true if hand is better pair
		return handScore > opponentScore;
	}

	vector<Card> handAndCommunityCards;
	vector<Card> opponentAndCommunityCards;
	vector<int> trimmedHand;
	vector<int> trimmedOpponentHand;
	for (Card card : hand) { handAndCommunityCards.push_back(card); }
	for (Card card : communityCards) { handAndCommunityCards.push_back(card); }
	for (Card card : opponentHand) { opponentAndCommunityCards.push_back(card); }
	for (Card card : communityCards) { opponentAndCommunityCards.push_back(card); }

	if (handScore != -1) {
		// Pairs are the same, remove the pairs from cards.

		string handPairRank = ranks[handScore];
		string opponentPairRank = ranks[opponentScore];

		// remove the paired cards
		int removedCards = 0;
		for (Card card : handAndCommunityCards) {
			if (card.get_rank() != handPairRank && removedCards < 2) {
				trimmedHand.push_back(getRankValue(card.get_rank()));
			}
		}

		removedCards = 0;
		for (Card card : opponentAndCommunityCards) {
			if (card.get_rank() != handPairRank && removedCards < 2) {
				trimmedOpponentHand.push_back(getRankValue(card.get_rank()));
			}
		}

		// sort the scores for the 5 remaining cards
		std::sort(trimmedHand.begin(), trimmedHand.end(), std::greater<int>());
		std::sort(trimmedOpponentHand.begin(), trimmedOpponentHand.end(), std::greater<int>());

		// check the next 3 highest cards and return the winner if they are different
		for (int i = 0; i < 3; i++) {
			if (trimmedHand[i] != trimmedOpponentHand[i]) {
				return trimmedHand[i] > trimmedOpponentHand[i];
			}
		}
		// draw as all top 3 cards are the same
		return false;
	}
	// High Card Check
	vector<int> handValues;
	vector<int> opponentHandValues;
	for (Card card : handAndCommunityCards) { handValues.push_back(getRankValue(card.get_rank())); }
	for (Card card : opponentAndCommunityCards) { opponentHandValues.push_back(getRankValue(card.get_rank())); }
	std::sort(handValues.begin(), handValues.end(), std::greater<int>());
	std::sort(opponentHandValues.begin(), opponentHandValues.end(), std::greater<int>());
	// check hand for high cards
	for (int i = 0; i < 5; i++) {
		if (handValues[i] != opponentHandValues[i]) {
			return handValues[i] > opponentHandValues[i];
		}
	}

	// draw
	return false;
}

int HandEvaluator::checkPair(vector<Card> hand, vector<Card> communityCards) {
	int highestRank = -1;
	vector<Card> allCards;
	for (Card card : hand) { allCards.push_back(card); }
	for (Card card : communityCards) { allCards.push_back(card); }

	for (int i = 0; i < allCards.size(); i++) {
		string rank = allCards[i].get_rank();
		int index = getRankValue(rank);
		for (int j = i+1; j < allCards.size(); j++) {
			if (allCards[i].get_rank() == allCards[j].get_rank() && index > highestRank) { highestRank = index; }
		}
	}

	return highestRank;
}

int HandEvaluator::getRankValue(string rank) {
	auto it = std::find(ranks.begin(), ranks.end(), rank);
	int index = -1;
	if (it != ranks.end()) {
		index = distance(ranks.begin(), it);
	}
	return index;
}
