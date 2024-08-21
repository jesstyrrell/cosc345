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

    uniTest(argc, argv); 


    HumanPlayer player1 = HumanPlayer("Jess", 1000);
    HumanPlayer player2 = HumanPlayer("James", 1000);
    RandomPlayer player3 = RandomPlayer("Corban", 1000);
    // Create a vector of pointers 
    std::vector<Player*> playerPointers;

    playerPointers.push_back(&player1);
    playerPointers.push_back(&player2);
    playerPointers.push_back(&player3);

    // Initiate a game with all the players 
    Game game = Game(playerPointers); // i swear you have to pass a pointer, but also its a list of two players

    // Play a hand
    game.playHand();

    // TESTING: Display stack sizes of all players
    for (Player* player : playerPointers) {
        std::cout << player->get_name() << "'s stack: " << player->get_stack() << std::endl;
    }

    // Play a hand
    game.playHand();

    // TESTING: Display stack sizes of all players
    for (Player* player : playerPointers) {
        std::cout << player->get_name() << "'s stack: " << player->get_stack() << std::endl;
    }
    

    // // Create an instance of HandEvaluator
    // HandEvaluator evaluator;

    // Deck deck;
    // deck.shuffle();
    // deck.shuffle();
    // deck.shuffle();
    // deck.shuffle();

    // std::vector<Card> hand;
    // hand.push_back(deck.deal());
    // hand.push_back(deck.deal());
    
    // std::vector<Card> communityCards;
    // communityCards.push_back(deck.deal());
    // communityCards.push_back(deck.deal());
    // communityCards.push_back(deck.deal());
    // communityCards.push_back(deck.deal());
    // communityCards.push_back(deck.deal());

    // int numPlayers = 1;

    // float probability = evaluator.evaluateHand(hand, communityCards, deck, numPlayers);

    // // Output the result
    // std::cout << "Winning Probability: " << probability * 100 << "%" << std::endl;

    // return 0;
}
