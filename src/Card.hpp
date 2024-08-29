#pragma once

#include <string>

/**
 * @class Card
 * @brief Represents a single card in a deck of cards. Each card has a suit and a rank.
 *
 * Example usage:
 * @code
 * Card card = Card("Hearts", "Ace");
 * @endcode
 */
class Card {
    public:
        std::string suit;  ///< The suit of the card (e.g., Hearts, Diamonds).
        std::string rank;  ///< The rank of the card (e.g., Ace, King, 7).

    public:
        /**
         * @brief Constructs a Card object with the given suit and rank.
         * @param suit The suit of the card.
         * @param rank The rank of the card.
         */
        Card(const std::string& suit, const std::string& rank);

        /**
         * @brief Gets the suit of the card.
         * @return The suit of the card as a string.
         */
        const std::string get_suit();

        /**
         * @brief Gets the rank of the card.
         * @return The rank of the card as a string.
         */
        const std::string get_rank();

        /**
         * @brief Gets the card's representation as a string.
         * @return A string representing the card (e.g., "Ace of Hearts").
         */
        const std::string get_card();

        /**
         * @brief Tests the Card class functionality.
         * @return True if the test passes, otherwise false.
         */
        static bool test_card();
};
