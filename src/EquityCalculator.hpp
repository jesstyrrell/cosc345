#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

#include "HandEvaluator.hpp"

class EquityCalculator {
private:
    HandEvaluator handEvaluator;

    vector<string> suits = { "Hearts", "Diamonds", "Clubs", "Spades" };
    vector<string> ranks = { "2", "3", "4", "5", "6", "7", "8", "9", "10",
                      "J", "Q", "K", "A" };
    int WIN = 1;
    int DRAW = 0;
    int LOSE = -1;


public:
    EquityCalculator();

    vector<float> evaluateHand(const vector<Card>& hand, const vector<Card>& communityCards, Deck deck, int numPlayers);

};
