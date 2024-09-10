// Author: Jess

#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <ctime>
#include <cstdlib> 
#include <cstring>
#include <cstring>

#include "src/Card.hpp"
#include "src/Deck.hpp"
#include "src/Player.hpp"
#include "src/Game.hpp"
#include "src/HandEvaluator.hpp"
#include "src/EquityCalculator.hpp"
#include "src/GUI.hpp"

using namespace std;

// A main method for testing the classes
int main(int argc, char* argv[]) {

    // Check if the ci flag is passed
    if (argc > 1 && strcmp(argv[1], "-ci") == 0) {
        return 0;
    }

    // Display the start screen 
    GUI::displayStartScreen();

    int menuChoice = GUI::displayMenu();
    if (menuChoice == 0) {
        GUI::displayEndMessage();
        return 0;
    }

    GUI::clearScreen();

    // TODO: Implement a way to get the number of players from the user

    // The first player will always be the human player 
    HumanPlayer player1 = HumanPlayer("Jess", 1000);
    RandomPlayer player2 = RandomPlayer("James", 1000);
    RandomPlayer player3 = RandomPlayer("Corban", 1000);
    RandomPlayer player4 = RandomPlayer("Katie", 1000);
    RandomPlayer player5 = RandomPlayer("Megan", 1000);
    RandomPlayer player6 = RandomPlayer("Loren", 1000);
    RandomPlayer player7 = RandomPlayer("Emily", 1000);
    RandomPlayer player8 = RandomPlayer("Mr. Robot", 1000);

    // Create a vector of pointers 
    std::vector<Player*> playerPointers;
    playerPointers.push_back(&player1);
    playerPointers.push_back(&player2);
    //playerPointers.push_back(&player3);
    //playerPointers.push_back(&player4);
    //playerPointers.push_back(&player5);
    //playerPointers.push_back(&player6);
    //playerPointers.push_back(&player7);
    //playerPointers.push_back(&player8);

    // Initiate a game with all the players and pass game object to GUI
    Game game = Game(playerPointers);   // i swear you have to pass a pointer, but also its a list of two players
    GUI::setGame(&game);

    GUI::displayGameState();
    
    // Start a game loop 
    while(true){
        // Play a hand
        game.playHand();

        // Check if the player wants to play another hand
        if (playerPointers[0]->endOfHand() != 1) {
            break;
        }

    }

    // Display the end message
     GUI::displayEndMessage();

    return 0;

}

