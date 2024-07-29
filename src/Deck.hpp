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
};
