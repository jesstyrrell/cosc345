#include <gtest/gtest.h>
#include <fstream>
#include <chrono>
#include <thread>

#include "../src/EquityCalculator.hpp"

// Mock functions for OS-specific behavior
#ifdef _WIN32
#define MOCK_OS "Windows"
#elif __APPLE__
#define MOCK_OS "MacOS"
#elif __linux__
#define MOCK_OS "Linux"
#else
#define MOCK_OS "Unknown"
#endif

// Declaring the functions used in the unit tests
std::string getFileStartPath();
bool fileExists(const std::string &filename);
std::vector<float> findEquity(const std::string &filename, const std::vector<std::string> &searchValues);

// Test fixture
class EquityCalculatorTest : public ::testing::Test {
    protected:
        EquityCalculator calculator;
};

// Test getFileStartPath function
TEST_F(EquityCalculatorTest, GetFileStartPath) {
    std::string result = getFileStartPath();
    #ifdef _WIN32
    EXPECT_EQ(result, "../../..");
    #elif __APPLE__ || __linux__
    EXPECT_EQ(result, "..");
    #else
    EXPECT_EQ(result, "");
    #endif
}

// Test fileExists function
TEST_F(EquityCalculatorTest, FileExists) {
    // Create a temporary file
    std::ofstream tempFile("temp.txt");
    tempFile.close();

    EXPECT_TRUE(fileExists("temp.txt"));
    EXPECT_FALSE(fileExists("nonexistent.txt"));

    // Clean up
    std::remove("temp.txt");
}

// Test findEquity function
TEST_F(EquityCalculatorTest, FindEquity) {
    // Create a test CSV file
    std::ofstream testFile("preflopEquity.csv");
    testFile << "A,K,true,2,0.6,0.1\n";
    testFile << "Q,J,false,3,0.4,0.05\n";
    testFile.close();

    std::vector<std::string> searchValues = {"A", "K", "true", "2"};
    auto result = findEquity("preflopEquity.csv", searchValues);
    EXPECT_EQ(result.size(), 2);
    EXPECT_FLOAT_EQ(result[0], 0.6f);
    EXPECT_FLOAT_EQ(result[1], 0.1f);

    // Test with non-matching values
    searchValues = {"X", "Y", "false", "4"};
    result = findEquity("preflopEquity.csv", searchValues);
    EXPECT_TRUE(result.empty());

    // Clean up
    std::remove("preflopEquity.csv");
}

// FIXME: Test calculateHandEquity function
TEST_F(EquityCalculatorTest, CalculateHandEquity) {
    std::vector<Card> hand = {Card("Hearts", "A"), Card("Spades", "K")};
    std::vector<Card> communityCards;
    Deck deck;
    int numPlayers = 2;

    // Test preflop equity calculation
    auto result = calculator.calculateHandEquity(hand, communityCards, deck, numPlayers);
    EXPECT_EQ(result.size(), 2);

    // Test with community cards (postflop)
    communityCards = {Card("Clubs", "7"), Card("Diamonds", "8"), Card("Hearts", "9")};
    result = calculator.calculateHandEquity(hand, communityCards, deck, numPlayers);
    EXPECT_EQ(result.size(), 3);
}

// Test evaluateHand function
TEST_F(EquityCalculatorTest, EvaluateHand) {
    std::vector<Card> hand = {Card("Hearts", "A"), Card("Spades", "K")};
    std::vector<Card> communityCards = {Card("Clubs", "7"), Card("Diamonds", "8"), Card("Hearts", "9")};
    Deck deck;
    int numPlayers = 2;

    auto result = calculator.evaluateHand(hand, communityCards, deck, numPlayers);
    EXPECT_EQ(result.size(), 3);
    EXPECT_GE(result[0], 0.0f);
    EXPECT_LE(result[0], 1.0f);
    EXPECT_GE(result[1], 0.0f);
    EXPECT_LE(result[1], 1.0f);
    EXPECT_GE(result[2], 0.0f);
    EXPECT_LE(result[2], 1.0f);
}

// Test buildPreflopEquityCSV function
// TEST_F(EquityCalculatorTest, BuildPreflopEquityCSV) {
//     // Redirect cout to capture progress output
//     std::stringstream buffer;
//     std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());

//     calculator.buildPreflopEquityCSV();

//     // Restore cout
//     std::cout.rdbuf(old);

//     // Check if the file was created
//     EXPECT_TRUE(fileExists(getFileStartPath() + "/preflopEquity.csv"));

//     // Check if the file contains data
//     std::ifstream csvFile(getFileStartPath() + "/preflopEquity.csv");
//     std::string line;
//     std::getline(csvFile, line); // Read header
//     EXPECT_FALSE(line.empty());
//     std::getline(csvFile, line); // Read first data line
//     EXPECT_FALSE(line.empty());

//     // Clean up
//     std::remove((getFileStartPath() + "/preflopEquity.csv").c_str());
// }

// Main function to run the tests
int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}