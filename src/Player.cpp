#include "Player.hpp"
#include "EquityCalculator.hpp"

using namespace std;

Player::Player(const std::string& name, int stack) {
    this->name = name;
    this->stack = stack;
}

void Player::bet(int amount) {
    if(amount > this->stack + this->current_bet) {
        cout << "You don't have enough chips to bet that amount. Betting all in." << endl;
        cout << amount << endl;
        while(true){}
    }
    this->stack -= amount - this->current_bet;
    this->current_bet = amount;
}

int Player::deduct_blind(int amount) {
    this->stack -= amount;
    this->current_bet = amount;
    return amount;
}

void Player::win(int amount) {
    this->stack += amount;
}

int Player::get_stack() {
    return this->stack;
}

string Player::get_name() {
    return this->name;
}

vector<Card> Player::get_hand() {
    return this->hand;
}

void Player::add_card_to_hand(Card card) {
    this->hand.push_back(card);
}

void Player::clear_hand() {
    this->hand.clear();
}

int Player::get_current_bet() {
    return this->current_bet;
}

void Player::show_hand() {
    for (Card card : hand) {
        cout << card.get_rank() << " of " << card.get_suit() << endl;
    }
}

void Player::reset_current_bet() {
    this->current_bet = 0;
}

vector<float> Player::get_equity(vector<Card> communityCards, int numPlayers) {
    if (this->hand.size() == 0) {
        return { -1, -1 };
    }
    EquityCalculator equityCalculator;
    Deck deck;
    for (Card c : communityCards) { deck.remove_card(c); };
    for (Card c : this->hand) { deck.remove_card(c); };
    return equityCalculator.calculateHandEquity(this->hand, communityCards, deck, numPlayers);
}