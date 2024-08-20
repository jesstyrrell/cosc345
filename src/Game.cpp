#include "Game.hpp"
#include "GUI.hpp"

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

std::vector<Player*> Game::get_players() {
    return players;
}

/**
 * Award the pot to the winner of the hand
 * @param winner: Player* - The player object who won the hand
 */
void Game::awardPot(Player* winner) {
    winner->win(this->pot);
    this->pot = 0;
}

/**
 * Perform a move for a user based on the provided move string
 * @param move: string - The move to perform received from the user input
 * @param player: Player* - The player object to perform the move for
 * @param pot: int - The current pot size
 */
int Game::makeMoveForUser(string move, Player* player, int playerIndex, int largestBet) {

    Move currentMove = getCurrentMove(move);

    // Perform correct move on the player's object
    switch (currentMove) {
        case Move::CALL: {
            int callAmount = largestBet - player->get_current_bet();
            // Check the call amount is less than the player's stack
            if (callAmount > player->get_stack()) {
                callAmount = player->get_stack();
            }
            this->pot += callAmount;
            player->bet(callAmount);
            return largestBet;
        }
        case Move::RAISE: {
            int raiseAmount = GUI::getBetSizing(SMALL_BLIND, player->get_stack() + player->get_current_bet());
            this->pot += raiseAmount - player->get_current_bet();
            player->bet(raiseAmount);
            return raiseAmount;
        }
        case Move::CHECK: {
            return player->get_current_bet();
        }
        case Move::FOLD: {
            player->clear_hand();
            return -1;  // Used to remove the player from the hand 
        }
    }
    
}

/**
 * Static method to test the Game class
 * 
 * @return bool - Whether the tests passed
 */
bool Game::test_game() {
    vector<Player*> players;
    Player player1 = Player("Jess", 1000);
    Player player2 = Player("James", 1000);

    players.push_back(&player1);
    players.push_back(&player2);

    Game game = Game(players);


    // Game should start with 52 cards
    if (game.deck.get_cards().size() != 52) {
        std::cout << "Deck does not have 52 cards" << std::endl;
        return false;
    }

    // Checking deal_hand
    game.deal_hands();
    for (Player* player : game.get_players()) {
        if (player->get_hand().size() != 2) {
            std::cout << "Player does not have 2 cards in hand" << std::endl;
            return false;
        }
    }
    if (game.deck.get_cards().size() != 48) {
        std::cout << "Deck does not have 48 cards" << std::endl;
        return false;
    }

    // Checking deal_flop
    game.deal_flop();
    if (game.community_cards.size() != 3) {
        std::cout << "Flop does not have 3 cards" << std::endl;
        return false;
    }
    if (game.deck.get_cards().size() != 44) {
        std::cout << "Deck does not have 45 cards" << std::endl;
        return false;
    }

    // Checking deal_turn
    game.deal_turn();
    if (game.community_cards.size() != 4) {
        std::cout << "Turn does not have 4 cards" << std::endl;
        return false;
    }
    if (game.deck.get_cards().size() != 42) {
        std::cout << "Deck does not have 44 cards" << std::endl;
        return false;
    }

    // Checking deal_river
    game.deal_river();
    if (game.community_cards.size() != 5) {
        std::cout << "River does not have 5 cards" << std::endl;
        return false;
    }
    if (game.deck.get_cards().size() != 40) {
        std::cout << "Deck does not have 42 cards" << std::endl;
        return false;
    }

    // Checking get_players
    if (game.get_players().size() != 2) {
        std::cout << "Game does not have 3 players" << std::endl;
        return false;
    }
    if (game.get_players()[0]->get_name() != "Jess") {
        std::cout << "Player 1 is not Jess" << std::endl;
        return false;
    }
    if (game.get_players()[1]->get_name() != "James") {
        std::cout << "Player 2 is not James" << std::endl;
        return false;
    }

    // Checking add_player
    Player player3 = Player("Corban", 1000);
    game.add_player(&player3);
    if (game.get_players().size() != 3) {
        std::cout << "Game does not have 3 players" << std::endl;
        return false;
    }

    // Free memory
    // for (Player* player : game.get_players()) {
    //     delete player;
    // }

    return true;
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
void Game::playHand() {

    // Deal cards out to the table 
    this->deal();

    // Store the number of players in the hand 
    int numPlayers = this->get_players().size();

    // A vector of booleans corresponding to the players in the game - keep track of who is still in the hand
    vector<bool> inGame = vector<bool>(numPlayers, true);

    // Get the small blind and big blind players
    Player* smallBlindPlayer = this->get_players()[(button + 1) % numPlayers];
    Player* bigBlindPlayer = this->get_players()[(button + 2) % numPlayers];

    // Extract blinds from the players and add them to the pot
    this->addBlindsToPot(bigBlindPlayer, smallBlindPlayer);

    int largestBet = BIG_BLIND;
    // Player *largestBetPlayer = bigBlindPlayer;

    // A loop for the 4 possible betting rounds
    for(int i = 0; i < 4; i ++){
        if(this->bettingRound(inGame, largestBet, numPlayers)){
            this->awardPot(this->get_final_winner(inGame));
            this->currentStage = PREFLOP;
            this->button = (this->button + 1) % numPlayers;

            return;
        }
        this->deal();
        largestBet = 0;
        GUI::displayCommunityCards(community_cards);
        resetPlayerBets();
    }
    
    // Go to showdown
    // TODO: find winner (hand evaluator)
    // Award the pot to the winner and announce the winner 
    // For now randomly pick a winner 
    Player *winner = this->get_players()[rand() % numPlayers];
    this->awardPot(winner);

    // TESTING: print who won the hand 
    cout << winner->get_name() << " won the hand" << endl;

    // Move the button 
    this->button = (this->button + 1) % numPlayers;
    // Reset all hands 
    this->resetPlayerHands();

}

/**
 * Get the final winner of the hand- given that there is only one player left 
 * @param inGame: vector<bool>& - A vector of booleans corresponding to the players in the game
 * @return Player* - The final winner of the hand
 */
Player* Game::get_final_winner(vector<bool>& inGame) {
    Player *winner = this->get_players()[find(inGame.begin(), inGame.end(), true) - inGame.begin()];  
            this->awardPot(winner);
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
    int currentPlayer;
    
    if(currentStage == Stage::FLOP){   // UTG is first to act if pre-flop
        currentPlayer = button + 3 % numPlayers;
    } else {    // Otherwise, the player to the left of the button is first to act
        currentPlayer = button + 1 % numPlayers;
        while(!inGame[currentPlayer]){
            currentPlayer = (currentPlayer + 1) % numPlayers;
        }
    }

    Player* largestBetPlayer = this->get_players()[currentPlayer];

    // Loop for the betting round 
    while(true) {

        // End the betting round if there is only one player left in the game
        if (count(inGame.begin(), inGame.end(), true) == 1) {
            return true;
        }

        // If the player is still in the game
        if (inGame[currentPlayer]) {
            GUI::displayPlayerHand(this->get_players()[currentPlayer]);
            GUI::displayPlayerStack(this->get_players()[currentPlayer]);
            // Check if the player can perform each action
            bool canCheck = largestBet == this->get_players()[currentPlayer]->get_current_bet();
            bool canRaise = this->get_players()[currentPlayer]->get_stack() > largestBet;
            // A player can only fold or call if they are not the largest better 
            bool canFold = this->get_players()[currentPlayer]->get_current_bet() != largestBet;
            bool canCall = canFold;
            // Get the player's move
            string move = GUI::getUserMove(canCheck, canRaise, canFold, canCall);

            // Perform the move for the player
            int betSize = makeMoveForUser(move, this->get_players()[currentPlayer], currentPlayer, largestBet);

            // If the player has folded, update the inGame vector
            if (betSize == -1) {
                inGame[currentPlayer] = false;
                continue;
            }
            
            // Update the current bet for the player
            get_players()[currentPlayer]->bet(betSize);

            // Update the largest bet if the player has bet more than the current largest bet
            if (betSize > largestBet) {
                largestBet = betSize;
                largestBetPlayer = this->get_players()[currentPlayer];
            }
        }

        // Move to the next player
        currentPlayer = (currentPlayer + 1) % numPlayers;

        // If we have looped back to the player who made the largest bet, break
        if (this->get_players()[currentPlayer] == largestBetPlayer) {
            return false;
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
    for (Player* player : this->get_players()) {
        player->reset_current_bet();
    }
    
}

void Game::resetPlayerHands(){
    for (Player* player : this->get_players()) {
        player->clear_hand();
    }
}

void Game::addBlindsToPot(Player *bigBlindPlayer, Player *smallBlindPlayer) {
    this->pot += bigBlindPlayer->deduct_blind(BIG_BLIND);
    this->pot += smallBlindPlayer->deduct_blind(SMALL_BLIND);
}