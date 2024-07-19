// Author: Jess

#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <ctime>


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

class Player {
    private:
        std::string name;
        std::vector<Card> hand;
        int stack;

    public:

        Player(std::string name, int stack) {
            this->name = name;
            this->stack = stack;
        }
        
        void bet(int amount) {
            stack -= amount;
        }

        void win(int amount) {
            stack += amount;
        }
};