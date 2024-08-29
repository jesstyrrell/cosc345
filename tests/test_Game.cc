#include <gtest/gtest.h>

#include "../src/Game.hpp"
#include "../src/Player.hpp"
#include "../src/RandomPlayer.cpp"
#include "../src/Deck.hpp"
#include "../src/Card.hpp"

class GameTest : public ::testing::Test
{
protected:
    RandomPlayer *player1;
    RandomPlayer *player2;
    std::vector<Player *> players;
    Game *game;

    void SetUp() override
    {
        player1 = new RandomPlayer("Jess", 1000);
        player2 = new RandomPlayer("James", 1000);

        players.push_back(player1);
        players.push_back(player2);

        game = new Game(players);
    }

    void TearDown() override
    {
        delete game;
        delete player1;
        delete player2;
    }
};

TEST_F(GameTest, ConstructorInitializesCorrectly)
{
    EXPECT_EQ(game->getPlayers().size(), 2);
    EXPECT_EQ(game->getPlayers()[0]->get_name(), "Jess");
    EXPECT_EQ(game->getPlayers()[1]->get_name(), "James");
    EXPECT_EQ(game->getPot(), 0);
    EXPECT_EQ(game->getCommunityCards().size(), 0);
}

TEST_F(GameTest, AddPlayer)
{
    HumanPlayer *player3 = new HumanPlayer("Corban", 1000);
    game->add_player(player3);
    EXPECT_EQ(game->getPlayers().size(), 3);
    EXPECT_EQ(game->getPlayers()[2]->get_name(), "Corban");
    delete player3;
}

TEST_F(GameTest, DealHands)
{
    game->deal_hands();
    for (Player *player : game->getPlayers())
    {
        EXPECT_EQ(player->get_hand().size(), 2);
    }
    EXPECT_EQ(game->deck.get_cards().size(), 48);
}

TEST_F(GameTest, DealFlop)
{
    game->deal_flop();
    EXPECT_EQ(game->getCommunityCards().size(), 3);
    EXPECT_EQ(game->deck.get_cards().size(), 48 - 3 - 1); // 3 cards for flop, 1 burn card
}

TEST_F(GameTest, DealTurn)
{
    game->deal_flop();
    game->deal_turn();
    EXPECT_EQ(game->getCommunityCards().size(), 4);
    EXPECT_EQ(game->deck.get_cards().size(), 48 - 3 - 1 - 1 - 1); // 3 flop, 1 burn, 1 turn, 1 burn
}

TEST_F(GameTest, DealRiver)
{
    game->deal_flop();
    game->deal_turn();
    game->deal_river();
    EXPECT_EQ(game->getCommunityCards().size(), 5);
    EXPECT_EQ(game->deck.get_cards().size(), 48 - 3 - 1 - 1 - 1 - 1 - 1); // 3 flop, 1 burn, 1 turn, 1 burn, 1 river, 1 burn
}

TEST_F(GameTest, AwardPot)
{
    player1->bet(100);
    player2->bet(100);
    game->awardPot({player1});
    EXPECT_EQ(player1->get_stack(), 1100);
    EXPECT_EQ(player2->get_stack(), 900);
    EXPECT_EQ(game->getPot(), 0);
}

TEST_F(GameTest, MakeMoveForUserCall)
{
    player1->bet(50);
    int largestBet = 50;
    game->makeMoveForUser("call", player2, 1, largestBet);
    EXPECT_EQ(player2->get_current_bet(), 50);
    EXPECT_EQ(game->getPot(), 100);
}

TEST_F(GameTest, MakeMoveForUserRaise)
{
    player1->bet(50);
    int largestBet = 50;
    game->makeMoveForUser("raise", player2, 1, largestBet);
    EXPECT_GT(player2->get_current_bet(), 50);
    EXPECT_GT(game->getPot(), 100);
}

TEST_F(GameTest, MakeMoveForUserCheck)
{
    int largestBet = 0;
    game->makeMoveForUser("check", player1, 0, largestBet);
    EXPECT_EQ(player1->get_current_bet(), 0);
}

TEST_F(GameTest, MakeMoveForUserFold)
{
    player1->bet(50);
    int largestBet = 50;
    game->makeMoveForUser("fold", player2, 1, largestBet);
    EXPECT_EQ(player2->get_current_bet(), 0);
    EXPECT_EQ(game->getPot(), 50);
}

TEST_F(GameTest, Deal)
{
    game->deal();
    EXPECT_EQ(game->getPlayers()[0]->get_hand().size(), 2);
    EXPECT_EQ(game->getPlayers()[1]->get_hand().size(), 2);
    EXPECT_EQ(game->getCommunityCards().size(), 0);
}

TEST_F(GameTest, NextStage)
{
    game->nextStage();
    EXPECT_EQ(game->currentStage, Stage::FLOP);
    game->nextStage();
    EXPECT_EQ(game->currentStage, Stage::TURN);
    game->nextStage();
    EXPECT_EQ(game->currentStage, Stage::RIVER);
    game->nextStage();
    EXPECT_EQ(game->currentStage, Stage::PREFLOP);
}

TEST_F(GameTest, PlayHand)
{
    game->playHand();
    EXPECT_EQ(game->getPlayers()[0]->get_hand().size(), 0);
    EXPECT_EQ(game->getPlayers()[1]->get_hand().size(), 0);
    EXPECT_EQ(game->getCommunityCards().size(), 0);
    EXPECT_EQ(game->getPot(), 0);
    EXPECT_EQ(game->currentStage, Stage::PREFLOP);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}