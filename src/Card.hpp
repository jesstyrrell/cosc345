#pragma once

#include <string>

/**
 * Card class
 * Represents a single card in a deck of cards. Each card has a suit and a rank.
 *
 * `Card card = Card("Hearts", "Ace");`
 */
class Card{
    public:
        std::string suit;
        std::string rank;

    public:
        Card(const std::string& suit, const std::string& rank);
        std::string get_suit();
        std::string get_rank();
        std::string get_card();
        static bool test_card();
};