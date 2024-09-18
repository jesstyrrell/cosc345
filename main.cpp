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

    // Call the GUI method to get the players name, and let them play as guest
    string playerName = GUI::signInMenu();
    int numberOfPlayers = GUI::getNumberOfPlayers();

    
    std::vector<Player*> playerPointers;
    HumanPlayer player = HumanPlayer(playerName, 1000);
    playerPointers.push_back(&player);

    for(int i = 0; i < numberOfPlayers-1; i++){
        string name = GUI::getRandomPlayerName();
        cout << name << endl;
        RandomPlayer *player = new RandomPlayer(name, 1000);
        playerPointers.push_back(player);
    }

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


