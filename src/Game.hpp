#pragma once

#include <iostream>
#include <vector>
#include <string>

#include "Player.hpp"
#include "Deck.hpp"
#include "Card.hpp"

using namespace std; 

class Game {
    private:
        Deck deck;
        vector<Player*> players;
        vector<Card> community_cards;
        int pot = 0;

    public:
        Game(vector<Player*>& players);
        void add_player(Player *player);
        void deal_hands();
        void deal_flop();
        void deal_turn();
        void deal_river();
        void show_community_cards();
        void show_player_hands();
        vector<Player*> get_players();
        bool static test_game();
};
