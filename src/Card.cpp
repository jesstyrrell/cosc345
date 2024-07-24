#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <ctime>

// Card class
// Represents a single card in a deck of cards
// Contains a suit and a rank
// Example: Card card = Card("Hearts", "Ace");

/**
 * Card class
 * Represents a single card in a deck of cards. Each card has a suit and a rank.
 * 
 * `Card card = Card("Hearts", "Ace");`
 */
class Card {
    
    private:
        std::string suit;
        std::string rank;

    public:
        Card(std::string suit, std::string rank) {
            this->suit = suit;
            this->rank = rank;
        }

        std::string get_suit() {
            return suit;
        }

        std::string get_rank() {
            return rank;
        }
};