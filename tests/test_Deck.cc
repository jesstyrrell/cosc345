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

TEST(TestDeck, TestDeckShuffle) {
    Deck deck = Deck();
    vector<Card> cards = deck.get_cards();
    deck.shuffle();
    vector<Card> shuffledCards = deck.get_cards();

    // Check if the cards are shuffled
    bool isShuffled = false;
    for (int i = 0; i < cards.size(); i++) {

        bool checkSuit = cards[i].get_suit() == shuffledCards[i].get_suit();
        bool checkRank = cards[i].get_rank() == shuffledCards[i].get_rank();

        // If any of the cards are are different, then the deck is shuffled
        if (!checkSuit || !checkRank) {
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

TEST(TestDeck, TestDeckFindCardNotExist) {
    Deck deck = Deck();
    Card card = deck.find_card("", "");

    ASSERT_EQ(card.get_suit(), "");
    ASSERT_EQ(card.get_rank(), "");
}

TEST(TestDeck, TestDeckRemoveCard) {
    Deck deck = Deck();
    Card card = deck.find_card("A", "Hearts");
    deck.remove_card(card);

    vector<Card> cards = deck.get_cards();
    bool cardExists = false;
    for (Card c : cards) {
        bool checkSuit = c.get_suit() == card.get_suit();
        bool checkRank = c.get_rank() == card.get_rank();

        if (checkSuit && checkRank) {
            cardExists = true;
            break;
        }
    }

    ASSERT_FALSE(cardExists);
}

