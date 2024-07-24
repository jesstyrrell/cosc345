#include <string>
#include <vector>

#include "Card.hpp"

#pragma once


class Player {
    private: 
        std::string name;
        std::vector<Card> hand;
        int stack;

    public:
        Player(std::string name, int stack);
        void bet(int amount);
        void win(int amount);
        int get_stack();
        std::string get_name();
        std::vector<Card> get_hand();
        void add_card_to_hand(Card card);
        void clear_hand();
        void show_hand();
};