#pragma once
#include <vector>

#include "../../application/Randomizer.h"
#include "SADXModLoader.h"
#include "../../application/structs/LocationData.h"


class EventDetector
{
public:
    explicit EventDetector(Randomizer& randomizer);
    void OnPlayingFrame() const;

private:
    Randomizer& _randomizer;
    mutable std::map<int, LocationData> _checkData;
};
