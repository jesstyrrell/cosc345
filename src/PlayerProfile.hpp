// PlayerProfile.h
#ifndef PLAYER_PROFILE_H
#define PLAYER_PROFILE_H

#include <string>

struct PlayerProfile {
    std::string name;
    int totalHandsPlayed;
    int numHandsEasy;
    int numHandsMedium;
    int numHandsHard;
    int easyPnl;
    int mediumPnl;
    int hardPnl;
    int numHandsVpip;
    bool isGuest;
};

#endif // PLAYER_PROFILE_H