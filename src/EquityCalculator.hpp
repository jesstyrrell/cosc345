#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

#include "HandEvaluator.hpp"

/**
 * @class EquityCalculator
 * @brief Calculates the equity (winning probability) of a poker hand against multiple opponents.
 */
class EquityCalculator {
private:
    HandEvaluator handEvaluator;  ///< Object used for evaluating poker hands.

    vector<string> suits = { "Hearts", "Diamonds", "Clubs", "Spades" };  ///< The possible suits in a deck of cards.
    vector<string> ranks = { "2", "3", "4", "5", "6", "7", "8", "9", "10",
                      "J", "Q", "K", "A" };  ///< The possible ranks in a deck of cards.

    int WIN = 1;  ///< Constant representing a win.
    int DRAW = 0;  ///< Constant representing a draw.
    int LOSE = -1;  ///< Constant representing a loss.

public:
    /**
     * @brief Constructs an EquityCalculator object.
     */
    EquityCalculator();

    /**
     * @brief Evaluates the equity of a hand against multiple opponents.
     * @param hand The player's hand as a vector of Card objects.
     * @param communityCards The community cards as a vector of Card objects.
     * @param deck The remaining deck of cards after dealing hand and community cards.
     * @param numPlayers The number of players in the game.
     * @return A vector of float values representing the equity of the hand.
     */
    vector<float> evaluateHand(const vector<Card>& hand, const vector<Card>& communityCards, Deck deck, int numPlayers);
};
