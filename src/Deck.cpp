#include <algorithm> // For std::shuffle
#include <random>    // For std::default_random_engine
#include <ctime>     // For time()

#include "Deck.hpp"

using namespace std;

Deck::Deck() {
    string suits[] = {"Hearts", "Diamonds", "Clubs", "Spades"};
    string ranks[] = {"2", "3", "4", "5", "6", "7", "8", "9", "10",
                      "Jack", "Queen", "King", "Ace"};

    for (const string& suit : suits) {
        for (const string& rank : ranks) {
            cards.push_back(Card(suit, rank));
        }
    }
}

void Deck::shuffle() {
    std::shuffle(cards.begin(), cards.end(), default_random_engine(time(0)));
}

Card Deck::deal() {
    Card card = cards.back();
    cards.pop_back();
    return card;
}
