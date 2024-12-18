#pragma once

#include "Player.hpp"
#include "GUI.hpp"
#include <random>
#include <chrono>
#include <algorithm>

class BetterPlayer : public Player {
private:
    std::default_random_engine rng;

public:
    BetterPlayer(const std::string& name, int stack) : Player(name, stack) {
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        rng.seed(seed);
    }

    std::string getMove(bool canCheck, bool canRaise, bool canFold, bool canCall, vector<Card> community_cards, int largestBet, int numPlayersInHand, int pot) override {
        // Get the bros equity from the equity calculator
        vector<float> equity = get_equity(community_cards, numPlayersInHand);
        double equityThreshold = 1.0/numPlayersInHand;
        equityThreshold *= 1.1;

        // If the equity is below the threshold, fold
        if (equity[0] < equityThreshold) {
            if(canFold){
                return "f";
            } else {
                return "a";
            }
        }

        if(canCall){
            // Radomly generate a double to decide whether to raise or call
            std::uniform_real_distribution<double> dist(0.0, 1.0);
            double randNum = dist(rng);

            if(equity[0] >= equityThreshold*1.5 && randNum > 0.4 && largestBet < 10000){
                return "r";
            } else {
                return "c";
            }
        }
        if(largestBet < 10000){
            return "r";
        }
        return "a";

    }

    int getBetSizing(int minBet, int maxBet) override {
        // randomly flip a coin until it is false and count the number of flips
        int count = 0;

        while(true){
            int flip = (rand()%5)+ 1 ;
            if (flip == 1){
               break;
            }
            count++;
        }
        // TESTING: print the bet sizing
        // std::cout << min(minBet*(count+1), maxBet) << std::endl;
        return min(minBet*(count+1), 10000);
    }

    int endOfHand() {
        return 1;
    }
    
};
