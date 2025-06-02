#pragma once
#include "../../application/structs/BossesStatus.h"

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
private:
    explicit GameStatus();
    inline static GameStatus* _instance = nullptr;

};
