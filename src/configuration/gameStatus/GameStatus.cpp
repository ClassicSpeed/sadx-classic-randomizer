#include "GameStatus.h"

GameStatus::GameStatus(Options& options): _options(options)
{
    unlock = UnlockStatus();
    levels = LevelStatus();
    bosses = BossesStatus();
    chao = ChaoStatus();
    missions = MissionStatus();
    visitedLevels = VisitedLevels();
}


void GameStatus::CheckGoalRequirements()
{
    bool levelsCompleted = true;
    bool emblemsCompleted = true;
    bool chaosEmeraldsCompleted = true;
    bool missionsCompleted = true;
    bool bossesCompleted = true;
    bool chaoRacesCompleted = true;

    if (_options.goalRequiresLevels)
        levelsCompleted = this->levels.levelsCompleted >= _options.levelGoal;

    if (_options.goalRequiresEmblems)
        emblemsCompleted = this->unlock.currentEmblems >= _options.emblemGoal;

    if (_options.goalRequiresMissions)
        missionsCompleted = this->missions.missionsCompleted >= _options.missionGoal;

    if (_options.goalRequiresChaosEmeralds)
        chaosEmeraldsCompleted = this->unlock.GotAllChaosEmeralds();

    if (_options.goalRequiresBosses)
        bossesCompleted = this->bosses.bossesCompleted >= _options.bossesGoal;

    if (_options.goalRequiresChaoRaces)
        chaoRacesCompleted = this->chao.racesCompleted >= this->chao.racesTotal;

    this->lastStoryRequirementsCompleted = levelsCompleted && emblemsCompleted && chaosEmeraldsCompleted &&
        missionsCompleted && bossesCompleted &&
        chaoRacesCompleted;
}
