#include "GameStatus.h"

GameStatus::GameStatus()
{
    unlock = UnlockStatus();
    levels = LevelStatus();
    bosses = BossesStatus();
    chao = ChaoStatus();
    missions = MissionStatus();
    visitedLevels = VisitedLevels();
}
