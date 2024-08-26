#pragma once 

#include <iostream>
#include <string>

using namespace std; 

class GUI {
    public: 
    
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
        static void displayWinner(Player* player);

        
        static int displayMenu();

}; 