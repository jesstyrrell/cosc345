#pragma once

#include "Player.hpp"
#include "GUI.hpp"
#include <random>
#include <chrono>
#include <algorithm>

class BetterPlayer : public Player
{
private:
    std::default_random_engine rng;
    int pot;

public:
    BetterPlayer(const std::string &name, int stack) : Player(name, stack)
    {
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        rng.seed(seed);
    }

    std::string getMove(bool canCheck, bool canRaise, bool canFold, bool canCall, vector<Card> community_cards, int largestBet, int numPlayersInHand, int pot) override
    {
        this->pot = pot;
        // Get the bros equity from the equity calculator
        vector<float> equity = get_equity(community_cards, numPlayersInHand);
        double equityThreshold = 1.0 / numPlayersInHand * 1.15;

        // If the equity is below the threshold, fold
        if (equity[0] < equityThreshold)
        {
            if (canFold)
            {
                return "f";
            }
            else
            {
                return "a";
            }
        }

        if (canCall)
        {
            if (equity[0] >= equityThreshold * 1.25)
            {
                return "r";
            }
            else
            {
                return "c";
            }
        }
        return "r";
    }


    int getBetSizing(int minBet, int maxBet) override {
        // Randomly choose a bet size that is either 1/4, 1/3, 1/2 or full pot
        std::uniform_int_distribution<int> betSize(1, 4);
        int bet = 0;
        switch(betSize(rng)){
            case 1:
                bet = pot/4;
                break;
            case 2:
                bet = pot/3;
                break;
            case 3:
                bet = pot/2;
                break;
            case 4:
                bet = pot;
                break;
        }

        return max(min(bet, maxBet), minBet);

    }

    int endOfHand()
    {
        return 1;
    }
};
