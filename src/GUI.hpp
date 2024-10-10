#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <fstream>
#include <sstream>
#include <chrono>
#include <iomanip>

#include "PlayerProfile.hpp"

class Game;

using namespace std;

/**
 * @struct Point
 * @brief Represents a point with x and y coordinates.
 */
struct Point {
    int x;  ///< The x-coordinate of the point.
    int y;  ///< The y-coordinate of the point.
};

// Enum for defining the menu options
enum MenuOption { START_GAME, CREATE_PROFILE, QUIT };

/**
 * @class GUI
 * @brief Provides a graphical user interface for interacting with the poker game.
 */
class GUI {
    private:
        /// Pointer to the game object used for getting game state information
        static Game* game;

        /**
         * @brief Creates a new player profile.
         * @return The newly created player profile.
         */
        static PlayerProfile createProfile();

        /**
         * @brief Gets the profile of a player from the `./data/profiles.csv` file.
         * @param name The name of the player.
         * @return The profile of the player.
         */
        static PlayerProfile getProfile(const std::string& name); 


    public:
        static const Point PLAYER_CARD_POSITIONS[8][2];  ///< Positions for player cards.
        static const Point COMMUNITY_CARD_POSITIONS[5];  ///< Positions for community cards.
        static const Point PLAYER_NAME_POSITIONS[8];     ///< Positions for player names.
        static const Point PLAYER_CURRENT_BETS[8];       ///< Positions for player current bets.
        static const Point PLAYER_BUTTON_POSITIONS[8];   ///< Positions for player buttons.
        static const Point PLAYER_EQUITY_POSITION[2];    ///< Positions for player equity.

        /**
         * @brief Sets the game object for the GUI.
         * @param game Pointer to the game object.
         */
        static void setGame(Game* game);

        /**
         * @brief Gets the game object for the GUI.
         * @return Reference to the game object.
         */
        static Game& getGame();

        /**
         * @brief Prompts the user to sign in.
         * @return The name of the user as a string.
         */
        static PlayerProfile signInMenu();

        /**
         * @brief Gets the number of players from the user.
         * @return The number of players as an integer.
         */
        static int getNumberOfPlayers();

        static int getBotDifficulty();

        /**
         * @brief Clears the console screen.
         */
        static void clearScreen();

        /**
         * @brief Generate a random name for a player.
         * @return The randomly generated name as a string.
         */
        static string getRandomPlayerName();

        // Methods performed on the user

        /**
         * @brief Prompts the user for their move.
         * @param canCheck Whether the player can check.
         * @param canRaise Whether the player can raise.
         * @param canFold Whether the player can fold.
         * @param canCall Whether the player can call.
         * @return The move chosen by the user as a string.
         */
        static string getUserMove(bool canCheck, bool canRaise, bool canFold, bool canCall);

        /**
         * @brief Prompts the user for bet sizing.
         * @param minBet The minimum bet allowed.
         * @param maxBet The maximum bet allowed.
         * @return The bet size chosen by the user.
         */
        static int getBetSizing(int minBet, int maxBet);

        // Methods performed on all players

        /**
         * @brief Displays the hands of all players.
         * @param players A vector of pointers to the players whose hands will be displayed.
         */
        static void displayAllPlayerHands(const std::vector<Player*>& players);

        /**
         * @brief Displays the community cards on the table.
         * @param community_cards A vector of community cards to be displayed.
         */
        static void displayCommunityCards(const std::vector<Card>& community_cards);
        
        // Methods performed on a single player 

        /**
         * @brief Displays the current chip stack of a player.
         * @param player Pointer to the player whose stack will be displayed.
         */
        static void displayPlayerStack(Player *player);

        /**
         * @brief Displays the hand of a player.
         * @param player Pointer to the player whose hand will be displayed.
         */
        static void displayPlayerHand(Player *player);

        // Methods performed on the game

        /**
         * @brief Displays the start screen of the game.
         */
        static void displayStartScreen();

        /**
         * @brief Displays the end message when the game is over.
         */
        static void displayEndMessage();

        //static void displayWinner(Player* player);

        /**
         * @brief Displays the main menu of the game.
         * @return The selected menu option as an integer.
         */
        static MenuOption displayMenu();

        /**
         * @brief Displays the menu at the end of a round.
         * @return The selected menu option as an integer.
         */
        static int endOfRoundMenu();

        /**
         * @brief Displays the current state of the game.
         */
        static void displayGameState();

        /**
         * @brief Displays a player's move.
         * @param player Pointer to the player making the move.
         * @param move The move made by the player as a string.
         * @param size The bet size associated with the move.
         */
        static void displayPlayerMove(Player* player, string move, int size);

        /**
         * @brief Displays input to the user to create a profile.
         */
        static PlayerProfile chooseAccount();
};
