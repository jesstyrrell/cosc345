#include <vector>

#include "Card.hpp"

#pragma once

class Deck {
    private: 
        std::vector<Card> cards;

    public: 
        Deck();
        void shuffle();
        Card deal();
};