#include <algorithm> // For std::shuffle
#include <random>    // For std::default_random_engine
#include <ctime>     // For time()
#include <iostream>

#include "Deck.hpp"

using namespace std;

Deck::Deck() {
    string suits[] = {"Hearts", "Diamonds", "Clubs", "Spades"};
    string ranks[] = {"2", "3", "4", "5", "6", "7", "8", "9", "10",
                      "J", "Q", "K", "A"};

    for (const string& suit : suits) {
        for (const string& rank : ranks) {
            cards.push_back(Card(suit, rank));
        }
    }
}

vector<Card> Deck::get_cards() {
    return cards;
}

void Deck::shuffle() {
    std::shuffle(cards.begin(), cards.end(), default_random_engine(time(0)));
}

Card Deck::deal() {
    Card card = cards.back();
    cards.pop_back();
    return card;
}

bool Deck::test_deck() {
    vector<Card> allCardsInDeck;

    Deck deck = Deck();
    deck.shuffle();

    // Check that all the cards in the deck are unique and not empty
    for (Card card : deck.get_cards()) {

        // Check if the cards are empty
        if (card.get_suit() == "" || card.get_rank() == "") {
            std::cout << "Card is empty" << std::endl;
            return false;
        }

        // Check if current card is in the vector of all cards
        for (Card c : allCardsInDeck) {
            if (c.get_suit() == card.get_suit() && c.get_rank() == card.get_rank()) {
                std::cout << "Card is not unique" << std::endl;
                return false;
            }
        }

        // Add the card to the vector of all cards
        allCardsInDeck.push_back(card);
    }

    // Free memory
    allCardsInDeck.clear();

    return true;
}
