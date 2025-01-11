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

constexpr int INDICATOR_HEIGHT = 15;
constexpr int EXTRA_INDICATOR_HEIGHT = 20;

constexpr int HEIGHT_SIZE = 4;
constexpr int EXTRA_HEIGHT_SIZE = 7;


class EventDetector
{
public:
    explicit EventDetector(Randomizer& randomizer);
    bool IsTargetableCheck(const LocationData& location) const;
    void OnPlayingFrame() const;
    void OnLevelEmblem(int character, int level, int mission);
    void OnGenericEmblem(int index);
    void SetMultipleMissions(bool completeMultipleMissions);
    void SetSanitySettings(bool trackerArrow, int trackerArrowColor, bool trackerArrowToggleable,
                           bool enemyIndicator, int enemyIndicatorColor,
                           bool capsuleIndicator, int capsuleIndicatorColor);
    LastStoryState lastStoryState = LastStoryNotStarted;
    bool completeMultipleLevelMissions = true;
    std::vector<CapsuleLocationData> capsules;
    std::vector<EnemyLocationData> enemies;
    mutable std::map<int, LocationData> checkData;
    mutable std::vector<NJS_POINT3> possibleChecks;
    Randomizer& randomizer;
    float deathDetectionCooldown = 0.5f;
    std::clock_t deathCooldownTimer = -1;
    mutable bool trackerArrow = true;
    bool trackerArrowToggleable= true;
    bool enemyIndicator= true;
    bool capsuleIndicator= true;

    std::unordered_map<taskwk*, int> enemyTaskMap;


    NJS_COLOR arrowColor[6] = {
        {0xAA00FF00},
        {0xAA00FF00},
        {0xAA00FF00},
        {0xAA00FF00},
        {0xAA00FF00},
        {0xAA00FF00},
    };

    NJS_COLOR enemyIndicatorColor[3] = {
        {0xFFFF1400},
        {0xFFFF1400},
        {0xFFFF1400},
    };
    NJS_COLOR capsuleIndicatorColor[3] = {
        {0xFFFF1400},
        {0xFFFF1400},
        {0xFFFF1400},
    };
    NJS_COLOR disabledIndicatorColor[3] = {
        {0xFF222222},
        {0xFF222222},
        {0xFF222222},
    };
};
