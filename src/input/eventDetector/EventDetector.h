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

struct ArrowTarget
{
    NJS_POINT3 point;
    LocationType type;
};

constexpr double MIN_ARROW_DISTANCE = 300.0;
constexpr double MAX_ARROW_DISTANCE = 1000.0;

constexpr double ARROW_HEIGHT = 2.5;
constexpr double EXTRA_ARROW_HEIGHT = 2.5;
constexpr double ARROW_BASE_WIDTH = 1.25;
constexpr double EXTRA_BASE_WIDTH = 1.25;

constexpr double MIN_INDICATOR_DISTANCE = 130.0;
constexpr double MAX_INDICATOR_DISTANCE = 170.0;

constexpr int INDICATOR_HEIGHT = 15;
constexpr int EXTRA_INDICATOR_HEIGHT = 20;

constexpr int HEIGHT_SIZE = 4;
constexpr int EXTRA_HEIGHT_SIZE = 7;

constexpr int ENEMY_STARTING_ID = 10000;
constexpr int ENEMY_INVALID_ID = -1;
constexpr int ENEMY_SEARCHING_ID = -2;


enum IndicatorType
{
    EnemyIndicator,
    CapsuleIndicator,
    FishIndicator,
};

enum HomingAttackIndicator
{
    HomingAttackIndicatorDisabled = 0,
    HomingAttackIndicatorEnabled = 1,
    HomingAttackIndicatorEnabledNoSound = 2,
};

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
                           bool trackerArrowShowDistance, bool trackerArrowOverrideColor,
                           bool enemyIndicator, int enemyIndicatorColor,
                           bool capsuleIndicator, int capsuleIndicatorColor,
                           bool fishIndicator, int fishIndicatorColor,
                           bool progressionIndicator, int progressionIndicatorColor);
    void setHomingAttackIndicator(HomingAttackIndicator homingAttackIndicator);
    void OnTwinkleCircuitCompleted(int character);
    LastStoryState lastStoryState = LastStoryNotStarted;
    bool completeMultipleLevelMissions = true;
    std::vector<CapsuleLocationData> capsules;
    std::vector<EnemyLocationData> enemies;
    mutable std::map<int, LocationData> checkData;
    mutable std::vector<ArrowTarget> possibleChecks;
    Randomizer& randomizer;
    float deathDetectionCooldown = 0.5f;
    std::clock_t deathCooldownTimer = -1;
    mutable bool trackerArrow = true;
    bool trackerArrowToggleable = false;
    bool trackerArrowOverrideColor = true;
    bool trackerArrowShowDistance = true;
    bool enemyIndicator = true;
    bool capsuleIndicator = true;
    bool fishIndicator = true;
    bool progressionIndicator = true;
    HomingAttackIndicator homingAttackIndicator = HomingAttackIndicatorDisabled;



    NJS_COLOR arrowColor[6] = {
        {0xFF00FF00},
        {0xFF00FF00},
        {0xFF00FF00},
        {0xFF00FF00},
        {0xFF00FF00},
        {0xFF00FF00},
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
    NJS_COLOR fishIndicatorColor[3] = {
        {0xFFFF1400},
        {0xFFFF1400},
        {0xFFFF1400},
    };
    NJS_COLOR disabledIndicatorColor[3] = {
        {0xFF222222},
        {0xFF222222},
        {0xFF222222},
    };
    NJS_COLOR progressionItemIndicatorColor[3] = {
        {0xFFD4AF37},
        {0xFFD4AF37},
        {0xFFD4AF37},
    };
};
