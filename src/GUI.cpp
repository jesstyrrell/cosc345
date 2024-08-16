
#include <iostream>
#include <string>
#include <vector>

#include "Card.hpp"
#include "Player.hpp"
#include "GUI.hpp"


/**
 * Clear the terminal screen
 */
void GUI::clearScreen() {
    // Clear the screen
    std::cout << "\033[2J\033[1;1H";
}

/**
 * Get user move from the terminal
 */
string GUI::getUserMove() {
    // Get user move 
    std::string move; 
    std::cout << "Enter your move: ";
    std::cin >> move; 
    return move; 
}

int GUI::getBetSizing() {
    // Get user move 
    int bet_sizing; 
    std::cout << "Enter your bet sizing: ";
    std::cin >> bet_sizing; 
    return bet_sizing; 
}

/** 
 * Display community cards to the terminal
 * 
 * @param community_cards: vector<Card> - Community cards to display
 */
void GUI::displayCommunityCards(std::vector<Card> community_cards) {
    // Display community cards
    for (Card card : community_cards) {
        std::cout << card.get_rank() << " of " << card.get_suit() << std::endl;
    }
}   

/** 
 * Display all player hands to the terminal
 * 
 * @param players: vector<Player*> - Players to display hands for
 */
void GUI::displayAllPlayerHands(std::vector<Player*> players) {
    for (Player* player : players) {
        std::cout << player->get_name() << "'s hand: " << std::endl;
        for (Card card : player->get_hand()) {
            std::cout << card.get_rank() << " of " << card.get_suit() << std::endl;
        }
        std::cout << "--------------" << std::endl;
    }
}

void GUI::displayPlayerStack(Player* player) {
    std::cout << player->get_name() << "'s stack: " << player->get_stack() << std::endl;
    std::cout << "    -----    " << std::endl;
}