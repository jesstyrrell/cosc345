#pragma once 

#include <iostream>
#include <string>

using namespace std; 

class GUI {
    public: 
    
        static void clearScreen();

        // Methods performed on the user
        static string getUserMove(bool canCheck, bool canRaise);
        static int getBetSizing(int minBet, int maxBet);

        // Methods performed on all players
        static void displayAllPlayerHands(std::vector<Player*> players);
        static void displayCommunityCards(std::vector<Card> community_cards);
        
        // Methods performed on a single player 
        static void displayPlayerStack(Player *player);
        static void displayPlayerHand(Player *player);
}; 