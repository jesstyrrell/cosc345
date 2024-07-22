// Author: Jess

#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <ctime>

// Card class
// Represents a single card in a deck of cards
// Contains a suit and a rank
// Example: Card card = Card("Hearts", "Ace");

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

class Game{
    private:
        Deck deck;
        std::vector<Player*> players;
        std::vector<Card> community_cards;
        int pot = 0;

    public:
        Game(std::vector<Player*>& players) {
            this->players = players;
            this->deck = Deck();
            this->deck.shuffle();
        }

        void deal_hands() {
            for (Player* player : players) {
                player->add_card_to_hand(deck.deal()); // Deal the first card to the player
                player->add_card_to_hand(deck.deal()); // Deal the second card to the player
                
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
            for (Player* player : players) {
                std::cout << player->get_name() << "'s hand: " << std::endl;
                for (Card card : player->get_hand()) {
                    std::cout << card.get_rank() << " of " << card.get_suit() << std::endl;
                }
                std::cout << "--------------" << std::endl;
            }
        }

        std::vector<Player*> get_players() {
            return players;
        }
};

// A main method for testing the classes
int main() {
    Player player1 = Player("Jess", 1000);
    Player player2 = Player("James", 1000);
    Player player3 = Player("Corban", 1000);
    // Create a vector of pointers 
    std::vector<Player*> playerPointers;

    playerPointers.push_back(&player1);
    playerPointers.push_back(&player2);
    playerPointers.push_back(&player3);

    Game game = Game(playerPointers); // i swear you have to pass a pointer, but also its a list of two players
    game.deal_hands();
    game.show_player_hands();
    game.deal_flop();
    game.deal_turn();
    game.deal_river();
    game.show_community_cards();
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


    return 0;
}
