#include "Player.hpp"

using namespace std;

Player::Player(string name, int stack) {
    this->name = name;
    this->stack = stack;
}

void Player::bet(int amount) {
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

bool Player::test_player() {
    Player player = Player("Jess", 1000);
    Card AceOfHearts = Card("Hearts", "A");
    Card AceOfSpades = Card("Spades", "A");

    player.add_card_to_hand(AceOfHearts);
    player.add_card_to_hand(AceOfSpades);


    if (player.get_hand().size() != 2) {
        cout << "Hand size is not 1" << endl;
        return false;
    }

    if (player.get_hand()[0].get_suit() != "Hearts" || player.get_hand()[0].get_rank() != "A") {
        cout << "Card is not correct" << endl;
        return false;
    }
    if (player.get_hand()[1].get_suit() != "Spades" || player.get_hand()[1].get_rank() != "A") {
        cout << "Card is not correct" << endl;
        return false;
    }

    player.clear_hand();

    if (player.get_hand().size() != 0) {
        cout << "Hand size is not 0" << endl;
        return false;
    }

    if (player.get_stack() != 1000) {
        cout << "Stack is not 1000" << endl;
        return false;
    }

    if (player.get_name() != "Jess") {
        cout << "Name is not Jess" << endl;
        return false;
    }

    player.bet(100);

    if (player.get_stack() != 900) {
        cout << "Stack is not 900" << endl;
        return false;
    }

    player.win(100);

    if (player.get_stack() != 1000) {
        cout << "Stack is not 1000" << endl;
        return false;
    }

    return true;
}