#pragma once
#include <vector>

#include "../../application/Randomizer.h"
#include "../../application/structs/LocationData.h"
#include <unordered_map>

enum LastStoryState
{
    LastStoryNotStarted,
    LastStoryStarted,
    LastStoryCompleted
};

constexpr double MIN_INDICATOR_DISTANCE = 130.0;
constexpr double MAX_INDICATOR_DISTANCE = 170.0;

constexpr int INDICATOR_HEIGHT = 14;
constexpr int EXTRA_INDICATOR_HEIGHT = 20;

constexpr int HEIGHT_SIZE = 4;
constexpr int EXTRA_HEIGHT_SIZE = 6;


class EventDetector
{
public:
    explicit EventDetector(Randomizer& randomizer);
    void OnPlayingFrame() const;
    void OnLevelEmblem(int character, int level, int mission);
    void OnGenericEmblem(int index);
    void SetMultipleMissions(bool completeMultipleMissions);
    void addTaskwk(taskwk* key, int value);
    int getTaskwkValue(taskwk* key);
    LastStoryState lastStoryState = LastStoryNotStarted;
    bool completeMultipleLevelMissions = true;
    std::vector<CapsuleLocationData> capsules;
    std::vector<EnemyLocationData> enemies;
    mutable std::map<int, LocationData> checkData;
    Randomizer& randomizer;
    float deathDetectionCooldown = 0.5f;
    std::clock_t deathCooldownTimer = -1;
    
    std::unordered_map<taskwk*, int> enemyTaskMap;
};
