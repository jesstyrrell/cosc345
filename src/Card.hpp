#include <string>

#pragma once

class Card {
    private: 
        std::string suit;
        std::string rank;

    public: 
        Card(std::string suit, std::string rank);
        std::string get_suit();
        std::string get_rank();
};