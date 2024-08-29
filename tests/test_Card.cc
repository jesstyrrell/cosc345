#include <gtest/gtest.h>

#include "../src/Card.hpp"

TEST(TestCard, TestCardConstructor) {
    Card card = Card("Hearts", "Ace");
    
    ASSERT_EQ(card.get_suit(), "Hearts");
    ASSERT_EQ(card.get_rank(), "Ace");
}

TEST(TestCard, TestCardGetSuit) {
    Card card = Card("Hearts", "Ace");
    ASSERT_EQ(card.get_suit(), "Hearts");
}

TEST(TestCard, TestCardGetRank) {
    Card card = Card("Hearts", "Ace");
    ASSERT_EQ(card.get_rank(), "Ace");
}

TEST(TestCard, TestCardGetCard) {
    Card card = Card("Hearts", "Ace");
    ASSERT_EQ(card.get_card(), "Ace of Hearts");
}