#include "Player.hpp"
#include "GUI.hpp"
#include <random>
#include <chrono>
#include <algorithm>

class RandomPlayer : public Player {
private:
    std::default_random_engine rng;

public:
    RandomPlayer(const std::string& name, int stack) : Player(name, stack) {
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        rng.seed(seed);
    }

    std::string getMove(bool canCheck, bool canRaise, bool canFold, bool canCall) override {
        vector<std::string> moves = {"a", "r", "f", "c"};
        // randomly select one of the bools that is true 
        std::vector<bool> possibleMoves = {canCheck, canRaise, canFold, canCall};
        std::uniform_int_distribution<int> dist(0, 3);
        int moveIndex = dist(rng);
        while (!possibleMoves[moveIndex]) {
            moveIndex = dist(rng);
        }
        // TESTING: print the move 
        std::cout << moves[moveIndex] << std::endl;
        return moves[moveIndex];
    }

    int getBetSizing(int minBet, int maxBet) override {
        // randomly flip a coin until it is false and count the number of flips
        int count = 0;

        while(true){
            srand (time(NULL));
            int flip = (rand()%2)+ 1 ;
            if (flip == 1){
               break;
            }
            count++;
        }
        
        // TESTING: print the bet sizing
        std::cout << min(minBet*(count+1), maxBet) << std::endl;
        return min(minBet*count, maxBet);
    }
    
};
