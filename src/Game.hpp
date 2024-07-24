#include <vector>

#include "Player.hpp"
#include "Deck.hpp"

#pragma once

class Game {
    private: 
        Deck deck;
        std::vector<Player*> players;
        std::vector<Card> community_cards;
        int pot;

    public:
        Game(std::vector<Player*>& players);
        void deal_hands();
        void deal_flop();
        void deal_turn();
        void deal_river();
        void show_community_cards();
        void show_player_hands();
        std::vector<Player*> get_players();
};