// Author: Jess

#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <ctime>
#include <cstdlib> 
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

    MenuOption menuChoice = GUI::displayMenu();
    if (menuChoice == MenuOption::QUIT) {
        GUI::displayEndMessage();
        return 0;
    }

    // Call the GUI method to get the players name, and let them play as guest
    PlayerProfile currentPlayer = GUI::signInMenu();
    int numberOfPlayers = GUI::getNumberOfPlayers();

    bool testBBPerRound = true;
    int startingStack = 1000;
    std::vector<Player*> playerPointers;
    if (testBBPerRound) {
        startingStack = 10000000;
        RandomPlayer player = RandomPlayer(currentPlayer.name, startingStack);
        playerPointers.push_back(&player);
    }
    else {
        HumanPlayer player = HumanPlayer(currentPlayer.name, startingStack);
        playerPointers.push_back(&player);
    }

    for(int i = 0; i < numberOfPlayers-1; i++){
        string randomPlayerName = GUI::getRandomPlayerName();
        RandomPlayer *player = new RandomPlayer(randomPlayerName, startingStack);
        playerPointers.push_back(player);
    }

    // Initiate a game with all the players and pass game object to GUI
    Game game = Game(playerPointers);   // i swear you have to pass a pointer, but also its a list of two players
    GUI::setGame(&game);

    GUI::displayGameState();
    
    int Round = 0;
    // Start a game loop
    while(true){
        Round++;
        // Play a hand
        game.playHand(10);

        // Check if the player wants to play another hand
        if (playerPointers[0]->endOfHand() != 1) {
            break;
        }
        if (testBBPerRound && Round >= 100) {
            cout << (playerPointers[0]->get_stack() - startingStack) / (game.getBigBlind() * Round) << endl;
            GUI::endOfRoundMenu();
            break;
        }
    }

    // Display the end message
     GUI::displayEndMessage();

    return 0;

}


