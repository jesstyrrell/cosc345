#pragma once

#include <iostream>
#include <vector>
#include <string>

#include "Game.hpp"
#include "Card.hpp"

using namespace std;

class Game;

/**
 * @class Player
 * @brief Represents a human player in the poker game.
 */
class RandomPlayer {

public:
    std::default_random_engine rng;
    /**
     * @brief Gets the human player's move during their turn by calling the getPlayerMove method in GUI class.
     * @param canCheck Whether the player can check.
     * @param canRaise Whether the player can raise.
     * @param canFold Whether the player can fold.
     * @param canCall Whether the player can call.
     * @return The player's chosen move as a string.
     */
    std::string getMove(bool canCheck, bool canRaise, bool canFold, bool canCall, vector<Card> community_cards, int largestBet, int numPlayersInHand);

    /**
     * @brief Gets the human player's bet sizing during their turn.
     * @param minBet The minimum bet allowed.
     * @param maxBet The maximum bet allowed.
     * @return The player's chosen bet size.
     */
    int getBetSizing(int minBet, int maxBet);

    /**
     * @brief Handles actions at the end of a hand for a human player.
     * @return The outcome of the end-of-hand process.
     */
    int endOfHand();

};
