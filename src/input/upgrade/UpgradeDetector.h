#pragma once
#include <vector>

#include "../../application/Randomizer.h"
#include "SADXModLoader.h"
#include "../../application/structs/CheckData.h"


class UpgradeDetector
{
public:
    explicit UpgradeDetector(Randomizer& randomizer);
    void OnPlayingFrame() const;

private:
    Randomizer& _randomizer;
    mutable std::map<int, CheckData> _checkData;
};
