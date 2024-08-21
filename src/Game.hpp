#pragma once

#include <iostream>
#include <vector>

#include "Player.hpp"
#include "RandomPlayer.cpp"
#include "HumanPlayer.cpp"
#include "Deck.hpp"
#include "Card.hpp"

enum Move { CHECK, CALL, RAISE, FOLD };
enum Stage { PREFLOP, FLOP, TURN, RIVER };

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

        Stage currentStage = PREFLOP;
        
        Move getCurrentMove(std::string move);

        void addBlindsToPot(Player *bigBlindPlayer, Player *smallBlindPlayer);

    public:
        Game(vector<Player*>& players);
        void add_player(Player *player);

        void deal();
        void nextStage();

        void deal_hands();
        void deal_flop();
        void deal_turn();
        void deal_river();

        void awardPot(Player *player);

        vector<Player*> get_players();

        void resetPlayerBets();
        void resetPlayerHands();
        void resetCommunityCards();

        void playHand(); 
        int makeMoveForUser(const std::string& move, Player *player, int playerIndex, int largestBet);

        bool bettingRound(vector<bool>& inGame, int largestBet, int numPlayers);

        Player* get_final_winner(vector<bool>& inGame);




        bool static test_game();
};
