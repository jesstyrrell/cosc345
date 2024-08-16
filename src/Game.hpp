#pragma once

#include <iostream>
#include <vector>

#include "Player.hpp"
#include "Deck.hpp"
#include "Card.hpp"

enum Move { CHECK, CALL, RAISE, FOLD };

class Game {
    private:
        Deck deck;
        vector<Player*> players;
        vector<Card> community_cards;

        const int BIG_BLIND = 10;
        const int SMALL_BLIND = 5;
        int pot = 0;
        int button = 0; 
        
        Move getCurrentMove(std::string move);

        void addBlindsToPot(Player *bigBlindPlayer, Player *smallBlindPlayer);

    public:
        Game(vector<Player*>& players);
        void add_player(Player *player);

        void deal_hands();
        void deal_flop();
        void deal_turn();
        void deal_river();

        vector<Player*> get_players();

        void playHand(); 
        void makeMoveForUser(std::string move, Player *player);


        bool static test_game();
};
