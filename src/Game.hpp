#pragma once

#include <iostream>
#include <vector>

#include "Player.hpp"
#include "RandomPlayer.cpp"
#include "HumanPlayer.cpp"
#include "Deck.hpp"
#include "Card.hpp"
#include "GUI.hpp"

enum Move { CHECK, CALL, RAISE, FOLD };
enum Stage { PREFLOP, FLOP, TURN, RIVER };

class Game {
    private:
        vector<Player*> players;
        vector<Card> community_cards = {};
        vector<int> currentBets;

        const int BIG_BLIND = 2;
        const int SMALL_BLIND = 1;
        const int STARTING_STACK = 1000;
        int pot = 0;
        int button = 0; 
        int removedPlayerCount = 0;
        bool atShowdown = false;

        
        Move getCurrentMove(std::string move);

        void addBlindsToPot(Player *bigBlindPlayer, Player *smallBlindPlayer);

    public:
        // Public variables for unit testing
        Deck deck;
        Stage currentStage = PREFLOP;

        Game(vector<Player*>& players);
        void add_player(Player *player);

        void deal();
        void nextStage();

        void deal_hands();
        void deal_flop();
        void deal_turn();
        void deal_river();

        int getPot();
        int getButton();
        bool getShowdown();

        void awardPot(vector<Player*> winners);

        vector<Player*> getPlayers();
        vector<Card> getCommunityCards();

        void resetPlayerBets();
        void resetPlayerHands();
        void resetCommunityCards();

        void playHand(); 
        int makeMoveForUser(const std::string& move, Player *player, int playerIndex, int largestBet);

        bool bettingRound(vector<bool>& inGame, int largestBet, int numPlayers);

        Player* get_final_winner(vector<bool>& inGame);

        vector<Player*> getWinner(vector<Player*> players, const vector<Card>& community_cards, const vector<bool>& inGame);



        bool static test_game();
};
