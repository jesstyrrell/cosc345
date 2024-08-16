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
    vector<string> suits;
    vector<string> ranks;


public:
    HandEvaluator();

    float evaluateHand(vector<Card> hand, vector<Card> communityCards, Deck deck, int numPlayers);

    bool compareHands(vector<Card> hand, vector<Card> opponentHand, vector<Card> communityCards);

    int checkPair(vector<Card> hand, vector<Card> communityCards);

    int getRankValue(string rank);
};