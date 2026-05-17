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

bool GameStatus::IsLevelCompleted(LevelIDs levelId, int character)
{
    if (character == Characters_Sonic)
    {
        switch (levelId)
        {
        case LevelIDs_EmeraldCoast:
            return levels.sonicEmeraldCoast;
        case LevelIDs_WindyValley:
            return levels.sonicWindyValley;
        case LevelIDs_Casinopolis:
            return levels.sonicCasinopolis;
        case LevelIDs_IceCap:
            return levels.sonicIceCap;
        case LevelIDs_TwinklePark:
            return levels.sonicTwinklePark;
        case LevelIDs_SpeedHighway:
            return levels.sonicSpeedHighway;
        case LevelIDs_RedMountain:
            return levels.sonicRedMountain;
        case LevelIDs_SkyDeck:
            return levels.sonicSkyDeck;
        case LevelIDs_LostWorld:
            return levels.sonicLostWorld;
        case LevelIDs_FinalEgg:
            return levels.sonicFinalEgg;
        case LevelIDs_Chaos0:
            return bosses.sonicChaos0;
        case LevelIDs_EggHornet:
            return bosses.sonicEggHornet;
        case LevelIDs_Chaos4:
            return bosses.sonicChaos4;
        case LevelIDs_EggViper:
            return bosses.sonicEggViper;
        case LevelIDs_Chaos6:
            return bosses.sonicChaos6;
        default:
            return false;
        }
    }
    else if (character == Characters_Tails)
    {
        switch (levelId)
        {
        case LevelIDs_WindyValley:
            return levels.tailsWindyValley;
        case LevelIDs_Casinopolis:
            return levels.tailsCasinopolis;
        case LevelIDs_IceCap:
            return levels.tailsIceCap;
        case LevelIDs_SkyDeck:
            return levels.tailsSkyDeck;
        case LevelIDs_SpeedHighway:
            return levels.tailsSpeedHighway;
        case LevelIDs_EggWalker:
            return bosses.tailsEggWalker;
        case LevelIDs_EggHornet:
            return bosses.tailsEggHornet;
        case LevelIDs_Chaos4:
            return bosses.tailsChaos4;
        default:
            return false;
        }
    }
    else if (character == Characters_Knuckles)
    {
        switch (levelId)
        {
        case LevelIDs_SpeedHighway:
            return levels.knucklesSpeedHighway;
        case LevelIDs_Casinopolis:
            return levels.knucklesCasinopolis;
        case LevelIDs_RedMountain:
            return levels.knucklesRedMountain;
        case LevelIDs_LostWorld:
            return levels.knucklesLostWorld;
        case LevelIDs_SkyDeck:
            return levels.knucklesSkyDeck;
        case LevelIDs_Chaos2:
            return bosses.knucklesChaos2;
        case LevelIDs_Chaos4:
            return bosses.knucklesChaos4;
        case LevelIDs_Chaos6:
            return bosses.knucklesChaos6;
        default:
            return false;
        }
    }
    else if (character == Characters_Amy)
    {
        switch (levelId)
        {
        case LevelIDs_TwinklePark:
            return levels.amyTwinklePark;
        case LevelIDs_HotShelter:
            return levels.amyHotShelter;
        case LevelIDs_FinalEgg:
            return levels.amyFinalEgg;
        case LevelIDs_Zero:
            return bosses.amyZero;
        default:
            return false;
        }
    }
    else if (character == Characters_Big)
    {
        switch (levelId)
        {
        case LevelIDs_TwinklePark:
            return levels.bigTwinklePark;
        case LevelIDs_IceCap:
            return levels.bigIceCap;
        case LevelIDs_EmeraldCoast:
            return levels.bigEmeraldCoast;
        case LevelIDs_HotShelter:
            return levels.bigHotShelter;
        case LevelIDs_Chaos6:
            return bosses.bigChaos6;
        default:
            return false;
        }
    }
    else if (character == Characters_Gamma)
    {
        switch (levelId)
        {
        case LevelIDs_FinalEgg:
            return levels.gammaFinalEgg;
        case LevelIDs_WindyValley:
            return levels.gammaWindyValley;
        case LevelIDs_EmeraldCoast:
            return levels.gammaEmeraldCoast;
        case LevelIDs_RedMountain:
            return levels.gammaRedMountain;
        case LevelIDs_HotShelter:
            return levels.gammaHotShelter;
        case LevelIDs_E101:
            return bosses.gammaBeta;
        case LevelIDs_E101R:
            return bosses.gammaBeta2;
        default:
            return false;
        }
    }
}
