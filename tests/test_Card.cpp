#include "../src/Card.hpp"
#include <cassert>
#include <iostream>


void test_get_suit() {
    Card card("Hearts", "Ace");
    assert(card.get_suit() == "Hearts");
}

void test_get_rank() {
    Card card("Hearts", "Ace");
    assert(card.get_rank() == "Ace");
}

void test_get_card() {
    Card card("Hearts", "Ace");
    assert(card.get_card() == "Ace of Hearts");
} 

int main() {
    test_get_suit();
    test_get_rank();
    test_get_card();
    return 0;
}