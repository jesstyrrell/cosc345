#pragma once
#include <gmock/gmock.h>

#include "../src/GUI.hpp"

class MockGUI {
    public:
        MOCK_METHOD(std::string, getUserMove, (bool, bool, bool, bool));
        MOCK_METHOD(int, getBetSizing, (int, int));
        MOCK_METHOD(int, endOfRoundMenu, ());
};