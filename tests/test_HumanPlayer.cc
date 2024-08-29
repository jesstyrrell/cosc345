#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "../src/HumanPlayer.cpp"

class GUIWrapper
{
public:
    virtual ~GUIWrapper() = default;
    virtual std::string getUserMove(bool canCheck, bool canRaise, bool canFold, bool canCall)
    {
        return GUI::getUserMove(canCheck, canRaise, canFold, canCall);
    }
    virtual int getBetSizing(int minBet, int maxBet)
    {
        return GUI::getBetSizing(minBet, maxBet);
    }
    virtual int endOfRoundMenu()
    {
        return GUI::endOfRoundMenu();
    }
};

class MockGUIWrapper : public GUIWrapper
{
public:
    MOCK_METHOD(std::string, getUserMove, (bool, bool, bool, bool), (override));
    MOCK_METHOD(int, getBetSizing, (int, int), (override));
    MOCK_METHOD(int, endOfRoundMenu, (), (override));
};

class HumanPlayer : public Player
{
private:
    GUIWrapper *guiWrapper;

public:
    HumanPlayer(const std::string &name, int stack, GUIWrapper *wrapper)
        : Player(name, stack), guiWrapper(wrapper) {}

    std::string getMove(bool canCheck, bool canRaise, bool canFold, bool canCall) override
    {
        return guiWrapper->getUserMove(canCheck, canRaise, canFold, canCall);
    }

    int getBetSizing(int minBet, int maxBet) override
    {
        return guiWrapper->getBetSizing(minBet, maxBet);
    }

    int endOfHand()
    {
        return guiWrapper->endOfRoundMenu();
    }
};


class HumanPlayerTest : public ::testing::Test
{
protected:
    std::unique_ptr<MockGUIWrapper> mockGui;
    std::unique_ptr<HumanPlayer> player;

    void SetUp() override
    {
        mockGui = std::make_unique<MockGUIWrapper>();
        player = std::make_unique<HumanPlayer>("TestPlayer", 1000, mockGui.get());
    }
};

TEST_F(HumanPlayerTest, GetMoveTest)
{
    EXPECT_CALL(*mockGui, getUserMove(true, true, true, true))
        .WillOnce(::testing::Return("call"));

    std::string move = player->getMove(true, true, true, true);
    EXPECT_EQ(move, "call");
}

TEST_F(HumanPlayerTest, GetBetSizingTest)
{
    EXPECT_CALL(*mockGui, getBetSizing(50, 1000))
        .WillOnce(::testing::Return(200));

    int betSize = player->getBetSizing(50, 1000);
    EXPECT_EQ(betSize, 200);
}

TEST_F(HumanPlayerTest, EndOfHandTest)
{
    EXPECT_CALL(*mockGui, endOfRoundMenu())
        .WillOnce(::testing::Return(1));

    int result = player->endOfHand();
    EXPECT_EQ(result, 1);
}

TEST_F(HumanPlayerTest, ConstructorTest)
{
    EXPECT_EQ(player->get_name(), "TestPlayer");
    EXPECT_EQ(player->get_stack(), 1000);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}