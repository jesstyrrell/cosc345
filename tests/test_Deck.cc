#include <gtest/gtest.h>

#include "../src/Deck.hpp"

TEST(TestDeck, TestDeckConstructor) {
    Deck deck = Deck();
    vector<Card> cards = deck.get_cards();

    ASSERT_EQ(cards.size(), 52);

    // Check if all the cards are unique
    for (int i = 0; i < cards.size(); i++) {
        for (int j = i + 1; j < cards.size(); j++) {

            const bool checkSuit = cards[i].get_suit() == cards[j].get_suit();
            const bool checkRank = cards[i].get_rank() == cards[j].get_rank();

            ASSERT_FALSE(checkSuit && checkRank);
        }
    }
}

TEST(TestDeck, TestDeckGetCards) {
    Deck deck = Deck();
    vector<Card> cards = deck.get_cards();
    
    ASSERT_EQ(cards.size(), 52);
}

TEST(TestDeck, TestDeckReset) {
    Deck deck = Deck();
    deck.shuffle();
    deck.reset();
    vector<Card> cards = deck.get_cards();
    ASSERT_EQ(cards.size(), 52);
}

// FIXME: This is currently failing in the ci but passes in the local environment
TEST(TestDeck, TestDeckShuffle) {
    Deck deck = Deck();
    vector<Card> cards = deck.get_cards();
    deck.shuffle();
    vector<Card> shuffledCards = deck.get_cards();

    // Check if the cards are shuffled
    bool isShuffled = false;
    for (int i = 0; i < cards.size(); i++) {

        const bool checkSuit = cards[i].get_suit() == shuffledCards[i].get_suit();
        const bool checkRank = cards[i].get_rank() == shuffledCards[i].get_rank();

        if (checkSuit && checkRank) {
            isShuffled = true;
            break;
        }
    }

    ASSERT_TRUE(isShuffled);
}

TEST(TestDeck, TestDeckDeal) {
    Deck deck = Deck();
    vector<Card> cards = deck.get_cards();

    Card card = deck.deal();
    vector<Card> newCards = deck.get_cards();

    ASSERT_EQ(cards.size(), 52);
    ASSERT_EQ(newCards.size(), 51);
}

TEST(TestDeck, TestDeckFindCard) {
    Deck deck = Deck();
    Card card = deck.find_card("A", "Hearts");

    ASSERT_EQ(card.get_suit(), "Hearts");
    ASSERT_EQ(card.get_rank(), "A");
}

TEST(TestDeck, TestDeckRemoveCard) {
    Deck deck = Deck();
    Card card = deck.find_card("A", "Hearts");
    deck.remove_card(card);

    vector<Card> cards = deck.get_cards();
    bool cardExists = false;
    for (Card c : cards) {
        if (c.get_suit() == card.get_suit() && c.get_rank() == card.get_rank()) {
            cardExists = true;
            break;
        }
    }

    ASSERT_FALSE(cardExists);
}

