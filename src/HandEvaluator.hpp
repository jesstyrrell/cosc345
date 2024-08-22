#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

#include "Card.hpp"
#include "Deck.hpp"

class HandEvaluator {
private:
    vector<string> suits = { "Hearts", "Diamonds", "Clubs", "Spades" };
    vector<string> ranks = { "2", "3", "4", "5", "6", "7", "8", "9", "10",
                      "J", "Q", "K", "A" };
    int WIN = 1;
    int DRAW = 0;
    int LOSE = -1;


public:
    HandEvaluator();

    vector<bool> evaluateTable(vector<vector<Card>> hands, vector<Card> communityCards);

    int compareHands(vector<Card> hand, vector<Card> opponentHand, vector<Card> communityCards);

    vector<int> checkForPairs(vector<Card> handAndCommunityCards);
    int checkOfAKind(vector<Card> handAndCommunityCards, int numOfAKind);
    vector<int> checkForFlush(vector<Card> handAndCommunityCards);
    int checkForStraight(vector<Card> handAndCommunityCards);

    int checkHighCard(vector<Card> handAndCommunityCards, vector<Card> opponentAndCommunityCards, int amountToCheck);
    int checkThreeTopCards(vector<Card> handAndCommunityCards, vector<Card> opponentAndCommunityCards, int pairValue);

    int getRankValue(string rank);
};
