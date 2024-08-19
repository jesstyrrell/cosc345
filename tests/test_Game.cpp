#include "../src/Game.hpp"
#include <cassert>
#include <iostream>
#include <stdexcept>
#include <cstdlib>

class TestGame {
    private: 
        Game *game;
        vector<Player*> players;

    public: 
        void setUp() {
            Player *player1 = new Player("Jess", 1000);
            Player *player2 = new Player("John", 1000);
            players.push_back(player1);
            players.push_back(player2);

            game = new Game(players);
        }

        void tareDown() {
            delete game;
            for (Player *player : players) {
                delete player;
            }
        }

        void test_add_player() {
            setUp();
            Player *player3 = new Player("James", 1000);
            game->add_player(player3);

            assert(game->get_players().size() == 3 && "Player was not added");
            tareDown();
        }

        void test_deal_hands() {
            setUp();
            game->deal_hands();

            // Asserting each player has 2 cards in hand
            for (Player *player : game->get_players()) {
                assert(player->get_hand().size() == 2 && "Player does not have 2 cards in hand");
            }

            // Asserting deck has 48 cards
            Deck deck = game->get_deck();
            assert(deck.get_cards().size() == 48 && "Deck does not have 48 cards");

            tareDown();
        }

        // void test_deal_flop() {
        //     setUp();
        //     game->deal_flop();

        //     // Asserting the flop has 3 cards
        //     vector<Card> community_cards = game->get_community_cards();
        //     assert(community_cards.size() == 3 && "Flop does not have 3 cards");


        //     Deck deck = game->get_deck();
        //     assert(deck.get_cards().size() == 49 && "Deck does not have 49 cards");
            
        //     tareDown();
        // }

        // void test_deal_turn() {
        //     setUp();
        //     game->deal_turn();

        //     // Asserting the turn has 4 cards
        //     vector<Card> community_cards = game->get_community_cards();
        //     assert(community_cards.size() == 1 && "Turn does not have 4 cards");

        //     Deck deck = game->get_deck();
        //     assert(deck.get_cards().size() == 50 && "Deck does not have 48 cards");

        //     tareDown();
        // }

        // void test_deal_river() {
        //     setUp();
        //     game->deal_river();

        //     // Asserting the river has 5 cards
        //     vector<Card> community_cards = game->get_community_cards();
        //     assert(community_cards.size() == 1 && "River does not have 5 cards");

        //     Deck deck = game->get_deck();
        //     assert(deck.get_cards().size() == 51 && "Deck does not have 51 cards");

        //     tareDown();
        // }

        // void test_get_players() {
        //     setUp();
        //     vector<Player*> players = game->get_players();
        //     assert(players.size() == 2 && "Game does not have 2 players");

        //     Player *player1 = players[0];
        //     Player *player2 = players[1];

        //     assert(player1->get_name() == "Jess" && player1->get_stack() == 1000 && "Player 1 is not correct");
        //     assert(player2->get_name() == "John" && player2->get_stack() == 1000 && "Player 2 is not correct");

        //     tareDown();
        // }

        // void test_get_community_cards() {
        //     setUp();

        //     vector<Card> community_cards = game->get_community_cards();
        //     assert(community_cards.size() == 0 && "Community cards is not empty");

        //     // Add 3 cards to the community cards
        //     game->deal_flop();

        //     community_cards = game->get_community_cards();
        //     assert(community_cards.size() == 3 && "Community cards is not empty");

        //     tareDown();
        // }

        // void test_get_deck() {
        //     setUp();
        //     Deck deck = game->get_deck();
        //     assert(deck.get_cards().size() == 52 && "Deck does not have 52 cards");

        //     tareDown();
        // }

        // void test_playHand() {
        //     setUp();
        //     game->playHand();
        //     tareDown();
        // }

        // void test_makeMoveForUser() {
        //     setUp();
        //     game->makeMoveForUser("c", players[0]);
        //     tareDown();
        // }

        // void test_getCurrentMove() {
        //     setUp();
        //     Move move = game->getCurrentMove("c");
        //     assert(move == CHECK && "Move is not check");

        //     move = game->getCurrentMove("C");
        //     assert(move == CHECK && "Move is not check");

        //     move = game->getCurrentMove("r");
        //     assert(move == RAISE && "Move is not raise");

        //     move = game->getCurrentMove("R");
        //     assert(move == RAISE && "Move is not raise");

        //     move = game->getCurrentMove("f");
        //     assert(move == FOLD && "Move is not fold");

        //     move = game->getCurrentMove("F");
        //     assert(move == FOLD && "Move is not fold");

        //     move = game->getCurrentMove("a");
        //     assert(move == CALL && "Move is not call");

        //     move = game->getCurrentMove("A");
        //     assert(move == CALL && "Move is not call");

        //     move = game->getCurrentMove("invalid");
        //     assert(move == CHECK && "Move is not check");

        //     tareDown();
        // }

        // void test_addBlindsToPot() {
        //     setUp();

        //     game->addBlindsToPot(players[0], players[1]);
        //     assert(game->get_pot() == 15 && "Pot is not 15");

        //     // Asserting that the players have the correct stack size
        //     assert(players[0]->get_stack() == 990 && "Player 1 stack is not 990");
        //     assert(players[1]->get_stack() == 995 && "Player 2 stack is not 995");

        //     tareDown();
        // }

        void test() {
            test_add_player();
            test_deal_hands();
            // test_deal_flop();
            // test_deal_turn();
            // test_deal_river();
            // test_get_players();
            // test_get_community_cards();
            // test_get_deck();
            // test_playHand();
            // test_makeMoveForUser();
            // test_getCurrentMove();
            // test_addBlindsToPot();
        }
}; 

int main() {
    TestGame test;
    test.test();
    return 0;
}