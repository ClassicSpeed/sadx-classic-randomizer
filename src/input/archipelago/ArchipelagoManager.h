#pragma once
#include "../../application/Randomizer.h"

class ArchipelagoManager
{
public:
    explicit ArchipelagoManager(Randomizer& randomizer);

    void Connect();
    void OnFrame();
    void SetConfigPath(std::string configPath) const;

private:
    Randomizer& _randomizer;
    mutable std::string _configPath;
    bool _connected;
};
