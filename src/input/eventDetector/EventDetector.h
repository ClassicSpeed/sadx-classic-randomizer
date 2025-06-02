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


class EventDetector
{
public:
    static EventDetector& Init(Options& options, Settings& settings, Randomizer& randomizer)
    {
        if (_instance == nullptr)
            _instance = new EventDetector(options, settings, randomizer);
        return *_instance;
    }

    bool IsTargetableCheck(const LocationData& location) const;
    void OnFrame() const;
    void OnLevelEmblem(int character, int level, int mission);
    void OnGenericEmblem(int index);
    void OnTwinkleCircuitCompleted(int character);
    void ShuffleSong();

    Options& options;
    Settings& settings;
    Randomizer& randomizer;

    LastStoryState lastStoryState = LastStoryNotStarted;
    std::vector<CapsuleLocationData> capsules;
    std::vector<EnemyLocationData> enemies;
    mutable std::map<int, LocationData> checkData;
    mutable std::vector<ArrowTarget> possibleChecks;
    float deathDetectionCooldown = 0.5f;
    std::clock_t deathCooldownTimer = -1;

    int lastRealSongId = -1;
    int lastShuffledSongId = -1;


  

private:
    explicit EventDetector(Options& options, Settings& settings, Randomizer& randomizer);
    inline static EventDetector* _instance = nullptr;
};
