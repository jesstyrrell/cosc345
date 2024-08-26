// Author: Jess

#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <ctime>
#include <cstdlib> 

#include "src/Card.hpp"
#include "src/Deck.hpp"
#include "src/Player.hpp"
#include "src/Game.hpp"
#include "src/HandEvaluator.hpp"
#include "src/EquityCalculator.hpp"
#include "src/GUI.hpp"

using namespace std;

bool uniTest(int argc, char* argv[]) {
    bool pass[4] = { 0 }; 

    pass[0] = Card::test_card();
    pass[1] = Deck::test_deck();
    pass[2] = Game::test_game();
    pass[3] = Player::test_player();

    bool allPassed = pass[0] && pass[1] && pass[2] && pass[3]; 

    
    if (allPassed) {
        // std::cout << "Unit tests passed" << std::endl;

        // Exiting the program if the tests passed and is running in CI
        if (argc > 1) {
            if (strcmp(argv[1], "-ci") == 0) {
                exit(0); 
            }
        }
        
        return allPassed; 
    }
    
    // Printing 
    std::cout << "Unit tests failed" << std::endl;
    std::cout << "Card test: " << pass[0] << std::endl;
    std::cout << "Deck test: " << pass[1] << std::endl;
    std::cout << "Game test: " << pass[2] << std::endl;
    std::cout << "Player test: " << pass[3] << std::endl;
    
    // Exiting the program if the tests failed
    exit(1);
}

// A main method for testing the classes
int main(int argc, char* argv[]) {

    if(!uniTest(argc, argv)){
        // Print a message to the user that the tests failed
        std::cout << "Unit tests failed" << std::endl;
        return 1;
    } 

    // Display the start screen 
    GUI::displayStartScreen();

    // TODO: Implement a way for the user to start a game or quit
    int menuChoice = GUI::displayMenu();

    if (menuChoice == 0) {
        GUI::displayEndMessage();
        return 0;
    }

    // TODO: Implement a way to get the number of players from the user


    HumanPlayer player1 = HumanPlayer("Jess", 1000);
    RandomPlayer player2 = RandomPlayer("James", 1000);
    RandomPlayer player3 = RandomPlayer("Corban", 1000);
    // Create a vector of pointers 
    std::vector<Player*> playerPointers;
    playerPointers.push_back(&player1);
    playerPointers.push_back(&player2);
    playerPointers.push_back(&player3);

    // Initiate a game with all the players 
    Game game = Game(playerPointers); // i swear you have to pass a pointer, but also its a list of two players

    // Start a game loop 
    while(true){
        // Play a hand
        game.playHand();
        // TESTING: Display stack sizes of all players
        for (Player* player : playerPointers) {
            std::cout << player->get_name() << "'s stack: " << player->get_stack() << std::endl;
        }
        // TODO: Implement a way to ask the user if they want to play another hand or quit

    }

}
