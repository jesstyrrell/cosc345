#include "Player.hpp"

using namespace std;

Player::Player(string name, int stack) {
    this->name = name;
    this->stack = stack;
}

void Player::bet(int amount) {
    this->stack -= amount;
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

void Player::show_hand() {
    for (Card card : hand) {
        cout << card.get_rank() << " of " << card.get_suit() << endl;
    }
}
