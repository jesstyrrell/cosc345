#pragma once

#include <iostream>
#include <vector>

#include "Player.hpp"
#include "RandomPlayer.cpp"
#include "HumanPlayer.cpp"
#include "Deck.hpp"
#include "Card.hpp"
#include "GUI.hpp"

/**
 * @enum Move
 * @brief Represents the possible moves a player can make in the game.
 */
enum Move { CHECK, CALL, RAISE, FOLD };

/**
 * @enum Stage
 * @brief Represents the different stages of a poker hand.
 */
enum Stage { PREFLOP, FLOP, TURN, RIVER };

/**
 * @class Game
 * @brief Manages the state and flow of a poker game.
 */
class Game {
    private:
        vector<Player*> players;
        vector<Card> community_cards = {};
        vector<int> currentBets;

        const int BIG_BLIND = 2;
        const int SMALL_BLIND = 1;
        const int STARTING_STACK = 100000;
        int pot = 0;
        int button = 0; 
        int removedPlayerCount = 0;
        bool atShowdown = false;
        
        /**
         * @brief Converts a move string into a Move enum.
         * @param move The move as a string.
         * @return The corresponding Move enum value.
         */
        Move getCurrentMove(std::string move);

        /**
         * @brief Adds the blinds to the pot from the appropriate players.
         * @param bigBlindPlayer Pointer to the player posting the big blind.
         * @param smallBlindPlayer Pointer to the player posting the small blind.
         */
        void addBlindsToPot(Player *bigBlindPlayer, Player *smallBlindPlayer);

    public:
        // Public variables for unit testing
        Deck deck;
        Stage currentStage = PREFLOP;

        /**
         * @brief Constructs a Game object with the given players.
         * @param players A vector of pointers to the players in the game.
         */
        Game(vector<Player*>& players);

        /**
         * @brief Adds a player to the game.
         * @param player Pointer to the player to be added.
         */
        void add_player(Player *player);

        /**
         * @brief Deals the cards to the players and the community.
         */
        void deal();

        /**
         * @brief Advances the game to the next stage.
         */
        void nextStage();

        /**
         * @brief Deals the hands to the players.
         */
        void deal_hands();

        /**
         * @brief Deals the flop (the first three community cards).
         */
        void deal_flop();

        /**
         * @brief Deals the turn (the fourth community card).
         */
        void deal_turn();

        /**
         * @brief Deals the river (the fifth community card).
         */
        void deal_river();

        /**
         * @brief Gets the current pot size.
         * @return The total amount of chips in the pot.
         */
        int getPot();

        /**
         * @brief Gets the current position of the dealer button.
         * @return The index of the dealer button.
         */
        int getButton();

        /**
         * @brief Checks if the game is at showdown.
         * @return True if the game is at showdown, otherwise false.
         */
        bool getShowdown();

        /**
         * @brief Awards the pot to the winning players.
         * @param winners A vector of pointers to the winning players.
         */
        void awardPot(vector<Player*> winners);

        /**
         * @brief Gets the players in the game.
         * @return A vector of pointers to the players.
         */
        vector<Player*> getPlayers();

        /**
         * @brief Gets the community cards on the table.
         * @return A vector of the community cards.
         */
        vector<Card> getCommunityCards();

        /**
         * @brief Resets the current bets of all players.
         */
        void resetPlayerBets();

        /**
         * @brief Resets the hands of all players.
         */
        void resetPlayerHands();

        /**
         * @brief Resets the community cards on the table.
         */
        void resetCommunityCards();

        /**
         * @brief Plays a single hand of poker.
         */
        void playHand(); 

        /**
         * @brief Processes a move made by the user.
         * @param move The move as a string.
         * @param player Pointer to the player making the move.
         * @param playerIndex The index of the player.
         * @param largestBet The current largest bet on the table.
         * @return The result of the move as an integer.
         */
        int makeMoveForUser(const std::string& move, Player *player, int playerIndex, int largestBet);

        /**
         * @brief Conducts a betting round.
         * @param inGame A vector indicating which players are still in the game.
         * @param largestBet The current largest bet on the table.
         * @param numPlayers The number of players in the game.
         * @return True if the betting round is successful, otherwise false.
         */
        bool bettingRound(vector<bool>& inGame, int largestBet, int numPlayers);

        /**
         * @brief Determines the final winner of the game.
         * @param inGame A vector indicating which players are still in the game.
         * @return Pointer to the final winning player.
         */
        Player* get_final_winner(vector<bool>& inGame);

        /**
         * @brief Determines the winner(s) of the current hand.
         * @param players A vector of pointers to the players in the game.
         * @param community_cards A vector of community cards.
         * @param inGame A vector indicating which players are still in the game.
         * @return A vector of pointers to the winning players.
         */
        vector<Player*> getWinner(vector<Player*> players, const vector<Card>& community_cards, const vector<bool>& inGame);

        /**
         * @brief Tests the Game class functionality.
         * @return True if the test passes, otherwise false.
         */
        bool static test_game();
};
