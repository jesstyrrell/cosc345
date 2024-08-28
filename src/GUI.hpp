#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <fstream>
#include <sstream>
#include <chrono>

class Game;

using namespace std; 

struct Point{
    int x;
    int y;
};

class GUI {
    private:
        // Pointer to the game object used for getting game state information
        static Game* game;

    public: 
        static const Point PLAYER_CARD_POSITIONS[8][2];
        static const Point COMMUNITY_CARD_POSITIONS[5];
        static const Point PLAYER_NAME_POSITIONS[8];
        static const Point PLAYER_CURRENT_BETS[8];
        static const Point PLAYER_BUTTON_POSITIONS[8];

        /**
         * Set the game object for the GUI
         * @param game: Game* - Pointer to the game object
         */
        static void setGame(Game* game);

        /**
         * Get the game object for the GUI
         * @return Game& - Reference to the game object
         */
        static Game& getGame();
    
        static void clearScreen();

        // Methods performed on the user
        static string getUserMove(bool canCheck, bool canRaise, bool canFold, bool canCall);
        static int getBetSizing(int minBet, int maxBet);

        // Methods performed on all players
        static void displayAllPlayerHands(const std::vector<Player*>& players);
        static void displayCommunityCards(const std::vector<Card>& community_cards);
        
        // Methods performed on a single player 
        static void displayPlayerStack(Player *player);
        static void displayPlayerHand(Player *player);

        // Methods performed on the game
        static void displayStartScreen();
        static void displayEndMessage();
        //static void displayWinner(Player* player);

        
        static int displayMenu();
        static int endOfRoundMenu();
        static void displayGameState();
        static void displayPlayerMove(Player* player, string move, int size);
}; 