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
#include "src/BasicPlayer.cpp"
#include "src/BetterPlayer.cpp"

using namespace std;

void playGame(){
    // Display the start screen
    GUI::displayStartScreen();

    MenuOption menuChoice = GUI::displayMenu();
    if (menuChoice == MenuOption::QUIT) {
        GUI::displayEndMessage();
        return;
    }

    // Call the GUI method to get the players name, and let them play as guest
    PlayerProfile currentPlayer = GUI::signInMenu();
    int difficulty = GUI::getBotDifficulty();
    int numberOfPlayers = GUI::getNumberOfPlayers();

    
    std::vector<Player*> playerPointers;
    HumanPlayer player = HumanPlayer(currentPlayer.name, 1000);
    playerPointers.push_back(&player);

    for(int i = 0; i < numberOfPlayers-1; i++){
        string randomPlayerName = GUI::getRandomPlayerName();
        if (difficulty == 1) {
            RandomPlayer randPlayer = RandomPlayer(randomPlayerName, 1000);
            playerPointers.push_back(&randPlayer);
        }
        if (difficulty == 2) {
            BasicPlayer basicPlayer = BasicPlayer(randomPlayerName, 1000);
            playerPointers.push_back(&basicPlayer);
        }
        if (difficulty == 3) {
            BetterPlayer betterPlayer = BetterPlayer(randomPlayerName, 1000);
            playerPointers.push_back(&betterPlayer);
        }
    }

    // Initiate a game with all the players and pass game object to GUI
    Game game = Game(playerPointers);   // i swear you have to pass a pointer, but also its a list of two players
    GUI::setGame(&game);

    GUI::displayGameState();
    
    // Start a game loop
    while(true){
        // Play a hand
        cout << "testing testing" << endl;
        game.playHand();

        int playerChoice = playerPointers[0]->endOfHand();
        // Check if the player wants to play another hand
        if (playerChoice == 0) {
            break;
        }
        if(playerChoice == 2){
            playGame();
            return;
        }

    }

    // Display the end message
    GUI::displayEndMessage();

    return;

}




// A main method for testing the classes
int main(int argc, char* argv[]) {

    // Check if the ci flag is passed
    if (argc > 1 && strcmp(argv[1], "-ci") == 0) {
        return 0;
    }
    playGame();
}

