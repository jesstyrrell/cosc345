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
#include "src/PlayerProfile.hpp"

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



    std::vector<Player*> playerPointers;

    // Ask the user if they want to create an account, play or play as guest
    PlayerProfile currentPlayer = GUI::chooseAccount();
    // Creating a human player from the player profile
    HumanPlayer humanPlayer = HumanPlayer(currentPlayer.name, 1000);
    cout << "[DEBUGGING] Player name: " << currentPlayer.name << endl;
    playerPointers.push_back(&humanPlayer);


    // Create n random players
    int numberOfPlayers = GUI::getNumberOfPlayers();
    cout << "[DEBUGGING] Number of players: " << numberOfPlayers << endl;
    for (int i = 0; i < numberOfPlayers - 1; i++) {
        int startingPot = 1000;

        RandomPlayer randomPlayer = RandomPlayer(Player::generate_random_name(), startingPot);
        playerPointers.push_back(&randomPlayer);
    }

    while(true) {
        // Click enter to break
        if (cin.get() == '\n') {
            break;
        }
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

