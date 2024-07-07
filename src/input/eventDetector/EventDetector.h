#pragma once
#include <vector>

#include "../../application/Randomizer.h"
#include "../../application/structs/LocationData.h"

enum LastStoryState
{
    LastStoryNotStarted,
    LastStoryStarted,
    LastStoryCompleted
};


class EventDetector
{
public:
    explicit EventDetector(Randomizer& randomizer);
    void OnPlayingFrame() const;
    void OnLevelEmblem(int character, int level, int mission);
    LastStoryState lastStoryState = LastStoryNotStarted;

private:
    Randomizer& _randomizer;
    mutable std::map<int, LocationData> _checkData;
};
