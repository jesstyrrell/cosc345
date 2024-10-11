// CSVWorker.h
#ifndef CSV_WORKER_H
#define CSV_WORKER_H

#include <string>
#include <vector>
#include "PlayerProfile.hpp"

class CSVWorker
{
private:
    std::string filename;
    std::vector<PlayerProfile> profiles;

public:
    CSVWorker(const std::string &fname);
    bool writeProfiles();
    std::vector<PlayerProfile> readProfiles();
    void addProfile(const PlayerProfile &profile);
    const std::vector<PlayerProfile> &getProfiles() const;
    void printProfiles() const;
    void updateProfile(const PlayerProfile &profile);
};

#endif // CSV_WORKER_H