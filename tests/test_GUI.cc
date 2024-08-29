// #include <gtest/gtest.h>
// #include <vector>
// #include <string>
// #include <sstream>
// #include <iostream>

// #include "../src/GUI.hpp"
// #include "../src/Game.hpp"
// #include "../src/Player.hpp"
// #include "../src/Card.hpp"

// class GUITest : public ::testing::Test
// {
// protected:
//     GUI *gui;
//     Game *game;
//     Player *player1;
//     Player *player2;

//     void SetUp() override
//     {
//         gui = new GUI();

//         player1 = std::make_unique<Player>("Player1", 1000);
//         player2 = std::make_unique<Player>("Player2", 1000);

//         player1 = new Player("Player1", 1000);
//         player2 = new Player("Player2", 1000);

//         vector<Player *> players = {player1, player2};
//         game = new Game(players);

//         GUI::setGame(game);
//     }

//     void TearDown() override
//     {
//         delete gui;
//         delete game;
//         delete player1;
//         delete player2;
//     }
// };

// TEST_F(GUITest, GetUserMove)
// {
//     std::istringstream input("f\n");
//     std::cin.rdbuf(input.rdbuf());

//     std::string move = gui->getUserMove(true, true, true, true);
//     EXPECT_EQ(move, "f");
// }

// TEST_F(GUITest, GetBetSizing)
// {
//     std::istringstream input("50\n");
//     std::cin.rdbuf(input.rdbuf());

//     int bet = gui->getBetSizing(10, 100);
//     EXPECT_EQ(bet, 50);
// }

// TEST_F(GUITest, DisplayCommunityCards)
// {
//     std::vector<Card> communityCards = {Card("Hearts", "2"), Card("Diamonds", "3")};
//     std::ostringstream output;
//     std::streambuf *oldCoutBuf = std::cout.rdbuf(output.rdbuf());

//     gui->displayCommunityCards(communityCards);

//     std::cout.rdbuf(oldCoutBuf);
//     std::string expectedOutput = "2 of Hearts\n3 of Diamonds\n";
//     EXPECT_EQ(output.str(), expectedOutput);
// }

// TEST_F(GUITest, DisplayAllPlayerHands)
// {
//     player1->addCardToHand(Card("Hearts", "2"));
//     player2->addCardToHand(Card("Diamonds", "3"));
//     std::vector<Player *> players = {player1, player2};
//     std::ostringstream output;
//     std::streambuf *oldCoutBuf = std::cout.rdbuf(output.rdbuf());

//     gui->displayAllPlayerHands(players);

//     std::cout.rdbuf(oldCoutBuf);
//     std::string expectedOutput = "Player1's hand: \n2 of Hearts\n--------------\nPlayer2's hand: \n3 of Diamonds\n--------------\n";
//     EXPECT_EQ(output.str(), expectedOutput);
// }

// TEST_F(GUITest, DisplayPlayerHand)
// {
//     player1->addCardToHand(Card("Hearts", "2"));
//     std::ostringstream output;
//     std::streambuf *oldCoutBuf = std::cout.rdbuf(output.rdbuf());

//     gui->displayPlayerHand(player1);

//     std::cout.rdbuf(oldCoutBuf);
//     std::string expectedOutput = "Player1's hand: \n2 of Hearts\n--------------\n";
//     EXPECT_EQ(output.str(), expectedOutput);
// }

// TEST_F(GUITest, DisplayPlayerStack)
// {
//     std::ostringstream output;
//     std::streambuf *oldCoutBuf = std::cout.rdbuf(output.rdbuf());

//     gui->displayPlayerStack(player1);

//     std::cout.rdbuf(oldCoutBuf);
//     std::string expectedOutput = "Player1's stack: 1000\n    -----    \n";
//     EXPECT_EQ(output.str(), expectedOutput);
// }

// TEST_F(GUITest, DisplayStartScreen)
// {
//     std::ostringstream output;
//     std::streambuf *oldCoutBuf = std::cout.rdbuf(output.rdbuf());

//     gui->displayStartScreen();

//     std::cout.rdbuf(oldCoutBuf);
//     std::string expectedOutput = R"(:::::::::  :::    ::: ::::    :::    ::::::::::: :::::::::::    ::::::::::: :::       ::: :::::::::::  ::::::::  :::::::::: 
// :+:    :+: :+:    :+: :+:+:   :+:        :+:         :+:            :+:     :+:       :+:     :+:     :+:    :+: :+:        
// +:+    +:+ +:+    +:+ :+:+:+  +:+        +:+         +:+            +:+     +:+       +:+     +:+     +:+        +:+        
// +#++:++#:  +#+    +:+ +#+ +:+ +#+        +#+         +#+            +#+     +#+  +:+  +#+     +#+     +#+        +#++:++#   
// +#+    +#+ +#+    +#+ +#+  +#+#+#        +#+         +#+            +#+     +#+ +#+#+ +#+     +#+     +#+        +#+        
// #+#    #+# #+#    #+# #+#   #+#+#        #+#         #+#            #+#      #+#+# #+#+#      #+#     #+#    #+# #+#        
// ###    ###  ########  ###    ####    ###########     ###            ###       ###   ###   ###########  ########  ########## )";
//     expectedOutput += "\n--------------------------------\n";
//     EXPECT_EQ(output.str(), expectedOutput);
// }

// TEST_F(GUITest, DisplayEndMessage)
// {
//     // This test is more complex due to the file reading and animation.
//     // You might need to mock file reading and time delays for a proper unit test.
// }

// TEST_F(GUITest, DisplayMenu)
// {
//     std::istringstream input("\n");
//     std::cin.rdbuf(input.rdbuf());

//     int result = gui->displayMenu();
//     EXPECT_EQ(result, 1);
// }

// TEST_F(GUITest, EndOfRoundMenu)
// {
//     std::istringstream input("\n");
//     std::cin.rdbuf(input.rdbuf());

//     int result = gui->endOfRoundMenu();
//     EXPECT_EQ(result, 1);
// }

// TEST_F(GUITest, DisplayPlayerMove)
// {
//     std::ostringstream output;
//     std::streambuf *oldCoutBuf = std::cout.rdbuf(output.rdbuf());

//     gui->displayPlayerMove(player1, "raise", 50);

//     std::cout.rdbuf(oldCoutBuf);
//     std::string expectedOutput = "Player1: raise 50\n";
//     EXPECT_EQ(output.str(), expectedOutput);
// }

// int main(int argc, char **argv)
// {
//     ::testing::InitGoogleTest(&argc, argv);
//     return RUN_ALL_TESTS();
// }