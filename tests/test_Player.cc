#include <gtest/gtest.h>
#include <sstream>

#include "../src/Player.hpp"
#include "../src/Card.hpp"
#include "../src/Deck.hpp"
#include "../src/EquityCalculator.hpp"

class PlayerTest : public ::testing::Test {
protected:
    Player* player;

    void SetUp() override {
        player = new Player("TestPlayer", 1000);
    }

    void TearDown() override {
        delete player;
    }

    // Helper function to capture cout output
    std::string captureOutput(std::function<void()> func) {
        std::stringstream buffer;
        std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());
        func();
        std::cout.rdbuf(old);
        return buffer.str();
    }
};

TEST_F(PlayerTest, Constructor) {
    EXPECT_EQ(player->get_name(), "TestPlayer");
    EXPECT_EQ(player->get_stack(), 1000);
}

TEST_F(PlayerTest, Bet) {
    player->bet(500);
    EXPECT_EQ(player->get_stack(), 500);
    EXPECT_EQ(player->get_current_bet(), 500);

    // Test betting more than available
    std::string output = captureOutput([this]() { player->bet(1000); });
    EXPECT_TRUE(output.find("You don't have enough chips to bet that amount") != std::string::npos);
    EXPECT_EQ(player->get_stack(), 0);
    EXPECT_EQ(player->get_current_bet(), 1000);
}

TEST_F(PlayerTest, DeductBlind) {
    int deducted = player->deduct_blind(50);
    EXPECT_EQ(deducted, 50);
    EXPECT_EQ(player->get_stack(), 950);
    EXPECT_EQ(player->get_current_bet(), 50);
}

TEST_F(PlayerTest, Win) {
    player->win(500);
    EXPECT_EQ(player->get_stack(), 1500);
}

TEST_F(PlayerTest, GetStack) {
    EXPECT_EQ(player->get_stack(), 1000);
}

TEST_F(PlayerTest, GetName) {
    EXPECT_EQ(player->get_name(), "TestPlayer");
}

TEST_F(PlayerTest, GetHand) {
    EXPECT_TRUE(player->get_hand().empty());
    player->add_card_to_hand(Card("Hearts", "A"));
    EXPECT_EQ(player->get_hand().size(), 1);
}

TEST_F(PlayerTest, AddCardToHand) {
    player->add_card_to_hand(Card("Hearts", "A"));
    player->add_card_to_hand(Card("Spades", "K"));
    EXPECT_EQ(player->get_hand().size(), 2);
}

TEST_F(PlayerTest, ClearHand) {
    player->add_card_to_hand(Card("Hearts", "A"));
    player->clear_hand();
    EXPECT_TRUE(player->get_hand().empty());
}

TEST_F(PlayerTest, GetCurrentBet) {
    player->bet(200);
    EXPECT_EQ(player->get_current_bet(), 200);
}

TEST_F(PlayerTest, ShowHand) {
    player->add_card_to_hand(Card("Hearts", "A"));
    player->add_card_to_hand(Card("Spades", "K"));
    std::string output = captureOutput([this]() { player->show_hand(); });
    EXPECT_TRUE(output.find("A of Hearts") != std::string::npos);
    EXPECT_TRUE(output.find("K of Spades") != std::string::npos);
}

TEST_F(PlayerTest, ResetCurrentBet) {
    player->bet(200);
    player->reset_current_bet();
    EXPECT_EQ(player->get_current_bet(), 0);
}

TEST_F(PlayerTest, GetEquity) {
    player->add_card_to_hand(Card("Hearts", "A"));
    player->add_card_to_hand(Card("Spades", "K"));
    std::vector<Card> communityCards = {Card("Diamonds", "Q"), Card("Clubs", "J"), Card("Hearts", "10")};
    std::vector<float> equity = player->get_equity(communityCards, 2);
    EXPECT_EQ(equity.size(), 2);
    EXPECT_GE(equity[0], 0.0f);
    EXPECT_LE(equity[0], 1.0f);
}

TEST_F(PlayerTest, GetEquityEmptyHand) {
    std::vector<Card> communityCards = {Card("Diamonds", "Q"), Card("Clubs", "J"), Card("Hearts", "10")};
    std::vector<float> equity = player->get_equity(communityCards, 2);
    EXPECT_EQ(equity, std::vector<float>{-1, -1});
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}