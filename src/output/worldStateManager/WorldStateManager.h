#pragma once

#include "../../pch.h"
#include <algorithm>
#include "../../configuration/options/Options.h"
#include "../../configuration/gameStatus/GameStatus.h"
#include "../../application/structs/LevelEntrances.h"
#include "../../application/structs/VisitedLevels.h"


constexpr float CROSS_SIZE_MIN = 4.0;
constexpr float CROSS_SIZE_MAX = 12.0;
constexpr float CROSS_SIZE_DIFF = CROSS_SIZE_MAX - CROSS_SIZE_MIN;


constexpr float ARROW_SIZE_MAX = 10.0;
constexpr float ARROW_SIZE_MIN = 10.0;

constexpr double MIN_DRAW_DOOR_ARROW_DISTANCE = 50.0;
constexpr double MAX_DRAW_DOOR_ARROW_DISTANCE = 100.0;


struct LevelArrow
{
    LevelAndActIDs levelAndAct;
    NJS_POINT3 postion;
    float angle;
    Levels entrance;
    std::vector<Characters> characters;

    bool isForCharacter(const Characters characterToFind)
    {
        return std::find(characters.begin(), characters.end(), characterToFind) != characters.end();
    }
};


class WorldStateManager : public IOnFrame
{
public:
    static WorldStateManager& Init(Options& options, Settings& settings, GameStatus& gameStatus)
    {
        if (_instance == nullptr)
            _instance = new WorldStateManager(options, settings,gameStatus);
        return *_instance;
    }

    void OnFrame() override;

    void SetEventFlags(std::vector<StoryFlags> storyFlags);
    void UnlockSuperSonic();
    void UpdateChecks(const std::map<int, LocationData>& checkData);
    void DrawDisableDoorIndicator(NJS_POINT3 basePoint, float angle);
    void DrawCorrectDoorIndicator(NJS_POINT3 basePoint, float angle);
    void DrawOtherDoorIndicator(NJS_POINT3 basePoint, float angle);
    void ShowLevelEntranceArrows();
    void SetStartingArea();
    void MarkBlacklistedMissionsAsCompleted(const std::vector<int>& missionBlacklist);
    void UpdateLevelEntrances(LevelEntrances levelEntrances);
    VisitedLevels GetVisitedLevels(int visitedLevel);
    Options& options;
    Settings& settings;
    GameStatus& gameStatus;
    VisitedLevels visitedLevels;
    LevelEntrances levelEntrances = {
        {EmeraldCoast, EmeraldCoast},
        {WindyValley, WindyValley},
        {Casinopolis, Casinopolis},
        {IceCap, IceCap},
        {TwinklePark, TwinklePark},
        {SpeedHighway, SpeedHighway},
        {RedMountain, RedMountain},
        {SkyDeck, SkyDeck},
        {LostWorld, LostWorld},
        {FinalEgg, FinalEgg},
        {HotShelter, HotShelter},
    };

private:
    explicit WorldStateManager(Options& options, Settings& settings, GameStatus& gameStatus);
    inline static WorldStateManager* _instance = nullptr;
    mutable std::map<int, LocationData> _checkData;
    NJS_COLOR _wrongDoorColor[12] = {
        {0xAAFF0000},
        {0xAAFF0000},
        {0xAAFF0000},
        {0xAAFF0000},
        {0xAAFF0000},
        {0xAAFF0000},
        {0xAAFF0000},
        {0xAAFF0000},
        {0xAAFF0000},
        {0xAAFF0000},
        {0xAAFF0000},
        {0xAAFF0000},
    };
    NJS_COLOR _arrowColor = {0xAA00FF00};

    NJS_COLOR _otherDoorColor[7] = {
        {0xAAFF4D00},
        {0xAAFF4D00},
        {0xAAFF4D00},
        {0xAAFF4D00},
        {0xAAFF4D00},
        {0xAAFF4D00},
        {0xAAFF4D00},
    };
    std::vector<LevelArrow> _levelArrows = {

        {
            LevelAndActIDs_StationSquare5, {-520, 10, 2093}, 135, EmeraldCoast,
            {Characters_Sonic, Characters_Tails, Characters_Knuckles, Characters_Amy, Characters_Big, Characters_Gamma}
        },
        {
            LevelAndActIDs_MysticRuins1, {640, 80, -143}, 145, WindyValley,
            {Characters_Sonic, Characters_Tails, Characters_Knuckles, Characters_Amy, Characters_Big, Characters_Gamma}
        },
        {
            LevelAndActIDs_StationSquare2, {-620, 12.5, 905}, 45, Casinopolis,
            {Characters_Sonic, Characters_Tails, Characters_Knuckles, Characters_Amy, Characters_Big, Characters_Gamma}
        },
        {
            LevelAndActIDs_MysticRuins2, {-1425, 53, 353}, 100, IceCap,
            {Characters_Sonic, Characters_Tails, Characters_Knuckles, Characters_Amy, Characters_Big, Characters_Gamma}
        },
        {
            LevelAndActIDs_StationSquare6, {804, 65, 1771.5f}, 90, TwinklePark,
            {Characters_Sonic, Characters_Tails, Characters_Knuckles, Characters_Amy, Characters_Big, Characters_Gamma}
        },
        {
            LevelAndActIDs_StationSquare4, {380, 20, 1370}, 90, SpeedHighway,
            {Characters_Sonic, Characters_Tails, Characters_Amy, Characters_Gamma, Characters_Big}
        },
        {
            LevelAndActIDs_StationSquare1, {270, 20, 255}, 0, SpeedHighway,
            {Characters_Knuckles}
        },
        {
            LevelAndActIDs_MysticRuins2, {-1955, -335, 1651.75f}, 268, RedMountain,
            {Characters_Sonic, Characters_Tails, Characters_Knuckles, Characters_Amy, Characters_Big, Characters_Gamma}
        },
        {
            LevelAndActIDs_EggCarrierOutside2, {0, 767, 391}, 0, SkyDeck,
            {Characters_Sonic, Characters_Tails, Characters_Amy, Characters_Big, Characters_Gamma}
        },
        {
            LevelAndActIDs_EggCarrierOutside6, {67, -54.5f, 0}, 90, SkyDeck,
            {Characters_Knuckles}
        },
        {
            LevelAndActIDs_MysticRuins3, {-516, 100, -994}, 180, LostWorld,
            {Characters_Sonic, Characters_Tails, Characters_Amy, Characters_Big, Characters_Gamma}
        },
        {
            LevelAndActIDs_MysticRuins3, {-516, 103, -1327}, 180, LostWorld,
            {Characters_Knuckles}
        },
        {
            LevelAndActIDs_MysticRuins4, {0, 124, -155}, 0, FinalEgg,
            {Characters_Gamma}
        },
        {
            LevelAndActIDs_MysticRuins4, {175, 135, -25.75}, 115, FinalEgg,
            {Characters_Sonic, Characters_Tails, Characters_Knuckles, Characters_Amy, Characters_Big}
        },
        {
            LevelAndActIDs_EggCarrierInside2, {0, 15, 245}, 0, HotShelter,
            {Characters_Sonic, Characters_Tails, Characters_Knuckles, Characters_Amy, Characters_Big, Characters_Gamma}
        },
    };
};
