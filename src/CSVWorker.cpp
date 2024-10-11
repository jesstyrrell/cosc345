// CSVWorker.cpp
#include "CSVWorker.hpp"
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

CSVWorker::CSVWorker(const std::string& fname) : filename(fname) {}

bool CSVWorker::writeProfiles() {
    std::ofstream file(filename);
    if (!file.is_open()) {
        return false;
    }

    file << "Name,TotalHandsPlayed,NumHandsEasy,NumHandsMedium,NumHandsHard,EasyPnl,MediumPnl,HardPnl,NumHandsVpip\n";
    for (const auto& profile : profiles) {
        file << profile.name << ","
             << profile.totalHandsPlayed << ","
                << profile.numHandsEasy << ","
                << profile.numHandsMedium << ","
                << profile.numHandsHard << ","
                << profile.easyPnl << ","
                << profile.mediumPnl << ","
                << profile.hardPnl << ","
                << profile.numHandsVpip << "\n";
    }

    file.close();
    return true;
}

std::vector<PlayerProfile> CSVWorker::readProfiles() {
    // Opening the file in read mode
    std::ifstream file(filename);
    if (!file.is_open()) {
        return std::vector<PlayerProfile>();
    }
    
    profiles.clear();
    std::string line;
    getline(file, line); // Skip header

    // Populating the profiles vector with the profiles in the file
    while (getline(file, line)) {
        std::istringstream ss(line);
        std::string field;
        PlayerProfile profile;

        getline(ss, profile.name, ',');
        getline(ss, field, ',');
        profile.totalHandsPlayed = std::stoi(field);
        getline(ss, field, ',');
        profile.numHandsEasy = std::stoi(field);
        getline(ss, field, ',');
        profile.numHandsMedium = std::stoi(field);
        getline(ss, field, ',');
        profile.numHandsHard = std::stoi(field);
        getline(ss, field, ',');
        profile.easyPnl = std::stoi(field);
        getline(ss, field, ',');
        profile.mediumPnl = std::stoi(field);
        getline(ss, field, ',');
        profile.hardPnl = std::stoi(field);
        getline(ss, field, ',');
        profile.numHandsVpip = std::stoi(field);


        profiles.push_back(profile);
    }

    // Closing the file and returning the profiles
    file.close();
    return profiles;
}

void CSVWorker::addProfile(const PlayerProfile& profile) {
    profiles.push_back(profile);
}

const std::vector<PlayerProfile>& CSVWorker::getProfiles() const {
    return profiles;
}

void CSVWorker::updateProfile(const PlayerProfile& profile) {
    this->readProfiles();
    for (auto& p : profiles) {
        if (p.name == profile.name) {
            p = profile;
            break;
        }
    }
    this->writeProfiles();
}

void CSVWorker::printProfiles() const {
    for (const auto& profile : profiles) {
        std::cout << "Name: " << profile.name
                    << ", Total Hands Played: " << profile.totalHandsPlayed
                    << ", Easy Hands: " << profile.numHandsEasy
                    << ", Medium Hands: " << profile.numHandsMedium
                    << ", Hard Hands: " << profile.numHandsHard
                    << ", Easy Pnl: " << profile.easyPnl
                    << ", Medium Pnl: " << profile.mediumPnl
                    << ", Hard Pnl: " << profile.hardPnl
                    << ", VPIP Hands: " << profile.numHandsVpip << std::endl;
    }
}