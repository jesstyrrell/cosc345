#include "HandEvaluator.hpp"

using namespace std;

HandEvaluator::HandEvaluator() {

}

vector<bool> HandEvaluator::evaluateTable(vector<vector<Card>> hands, vector<Card> communityCards) {
	vector<bool> results;
	for (int i = 0; i < hands.size(); i++) { results.push_back(true); }

	for (int i = 0; i < hands.size(); i++) {
		for (int j = i + 1; j < hands.size(); j++) {
			int result = compareHands(hands[i], hands[j], communityCards);
			if (result == WIN) { results[j] = false; }
			else if (result == LOSE) { results[i] = false; }
		}
	}
	return results;
}

int HandEvaluator::compareHands(vector<Card> hand, vector<Card> opponentHand, vector<Card> communityCards) {
	vector<Card> handAndCommunityCards;
	vector<Card> opponentAndCommunityCards;
	for (Card card : hand) { handAndCommunityCards.push_back(card); }
	for (Card card : communityCards) { handAndCommunityCards.push_back(card); }
	for (Card card : opponentHand) { opponentAndCommunityCards.push_back(card); }
	for (Card card : communityCards) { opponentAndCommunityCards.push_back(card); }

	vector<int> handPairs = checkForPairs(handAndCommunityCards);
	int firstHandPair = handPairs[0];
	int secondHandPair = handPairs[1];
	vector<int> opponentPairs = checkForPairs(opponentAndCommunityCards);
	int firstOpponentPair = opponentPairs[0];
	int secondOpponentPair = opponentPairs[1];

	int handThreeScore = checkOfAKind(handAndCommunityCards, 3);
	int opponentThreeScore = checkOfAKind(opponentAndCommunityCards, 3);

	int handFourScore = checkOfAKind(handAndCommunityCards, 4);
	int opponentFourScore = checkOfAKind(opponentAndCommunityCards, 4);

	vector<int> handFlushScore = checkForFlush(handAndCommunityCards);
	vector<int> opponentFlushScore = checkForFlush(opponentAndCommunityCards);

	int handStraightScore = checkForStraight(handAndCommunityCards);
	int opponentStraightScore = checkForStraight(opponentAndCommunityCards);


	// If either player has a straight
	if (handStraightScore != -1 || opponentStraightScore != -1) {
		int handStraightFlushScore = -1;
		int opponentStraightFlushScore = -1;
		if (handStraightScore != -1) {
			// Extract straight
			vector<Card> handStraightCards;
			for (Card c : handAndCommunityCards) {
				int rank = getRankValue(c.get_rank());
				if (rank <= handStraightScore && rank > handStraightScore - 5) { handStraightCards.push_back(c); }
			}
			vector<int> flush = checkForFlush(handStraightCards);
			if (flush.size() > 0) {
				handStraightFlushScore = flush[0];
			}
		}
		if (opponentStraightScore != -1) {
			// Extract straight
			vector<Card> opponentStraightCards;
			for (Card c : opponentAndCommunityCards) {
				int rank = getRankValue(c.get_rank());
				if (rank <= opponentStraightScore && rank > opponentStraightScore - 5) { opponentStraightCards.push_back(c); }
			}
			vector<int> flush = checkForFlush(opponentStraightCards);
			if (flush.size() > 0) {
				opponentStraightFlushScore = flush[0];
			}
		}
		if (handStraightFlushScore > opponentStraightFlushScore) { return WIN; }
		else if (opponentStraightFlushScore > handStraightFlushScore) { return LOSE; }
		if (handStraightFlushScore != -1) { return DRAW; }
		// No straight flush, continue
	}

	if (handFourScore > opponentFourScore) { return WIN; }
	else if (opponentFourScore > handFourScore) { return LOSE; }

	vector<int> handFullHouse;
	vector<int> opponentFullHouse;
	// If hand has a three of a kind
	if (handThreeScore != -1) {
		// Remove the three cards from hand
		int removedCards = 0;
		string threeOfAKindRank = ranks[handThreeScore];
		vector<Card> trimmedHand;
		for (Card card : handAndCommunityCards) {
			if (card.get_rank() != threeOfAKindRank || removedCards >= 3) {
				trimmedHand.push_back(card);
			}
			else {
				removedCards++;
			}
		}
		int pair = checkOfAKind(trimmedHand, 2);
		if (pair != -1) {
			handFullHouse = { handThreeScore, pair };
		}
	}
	// If opponent has a three of a kind
	if (opponentThreeScore != -1) {
		// Remove the three cards from hand
		int removedCards = 0;
		string threeOfAKindRank = ranks[opponentThreeScore];
		vector<Card> trimmedHand;
		for (Card card : opponentAndCommunityCards) {
			if (card.get_rank() != threeOfAKindRank || removedCards >= 3) {
				trimmedHand.push_back(card);
			}
			else {
				removedCards++;
			}
		}
		int pair = checkForPairs(trimmedHand)[0];
		if (pair != -1) {
			opponentFullHouse = { opponentThreeScore, pair };
		}
	}
	// If one person has a full house, return the winner
	if (handFullHouse.size() > opponentFullHouse.size()) { return WIN; }
	else if (opponentFullHouse.size() > handFullHouse.size()) { return LOSE; }
	// If both players have a full house
	if (handFullHouse.size() == 2 && opponentFullHouse.size() == 2) {
		if (handFullHouse[0] != opponentFullHouse[0]) {
			if (handFullHouse[0] > opponentFullHouse[0]) { return WIN; }
			else { return LOSE; }
		}
		else if (handFullHouse[1] != opponentFullHouse[1]) {
			if (handFullHouse[1] > opponentFullHouse[0]) { return WIN; }
			else { return LOSE; }
		}
		return DRAW;
	}

	// Both players have a flush
	if (handFlushScore.size() != 0 && opponentFlushScore.size() != 0) {
		for (int i = 0; i < 5; i++) {
			if (handFlushScore[i] > opponentFlushScore[i]) { return WIN; }
			else { return LOSE; }
		}
		return DRAW;
	}
	// One player has a flush
	if (handFlushScore.size() != 0 || opponentFlushScore.size() != 0) {
		if (handFlushScore.size() > opponentFlushScore.size()) { return WIN; }
		else { return LOSE; }
	}
	// If straight scores are different, return winner, else there is no straight found
	if (handStraightScore > opponentStraightScore) { return WIN; }
	else if (opponentStraightScore > handStraightScore) { return LOSE; }

	// If someone has a three of a kind
	if (handThreeScore + opponentThreeScore > -2) {
		// Both have a three of a kind
		if (handThreeScore != -1 && opponentThreeScore != -1) {
			if (handThreeScore != opponentThreeScore) {
				if (handThreeScore > opponentThreeScore) { return WIN; }
				else { return LOSE; }
			} 
			// else the threes are the same
			vector<Card> trimmedHand;
			vector<Card> trimmedOpponentHand;
			string threeOfAKindRank = ranks[handThreeScore];
			// remove the paired cards
			int removedCards = 0;
			for (Card card : handAndCommunityCards) {
				if (card.get_rank() != threeOfAKindRank || removedCards >= 3) {
					trimmedHand.push_back(card);
				}
				else {
					removedCards++;
				}
			}
			removedCards = 0;
			for (Card card : opponentAndCommunityCards) {
				if (card.get_rank() != threeOfAKindRank || removedCards >= 3) {
					trimmedOpponentHand.push_back(card);
				}
				else {
					removedCards++;
				}
			}
			return checkHighCard(trimmedHand, trimmedOpponentHand, 2);
		}
		if (handThreeScore > opponentThreeScore) { return WIN; }
		else { return LOSE; }
	}

	// If someone has a two pair
	if (secondOpponentPair + secondHandPair != -2) {
		// Both have a two pair, check best pairs
		if (secondOpponentPair != -1 && secondHandPair != -1) {
			if (firstHandPair != firstOpponentPair) {
				// Pairs are different, return true if hand is better pair
				if (firstHandPair > firstOpponentPair) { return WIN; }
				else { return LOSE; }
			} // else the first pairs are equal, check second pair
			else if (secondHandPair != secondOpponentPair){
				if (secondHandPair > secondOpponentPair) { return WIN; }
				else { return LOSE; }
			}
			// Both pairs are equal, check kicker
			vector<Card> trimmedHand;
			vector<Card> trimmedOpponentHand;
			string firstPairRank = ranks[firstHandPair];
			string secondPairRank = ranks[firstHandPair];
			// remove the paired cards
			int removedCards = 0;
			for (Card card : handAndCommunityCards) {
				if (card.get_rank() != firstPairRank && card.get_rank() != secondPairRank || removedCards >= 2) {
					trimmedHand.push_back(card);
				}
				else {
					removedCards++;
				}
			}
			for (Card card : opponentAndCommunityCards) {
				if (card.get_rank() != firstPairRank && card.get_rank() != secondPairRank || removedCards >= 2) {
					trimmedOpponentHand.push_back(card);
				}
				else {
					removedCards++;
				}
			}
			return checkHighCard(trimmedHand, trimmedOpponentHand, 1);
		}
		if (secondHandPair > secondOpponentPair) { return WIN; }
		else { return LOSE; }
	}


	if (firstHandPair != firstOpponentPair) {
		// Pairs are different, return true if hand is better pair
		if (firstHandPair > firstOpponentPair) { return WIN; }
		else { return LOSE; }
	}


	if (firstHandPair != -1) {
		// Pairs are the same
		return checkThreeTopCards(handAndCommunityCards, opponentAndCommunityCards, firstHandPair);
	}
	if (getRankValue(opponentHand[0].get_rank()) + getRankValue(opponentHand[1].get_rank()) == getRankValue(hand[0].get_rank()) + getRankValue(hand[1].get_rank())) {
		int i = 0;
	}
	// High Card Check
	return checkHighCard(handAndCommunityCards, opponentAndCommunityCards, 5);

	// draw
	return DRAW;
}

vector<int> HandEvaluator::checkForPairs(vector<Card> handAndCommunityCards) {
	int highestRank = -1;
	int secondHighestRank = -1;

	for (int i = 0; i < handAndCommunityCards.size(); i++) {
		int rank = getRankValue(handAndCommunityCards[i].get_rank());
		for (int j = i+1; j < handAndCommunityCards.size(); j++) {
			if (handAndCommunityCards[i].get_rank() == handAndCommunityCards[j].get_rank() && rank != highestRank) {
				if (rank > highestRank) {
					secondHighestRank = highestRank;
					highestRank = rank;
				}
				else if (rank > secondHighestRank) {
					secondHighestRank = rank;
				}
			}
		}
	}
	return { highestRank, secondHighestRank };
}

int HandEvaluator::checkOfAKind(vector<Card> handAndCommunityCards, int numOfAKind) {
	vector<int> counts = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	for (Card c : handAndCommunityCards) {
		counts[12-getRankValue(c.get_rank())]++;
	}
	for (int i = 0; i < 13; i++) {
		if (counts[i] >= numOfAKind) {
			return 12-i;
		}
	}
	return -1;
}

vector<int> HandEvaluator::checkForFlush(vector<Card> handAndCommunityCards) {
	vector<int> hearts;
	vector<int> diamonds;
	vector<int> clubs;
	vector<int> spades;
	
	for (Card c : handAndCommunityCards) {
		if (c.get_suit() == "Hearts") { hearts.push_back(getRankValue(c.get_rank())); }
		if (c.get_suit() == "Diamonds") { diamonds.push_back(getRankValue(c.get_rank())); }
		if (c.get_suit() == "Clubs") { clubs.push_back(getRankValue(c.get_rank())); }
		if (c.get_suit() == "Spades") { spades.push_back(getRankValue(c.get_rank())); }
	}
	std::sort(hearts.begin(), hearts.end(), std::greater<int>());
	std::sort(diamonds.begin(), diamonds.end(), std::greater<int>());
	std::sort(clubs.begin(), clubs.end(), std::greater<int>());
	std::sort(spades.begin(), spades.end(), std::greater<int>());

	if (hearts.size() > 4) { return hearts; }
	if (diamonds.size() > 4) { return diamonds; }
	if (clubs.size() > 4) { return clubs; }
	if (spades.size() > 4) { return spades; }
	return {};
}

int HandEvaluator::checkForStraight(vector<Card> handAndCommunityCards) {
	vector<int> cards;
	for (Card c : handAndCommunityCards) { cards.push_back(getRankValue(c.get_rank())); }
	std::sort(cards.begin(), cards.end(), std::greater<int>());
	int prevC = -2;
	int straightCards = 1;
	int highestStraight = -1;
	for (int c : cards) {
		if (prevC-1 == c) {
			straightCards++;
			prevC = c;
		}
		else {
			prevC = c;
			straightCards = 1;
			highestStraight = c;
		}
		if (straightCards == 5) {
			break;
		}
	}
	if (straightCards < 5) { highestStraight = -1; }
	return highestStraight;
}

int HandEvaluator::checkHighCard(vector<Card> handAndCommunityCards, vector<Card> opponentAndCommunityCards, int amountToCheck) {
	vector<int> handValues;
	vector<int> opponentHandValues;
	for (Card card : handAndCommunityCards) { handValues.push_back(getRankValue(card.get_rank())); }
	for (Card card : opponentAndCommunityCards) { opponentHandValues.push_back(getRankValue(card.get_rank())); }
	std::sort(handValues.begin(), handValues.end(), std::greater<int>());
	std::sort(opponentHandValues.begin(), opponentHandValues.end(), std::greater<int>());
	// check hand for high cards
	for (int i = 0; i < amountToCheck; i++) {
		if (handValues[i] != opponentHandValues[i]) {
			if (handValues[i] > opponentHandValues[i]) { return WIN; }
			else { return LOSE; }
		}
	}
	return DRAW;
}

int HandEvaluator::checkThreeTopCards(vector<Card> handAndCommunityCards, vector<Card> opponentAndCommunityCards, int pairValue) {
	string pairRank = ranks[pairValue];
	vector<int> trimmedHand;
	vector<int> trimmedOpponentHand;

	// remove the paired cards
	int removedCards = 0;
	for (Card card : handAndCommunityCards) {
		if (card.get_rank() != pairRank || removedCards >= 2) {
			trimmedHand.push_back(getRankValue(card.get_rank()));
		} 
		else {
			removedCards++;
		}
	}
	removedCards = 0;
	for (Card card : opponentAndCommunityCards) {
		if (card.get_rank() != pairRank || removedCards >= 2) {
			trimmedOpponentHand.push_back(getRankValue(card.get_rank()));
		}
		else {
			removedCards++;
		}
	}

	// sort the scores for the 5 remaining cards
	std::sort(trimmedHand.begin(), trimmedHand.end(), std::greater<int>());
	std::sort(trimmedOpponentHand.begin(), trimmedOpponentHand.end(), std::greater<int>());

	// check the next 3 highest cards and return the winner if they are different
	for (int i = 0; i < 3; i++) {
		if (trimmedHand[i] != trimmedOpponentHand[i]) {
			if (trimmedHand[i] > trimmedOpponentHand[i]) { return WIN; }
			else { return LOSE; }
		}
	}
	// draw as all top 3 cards are the same
	return DRAW;
}

int HandEvaluator::getRankValue(string rank) {
	auto it = std::find(ranks.begin(), ranks.end(), rank);
	int index = -1;
	if (it != ranks.end()) {
		index = distance(ranks.begin(), it);
	}
	return index;
}
