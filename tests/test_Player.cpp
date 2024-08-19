#include "../src/Player.hpp" 
#include <cassert>
#include <iostream>

class TestPlayer {
    private:
        Player *player;
        Card *AceOfHearts;
        Card *AceOfSpades;

    public:
        void setUp() {
            player = new Player("Jess", 1000);
            
            AceOfHearts = new Card("Hearts", "Ace");
            AceOfSpades = new Card("Spades", "Ace");
        }

        void tareDown() {
            delete player;
            delete AceOfHearts;
            delete AceOfSpades;
        }

        void test_add_card_to_hand() {
            setUp(); 
            player->add_card_to_hand(*AceOfHearts);
            player->add_card_to_hand(*AceOfSpades);

            assert(player->get_hand().size() == 2 && "Hand size is not 2");
            tareDown();
        }

        void test_clear_hand() {
            setUp(); 
            player->clear_hand();

            assert(player->get_hand().size() == 0 && "Hand size is not 0");
            tareDown();
        }

        void test_get_stack() {
            setUp(); 
            assert(player->get_stack() == 1000 && "Stack is not 1000");
            tareDown();
        }

        void test_get_hand() {
            setUp(); 
            player->add_card_to_hand(*AceOfHearts);
            player->add_card_to_hand(*AceOfSpades);

            assert(player->get_hand()[0].get_suit() == "Hearts" && player->get_hand()[0].get_rank() == "Ace" && "Card is not correct");
            assert(player->get_hand()[1].get_suit() == "Spades" && player->get_hand()[1].get_rank() == "Ace" && "Card is not correct");
            tareDown();
        }

        void test_get_name() {
            setUp();
            assert(player->get_name() == "Jess" && "Name is not Jess");
            tareDown();
        }

        void test_show_hand() {
            setUp();
            player->add_card_to_hand(*AceOfHearts);
            player->add_card_to_hand(*AceOfSpades);

            player->show_hand();
            tareDown();
        }

        void test_player() {
            test_add_card_to_hand();
            test_clear_hand();
            test_get_stack();
            test_get_hand();
            test_get_name();
            test_show_hand();
        }
};

int main() {
    TestPlayer testPlayer;
    testPlayer.test_player();
    return 0;
}

