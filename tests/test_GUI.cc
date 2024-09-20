// #include <gtest/gtest.h>
// #include <sstream>
// #include <fstream>

// #include "../src/GUI.hpp"
// #include "../src/Game.hpp"
// #include "../src/Player.hpp"

// class Player; // Forward declaration

// class GUITest : public ::testing::Test {
// protected:
//     GUI gui;
//     Game game;

//     void SetUp() override {
//         GUI::setGame(&game);
//     }

//     // Helper function to capture cout output
//     std::string captureOutput(std::function<void()> func) {
//         std::stringstream buffer;
//         std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());
//         func();
//         std::cout.rdbuf(old);
//         return buffer.str();
//     }
// };

// TEST_F(GUITest, SetAndGetGame) {
//     Game* testGame = new Game();
//     GUI::setGame(testGame);
//     EXPECT_EQ(&GUI::getGame(), testGame);
//     delete testGame;
// }

// TEST_F(GUITest, ClearScreen) {
//     std::string output = captureOutput([]() { GUI::clearScreen(); });
//     #ifdef _WIN32
//     EXPECT_EQ(output, "cls");
//     #else
//     EXPECT_EQ(output, "clear");
//     #endif
// }

// TEST_F(GUITest, GetUserMove) {
//     std::istringstream input("f\n");
//     std::cin.rdbuf(input.rdbuf());
//     EXPECT_EQ(GUI::getUserMove(true, true, true, true), "f");
// }

// TEST_F(GUITest, GetBetSizing) {
//     std::istringstream input("50\n");
//     std::cin.rdbuf(input.rdbuf());
//     EXPECT_EQ(GUI::getBetSizing(10, 100), 50);
// }

// TEST_F(GUITest, DisplayCommunityCards) {
//     std::vector<Card> communityCards = {Card("Hearts", "A"), Card("Spades", "K")};
//     std::string output = captureOutput([&]() { GUI::displayCommunityCards(communityCards); });
//     EXPECT_TRUE(output.find("A of Hearts") != std::string::npos);
//     EXPECT_TRUE(output.find("K of Spades") != std::string::npos);
// }

// TEST_F(GUITest, DisplayAllPlayerHands) {
//     std::vector<Player*> players = {new Player("Alice", 1000), new Player("Bob", 1000)};
//     players[0]->add_card(Card("Hearts", "A"));
//     players[0]->add_card(Card("Spades", "K"));
//     players[1]->add_card(Card("Diamonds", "Q"));
//     players[1]->add_card(Card("Clubs", "J"));
//     std::string output = captureOutput([&]() { GUI::displayAllPlayerHands(players); });
//     EXPECT_TRUE(output.find("Alice's hand:") != std::string::npos);
//     EXPECT_TRUE(output.find("Bob's hand:") != std::string::npos);
//     EXPECT_TRUE(output.find("A of Hearts") != std::string::npos);
//     EXPECT_TRUE(output.find("J of Clubs") != std::string::npos);
//     for (auto player : players) delete player;
// }

// TEST_F(GUITest, DisplayPlayerHand) {
//     Player* player = new Player("Alice", 1000);
//     player->add_card(Card("Hearts", "A"));
//     player->add_card(Card("Spades", "K"));
//     std::string output = captureOutput([&]() { GUI::displayPlayerHand(player); });
//     EXPECT_TRUE(output.find("Alice's hand:") != std::string::npos);
//     EXPECT_TRUE(output.find("A of Hearts") != std::string::npos);
//     EXPECT_TRUE(output.find("K of Spades") != std::string::npos);
//     delete player;
// }

// TEST_F(GUITest, DisplayStartScreen) {
//     std::string output = captureOutput([]() { GUI::displayStartScreen(); });
//     EXPECT_TRUE(output.find("POKER CLI") != std::string::npos);
// }

// TEST_F(GUITest, DisplayEndMessage) {
//     std::string output = captureOutput([]() { GUI::displayEndMessage(); });
//     EXPECT_TRUE(output.find("cardAnimation") != std::string::npos);
// }

// TEST_F(GUITest, DisplayMenu) {
//     std::istringstream input("\n");
//     std::cin.rdbuf(input.rdbuf());
//     EXPECT_EQ(GUI::displayMenu(), 1);
// }

// TEST_F(GUITest, SignInMenu) {
//     std::istringstream input("3\nTestPlayer\n");
//     std::cin.rdbuf(input.rdbuf());
//     EXPECT_EQ(GUI::signInMenu(), "TestPlayer");
// }

// TEST_F(GUITest, GetNumberOfPlayers) {
//     std::istringstream input("4\n");
//     std::cin.rdbuf(input.rdbuf());
//     EXPECT_EQ(GUI::getNumberOfPlayers(), 4);
// }

// TEST_F(GUITest, EndOfRoundMenu) {
//     std::istringstream input("\n");
//     std::cin.rdbuf(input.rdbuf());
//     EXPECT_EQ(GUI::endOfRoundMenu(), 1);
// }

// TEST_F(GUITest, DisplayPlayerStack) {
//     Player* player = new Player("Alice", 1000);
//     std::string output = captureOutput([&]() { GUI::displayPlayerStack(player); });
//     EXPECT_TRUE(output.find("Alice's stack: 1000") != std::string::npos);
//     delete player;
// }

// TEST_F(GUITest, DisplayGameState) {
//     // Set up a game state
//     game.addPlayer(new Player("Alice", 1000));
//     game.addPlayer(new Player("Bob", 1000));
//     game.getCommunityCards().push_back(Card("Hearts", "A"));
//     std::string output = captureOutput([]() { GUI::displayGameState(); });
//     EXPECT_TRUE(output.find("Alice") != std::string::npos);
//     EXPECT_TRUE(output.find("Bob") != std::string::npos);
//     EXPECT_TRUE(output.find("A") != std::string::npos);
// }

// TEST_F(GUITest, DisplayPlayerMove) {
//     Player* player = new Player("Alice", 1000);
//     std::string output = captureOutput([&]() { GUI::displayPlayerMove(player, "raise", 50); });
//     EXPECT_TRUE(output.find("Alice: raise 50") != std::string::npos);
//     delete player;
// }

// TEST_F(GUITest, GetRandomPlayerName) {
//     std::string name = GUI::getRandomPlayerName();
//     EXPECT_FALSE(name.empty());
// }

// int main(int argc, char **argv) {
//     testing::InitGoogleTest(&argc, argv);
//     return RUN_ALL_TESTS();
// }