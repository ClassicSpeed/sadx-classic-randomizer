#include "LevelEntrances.h"


std::map<CharacterLevelKey, LevelAndActIDs> characterLevelMap = {
    {{Characters_Sonic, EmeraldCoast}, LevelAndActIDs_EmeraldCoast1},
    {{Characters_Sonic, WindyValley}, LevelAndActIDs_WindyValley1},
    {{Characters_Sonic, Casinopolis}, LevelAndActIDs_Casinopolis1},
    {{Characters_Sonic, IceCap}, LevelAndActIDs_IceCap1},
    {{Characters_Sonic, TwinklePark}, LevelAndActIDs_TwinklePark1},
    {{Characters_Sonic, SpeedHighway}, LevelAndActIDs_SpeedHighway1},
    {{Characters_Sonic, RedMountain}, LevelAndActIDs_RedMountain1},
    {{Characters_Sonic, SkyDeck}, LevelAndActIDs_SkyDeck1},
    {{Characters_Sonic, LostWorld}, LevelAndActIDs_LostWorld1},
    {{Characters_Sonic, FinalEgg}, LevelAndActIDs_FinalEgg1},

    {{Characters_Tails, WindyValley}, LevelAndActIDs_WindyValley3},
    {{Characters_Tails, Casinopolis}, LevelAndActIDs_Casinopolis2},
    {{Characters_Tails, IceCap}, LevelAndActIDs_IceCap3},
    {{Characters_Tails, SkyDeck}, LevelAndActIDs_SkyDeck1},
    {{Characters_Tails, SpeedHighway}, LevelAndActIDs_SpeedHighway1},

    {{Characters_Knuckles, SpeedHighway}, LevelAndActIDs_SpeedHighway3},
    {{Characters_Knuckles, Casinopolis}, LevelAndActIDs_Casinopolis1},
    {{Characters_Knuckles, RedMountain}, LevelAndActIDs_RedMountain3},
    {{Characters_Knuckles, LostWorld}, LevelAndActIDs_LostWorld2},
    {{Characters_Knuckles, SkyDeck}, LevelAndActIDs_SkyDeck3},

    {{Characters_Amy, TwinklePark}, LevelAndActIDs_TwinklePark2},
    {{Characters_Amy, HotShelter}, LevelAndActIDs_HotShelter1},
    {{Characters_Amy, FinalEgg}, LevelAndActIDs_FinalEgg1},

    {{Characters_Big, TwinklePark}, LevelAndActIDs_TwinklePark2},
    {{Characters_Big, IceCap}, LevelAndActIDs_IceCap4},
    {{Characters_Big, EmeraldCoast}, LevelAndActIDs_EmeraldCoast3},
    {{Characters_Big, HotShelter}, LevelAndActIDs_HotShelter1},

    {{Characters_Gamma, FinalEgg}, LevelAndActIDs_FinalEgg3},
    {{Characters_Gamma, EmeraldCoast}, LevelAndActIDs_EmeraldCoast1},
    {{Characters_Gamma, WindyValley}, LevelAndActIDs_WindyValley1},
    {{Characters_Gamma, RedMountain}, LevelAndActIDs_RedMountain2},
    {{Characters_Gamma, HotShelter}, LevelAndActIDs_HotShelter3},
};

// Define the map of characters to their accessible levels
static const std::map<short, std::vector<Levels>> CHARACTER_LEVELS = {
    {
        Characters_Sonic, {
            EmeraldCoast, WindyValley, Casinopolis, IceCap, TwinklePark, SpeedHighway, RedMountain, SkyDeck,
            LostWorld, FinalEgg
        }
    },
    {Characters_Tails, {WindyValley, Casinopolis, IceCap, SkyDeck, SpeedHighway}},
    {Characters_Knuckles, {SpeedHighway, Casinopolis, RedMountain, LostWorld, SkyDeck}},
    {Characters_Amy, {TwinklePark, HotShelter, FinalEgg}},
    {Characters_Big, {TwinklePark, IceCap, EmeraldCoast, HotShelter}},
    {Characters_Gamma, {FinalEgg, EmeraldCoast, WindyValley, RedMountain, HotShelter}}


};

LevelEntrances::LevelEntrances()
{
}

LevelEntrances::LevelEntrances(const std::initializer_list<std::pair<Levels, Levels>> pairs)
{
    for (const auto& pair : pairs)
    {
        addRelationship(pair.first, pair.second);
    }
}

void LevelEntrances::addRelationship(const Levels levelEntrance, const Levels actualLevel)
{
    _entranceToLevel[levelEntrance] = actualLevel;
    _levelToEntrance[actualLevel] = levelEntrance;
}

Levels LevelEntrances::getLevelFromEntrance(const Levels entrance) const
{
    if (_entranceToLevel.find(entrance) != _entranceToLevel.end())
        return _entranceToLevel.at(entrance);
    return entrance;
}
std::string LevelEntrances::getLevelInitialsFromEntrance(const Levels entrance) const
{
    Levels level = getLevelFromEntrance(entrance);
    switch (level)
    {
    case EmeraldCoast: return "EC";
    case WindyValley: return "WV";
    case Casinopolis: return "C ";
    case IceCap: return "IC";
    case TwinklePark: return "TP";
    case SpeedHighway: return "SH";
    case RedMountain: return "RM";
    case SkyDeck: return "SD";
    case LostWorld: return "LW";
    case FinalEgg: return "FE";
    case HotShelter: return "HS";
    default: return "??";
    }
}

LevelAndActIDs LevelEntrances::getLevelAndActIdFromEntrance(const Levels entrance, const int characters) const
{
    const Levels newLevel = getLevelFromEntrance(entrance);
    const auto it = characterLevelMap.find({characters, newLevel});
    if (it != characterLevelMap.end())
    {
        return it->second;
    }
    return LevelAndActIDs_HedgehogHammer;
}

Levels LevelEntrances::getEntranceFromLevel(const Levels level) const
{
    if (_levelToEntrance.find(level) != _levelToEntrance.end())
        return _levelToEntrance.at(level);

    return level;
}

LevelIDs LevelEntrances::getEntranceLevelIdFromLevel(const LevelIDs currentLevel) const
{
    const Levels level = ConvertLevelIDsToLevel(currentLevel);
    const Levels entrance = this->getEntranceFromLevel(level);
    return ConvertLevelsToLevelIDs(entrance);
}

bool LevelEntrances::canEnter(const Levels levelEntrance, const short currentCharacter)
{
    const auto it = CHARACTER_LEVELS.find(currentCharacter);
    if (it != CHARACTER_LEVELS.end())
    {
        const auto& levels = it->second;
        return std::find(levels.begin(), levels.end(), getLevelFromEntrance(levelEntrance)) != levels.end();
    }
    return false;
}

LevelIDs LevelEntrances::ConvertLevelsToLevelIDs(const Levels level)
{
    switch (level)
    {
    case EmeraldCoast: return LevelIDs_EmeraldCoast;
    case WindyValley: return LevelIDs_WindyValley;
    case Casinopolis: return LevelIDs_Casinopolis;
    case IceCap: return LevelIDs_IceCap;
    case TwinklePark: return LevelIDs_TwinklePark;
    case SpeedHighway: return LevelIDs_SpeedHighway;
    case RedMountain: return LevelIDs_RedMountain;
    case SkyDeck: return LevelIDs_SkyDeck;
    case LostWorld: return LevelIDs_LostWorld;
    case FinalEgg: return LevelIDs_FinalEgg;
    case HotShelter: return LevelIDs_HotShelter;
    default: return LevelIDs_HedgehogHammer;
    }
}

Levels LevelEntrances::ConvertLevelIDsToLevel(const LevelIDs levelIdS)
{
    switch (levelIdS)
    {
    case LevelIDs_EmeraldCoast: return EmeraldCoast;
    case LevelIDs_WindyValley: return WindyValley;
    case LevelIDs_Casinopolis: return Casinopolis;
    case LevelIDs_IceCap: return IceCap;
    case LevelIDs_TwinklePark: return TwinklePark;
    case LevelIDs_SpeedHighway: return SpeedHighway;
    case LevelIDs_RedMountain: return RedMountain;
    case LevelIDs_SkyDeck: return SkyDeck;
    case LevelIDs_LostWorld: return LostWorld;
    case LevelIDs_FinalEgg: return FinalEgg;
    case LevelIDs_HotShelter: return HotShelter;
    default: return EmeraldCoast; // Default case
    }
}

int LevelEntrances::transformToHex(const LevelIDs levelId)
{
    return levelId << 8;
}
