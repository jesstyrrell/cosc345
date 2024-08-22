#include "../src/Card.hpp"
#include <cassert>
#include <iostream>

void test_card()
{
    Card card("Hearts", "Ace");

    assert(card.get_suit() == "Hearts" && "Incorrect suit");
    assert(card.get_rank() == "Ace" && "Incorrect rank");

    std::cout << "Card test passed!" << std::endl;
}

int main()
{
    test_card();
    return 0;
}