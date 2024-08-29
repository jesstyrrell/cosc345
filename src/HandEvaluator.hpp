#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

#include "Card.hpp"
#include "Deck.hpp"

/**
 * @class HandEvaluator
 * @brief Evaluates poker hands and determines winners, draws, or losses.
 */
class HandEvaluator {
private:
    vector<string> suits = { "Hearts", "Diamonds", "Clubs", "Spades" }; ///< The four suits in a deck of cards.
    vector<string> ranks = { "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A" }; ///< The thirteen ranks in a deck of cards.
    int WIN = 1;    ///< Constant for a winning hand.
    int DRAW = 0;   ///< Constant for a draw between hands.
    int LOSE = -1;  ///< Constant for a losing hand.

public:
    /**
     * @brief Constructs a HandEvaluator object.
     */
    HandEvaluator();

    /**
     * @brief Evaluates multiple hands against community cards.
     * @param hands A vector of player hands to evaluate.
     * @param communityCards The community cards shared among players.
     * @return A vector of booleans indicating which hands win.
     */
    vector<bool> evaluateTable(const vector<vector<Card>>& hands, const vector<Card>& communityCards);

    /**
     * @brief Compares two hands to determine the winner.
     * @param hand The first player's hand.
     * @param opponentHand The opponent's hand.
     * @param communityCards The community cards shared among players.
     * @return WIN if the first hand wins, LOSE if the opponent's hand wins, DRAW if they are equal.
     */
    int compareHands(vector<Card> hand, vector<Card> opponentHand, const vector<Card>& communityCards);

    /**
     * @brief Checks for pairs in a combined hand and community cards.
     * @param handAndCommunityCards A vector of cards combining a player's hand and community cards.
     * @return A vector of integers representing the pairs found.
     */
    vector<int> checkForPairs(vector<Card> handAndCommunityCards);

    /**
     * @brief Checks for a specified number of a kind in a hand and community cards.
     * @param handAndCommunityCards A vector of cards combining a player's hand and community cards.
     * @param numOfAKind The number of identical ranks to check for (e.g., 3 for three-of-a-kind).
     * @return The value of the rank if found, otherwise 0.
     */
    int checkOfAKind(const vector<Card>& handAndCommunityCards, int numOfAKind);

    /**
     * @brief Checks for a flush in a combined hand and community cards.
     * @param handAndCommunityCards A vector of cards combining a player's hand and community cards.
     * @return A vector of integers representing the flush found.
     */
    vector<int> checkForFlush(const vector<Card>& handAndCommunityCards);

    /**
     * @brief Checks for a straight in a combined hand and community cards.
     * @param handAndCommunityCards A vector of cards combining a player's hand and community cards.
     * @return The value of the highest card in the straight if found, otherwise 0.
     */
    int checkForStraight(const vector<Card>& handAndCommunityCards);

    /**
     * @brief Compares high cards between two hands.
     * @param handAndCommunityCards The first player's combined hand and community cards.
     * @param opponentAndCommunityCards The opponent's combined hand and community cards.
     * @param amountToCheck The number of top cards to check.
     * @return WIN if the first hand's high cards win, LOSE if the opponent's high cards win, DRAW if they are equal.
     */
    int checkHighCard(const vector<Card>& handAndCommunityCards, const vector<Card>& opponentAndCommunityCards, int amountToCheck);

    /**
     * @brief Compares the top three cards between two hands after pairs have been evaluated.
     * @param handAndCommunityCards The first player's combined hand and community cards.
     * @param opponentAndCommunityCards The opponent's combined hand and community cards.
     * @param pairValue The value of the pair to check.
     * @return WIN if the first hand's top three cards win, LOSE if the opponent's top three cards win, DRAW if they are equal.
     */
    int checkThreeTopCards(const vector<Card>& handAndCommunityCards, const vector<Card>& opponentAndCommunityCards, int pairValue);

    /**
     * @brief Gets the numerical value of a card rank.
     * @param rank The rank as a string (e.g., "A", "10", "K").
     * @return The numerical value of the rank.
     */
    int getRankValue(string rank);
};
