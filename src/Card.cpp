#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <ctime>

#include "Card.hpp"

using namespace std;

/**
 * Constructor for the Card class.
 * Initializes a card with a given suit and rank.
 *
 * @param suit The suit of the card (e.g., "Hearts").
 * @param rank The rank of the card (e.g., "Ace").
 */
Card::Card(const std::string& suit, const std::string& rank) : suit(suit), rank(rank) {}

/**
 * Getter for the suit of the card.
 *
 * @return The suit of the card.
 */
const string Card::get_suit() {
    return suit;
}

/**
 * Getter for the rank of the card.
 *
 * @return The rank of the card.
 */
const string Card::get_rank() {
    return rank;
}

/**
 * Method returning the string representation of the card
 * 
 * @return string representation of the card object
 */
const string Card::get_card() {
    return rank + " of " + suit;
}