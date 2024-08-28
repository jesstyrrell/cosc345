#pragma once

#include <vector>

#include "Card.hpp"

using namespace std; 

class Deck {
    private:
        vector<Card> cards;

    public:
        Deck();
        void shuffle();
        Card deal();
        vector<Card> get_cards();
        bool static test_deck();

        // Helper functions for evaluating cards
        Card find_card(const string& rank, const string& suit);
        void remove_card(Card card);
        void reset();
};
