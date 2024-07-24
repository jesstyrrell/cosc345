#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <ctime>

#include "Player.hpp"
#include "Deck.hpp"


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