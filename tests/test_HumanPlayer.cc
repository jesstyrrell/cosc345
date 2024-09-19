
#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "MockGUI.hpp"
#include "../src/HumanPlayer.hpp"
#include "../src/Player.hpp"

class HumanPlayerTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Replace the real GUI with our mock
        GUI::getUserMove = MockGUI::getUserMove;
        GUI::getBetSizing = MockGUI::getBetSizing;
        GUI::endOfRoundMenu = MockGUI::endOfRoundMenu;
    }

    void TearDown() override {
        // Reset the GUI functions to their original implementations if needed
    }
};

TEST_F(HumanPlayerTest, Constructor) {
    HumanPlayer player("TestPlayer", 1000);
    EXPECT_EQ(player.get_name(), "TestPlayer");
    EXPECT_EQ(player.get_stack(), 1000);
}

TEST_F(HumanPlayerTest, GetMove) {
    HumanPlayer player("TestPlayer", 1000);
    
    EXPECT_CALL(MockGUI::getUserMove, (true, true, true, true))
        .WillOnce(::testing::Return("raise"));

    std::string move = player.getMove(true, true, true, true);
    EXPECT_EQ(move, "raise");
}

TEST_F(HumanPlayerTest, GetBetSizing) {
    HumanPlayer player("TestPlayer", 1000);
    
    EXPECT_CALL(MockGUI::getBetSizing, (50, 200))
        .WillOnce(::testing::Return(100));

    int betSize = player.getBetSizing(50, 200);
    EXPECT_EQ(betSize, 100);
}

TEST_F(HumanPlayerTest, EndOfHand) {
    HumanPlayer player("TestPlayer", 1000);
    
    EXPECT_CALL(MockGUI::endOfRoundMenu, ())
        .WillOnce(::testing::Return(1));

    int result = player.endOfHand();
    EXPECT_EQ(result, 1);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}