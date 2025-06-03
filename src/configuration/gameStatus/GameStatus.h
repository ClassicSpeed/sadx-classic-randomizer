#pragma once
#include "../../application/structs/BossesStatus.h"
#include "../../application/structs/LevelStatus.h"
#include "../../application/structs/UnlockStatus.h"
#include "../../application/structs/ChaoStatus.h"
#include "../../application/structs/MissionStatus.h"
#include "../../application/structs/VisitedLevels.h"

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
private:
    explicit GameStatus();
    inline static GameStatus* _instance = nullptr;

};
