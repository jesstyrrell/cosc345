#include <gtest/gtest.h>

#include "../src/HandEvaluator.hpp"
#include "../src/Card.hpp"

class HandEvaluatorTest : public ::testing::Test
{
protected:
    HandEvaluator evaluator;

    void SetUp() override
    {
        // This method will be called before each test
    }

    // Helper function to create a card
    Card createCard(const std::string &suit, const std::string &rank)
    {
        return Card(suit, rank);
    }
};

TEST_F(HandEvaluatorTest, EvaluateTableWithTwoHands)
{
    std::vector<std::vector<Card>> hands = {
        {createCard("Hearts", "A"), createCard("Spades", "K")},
        {createCard("Diamonds", "Q"), createCard("Clubs", "J")}
    };
    
    std::vector<Card> communityCards = {
        createCard("Hearts", "10"),
        createCard("Spades", "9"),
        createCard("Diamonds", "8"),
        createCard("Clubs", "7"),
        createCard("Hearts", "6")
    };

    std::vector<bool> results = evaluator.evaluateTable(hands, communityCards);

    ASSERT_EQ(results.size(), 2);

    EXPECT_FALSE(results[0]);   // Expect QJ to win as they have a straight
    EXPECT_TRUE(results[1]);    // Expect AK to lose as they only have a high card
    
}

TEST_F(HandEvaluatorTest, EvaluateTableWithThreeHands)
{
    std::vector<std::vector<Card>> hands = {
        {createCard("Hearts", "A"), createCard("Spades", "K")},
        {createCard("Diamonds", "A"), createCard("Clubs", "A")},
        {createCard("Hearts", "Q"), createCard("Spades", "Q")}};
    std::vector<Card> communityCards = {
        createCard("Hearts", "10"),
        createCard("Spades", "9"),
        createCard("Diamonds", "8"),
        createCard("Clubs", "7"),
        createCard("Hearts", "6")};

    std::vector<bool> results = evaluator.evaluateTable(hands, communityCards);

    ASSERT_EQ(results.size(), 3);
    EXPECT_FALSE(results[0]); // Expect AK to lose
    EXPECT_TRUE(results[1]);  // Expect AA to win
    EXPECT_FALSE(results[2]); // Expect QQ to lose
}

TEST_F(HandEvaluatorTest, EvaluateTableWithTie)
{
    std::vector<std::vector<Card>> hands = {
        {createCard("Hearts", "A"), createCard("Spades", "K")},
        {createCard("Diamonds", "A"), createCard("Clubs", "K")}};
    std::vector<Card> communityCards = {
        createCard("Hearts", "Q"),
        createCard("Spades", "J"),
        createCard("Diamonds", "10"),
        createCard("Clubs", "9"),
        createCard("Hearts", "8")};

    std::vector<bool> results = evaluator.evaluateTable(hands, communityCards);

    ASSERT_EQ(results.size(), 2);
    EXPECT_TRUE(results[0]); // Expect both hands to be marked as winners in a tie
    EXPECT_TRUE(results[1]);
}

TEST_F(HandEvaluatorTest, EvaluateTableWithEmptyHands)
{
    std::vector<std::vector<Card>> hands = {};
    std::vector<Card> communityCards = {
        createCard("Hearts", "A"),
        createCard("Spades", "K"),
        createCard("Diamonds", "Q"),
        createCard("Clubs", "J"),
        createCard("Hearts", "10")};

    std::vector<bool> results = evaluator.evaluateTable(hands, communityCards);

    EXPECT_TRUE(results.empty());
}

TEST_F(HandEvaluatorTest, EvaluateTableWithEmptyCommunityCards)
{
    std::vector<std::vector<Card>> hands = {
        {createCard("Hearts", "A"), createCard("Spades", "K")},
        {createCard("Diamonds", "Q"), createCard("Clubs", "J")}};
    std::vector<Card> communityCards = {};

    std::vector<bool> results = evaluator.evaluateTable(hands, communityCards);

    ASSERT_EQ(results.size(), 2);
    EXPECT_TRUE(results[0]);  // Expect AK to win
    EXPECT_FALSE(results[1]); // Expect QJ to lose
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}