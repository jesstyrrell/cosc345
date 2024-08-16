#include "HandEvaluator.hpp"

using namespace std;

HandEvaluator::HandEvaluator() {
	suits = { "Hearts", "Diamonds", "Clubs", "Spades" };
	ranks = { "2", "3", "4", "5", "6", "7", "8", "9", "10",
					  "Jack", "Queen", "King", "Ace" };
}


float HandEvaluator::evaluateHand(vector<Card> hand, vector<Card> communityCards, Deck deck, int numPlayers) {
	
	for (int iteration = 0; iteration < 100; iteration++) {
		bool win = true;
		Deck deckCopy(deck);
		deck.shuffle();
		for (int player = 0; player < numPlayers; player++) {
			vector<Card> otherHand;
			for (int i = 0; i < 2; i++) { otherHand.push_back(deck.deal()); }
			bool win = compareHands(hand, otherHand, communityCards);
		}
		
	}


	cout << "Hand: " << endl;
	for (Card c : hand) { cout << c.get_card() << endl; }
	cout << "Community Cards: " << endl;
	for (Card c : communityCards) { cout << c.get_card() << endl; }

	int pairIndex = checkPair(hand, communityCards);
	if (pairIndex != -1) { cout << "\npair of " << ranks[pairIndex] << endl; }
	else { cout << "\nno pair found " << endl; }

	return 0.0f;
}

bool HandEvaluator::compareHands(vector<Card> hand, vector<Card> opponentHand, vector<Card> communityCards) {
	if (checkPair(hand, communityCards) != checkPair(opponentHand, communityCards)) {
		return checkPair(hand, communityCards) > checkPair(opponentHand, communityCards);
	} else
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
