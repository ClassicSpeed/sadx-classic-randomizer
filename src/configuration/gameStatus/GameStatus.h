#pragma once
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
    static GameStatus& Init()
    {
        if (_instance == nullptr)
            _instance = new GameStatus();
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

private:
    explicit GameStatus();
    inline static GameStatus* _instance = nullptr;
};
