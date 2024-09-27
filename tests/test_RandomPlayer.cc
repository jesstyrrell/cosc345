#include <gtest/gtest.h>
#include <string>
#include <vector>

#include "../src/RandomPlayer.cpp" 

class RandomPlayerTest : public ::testing::Test
{
protected:
    RandomPlayer *player;

    void SetUp() override
    {
        player = new RandomPlayer("TestPlayer", 1000);
    }

    void TearDown() override
    {
        delete player;
    }
};

// TEST_F(RandomPlayerTest, GetMove)
// {
//     std::vector<std::string> validMoves = {"a", "r", "f", "c"};

//     // Test all possible combinations of boolean inputs
//     std::string move = player->getMove(true, false, false, false, {}, 0, 0);
//     EXPECT_EQ(move, "a");

//     move = player->getMove(false, true, false, false);
//     EXPECT_EQ(move, "r");

//     move = player->getMove(false, false, true, false);
//     EXPECT_EQ(move, "f");

//     move = player->getMove(false, false, false, true);
//     EXPECT_EQ(move, "c");

//     // Test a case where multiple moves are possible
//     move = player->getMove(true, true, true, true);
//     EXPECT_NE(std::find(validMoves.begin(), validMoves.end(), move), validMoves.end());
// }

TEST_F(RandomPlayerTest, GetBetSizing)
{
    int minBet = 10;
    int maxBet = 100;

    // Test that the bet sizing is within the expected range
    int bet = player->getBetSizing(minBet, maxBet);
    EXPECT_GE(bet, minBet);
    EXPECT_LE(bet, maxBet);
}

TEST_F(RandomPlayerTest, EndOfHand)
{
    // Test the endOfHand method
    int result = player->endOfHand();
    EXPECT_EQ(result, 1);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}