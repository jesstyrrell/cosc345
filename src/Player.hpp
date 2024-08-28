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
        int current_bet = 0;

    public:
        Player(const std::string& name, int stack);
        
        void bet(int amount);
        int deduct_blind(int amount);
        void win(int amount);
        int get_stack();
        string get_name();
        vector<Card> get_hand();
        void add_card_to_hand(Card card);
        void clear_hand();
        void show_hand();
        bool static test_player();
        int get_current_bet();
        void reset_current_bet();

        // virtual methods to overide in human player and AI player
        virtual std::string getMove(bool canCheck, bool canRaise, bool canFold, bool canCall) = 0;
        virtual int getBetSizing(int minBet, int maxBet) = 0;
        virtual int endOfHand() = 0;

};
