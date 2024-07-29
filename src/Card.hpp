#pragma once

#include <string>

/**
 * Card class
 * Represents a single card in a deck of cards. Each card has a suit and a rank.
 *
 * `Card card = Card("Hearts", "Ace");`
 */
class Card{
    private:
        std::string suit;
        std::string rank;

    public:
        Card(std::string suit, std::string rank);
        std::string get_suit();
        std::string get_rank();
        static bool test_card();
};