#pragma once

#include <vector>

#include "Card.hpp"

using namespace std;

/**
 * @class Deck
 * @brief Represents a deck of playing cards, providing functionality to shuffle, deal, and manage the deck.
 */
class Deck {
    private:
        vector<Card> cards;  ///< The collection of cards in the deck.

    public:
        /**
         * @brief Constructs a Deck object and initializes the deck with all 52 cards.
         */
        Deck();

        /**
         * @brief Shuffles the deck of cards.
         */
        void shuffle();

        /**
         * @brief Deals a card from the top of the deck.
         * @return The top card from the deck.
         */
        Card deal();

        /**
         * @brief Retrieves the current set of cards in the deck.
         * @return A vector of Card objects representing the current deck.
         */
        vector<Card> get_cards();

        /**
         * @brief Tests the Deck class functionality.
         * @return True if the test passes, otherwise false.
         */
        bool static test_deck();

        /**
         * @brief Finds a specific card in the deck based on rank and suit.
         * @param rank The rank of the card to find.
         * @param suit The suit of the card to find.
         * @return The Card object matching the specified rank and suit.
         */
        Card find_card(const string& rank, const string& suit);

        /**
         * @brief Removes a specified card from the deck.
         * @param card The Card object to be removed.
         */
        void remove_card(Card card);

        /**
         * @brief Resets the deck to its initial state with all 52 cards.
         */
        void reset();
};
