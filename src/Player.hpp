#pragma once

#include <iostream>
#include <vector>
#include <string>

#include "Card.hpp"

using namespace std; 

class Player {
    private:
        string name;
        vector<Card> hand;
        int stack;

    public:
        Player(string name, int stack);
        
        void bet(int amount);
        void win(int amount);
        int get_stack();
        string get_name();
        vector<Card> get_hand();
        void add_card_to_hand(Card card);
        void clear_hand();
        void show_hand();
};
