#pragma once 

#include <iostream>
#include <string>

using namespace std; 

class GUI {
    public: 
        static void clearScreen();

        static string getUserMove();
        static int getBetSizing();

        // Methods performed on all players
        static void displayAllPlayerHands(std::vector<Player*> players);
        static void displayCommunityCards(std::vector<Card> community_cards);
        
        // Methods performed on a single player 
        static void displayPlayerStack(Player *player);
}; 