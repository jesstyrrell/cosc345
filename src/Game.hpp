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
        vector<int> currentBets;

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

        void awardPot(Player *player);

        vector<Player*> get_players();

        void resetPlayerBets();

        void playHand(); 
        int makeMoveForUser(std::string move, Player *player, int playerIndex, int largestBet);

        void bettingRound(vector<bool>& inGame, int largestBet, int numPlayers, Player *largestBetPlayer, bool preflop);


        bool static test_game();
};
