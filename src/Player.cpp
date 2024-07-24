#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <ctime>

#include "Card.hpp"

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
            this->stack -= amount;
        }

        void win(int amount) {
            this->stack += amount;
        }

        int get_stack() {
            return this->stack;
        }

        std::string get_name() {
            return this->name;
        }

        std::vector<Card> get_hand() {
            return this->hand;
        }

        void add_card_to_hand(Card card) {
            this->hand.push_back(card);
        }

        void clear_hand() {
            this->hand.clear();
        }

        void show_hand() {
            for (Card card : hand) {
                std::cout << card.get_rank() << " of " << card.get_suit() << std::endl;
            }
        }
};