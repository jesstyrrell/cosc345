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

    // Play a hand
    // game.playHand();
    
    
    // Game loop 
    while (false) {

        // Deal hands for all players 
        game.deal_hands();

        // Deal flop
        game.deal_flop();

        // Betting commences for each player at the table
        for (Player* currentPlayer : game.get_players()) {

            GUI::displayPlayerStack(currentPlayer);

            string move = GUI::getUserMove();

            game.makeMoveForUser(move, currentPlayer, 0, 0);

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


    // Create an instance of HandEvaluator
    EquityCalculator equityCalculator;

    Deck deck;
    deck.shuffle();
    deck.shuffle();
    deck.shuffle();
    deck.shuffle();

    std::vector<Card> hand;
    Card c1 = deck.find_card("9", "Clubs");
    Card c2 = deck.find_card("A", "Spades");
    deck.remove_card(c1);
    deck.remove_card(c2);
    hand.push_back(c1);
    hand.push_back(c2);/*
    hand.push_back(deck.deal());
    hand.push_back(deck.deal());*/
    deck.shuffle();


    
    std::vector<Card> communityCards;
    Card c3 = deck.find_card("2", "Hearts");
    Card c4 = deck.find_card("3", "Clubs");
    Card c5 = deck.find_card("7", "Diamonds");
    Card c6 = deck.find_card("J", "Spades");
    Card c7 = deck.find_card("J", "Diamonds");
    deck.remove_card(c3);
    deck.remove_card(c4);
    deck.remove_card(c5);
    deck.remove_card(c6);
    deck.remove_card(c7);
    communityCards.push_back(c3);
    communityCards.push_back(c4);
    communityCards.push_back(c5);
    communityCards.push_back(c6);
    communityCards.push_back(c7);


    std::vector<Card> hand2;
    hand2.push_back(deck.deal());
    hand2.push_back(deck.deal());
    deck.shuffle();
    
    std::vector<Card> hand3;
    hand3.push_back(deck.deal());
    hand3.push_back(deck.deal());
    deck.shuffle();
    std::vector<std::vector<Card>> hands = { hand, hand2, hand3 };

    int numPlayers = 3;

    vector<float> probabilities = equityCalculator.evaluateHand(hand, communityCards, deck, numPlayers);
    float winProbability = probabilities[0];
    float drawProbability = probabilities[1];
    float loseProbability = probabilities[2];
    
    // Output the result
    std::cout << "Winning Probability: " << winProbability * 100 << "%" << std::endl;
    std::cout << "Drawing Probability: " << drawProbability * 100 << "%" << std::endl;
    std::cout << "Losing Probability: " << loseProbability * 100 << "%" << std::endl;

    HandEvaluator evaluator;
    std::vector<bool> results = evaluator.evaluateTable(hands, communityCards);


    return 0;
}
