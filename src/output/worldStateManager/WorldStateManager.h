#pragma once

#include "../../pch.h"
#include <algorithm>
#include "../../configuration/options/Options.h"
#include "../../configuration/gameStatus/GameStatus.h"
#include "../../application/structs/LevelEntrances.h"
#include "doorIndicatorManager/DoorIndicatorManager.h"
#include "setObjectManager/SetObjectManager.h"


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
            _instance = new WorldStateManager(options, settings, gameStatus);
        return *_instance;
    }

    void OnFrame() override;
    void UpdateLevelEntrances();
    void UpdateVisitedLevels(int visitedLevel);

private:
    explicit WorldStateManager(Options& options, Settings& settings, GameStatus& gameStatus);
    inline static WorldStateManager* _instance = nullptr;
    Options& _options;
    Settings& _settings;
    GameStatus& _gameStatus;
    DoorIndicatorManager& _doorIndicatorManager;
    SetObjectManager& _setObjectManager;
    void ShowLevelEntranceArrows();
    LevelEntrances _levelEntrances = {
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

    static void __cdecl OnSceneChangeMr(int newScene);
    static int __cdecl OnTwinkleParkDoor(char character);
    static int __cdecl OnEggCarrierEggDoor(int a1);
    static int __cdecl OnEggCarrierOutsideDoor(int a1);
    static void __cdecl OnSceneChangeEcInside(int a1, int a2);
    static void __cdecl OnSceneChangeEcOutside(int a1);
    static int __cdecl OnSkyDeckDoor(EntityData1* a1);

    static void __cdecl HandleWindyValleyEntrance();


    inline DataPointer(int, _showExitMenuTwinkleCircuit, 0x3C5D430);
    inline DataArray(int16_t, _chaoStatValues, 0x8895C8, 0x402);
    inline FunctionPointer(int, _isMonkeyDead, (int a1), 0x53F920);


    inline static FunctionHook<void, task*> _collisionCubeHook{0x4D47E0};
    static void OnCollisionCube(task* tp);

    inline static FunctionHook<BOOL> _isStationDoorOpenHook{0x63AB70};
    static BOOL OnIsStationDoorOpen();

    inline static FunctionHook<BOOL> _isHotelDoorOpenHook{0x630900};
    static BOOL OnIsHotelDoorOpen();

    inline static FunctionHook<BOOL> _isCasinoHotelDoorOpenHook{0x630970};
    static BOOL OnIsCasinoHotelDoorOpen();

    inline static FunctionHook<BOOL> _isCasinoStationDoorOpenHook{0x638880};
    static BOOL OnIsCasinoStationDoorOpen();

    inline static FunctionHook<void, task*> _mysticRuinsKeyHook{0x532400};
    static void OnMysticRuinsKey(task* tp);

    inline static FunctionHook<void, task*> _employeeCardHook{0x63C370};
    static void OnEmployeeCard(task* tp);

    inline static FunctionHook<void, task*> _setStartPosReturnToFieldHook{0x414500};
    static void OnSetStartPosReturnToField(task* tp);

    inline static FunctionHook<void, task*> _sceneChangeMainStationSquareHook{0x640850};
    static void OnSceneChangeMainStationSquare(task* tp);

    inline static FunctionHook<void, Uint8, Uint8> _setNextLevelAndActCutsceneModeHook{0x4145D0};
    static void OnSetNextLevelAndActCutsceneMode(Uint8 level, Uint8 act);

    inline static FunctionHook<void, task*> _twinkleCircuitResultsMaybeHook{0x4DAFB0};
    static void OnTwinkleCircuitResultsMaybe(task* tp);

    inline static FunctionHook<BOOL> _isEmeraldCoastOpenHook{0x639A30};
    static BOOL OnIsEmeraldCoastOpen();

    inline static FunctionHook<void, task*> _loadEmeraldCoastGateTargetsHook{0x63A0C0};
    static void OnLoadEmeraldCoastGateTargets(task* tp);

    inline static FunctionHook<BOOL> _isWindyValleyOpenHook{0x536E40};
    static BOOL OnIsWindyValleyOpen();

    inline static FunctionHook<BOOL> _isCasinoOpenHook{0x6383E0};
    static BOOL OnIsCasinoOpen();

    inline static FunctionHook<BOOL> _isSpeedHighwayShutterOpenHook{0x63A2A0};
    static BOOL OnIsSpeedHighwayShutterOpen();

    inline static FunctionHook<void, task*> _loadSpeedHighwayShutterHook{0x63A530};
    static void OnLoadSpeedHighwayShutter(task* tp);

    inline static FunctionHook<void, task*> _loadSpeedHighwayShutter2Hook{0x63A500};
    static void OnLoadSpeedHighwayShutter2(task* tp);

    inline static FunctionHook<void, ObjectMaster*> _oHighEleHook{0x6393F0};
    static void OnOHighEle(ObjectMaster* tp);

    inline static FunctionHook<BOOL> _isCityHallDoorOpenHook{0x636BF0};
    static BOOL OnIsCityHallDoorOpen();

    inline static FunctionHook<void, task*> _loadBarricadeHook{0x637580};
    static void OnLoadBarricade(task* tp);

    inline static FunctionHook<BOOL, EntityData1*> _isFinalEggGammaDoorOpenHook{0x53ED30};
    static BOOL OnIsFinalEggGammaDoorOpen(EntityData1* entity);

    inline static FunctionHook<void, task*> _loadSceneChangeMrHook{0x5394F0};
    static void OnLoadSceneChangeMr(task* tp);

    inline static FunctionHook<BOOL> _isLostWorldBackEntranceOpenHook{0x53B6C0};
    static BOOL OnIsLostWorldBackEntranceOpen();

    inline static FunctionHook<BOOL> _isLostWorldFrontEntranceOpenHook{0x532E60};
    static BOOL OnIsLostWorldFrontEntranceOpen();

    inline static FunctionHook<BOOL> _isAngelIslandOpenHook{0x534570};
    static BOOL OnIsAngelIslandOpen();

    inline static FunctionHook<BOOL, int> _isMonkeyDoorOpenHook{0x53E5D0};
    static BOOL OnIsMonkeyDoorOpen(int a1);

    inline static FunctionHook<void, task*> _loadMonkeyCageHook{0x540730};
    static void OnLoadMonkeyCage(task* tp);

    inline static FunctionHook<void, task*> _loadLongLadderMrHook{0x536CB0};
    static void OnLoadLongLadderMr(task* tp);

    inline static FunctionHook<BOOL, int> _preventKeyStoneFromSpawningHook{0x53C630};
    static BOOL OnPreventKeyStoneFromSpawning(int a1);

    inline static FunctionHook<void, task*> _loadPoolWaterHook{0x51DC30};
    static void OnLoadPoolWater(task* tp);

    inline static FunctionHook<void, task*> _loadPoolDoorHook{0x51E320};
    static void OnLoadPoolDoor(task* tp);
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
