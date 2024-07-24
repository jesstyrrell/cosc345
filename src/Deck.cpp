#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <ctime>

#include "Card.hpp"

class Deck {
    private:
        std::vector<Card> cards;

    public:
        Deck() {
            std::string suits[] = {"Hearts", "Diamonds", "Clubs", "Spades"};
            std::string ranks[] = {"2", "3", "4", "5", "6", "7", "8", "9", "10",
                                "Jack", "Queen", "King", "Ace"};

            for (std::string suit : suits) {
                for (std::string rank : ranks) {
                    cards.push_back(Card(suit, rank));
                }
            }
        }

        void shuffle() {
            std::shuffle(cards.begin(), cards.end(), std::default_random_engine(time(0)));
        }

        Card deal() {
            Card card = cards.back();
            cards.pop_back();
            return card;
        }

};