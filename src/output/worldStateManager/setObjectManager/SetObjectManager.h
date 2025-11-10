#pragma once
#include "../../../pch.h"
#include "../../../configuration/options/Options.h"

constexpr int WARP_EGG_CARRIER_INSIDE = 35;

constexpr int WARP_STATION_SQUARE = 17;
constexpr int WARP_MYSTIC_RUINS = 6;
constexpr int WARP_EGG_CARRIER_OUTSIDE = 6;
constexpr int WARP_PAST = 10;

constexpr int COLLISION_CUBE_MYSTIC_RUINS = 42;
constexpr int WALL_THAT_PUSHES_YOU_MYSTIC_RUINS = 43;
constexpr int SCENE_CHANGE_MYSTIC_RUINS = 33;
constexpr int RED_MOUNTAIN_DOOR_MYSTIC_RUINS = 15;
constexpr int LONG_LADDER_MYSTIC_RUINS = 59;
constexpr int CAVE_WIND_CHANGE_SCENE_MYSTIC_RUINS = 31;
constexpr int EMBLEM_MYSTIC_RUINS = 65;
constexpr int WIND_STONE_MYSTIC_RUINS = 21;

constexpr int SCENE_CHANGE_STATION_SQUARE = 78;
constexpr int BEACH_GATE_STATION_SQUARE = 67;
constexpr int WALL_THAT_PUSHES_YOU_STATION_SQUARE = 93;
constexpr int BARRICADE_STATION_SQUARE = 74;

constexpr int EGG_CAP_EGG_CARRIER_OUTSIDE = 30;
constexpr int SCENE_CHANGE_EGG_CARRIER_OUTSIDE = 8;
constexpr int SCENE_CHANGE_EGG_CARRIER_INSIDE = 7;


constexpr char LEON_TIMER1 = 10;
constexpr char LEON_TIMER2 = 30;


typedef struct
{
    int x;
    int y;
    int z;
} NJS_INT_POINT3;


class SetObjectManager : public IOnFrame
{
public:
    static SetObjectManager& Init(Options& options, Settings& settings)
    {
        if (_instance == nullptr)
            _instance = new SetObjectManager(options, settings);
        return *_instance;
    }

    void OnFrame() override;

private:
    explicit SetObjectManager(Options& options, Settings& settings);
    inline static SetObjectManager* _instance = nullptr;
    Options& _options;
    Settings& _settings;

    static void AddSetToLevel(const SETEntry& newSetEntry, LevelAndActIDs levelAndAct, Characters character);
    void SetStartingArea();

    inline static FunctionHook<void> _countSetItemsMaybeHook{0x0046BD20};
    static void OnCountSetItemsMaybe();

    inline static FunctionHook<void, task*> _collisionCubeHook{0x4D47E0};
    static void OnCollisionCube(task* tp);

    inline static FunctionHook<void, task*> _collisionCylinderHook{0x4D4770};
    static void OnCollisionCylinder(task* tp);

    inline static FunctionHook<BOOL> _isChaos2DoorOpenHook{0x638D50};
    static BOOL OnIsChaos2DoorOpen();

    inline static FunctionHook<void, taskwk*> _getEntranceMRuinsHook{0x530790};
    static void OnGetEntranceMRuins(taskwk* twp);

    inline static FunctionHook<void, EntityData1*> _getEntranceEggCarrierHook{0x52D820};
    static void OnGetEntranceEggCarrier(EntityData1* a1);

    inline static FunctionHook<void, taskwk*> _getEntrancePastHook{0x542180};
    static void OnGetEntrancePast(taskwk* twp);

    inline static FunctionHook<void, Sint8> _setTimeOfDayHook{0x412C00};
    static void OnSetTimeOfDay(Sint8 time);

    inline static FunctionHook<void> _adventureSetLevelAndActHook{0x4133E0};
    static void OnAdventureSetLevelAndAct();

    inline static FunctionHook<Sint32> _prepareLevelHook{0x415210};
    static Sint32 OnPrepareLevel();

    inline static FunctionHook<void, task*> _emblemMainHook{0x4B4940};
    static void OnEmblemMain(task* tp);

    inline static FunctionHook<void> _missionSetLoadHook{0x591A70};
    static void OnMissionSetLoad();

    inline static FunctionHook<Sint32> _finishedLevelMaybeHook{0x414090};
    static Sint32 OnFinishedLevelMaybe();

    inline static FunctionHook<void> _bigHudDrawWeightAndLifeHook{0x46FB00};
    static void OnBigHudDrawWeightAndLife();

    inline static FunctionHook<BOOL> _isFinalEggTowerActiveHook{0x538550};
    static BOOL OnIsFinalEggTowerActive();

    inline static FunctionHook<BOOL> _isFinalEggDoorActiveHook{0x53EDF0};
    static BOOL OnIsFinalEggDoorActive();


    static int __cdecl OnTwinkleCircuitDoor(char character);
    static void __cdecl OnFinalEggDoorCheckA(int a1);
    static int16_t __cdecl OnFinalEggDoorCheckB(int a1);
    static void __cdecl OnLostWorldEntranceCollision(int a1);

    static bool __cdecl HandleHedgehogHammer();
    static void __cdecl HandleWarp();


    inline DataPointer(int16_t, _eggCarrierSunk, 0x3C62394);
};

inline SETEntry CreateSetEntry(const int16_t objectType, const NJS_VECTOR& position,
                               const NJS_INT_POINT3 rotation = {0, 0, 0},
                               const NJS_VECTOR& scale = {1, 1, 1})
{
    SETEntry setEntry;
    setEntry.ObjectType = objectType;
    setEntry.XRotation = rotation.x;
    setEntry.YRotation = rotation.y;
    setEntry.ZRotation = rotation.z;
    setEntry.Position = position;
    setEntry.Properties = scale;
    return setEntry;
}


const SETEntry FINAL_EGG_SPRING = CreateSetEntry(1, {-52.21f, -3240.81f, -190.0f});
const SETEntry SEWERS_SPRING = CreateSetEntry(1, {505, -89, 635},
                                              {0, 0, 0}, {0.3f, 0, 51});
const SETEntry SEWERS_SPRING_BIG = CreateSetEntry(2, {505, -89, 635},
                                                  {0, 0, 0}, {0.1f, 1.2f, 0});
const SETEntry EXTRA_SEWERS_SPRING = CreateSetEntry(2, {350, -115, 860},
                                                    {0, 0, 0xE000}, {0, 0, 0});

const SETEntry RED_MOUNTAIN_SCENE_CHANGE_MR = CreateSetEntry(SCENE_CHANGE_MYSTIC_RUINS, {-2100, -304, 1650},
                                                             {0, 0, 0}, {40, 50, 0});

const SETEntry ICE_CAP_SCENE_CHANGE_MR = CreateSetEntry(SCENE_CHANGE_MYSTIC_RUINS, {-1450, 95, 360},
                                                        {1, 0, 0}, {20, 5, 0});
const SETEntry ICE_CAP_LADDER_MR = CreateSetEntry(LONG_LADDER_MYSTIC_RUINS, {-1450, 40, 360},
                                                  {0, 0XC800, 0}, {0, 0, 0});

const SETEntry CAVE_WIND_CHANGE_SCENE_MR = CreateSetEntry(CAVE_WIND_CHANGE_SCENE_MYSTIC_RUINS, {-727, 168, 744});

const SETEntry WIND_STONE_MR = CreateSetEntry(WIND_STONE_MYSTIC_RUINS, {1392.39f, 191, 863.86f},
                                              {0xFF57, 0x8220, 0xF920}, {1, 0, 0});

const SETEntry RED_MOUNTAIN_DOOR_MR = CreateSetEntry(RED_MOUNTAIN_DOOR_MYSTIC_RUINS, {-1960.7f, -350.19f, 1652.01f},
                                                     {0x1, 0xBEFB, 0xFF6E}, {0.3f, 0, 0});

const SETEntry ICE_CAP_SPRING = CreateSetEntry(1, {-1070, -35, 236},
                                               {0, 0, 0}, {0.3f, -1.25f, 1});

const SETEntry BEACH_GATE_SS = CreateSetEntry(BEACH_GATE_STATION_SQUARE, {-525, -10, 2098},
                                              {0, 0x2000, 0});

const SETEntry CITY_HALL_SCENE_CHANGE_SS = CreateSetEntry(SCENE_CHANGE_STATION_SQUARE, {270, -1, 234},
                                                          {0, 0, 0X402}, {8, 3.2f, 0});

const SETEntry CITY_HALL_SEWERS_SCENE_CHANGE_SS = CreateSetEntry(SCENE_CHANGE_STATION_SQUARE, {367, -50, 961},
                                                                 {0, 0, 0X1A02}, {2, 2, 2});

//Egg Carrier
const SETEntry EGG_CARRIER_TRANSFORM_AREA_SPRING = CreateSetEntry(1, {-83.42f, 0, 0.54f});

//Station Square Bosses
const SETEntry WARP_CHAOS0 = CreateSetEntry(WARP_STATION_SQUARE, {270, 0, 450});

const SETEntry WARP_EGG_WALKER = CreateSetEntry(WARP_STATION_SQUARE, {-400, -3, 955});


//Mystic Ruins Bosses
const SETEntry WARP_EGG_HORNET = CreateSetEntry(WARP_MYSTIC_RUINS, {950, 127, 950});

const SETEntry WARP_CHAOS4 = CreateSetEntry(WARP_MYSTIC_RUINS, {80, 72, 180});

const SETEntry WARP_EGG_VIPER = CreateSetEntry(WARP_MYSTIC_RUINS, {0, 0, 0});

const SETEntry WARP_E101 = CreateSetEntry(WARP_MYSTIC_RUINS, {0, 0, 0});

//Egg Carrier Bosses
const SETEntry WARP_CHAOS6 = CreateSetEntry(WARP_EGG_CARRIER_OUTSIDE, {0, 750.5f, -385.69f});

const SETEntry WARP_ZERO = CreateSetEntry(WARP_EGG_CARRIER_OUTSIDE, {0, 750.5f, -385.69f});

const SETEntry WARP_E101_MK2 = CreateSetEntry(WARP_EGG_CARRIER_OUTSIDE, {0, 750.5f, -385.69f});

//Sky Chase
const SETEntry WARP_SKY_CHASE_1_WITHOUT_RUNWAY = CreateSetEntry(WARP_MYSTIC_RUINS, {1561, 191, 900}, {0, 0x1C00, 0});
const SETEntry WARP_SKY_CHASE_1_WITH_RUNWAY = CreateSetEntry(WARP_MYSTIC_RUINS, {1561, 201, 900}, {0, 0x1C00, 0});
const SETEntry WARP_SKY_CHASE_2_EC1 = CreateSetEntry(WARP_EGG_CARRIER_OUTSIDE, {0, 700, -1100});
const SETEntry WARP_SKY_CHASE_2_EC2 = CreateSetEntry(WARP_EGG_CARRIER_OUTSIDE, {0, 650, -1100});

//Past
const SETEntry WARP_TO_PAST = CreateSetEntry(WARP_MYSTIC_RUINS, {-2.5f, -240, 2397.5f});
const SETEntry WARP_TO_PAST_2 = CreateSetEntry(WARP_MYSTIC_RUINS, {-667, 90.5f, -1181});
const SETEntry WARP_FROM_PAST = CreateSetEntry(WARP_PAST, {0, 7, 247.5f});
const SETEntry WARP_FROM_PAST_2 = CreateSetEntry(WARP_PAST, {-151.5f, 300, 0});

// Adventure Field Randomization
const SETEntry SS_MAIN_BARRICADE_SS = CreateSetEntry(BARRICADE_STATION_SQUARE, {443, 1, 1077},
                                                     {0, 0x5000, 0});
const SETEntry CITY_HALL_BARRICADE_SS = CreateSetEntry(BARRICADE_STATION_SQUARE, {622.61f, 0, 875});
const SETEntry CITY_HALL_BARRICADE_WALL_SS = CreateSetEntry(WALL_THAT_PUSHES_YOU_STATION_SQUARE, {622.61f, 0, 878},
                                                            {0, 0x8000, 0}, {60, 50, 0});


const SETEntry EXTRA_WALL_FROM_ANGEL_ISLAND_MR = CreateSetEntry(WALL_THAT_PUSHES_YOU_MYSTIC_RUINS,
                                                                {-22.44872f, 12.040001f, 11.618795f},
                                                                {0xFE7CA, 0xFCDE6, 0xFE8E}, {100, 50, 5});
const SETEntry EGG_CAP_EC = CreateSetEntry(EGG_CAP_EGG_CARRIER_OUTSIDE, {-79.92f, 51, 0.04f},
                                           {0x8000, 0, 0});

const SETEntry SCENE_CHANGE_CAPTAIN_ROOM_EC = CreateSetEntry(SCENE_CHANGE_EGG_CARRIER_OUTSIDE, {-80, 63, 0},
                                                             {0x4, 0x2E8F, 0}, {18, 27, 0});

const SETEntry FINAL_EGG_TO_EC_MR = CreateSetEntry(SCENE_CHANGE_MYSTIC_RUINS, {0, 16, -211.69},
                                                   {5, 0, 0}, {20, 20, 0});


const SETEntry SCENE_CHANGE_LEFT_DOOR_EC = CreateSetEntry(SCENE_CHANGE_EGG_CARRIER_INSIDE, {86, -3, 216},
                                                          {0x32, 0, 1}, {21, 19, 0});
