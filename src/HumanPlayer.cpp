#include "Player.hpp"
#include "GUI.hpp"

class HumanPlayer : public Player {
public:
    HumanPlayer(const std::string& name, int stack) : Player(name, stack) {}

    std::string getMove(bool canCheck, bool canRaise, bool canFold, bool canCall, vector<Card> community_cards, int largestBet, int numPlayersInHand, int pot) override {
        // Call GUI to get user move
        return GUI::getUserMove(canCheck, canRaise, canFold, canCall);
    }

    int getBetSizing(int minBet, int maxBet) override {
        // Call GUI to get bet sizing
        return GUI::getBetSizing(minBet, maxBet);
    }

    int endOfHand() {
        return GUI::endOfRoundMenu();
    }

};
