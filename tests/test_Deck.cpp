#include "../src/Deck.hpp"
#include <cassert>
#include <iostream>

void test_deck()
{
    Deck deck = Deck();
    deck.shuffle();

    vector<Card> allCardsInDeck;

    // Check that all the cards in the deck are unique and not empty
    for (Card card : deck.get_cards()) {

        // Check if the cards are empty
        assert(card.get_suit() != "" && "Card is empty");
        assert(card.get_rank() != "" && "Card is empty");

        // Check if current card is in the vector of all cards
        for (Card c : allCardsInDeck) {
            bool checkSuitIsEqual = c.get_suit() == card.get_suit();
            bool checkRankIsEqual = c.get_rank() == card.get_rank();

            assert(!(checkSuitIsEqual && checkRankIsEqual) && "Card is not unique");
        }

        // Add the card to the vector of all cards
        allCardsInDeck.push_back(card);
    }

    std::cout << "Deck test passed!" << std::endl;
}

int main()
{
    test_deck();
    return 0;
}