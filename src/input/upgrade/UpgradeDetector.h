#pragma once
#include <vector>

#include "../../application/Randomizer.h"
#include "SADXModLoader.h"

struct UpgradeData
{
    std::string displayName;
    EventFlags eventFlag;
    Upgrades upgradeFlag;
    mutable bool gotCheck;
    bool gotUpgrade;
};

class UpgradeDetector
{
public:
    explicit UpgradeDetector(Randomizer& randomizer);
    void OnPlayingFrame() const;

private:
    Randomizer& _randomizer;
    std::vector<UpgradeData> _upgrades;
};
