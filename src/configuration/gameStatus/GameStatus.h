#pragma once
#include "../options/Options.h"
#include "status/BossesStatus.h"
#include "status/LevelStatus.h"
#include "status/UnlockStatus.h"
#include "status/ChaoStatus.h"
#include "status/MissionStatus.h"
#include "status/VisitedLevels.h"
#include "sanity/FishSanity.h"
#include "sanity/EnemySanity.h"
#include "sanity/CapsuleSanity.h"


class GameStatus
{
public:
    static GameStatus& Init(Options& options)
    {
        if (_instance == nullptr)
            _instance = new GameStatus(options);
        return *_instance;
    }

    BossesStatus bosses;
    LevelStatus levels;
    UnlockStatus unlock;
    ChaoStatus chao;
    MissionStatus missions;
    VisitedLevels visitedLevels;
    FishSanity fishSanity;
    EnemySanity enemySanity;
    CapsuleSanity capsuleSanity;

    void CheckGoalRequirements();
    bool lastStoryRequirementsCompleted = false;

private:
    explicit GameStatus(Options& options);
    inline static GameStatus* _instance = nullptr;
    Options& _options;
};
