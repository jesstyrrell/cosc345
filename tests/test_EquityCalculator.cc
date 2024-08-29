#include <gtest/gtest.h>

#include "../src/EquityCalculator.hpp"
#include "../src/Card.hpp"
#include "../src/Deck.hpp"

class EquityCalculatorTest : public ::testing::Test
{
protected:
    EquityCalculator calculator;
    Deck deck;
    std::vector<Card> hand;
    std::vector<Card> communityCards;

    void SetUp() override
    {
        // Initialize deck, hand, and community cards
        deck = Deck();
        
        hand.push_back(Card("H", "A"));
        hand.push_back(Card("H", "K"));

        communityCards.push_back(Card("H", "Q"));
        communityCards.push_back(Card("H", "J"));
        communityCards.push_back(Card("H", "10"));
    }
};

TEST_F(EquityCalculatorTest, EvaluateHand)
{
    int numPlayers = 2;
    std::vector<float> result = calculator.evaluateHand(hand, communityCards, deck, numPlayers);

    // Check if the result is within expected range
    EXPECT_GE(result[0], 0.0f);
    EXPECT_LE(result[0], 1.0f);
    EXPECT_GE(result[1], 0.0f);
    EXPECT_LE(result[1], 1.0f);
    EXPECT_GE(result[2], 0.0f);
    EXPECT_LE(result[2], 1.0f);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}