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
        std::cout << "Unit tests passed" << std::endl;

        // Exiting the program if the tests passed and is running in CI
        if (argc > 1) {
            if (strcmp(argv[1], "-ci") == 0) {
                exit(1); 
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
    exit(0);
}

// A main method for testing the classes
int main(int argc, char* argv[]) {

    uniTest(argc, argv); 


    Player player1 = Player("Jess", 1000);
    Player player2 = Player("James", 1000);
    Player player3 = Player("Corban", 1000);
    // Create a vector of pointers 
    std::vector<Player*> playerPointers;

    playerPointers.push_back(&player1);
    playerPointers.push_back(&player2);
    playerPointers.push_back(&player3);

    // Initiate a game with all the players 
    Game game = Game(playerPointers); // i swear you have to pass a pointer, but also its a list of two players
    
    
    // Game loop 
    while (true) {

        // Deal hands for all players 
        game.deal_hands();

        // Deal flop
        game.deal_flop();

        // Betting commences for each player at the table
        for (Player* currentPlayer : game.get_players()) {

            GUI::displayPlayerStack(currentPlayer);

            string move = GUI::getUserMove();

            game.makeMoveForUser(move, currentPlayer);

            // GUI::clearScreen();
        }
        
    }


    game.deal_flop();
    game.deal_turn();
    game.deal_river();
    std::cout << "--------------" << std::endl;
    // Print the stack of each player 
    for (Player* player : game.get_players()) {
        std::cout << player->get_name() << "'s stack: " << player->get_stack() << std::endl;
        std::cout << "    -----    " << std::endl;
    }
    player1.bet(100);
    player2.bet(200);
    player3.bet(300);
    for (Player* player : game.get_players()) {
        std::cout << player->get_name() << "'s stack: " << player->get_stack() << std::endl;
        std::cout << "    -----    " << std::endl;
    }

    player1.win(1000);
    player2.win(2000);
    player3.win(3000);

    for (Player* player : game.get_players()) {
        std::cout << player->get_name() << "'s stack: " << player->get_stack() << std::endl;
        std::cout << "    -----    " << std::endl;
    }


    return 0;
}
