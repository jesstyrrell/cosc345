#include "Game.hpp"

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

void Game::show_community_cards() {
    for (Card card : community_cards) {
        std::cout << card.get_rank() << " of " << card.get_suit() << std::endl;
    }
}

void Game::show_player_hands() {
    for (Player* player : players) {
        std::cout << player->get_name() << "'s hand: " << std::endl;
        for (Card card : player->get_hand()) {
            std::cout << card.get_rank() << " of " << card.get_suit() << std::endl;
        }
        std::cout << "--------------" << std::endl;
    }
}

std::vector<Player*> Game::get_players() {
    return players;
}

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
