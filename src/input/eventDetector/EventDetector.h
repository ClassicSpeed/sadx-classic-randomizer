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
    void OnBossCompleted(int character, int level);
    void OnGenericEmblem(int index);
    void SetMultipleMissions(bool completeMultipleMissions);
    void OnLevelCompleted(short character, short level);
    void OnSublevelCompleted(short character, short level, int mission);
    LastStoryState lastStoryState = LastStoryNotStarted;
    bool completeMultipleLevelMissions = true;
    std::vector<LifeBoxLocationData> lifeCapsules;
    mutable std::map<int, LocationData> checkData;
    Randomizer& randomizer;

};
