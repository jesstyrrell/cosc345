#pragma once

#include <iostream>
#include <vector>
#include <string>

#include "Card.hpp"

using namespace std;

/**
 * @class Player
 * @brief Represents a player in the poker game.
 */
class Player {
    private:
        string name;                ///< The name of the player.
        vector<Card> hand;          ///< The player's hand of cards.
        int stack;                  ///< The player's current chip stack.
        int current_bet = 0;        ///< The player's current bet in the ongoing hand.

    public:
        /**
         * @brief Constructs a Player object with a given name and stack.
         * @param name The name of the player.
         * @param stack The initial chip stack for the player.
         */
        Player(const std::string& name, int stack);
        
        /**
         * @brief Places a bet by the player.
         * @param amount The amount to bet.
         */
        void bet(int amount);

        /**
         * @brief Deducts a blind amount from the player's stack.
         * @param amount The amount of the blind to deduct.
         * @return The remaining stack after deducting the blind.
         */
        int deduct_blind(int amount);

        /**
         * @brief Adds a winning amount to the player's stack.
         * @param amount The amount won.
         */
        void win(int amount);

        /**
         * @brief Gets the current stack of the player.
         * @return The player's current chip stack.
         */
        int get_stack();

        /**
         * @brief Gets the name of the player.
         * @return The player's name.
         */
        string get_name();

        /**
         * @brief Gets the player's current hand of cards.
         * @return A vector containing the player's hand of cards.
         */
        vector<Card> get_hand();

        /**
         * @brief Adds a card to the player's hand.
         * @param card The card to be added.
         */
        void add_card_to_hand(Card card);

        /**
         * @brief Clears the player's hand of all cards.
         */
        void clear_hand();

        /**
         * @brief Displays the player's current hand.
         */
        void show_hand();

        /**
         * @brief Tests the Player class functionality.
         * @return True if the test passes, otherwise false.
         */
        bool static test_player();

        /**
         * @brief Gets the player's current bet in the ongoing hand.
         * @return The player's current bet amount.
         */
        int get_current_bet();

        /**
         * @brief Resets the player's current bet to zero.
         */
        void reset_current_bet();

        /**
         * @brief Generates a random name for the player.
         * @return The randomly generated name.
         */
        static string generate_random_name();

        /**
         * @brief Returns the equity of the players hand for the current stage of the game
         * @param communityCards The community cards to check player cards against.
         * @param numPlayers The number of players in the game.
         */
        vector<float> get_equity(vector<Card> communityCards, int numPlayers);

        // virtual methods to override in human player and AI player

        /**
         * @brief Gets the player's move during their turn.
         * @param canCheck Whether the player can check.
         * @param canRaise Whether the player can raise.
         * @param canFold Whether the player can fold.
         * @param canCall Whether the player can call.
         * @return The player's chosen move as a string.
         */
        virtual std::string getMove(bool canCheck, bool canRaise, bool canFold, bool canCall, vector<Card> community_cards, int largestBet, int numPlayersInHand) = 0;

        /**
         * @brief Gets the player's bet sizing during their turn.
         * @param minBet The minimum bet allowed.
         * @param maxBet The maximum bet allowed.
         * @return The player's chosen bet size.
         */
        virtual int getBetSizing(int minBet, int maxBet) = 0;

        /**
         * @brief Handles actions at the end of a hand.
         * @return The outcome of the end-of-hand process.
         */
        virtual int endOfHand() = 0;
};
