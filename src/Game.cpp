#include "Game.hpp"
#include <algorithm>
#include <iostream>
#include <ctime>
#include "HandEvaluator.hpp"

using namespace std;

/**
 * Constructor for the Game class
 * @param players: vector<Player*>& - A vector of pointers to the players in the game
 */
Game::Game(std::vector<Player*>& players) {
    this->players = players;
    this->deck = Deck();
    this->deck.shuffle();
}

void Game::add_player(Player* player) {
    players.push_back(player);
}

void Game::setPot(int pot) {
    this->pot = pot;
}

void Game::deal_hands() {
    for (Player* player : players) {
        player->add_card_to_hand(deck.deal()); // Deal the first card to the player
        player->add_card_to_hand(deck.deal()); // Deal the second card to the player
    }
}

void Game::deal_flop() {
    deck.deal();    // Burn card
    for (int i = 0; i < 3; i++) {
        community_cards.push_back(deck.deal()); // Deal 3 cards for the flop 
    }
}

void Game::deal_turn() {
    deck.deal();    // Burn card
    community_cards.push_back(deck.deal()); // Deal 1 card for the turn
}

void Game::deal_river() {
    deck.deal();    // Burn card
    community_cards.push_back(deck.deal()); // Deal 1 card for the river
}

std::vector<Player*> Game::getPlayers() {
    return players;
}

std::vector<Card> Game::getCommunityCards() {
    return community_cards;
}

int Game::getPot() {
    return pot;
}

int Game::getButton() {
    return button;
}

bool Game::getShowdown() {
    return atShowdown;
}

/**
 * Award the pot to the winner of the hand
 * @param winner: Player* - The player object who won the hand
 */
void Game::awardPot(vector<Player*> winners, vector<bool>& inGame) {

    int count = 0;
    // Loop through the winners and award the pot to each winner
    while(pot > 0){
        count++;
        if (winners.size() == 1) {
            Player* winner = winners[0];
            int winAmount = 0;
            int amountBet = winner->get_total_bet();

            for (Player* player : players) {
                winAmount += min(player->get_total_bet(), amountBet);
                // reduce each players total bet
                player->setTotalBet(max(0, player->get_total_bet() - amountBet));
                cout << player->get_total_bet() << endl;
            }
            winner->win(min(winAmount, (int)(pot)));
            if(winAmount > pot){
                pot = 0;
            } else {
                pot -= winAmount;
            }
            // Set the winner to no longer be inGame 
            inGame[distance(players.begin(), find(players.begin(), players.end(), winner))] = false;
            winners = this->getWinner(this->getPlayers(), this->community_cards, inGame);
        } else {

            // Sort the winners by total bet (smallest to largest)
            sort(winners.begin(), winners.end(), [](Player* a, Player* b) {
                return a->get_total_bet() < b->get_total_bet();
            });

            int cumulativeAmountWon = 0;
            int numWinners = winners.size();

            for(Player* winner : winners){
                int winAmount = 0;
                int amountBet = winner->get_total_bet();
                for(Player* player : players){
                    winAmount += min(player->get_total_bet(), amountBet);
                    // reduce each players total bet
                    player->setTotalBet(max(0, player->get_total_bet() - amountBet));
                }
                // Award every winner the same amount 
                winner->win(((winAmount))/ numWinners + cumulativeAmountWon);
                this->pot -= ((winAmount))/ numWinners + cumulativeAmountWon;
                cumulativeAmountWon += ((winAmount))/ numWinners;
                numWinners--;
            }

        }
    }

}

/**
 * Perform a move for a user based on the provided move string
 * @param move: string - The move to perform received from the user input
 * @param player: Player* - The player object to perform the move for
 * @param pot: int - The current pot size
 */
int Game::makeMoveForUser(const std::string& move, Player* player, int playerIndex, int largestBet) {

    Move currentMove = getCurrentMove(move);

    // Perform correct move on the player's object
    switch (currentMove) {
        case Move::CALL: {
            int callAmount = largestBet;
            // Check the call amount is less than the player's stack
            if (callAmount > player->get_stack() + player->get_current_bet()) {
                callAmount = player->get_stack() + player->get_current_bet();
            }
            
            this->pot += callAmount - player->get_current_bet();

            

            player->bet(callAmount);
            GUI::displayPlayerMove(player, "Call", -1);
            return largestBet;
        }
        case Move::RAISE: {
            int raiseAmount = player->getBetSizing(largestBet+BIG_BLIND, player->get_stack() + player->get_current_bet());
            this->pot += raiseAmount - player->get_current_bet();
        
            player->bet(raiseAmount);
            GUI::displayPlayerMove(player, "Raise", raiseAmount);
            return raiseAmount;
        }
        case Move::CHECK: {
            GUI::displayPlayerMove(player, "Check", -1);
            return player->get_current_bet();
        }
        case Move::FOLD: {
            player->clear_hand();
            player->reset_current_bet();
            GUI::displayPlayerMove(player, "Fold", -1);
            return -1;  // Used to remove the player from the hand 
        }
    }
    
}

/**
 * Deal cards to the table based on the current stage of the game
 */
void Game::deal(){
    // Check the game stage and deal the appropriate cards
    switch (currentStage) {
        case PREFLOP:
            this->deal_hands();
            break;
        case FLOP:
            this->deal_flop();
            break;
        case TURN:
            this->deal_turn();
            break;
        case RIVER:
            this->deal_river();
            break;
    }

    // Move to the next stage
    this->nextStage();
}

/** 
 * Move to the next stage of the game
 */
void Game::nextStage(){
    // Check the game stage and move to the next stage
    switch (currentStage) {
        case Stage::PREFLOP:
            currentStage = Stage::FLOP;
            break;
        case Stage::FLOP:
            currentStage = Stage::TURN;
            break;
        case Stage::TURN:
            currentStage = Stage::RIVER;
            break;
        case Stage::RIVER:
            currentStage = Stage::PREFLOP;
            break;
    }
}   

/**
 * Play a hand of poker
 * 
 * Called in main.cpp to play a hand of poker
 */
vector<int> Game::playHand() {
    int humanPlayerStartingStack = this->getPlayers()[0]->get_stack();

    // Deal cards out to the table 
    this->deal();

    // Store the number of players in the hand 
    int numPlayers = this->getPlayers().size();

    // A vector of booleans corresponding to the players in the game - keep track of who is still in the hand
    vector<bool> inGame = vector<bool>(numPlayers, true);
 
    // Get the small blind and big blind players
    Player* smallBlindPlayer = this->getPlayers()[(button + 1) % numPlayers];
    Player* bigBlindPlayer = this->getPlayers()[(button + 2) % numPlayers];

    // Extract blinds from the players and add them to the pot
    this->addBlindsToPot(bigBlindPlayer, smallBlindPlayer);

    int largestBet = BIG_BLIND;

    Player* winner = nullptr;

    // A loop for the 4 possible betting rounds
    for(int i = 0; i < 4; i ++){
        if(this->bettingRound(inGame, largestBet, numPlayers)){
            resetPlayerBets();
            break;
        }
        if(i != 3){
            this->deal();
        }
        
        largestBet = 0;
        resetPlayerBets();
    }

    // if the number of community cards is less than 5, deal the remaining cards
    while(community_cards.size() < 5){
        this->deal();
    }

    vector<Player*> winners = this->getWinner(this->getPlayers(), this->community_cards, inGame);

    //GUI::displayCommunityCards(community_cards);

    atShowdown = count(inGame.begin(), inGame.end(), true) > 1;
    GUI::displayGameState();
    // sleep for 1 second 
    // std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    // Award the pot to the winner/s
    this->awardPot(winners, inGame);
    GUI::displayGameState();
    // sleep for 1 second 
    // std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    atShowdown = false;
    // Move the button 
    this->button = (this->button + 1) % numPlayers;
    // Reset all hands 
    this->resetPlayerHands();
    // Reset the community cards
    this->resetCommunityCards();
    // Reset the deck 
    this->deck.reset();
    // Reset the game stage
    this->currentStage = PREFLOP;

    // Reset the total bets of all players
    this->resetPlayerTotalBets();

    // TESTING: check that the sum of all player stacks is the same as the starting stack
    int totalStack = 0;
    for (Player* player : this->getPlayers()) {
        totalStack += player->get_stack();
        
        if(player->get_stack() <= 0){
            // cout << player->get_name() << "'s stack: " << player->get_stack() << endl;
            // cout << "Player stack too small, removing from game" << endl;
            // Remove the player from the players vector
            this->players.erase(remove(players.begin(), players.end(), player), players.end());
            this->removedPlayerCount++;
            // Print all the names of the players in the game
            for (Player* player : this->getPlayers()) {
                // cout << player->get_name() << endl;
            }
            // print the length of the players vector
            // cout << "Length of players vector: " << this->getPlayers().size() << endl;
            // while(true){}

        }
    }

    // Here we want to return a vector of the amount of chips the first player won, and if they put in voluntarily
    int pnl = this->getPlayers()[0]->get_stack() - humanPlayerStartingStack;

    bool vpip = abs(pnl) > 0;

    // If the player was in the small b
    if(bigBlindPlayer == this->getPlayers()[0] && (pnl == -BIG_BLIND || pnl == SMALL_BLIND)){
        vpip = false;
    }

    if(smallBlindPlayer == this->getPlayers()[0] && pnl == -SMALL_BLIND){
        vpip = false;
    }

    int vpipInt = vpip ? 1 : 0;

    return {pnl, vpipInt};




}


void Game::resetPlayerTotalBets(){
    for(Player* player : this->getPlayers()){
        player->reset_total_bet();
    }
}

/**
 * Get the final winner of the hand- given that there is only one player left 
 * @param inGame: vector<bool>& - A vector of booleans corresponding to the players in the game
 * @return Player* - The final winner of the hand
 */
Player* Game::get_final_winner(vector<bool>& inGame) {
    Player *winner = this->getPlayers()[find(inGame.begin(), inGame.end(), true) - inGame.begin()];  
    return winner;
}

/**
 * Perform a betting round for the players in the game
 * @param inGame: vector<bool>& - A vector of booleans corresponding to the players in the game
 * @param largestBet: int - The current largest bet in the game
 * @param numPlayers: int - The number of players in the game
 * @param largestBetPlayer: Player* - The player who made the largest bet
 * @param preflop: bool - Whether the betting round is pre-flop or not
 * @return bool - whether the entire hand should be ended
 */
bool Game::bettingRound(vector<bool>& inGame, int largestBet, int numPlayers) {
    // TESTING: display game state 
    GUI::displayGameState();
    // sleep for 1 second 
    // std::this_thread::sleep_for(std::chrono::milliseconds(2000));

    int currentPlayer;
    
    if(currentStage == Stage::FLOP){   // UTG is first to act if pre-flop
        currentPlayer = (button + 3) % numPlayers;
    } else {    // Otherwise, the player to the left of the button is first to act
        currentPlayer = (button + 1) % numPlayers;
        while(!inGame[currentPlayer]){
            currentPlayer = (currentPlayer + 1) % numPlayers;
        }
    }
    Player* largestBetPlayer = this->getPlayers()[currentPlayer];

    // Loop for the betting round 
    while(true) {
        GUI::displayGameState();

        // End the betting round if there is only one player left in the game
        if (count(inGame.begin(), inGame.end(), true) == 1) {
            return true;
        }

        // If the player is still in the game
        if (inGame[currentPlayer]) {
        
            Player* player = this->getPlayers()[currentPlayer];

            // Get the current number of players in the hand
            int numPlayersInHand = count(inGame.begin(), inGame.end(), true);

            bool canCheck = (largestBet == this->getPlayers()[currentPlayer]->get_current_bet()) || (this->getPlayers()[currentPlayer]->get_stack() == 0);
            bool canRaise = this->getPlayers()[currentPlayer]->get_stack() + this->getPlayers()[currentPlayer]->get_current_bet() > largestBet;
            // A player can only fold or call if they are not the largest better 
            bool canFold = this->getPlayers()[currentPlayer]->get_current_bet() != largestBet && this->getPlayers()[currentPlayer]->get_stack() > 0;
            bool canCall = canFold;
            // Get the player's move
            string move = player->getMove(canCheck, canRaise, canFold, canCall, community_cards, largestBet, numPlayersInHand, pot);

            // Perform the move for the player

            int betSize = makeMoveForUser(move, this->getPlayers()[currentPlayer], currentPlayer, largestBet);
            // std::this_thread::sleep_for(std::chrono::milliseconds(2000));

            // If the player has folded, update the inGame vector
            if (betSize == -1) {
                inGame[currentPlayer] = false;
                continue;
            }

            // Update the largest bet if the player has bet more than the current largest bet
            if (betSize > largestBet) {
                largestBet = betSize;
                largestBetPlayer = this->getPlayers()[currentPlayer];
            }
             GUI::displayGameState();
            //  std::this_thread::sleep_for(std::chrono::milliseconds(2000));
        }

        // Move to the next player
        currentPlayer = (currentPlayer + 1) % numPlayers;

        // If we have looped back to the player who made the largest bet, break
        if (this->getPlayers()[currentPlayer] == largestBetPlayer) {
            return false;
        }

        // Check if the stack size of all players in the game is 0 
        int numStacksNonZero = 0;
        for(int i = 0; i < numPlayers; i++){
            if(inGame[i] && this->getPlayers()[i]->get_stack() > 0){
                numStacksNonZero++;
            }
        }
        if(numStacksNonZero <= 1){
            return true;
        }
    }
}

/**
 * Private method used for converting a string move to a Move enum
 * @param move: string - The move to convert
 * @return Move - The converted move
 */
Move Game::getCurrentMove(std::string move) {

    // Strip the move of any whitespace
    move.erase(remove_if(move.begin(), move.end(), ::isspace), move.end());

    switch (move[0]) {
        case 'a': 
            return Move::CHECK;
        case 'c':
            return Move::CALL;
        case 'r':
            return Move::RAISE;
        case 'f':
            return Move::FOLD;
        default:
            return Move::FOLD;
    }
}

void Game::resetPlayerBets() {
    for (Player* player : this->getPlayers()) {
        player->reset_current_bet();
    }
    
}

void Game::resetPlayerHands(){
    for (Player* player : this->getPlayers()) {
        player->clear_hand();
    }
}

void Game::resetCommunityCards(){
    this->community_cards.clear();
}

void Game::addBlindsToPot(Player *bigBlindPlayer, Player *smallBlindPlayer) {
    this->pot += bigBlindPlayer->deduct_blind(BIG_BLIND);
    this->pot += smallBlindPlayer->deduct_blind(SMALL_BLIND);
}

vector<Player*> Game::getWinner(vector<Player*> players, const vector<Card>& community_cards, const vector<bool>& inGame){
    vector<Player*> winners;
    vector<vector<Card>> playerHands;
    vector<Player*> playersInGame;

    HandEvaluator handEvaluator = HandEvaluator();

    for(int i = 0; i < players.size(); i++){
        if(inGame[i]){
            vector<Card> playerHand = players[i]->get_hand();
            playerHands.push_back(playerHand);
            playersInGame.push_back(players[i]);
        }
    }

    vector<bool> winningIndex = handEvaluator.evaluateTable(playerHands, community_cards);

   
    for(int i = 0; i < winningIndex.size(); i++){
        if(winningIndex[i]){
            winners.push_back(playersInGame[i]);
            // print the name of the winner
            // cout << playersInGame[i]->get_name() << endl;
        }
    }
    return winners;
}

