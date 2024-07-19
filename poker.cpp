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

        int get_stack() {
            return stack;
        }

        std::string get_name() {
            return name;
        }

        std::vector<Card> get_hand() {
            return hand;
        }
};

class Game{
    private:
        Deck deck;
        std::vector<Player> players;
        std::vector<Card> community_cards;
        int pot = 0;

    public:
        Game(std::vector<Player> players) {
            this->players = players;
            this->deck = Deck();
            this->deck.shuffle();
        }

        void deal_hands() {
            for (Player player : players) {
                player.get_hand().push_back(deck.deal());
                player.get_hand().push_back(deck.deal());
            }
        }

        void deal_flop() {
            deck.deal();    // Burn card
            for (int i = 0; i < 3; i++) {
                community_cards.push_back(deck.deal()); // Deal 3 cards for the flop 
            }
        }

        void deal_turn() {
            deck.deal();    // Burn card
            community_cards.push_back(deck.deal()); // Deal 1 card for the turn
        }

        void deal_river() {
            deck.deal();    // Burn card
            community_cards.push_back(deck.deal()); // Deal 1 card for the river
        }

        void show_community_cards() {
            for (Card card : community_cards) {
                std::cout << card.get_rank() << " of " << card.get_suit() << std::endl;
            }
        }

        void show_player_hands() {
            for (Player player : players) {
                std::cout << player.get_name() << "'s hand: " << std::endl;
                for (Card card : player.get_hand()) {
                    std::cout << card.get_rank() << " of " << card.get_suit() << std::endl;
                }
            }
        }
};
