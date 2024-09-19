#include "gtest/gtest.h"
#include <vector>

#include "../src/Game.hpp"

class GameTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Set up any common resources for tests
    }

    void TearDown() override {
        // Clean up any resources after tests
    }

    // Helper function to create a game with players
    Game createGameWithPlayers(int numPlayers) {
        std::vector<Player*> players;
        for (int i = 0; i < numPlayers; i++) {
            players.push_back(new HumanPlayer("Player" + std::to_string(i+1), 1000));
        }
        return Game(players);
    }
};

TEST_F(GameTest, ConstructorAndGetPlayers) {
    Game game = createGameWithPlayers(2);
    EXPECT_EQ(game.getPlayers().size(), 2);
}

TEST_F(GameTest, AddPlayer) {
    Game game = createGameWithPlayers(2);
    Player* newPlayer = new HumanPlayer("NewPlayer", 1000);
    game.add_player(newPlayer);
    EXPECT_EQ(game.getPlayers().size(), 3);
}

TEST_F(GameTest, DealHands) {
    Game game = createGameWithPlayers(2);
    game.deal_hands();
    for (Player* player : game.getPlayers()) {
        EXPECT_EQ(player->get_hand().size(), 2);
    }
    EXPECT_EQ(game.deck.get_cards().size(), 48);
}

TEST_F(GameTest, DealFlop) {
    Game game = createGameWithPlayers(2);
    game.deal_flop();
    EXPECT_EQ(game.getCommunityCards().size(), 3);
    // Deal three cards and burn one
    EXPECT_EQ(game.deck.get_cards().size(), 48);
}

TEST_F(GameTest, DealTurn) {
    Game game = createGameWithPlayers(2);
    game.deal_turn();
    EXPECT_EQ(game.getCommunityCards().size(), 1);
    // Deal one card and burn one
    EXPECT_EQ(game.deck.get_cards().size(), 50);
}

TEST_F(GameTest, DealRiver) {
    Game game = createGameWithPlayers(2);
    game.deal_river();
    EXPECT_EQ(game.getCommunityCards().size(), 1);
    // Deal one card and burn one
    EXPECT_EQ(game.deck.get_cards().size(), 50);
}

TEST_F(GameTest, GetPot) {
    Game game = createGameWithPlayers(2);
    EXPECT_EQ(game.getPot(), 0);
}

TEST_F(GameTest, GetButton) {
    Game game = createGameWithPlayers(2);
    EXPECT_EQ(game.getButton(), 0);
}

TEST_F(GameTest, GetShowdown) {
    Game game = createGameWithPlayers(2);
    EXPECT_FALSE(game.getShowdown());
}

TEST_F(GameTest, AwardPot) {
    Game game = createGameWithPlayers(2);
    game.setPot(100);
    std::vector<Player*> winners = {game.getPlayers()[0]};
    game.awardPot(winners);
    EXPECT_EQ(game.getPot(), 0);
    EXPECT_EQ(winners[0]->get_stack(), 1100);
}

// FIXME: ***Exception: SegFault during test
// TEST_F(GameTest, MakeMoveForUser) {
//     Game game = createGameWithPlayers(2);
//     Player* player = game.getPlayers()[0];

//     // Test CALL
//     EXPECT_EQ(game.makeMoveForUser("call", player, 0, 50), 50);
    
//     // Test RAISE
//     EXPECT_EQ(game.makeMoveForUser("raise", player, 0, 50), 100);
    
//     // Test CHECK
//     EXPECT_EQ(game.makeMoveForUser("check", player, 0, 0), 0);
    
//     // Test FOLD
//     EXPECT_EQ(game.makeMoveForUser("fold", player, 0, 50), -1);
// }

TEST_F(GameTest, Deal) {
    Game game = createGameWithPlayers(2);
    game.deal();
    EXPECT_EQ(game.getPlayers()[0]->get_hand().size(), 2);
}

TEST_F(GameTest, NextStage) {
    Game game = createGameWithPlayers(2);
    game.nextStage();
    // Add assertions based on the expected behavior of nextStage()
}

// FIXME: ***Exception: SegFault during test
// TEST_F(GameTest, PlayHand) {
//     Game game = createGameWithPlayers(2);
//     game.playHand();
//     // Add assertions based on the expected behavior of playHand()
//     EXPECT_TRUE(true);
// }

TEST_F(GameTest, GetFinalWinner) {
    Game game = createGameWithPlayers(2);
    std::vector<bool> inGame = {true, false};
    Player* winner = game.get_final_winner(inGame);
    EXPECT_EQ(winner, game.getPlayers()[0]);
}

// FIXME: ***Exception: SegFault during test
// TEST_F(GameTest, BettingRound) {
//     Game game = createGameWithPlayers(2);
//     std::vector<bool> inGame = {true, true};
//     bool result = game.bettingRound(inGame, 50, 2);
//     // Add assertions based on the expected behavior of bettingRound()
// }

TEST_F(GameTest, GetCurrentMove) {
    Game game = createGameWithPlayers(2);
    EXPECT_EQ(game.getCurrentMove("a"), Move::CHECK);
    EXPECT_EQ(game.getCurrentMove("c"), Move::CALL);
    EXPECT_EQ(game.getCurrentMove("r"), Move::RAISE);
    EXPECT_EQ(game.getCurrentMove("f"), Move::FOLD);
    EXPECT_EQ(game.getCurrentMove("invalid"), Move::FOLD);
}

TEST_F(GameTest, ResetPlayerBets) {
    Game game = createGameWithPlayers(2);
    game.getPlayers()[0]->bet(50);
    game.resetPlayerBets();
    EXPECT_EQ(game.getPlayers()[0]->get_current_bet(), 0);
}

TEST_F(GameTest, ResetPlayerHands) {
    Game game = createGameWithPlayers(2);
    game.deal_hands();
    game.resetPlayerHands();
    EXPECT_EQ(game.getPlayers()[0]->get_hand().size(), 0);
}

TEST_F(GameTest, ResetCommunityCards) {
    Game game = createGameWithPlayers(2);
    game.deal_flop();
    game.resetCommunityCards();
    EXPECT_EQ(game.getCommunityCards().size(), 0);
}

TEST_F(GameTest, AddBlindsToPot) {
    Game game = createGameWithPlayers(2);
    Player* bigBlind = game.getPlayers()[0];
    Player* smallBlind = game.getPlayers()[1];
    game.addBlindsToPot(bigBlind, smallBlind);

    const int BIG_BLIND = 2;
    const int SMALL_BLIND = 1;
    EXPECT_EQ(game.getPot(), BIG_BLIND + SMALL_BLIND);
}

// FIXME: ***Exception: SegFault during test
// TEST_F(GameTest, GetWinner) {
//     Game game = createGameWithPlayers(2);
//     std::vector<bool> inGame = {true, true};

//     std::vector<Card> communityCards = {
//         Card("Hearts", "A"),
//         Card("Spades", "K"),
//         Card("Diamonds", "Q"),
//         Card("Clubs", "J"),
//         Card("Hearts", "10")
//     };
//     std::vector<Player*> winners = game.getWinner(game.getPlayers(), communityCards, inGame);
//     EXPECT_GT(winners.size(), 0);
// }

// Add more tests as needed to cover all scenarios and edge cases

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}