#include "WorldStateManager.h"

#include <algorithm>
#include "sadx-mod-loader/SADXModLoader/include/UsercallFunctionHandler.h"

WorldStateManager* worldStateManagerPtr;


constexpr int WARP_EGG_CARRIER_INSIDE = 35;

constexpr int WARP_STATION_SQUARE = 17;
constexpr int WARP_MYSTIC_RUINS = 6;
constexpr int WARP_EGG_CARRIER_OUTSIDE = 6;
constexpr int WARP_PAST = 10;

constexpr int COLLISION_CUBE_MYSTIC_RUINS = 42;
constexpr int SCENE_CHANGE_MYSTIC_RUINS = 33;
constexpr int RED_MOUNTAIN_DOOR_MYSTIC_RUINS = 15;
constexpr int LONG_LADDER_MYSTIC_RUINS = 59;

constexpr int SCENE_CHANGE_STATION_SQUARE = 78;
constexpr int BEACH_GATE_STATION_SQUARE = 67;


// //We pretend that the egg carrier is sunk so that the hedgehog hammer is works
static bool __cdecl HandleHedgehogHammer()
{
    return GetEventFlag(EventFlags_Amy_WarriorFeather);
}

static void __cdecl HandleWarp()
{
    DisableController(0);
    if (levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_StationSquare1 && CurrentCharacter == Characters_Sonic)
        SetNextLevelAndAct_CutsceneMode(LevelIDs_Chaos0, 0);

    else if (levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_StationSquare2 && CurrentCharacter ==
        Characters_Tails)
        SetNextLevelAndAct_CutsceneMode(LevelIDs_EggWalker, 0);

    else if (levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_MysticRuins4 && CurrentCharacter == Characters_Sonic)
        SetNextLevelAndAct_CutsceneMode(LevelIDs_EggViper, 0);

    else if (levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_MysticRuins4 && CurrentCharacter == Characters_Gamma)
        SetNextLevelAndAct_CutsceneMode(LevelIDs_E101, 0);

    else if (levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_MysticRuins1 && (CurrentCharacter == Characters_Sonic
            || CurrentCharacter == Characters_Tails || CurrentCharacter == Characters_Knuckles)
        && EntityData1Ptrs[0]->Position.y < 100)
        SetNextLevelAndAct_CutsceneMode(LevelIDs_Chaos4, 0);

    else if (levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_MysticRuins1
        && (CurrentCharacter == Characters_Sonic || CurrentCharacter == Characters_Tails)
        && EntityData1Ptrs[0]->Position.y > 100 && EntityData1Ptrs[0]->Position.y < 150)
        SetNextLevelAndAct_CutsceneMode(LevelIDs_EggHornet, 0);

    else if (levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_MysticRuins1 && (CurrentCharacter == Characters_Sonic
        || CurrentCharacter == Characters_Tails) && EntityData1Ptrs[0]->Position.y > 150)
        SetNextLevelAndAct_CutsceneMode(LevelIDs_SkyChase1, 0);

    else if (CurrentLevel == LevelIDs_EggCarrierOutside && CurrentCharacter == Characters_Gamma)
        SetNextLevelAndAct_CutsceneMode(LevelIDs_E101R, 0);

    else if (CurrentLevel == LevelIDs_EggCarrierOutside && CurrentCharacter == Characters_Amy)
        SetNextLevelAndAct_CutsceneMode(LevelIDs_Zero, 0);

    else if (CurrentLevel == LevelIDs_EggCarrierOutside && EntityData1Ptrs[0]->Position.z > -500
        && (CurrentCharacter == Characters_Sonic || CurrentCharacter == Characters_Big))

        SetNextLevelAndAct_CutsceneMode(LevelIDs_Chaos6, 0);

    else if (CurrentLevel == LevelIDs_EggCarrierOutside && (CurrentCharacter == Characters_Knuckles))
        SetNextLevelAndAct_CutsceneMode(LevelIDs_Chaos6, 1);

    else if (CurrentLevel == LevelIDs_EggCarrierOutside && EntityData1Ptrs[0]->Position.z < -500
        && (CurrentCharacter == Characters_Sonic || CurrentCharacter == Characters_Tails))
        SetNextLevelAndAct_CutsceneMode(LevelIDs_SkyChase2, 0);

    else if (levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_MysticRuins2)
        SetNextLevelAndAct_CutsceneMode(LevelIDs_Past, 1);

    else if (levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_Past2)
        SetNextLevelAndAct_CutsceneMode(LevelIDs_MysticRuins, 1);

    else
        SetNextLevelAndAct_CutsceneMode(LevelIDs_ECGarden, 0);
}


//We don't create animals outside levels
//Allow us to spawn enemies in the adventure fields
FunctionHook<void, int, float, float, float> onCreateAnimal(0x4BE610, [](int e_num, float x, float y, float z)-> void
{
    if (CurrentLevel > LevelIDs_HedgehogHammer && CurrentLevel <= LevelIDs_HotShelter)
        onCreateAnimal.Original(e_num, x, y, z);
});
FunctionHook<void, task*> onCollisionCube(0x4D47E0, [](task* tp) -> void
{
    if (levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_MysticRuins2)
    {
        //We find the cube collision that prevent tails from entering the Master Emerald Shrine and delete it
        if (tp->twp->pos.x < -1070 && tp->twp->pos.x > -1080
            && tp->twp->pos.y < -210 && tp->twp->pos.y > -220
            && tp->twp->pos.z < -1030 && tp->twp->pos.z > -1050)
            FreeTask(tp);
    }
    else if (levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_Casinopolis2)
    {
        //We find the cube collision that prevent sonic from entering the life capsule path in SADX and delete it
        if (tp->twp->pos.x < 2 && tp->twp->pos.x > 0
            && tp->twp->pos.y < -1713 && tp->twp->pos.y > -1716
            && tp->twp->pos.z < 2769 && tp->twp->pos.z > 2765)
            FreeTask(tp);
    }
    else if (levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_MysticRuins1
        && worldStateManagerPtr->unlockStatus.keyDynamite)
    {
        //We find the cube collision that we created for the dynamite and delete it
        if (tp->twp->pos.x < -394 && tp->twp->pos.x > -392
            && tp->twp->pos.y < 121 && tp->twp->pos.y > 118
            && tp->twp->pos.z < 891 && tp->twp->pos.z > 889)
            FreeTask(tp);
    }

    else
        onCollisionCube.Original(tp);
});

static void __cdecl HandleSpeedHighwayEntrance();
static void __cdecl HandleWindyValleyEntrance();
UsercallFuncVoid(onSceneChangeMr_t, (int a1), (a1), 0x539220, rEBX);
static void __cdecl HandleMREntrance(int newScene);

UsercallFunc(bool, onTwinkleParkDoor_t, (char tpChar), (tpChar), 0x63EA90, rEAX, rEAX);
static bool __cdecl HandleTwinkleParkEntrance(char character);


UsercallFunc(int, onEggCarrierEggDoor_t, (int a1), (a1), 0x52B420, rEAX, rESI);
static int __cdecl HandleEggCarrierEggDoor(int tp);


UsercallFuncVoid(_onSceneChangeECInside_t, (int a1, int a2), (a1,a2), 0x52D690, rEAX, rECX);
static void __cdecl HandleSceneChangeEcInside(int a1, int a2);

UsercallFuncVoid(_onSceneChangeECOutside_t, (int a1), (a1), 0x524FE0, rEAX);
static void __cdecl HandleSceneChangeEcOutside(int a1);

UsercallFunc(bool, onSkyDeckDoor_t, (EntityData1 * a1), (a1), 0x51DEB0, rEAX, rESI);
static bool __cdecl HandleSkyDeckDoor(EntityData1* a1);


WorldStateManager::WorldStateManager()
{
    onSceneChangeMr_t.Hook(HandleMREntrance);
    onTwinkleParkDoor_t.Hook(HandleTwinkleParkEntrance);
    onEggCarrierEggDoor_t.Hook(HandleEggCarrierEggDoor);
    _onSceneChangeECInside_t.Hook(HandleSceneChangeEcInside);
    _onSceneChangeECOutside_t.Hook(HandleSceneChangeEcOutside);
    onSkyDeckDoor_t.Hook(HandleSkyDeckDoor);
    WriteCall(reinterpret_cast<void*>(0x5264C5), &HandleWarp);

    WriteCall(reinterpret_cast<void*>(0x528271), &HandleHedgehogHammer);

    WriteCall(reinterpret_cast<void*>(0x639198), &HandleSpeedHighwayEntrance);

    WriteCall(reinterpret_cast<void*>(0x537F52), &HandleWindyValleyEntrance);
    WriteCall(reinterpret_cast<void*>(0x537F64), &HandleWindyValleyEntrance);


    worldStateManagerPtr = this;

    //We allow Tails and Big to enter the Master Emerald Shrine
    DataArray(int, islandDoorFlags, 0x111E010, 8);
    islandDoorFlags[Characters_Tails] = FLAG_SONIC_MR_ISLANDDOOR;
    islandDoorFlags[Characters_Big] = FLAG_SONIC_MR_ISLANDDOOR;

    //We replace the checkpoint for a warp object from the Egg Carrier
    ObjList_SSquare[WARP_STATION_SQUARE] = ObjList_ECarrier3[WARP_EGG_CARRIER_INSIDE];
    ObjList_MRuins[WARP_MYSTIC_RUINS] = ObjList_ECarrier3[WARP_EGG_CARRIER_INSIDE];
    ObjList_ECarrier0[WARP_EGG_CARRIER_OUTSIDE] = ObjList_ECarrier3[WARP_EGG_CARRIER_INSIDE];
    ObjList_Past[WARP_PAST] = ObjList_ECarrier3[WARP_EGG_CARRIER_INSIDE];
}


void WorldStateManager::SetEventFlags(std::vector<StoryFlags> storyFlags)
{
    for (StoryFlags storyFlag : storyFlags)
    {
        SetEventFlag(static_cast<EventFlags>(storyFlag));
    }
    WriteSaveFile();
}


void WorldStateManager::UnlockSuperSonic()
{
    SetEventFlag(static_cast<EventFlags>(FLAG_SUPERSONIC_PLAYABLE));
    WriteSaveFile();
}

void WorldStateManager::UpdateOptions(const Options newOptions)
{
    this->options = newOptions;
}

void WorldStateManager::UpdateUnlockStatus(UnlockStatus newUnlockStatus)
{
    this->unlockStatus = newUnlockStatus;
}

void WorldStateManager::OnFrame()
{
    if (DemoPlaying > 0)
        return;
    if (CurrentLevel == LevelIDs_PerfectChaos)
        return;
    if (CurrentLevel >= LevelIDs_TwinkleCircuit && CurrentLevel <= LevelIDs_SandHill)
        GameMode = GameModes_Adventure_ActionStg;
    else if (GameMode == GameModes_Adventure_Field || GameMode == GameModes_Adventure_ActionStg)
        GameMode = GameModes_Mission;
}

//Enable all GameGear Games
FunctionHook<int> onHowManyGameGearGames(0x6FDA90, []()-> int
{
    return 12;
});

FunctionHook<bool> onIsGameGearMenuEnabled(0x506460, []()-> bool
{
    return true;
});

//Allow Knuckles to fight Chaos 2
FunctionHook<BOOL> isChaos2DoorOpen(0x638D50, []()-> BOOL
{
    return CurrentCharacter == Characters_Knuckles;
});

//We open the station door if we have the keys
FunctionHook<BOOL> isStationDoorOpen(0x63AB70, []()-> BOOL
{
    return worldStateManagerPtr->unlockStatus.keyStationKeys;
});

//We open the main hotel door if we have the keys
FunctionHook<BOOL> isHotelDoorOpen(0x630900, []()-> BOOL
{
    return worldStateManagerPtr->unlockStatus.keyHotelKeys;
});

//We open both casino entrances if we have the casino district keys
FunctionHook<BOOL> isCasinoHotelDoorOpen(0x630970, []()-> BOOL
{
    return worldStateManagerPtr->unlockStatus.keyCasinoKeys;
});
FunctionHook<BOOL> isCasinoStationDoorOpen(0x638880, []()-> BOOL
{
    return worldStateManagerPtr->unlockStatus.keyCasinoKeys;
});


//Prevents the recap screen from showing on the last story
FunctionHook<int, int> showRecap(0x643C00, [](int _)-> int
{
    return -1;
});

// Replace Super Sonic "Hmph" with "I'll show you what the Chaos Emeralds can really do."
FunctionHook<void, int> onPlayVoice(0x425710, [](int a1)-> void
{
    if (a1 == 396)
        return onPlayVoice.Original(388);

    return onPlayVoice.Original(a1);
});

//Prevents adding extra 10 seconds for Sonic and Tails
FunctionHook<void, int> onAddSeconds(0x426640, [](int seconds)-> void
{
    if (seconds == 10 && (CurrentCharacter == Characters_Sonic || CurrentCharacter == Characters_Tails))
        return;

    return onAddSeconds.Original(seconds);
});

//We create a custom spawn point after exiting sand hill
FunctionHook<void, EntityData1*> onGetEntranceMRuins(0x530790, [](EntityData1* a1)-> void
{
    onGetEntranceMRuins.Original(a1);
    if (LastLevel == LevelIDs_SandHill)
    {
        a1->Position.x = -1500;
        a1->Position.y = 50;
        a1->Position.z = -70;
        a1->Rotation.x = 0;
        a1->Rotation.y = 4000;
        a1->Rotation.z = 0;
    }
    else if (LastLevel == LevelIDs_Past)
    {
        a1->Position.x = -2.5f;
        a1->Position.y = -240;
        a1->Position.z = 2480;
        a1->Rotation.x = 0;
        a1->Rotation.y = 4000;
        a1->Rotation.z = 0;
    }
});

//We spawn in the middle on the runway for the transformed Egg Carrier
FunctionHook<void, EntityData1*> onGetEntranceEggCarrier(0x52D820, [](EntityData1* a1)-> void
{
    onGetEntranceEggCarrier.Original(a1);
    if (levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_EggCarrierOutside2 && LevelEntrance == 0)
    {
        a1->Position.x = 0;
        a1->Position.y = 650;
        a1->Position.z = -1000;
        a1->Rotation.x = 0;
        a1->Rotation.y = 0x4000;
        a1->Rotation.z = 0;
    }
});

//We spawn in front of the Master Emerald Shrine in the past when time traveling
FunctionHook<void, EntityData1*> onGetEntrancePast(0x542180, [](EntityData1* a1)-> void
{
    onGetEntrancePast.Original(a1);
    if (levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_Past2 && LastLevel == LevelIDs_MysticRuins)
    {
        a1->Position.x = 0;
        a1->Position.y = 10;
        a1->Position.z = 380;
        a1->Rotation.x = 0;
        a1->Rotation.y = 0x4000;
        a1->Rotation.z = 0;
    }
});

//Set starting location when we get a game over 
FunctionHook<void, Sint8> onSetTimeOfDay(0x412C00, [](Sint8 time)-> void
{
    onSetTimeOfDay.Original(time);
    if (GameState == MD_GAME_CONTINUE)
        worldStateManagerPtr->SetStartingArea();
});

//Set starting location when starting the adventure
FunctionHook<void> onAdventureSetLevelAndAct(0x4133E0, []()-> void
{
    onAdventureSetLevelAndAct.Original();
    worldStateManagerPtr->SetStartingArea();
});

void WorldStateManager::SetStartingArea()
{
    if (LastStoryFlag == 1)
        return;
    switch (this->options.GetCharacterStartingArea(static_cast<Characters>(CurrentCharacter)))
    {
    case StationSquareMain:
        SetLevelAndAct(LevelIDs_StationSquare, 3);
        break;
    case Station:
        SetLevelAndAct(LevelIDs_StationSquare, 1);
        SetEntranceNumber(0);
        break;
    case HotelArea:
        SetLevelAndAct(LevelIDs_StationSquare, 4);
        break;
    case CasinoArea:
        SetLevelAndAct(LevelIDs_StationSquare, 1);
        SetEntranceNumber(2);
        break;
    case TwinkleParkArea:
        SetLevelAndAct(LevelIDs_StationSquare, 5);
        break;
    case MysticRuinsMain:
        SetLevelAndAct(LevelIDs_MysticRuins, 0);
        break;
    case Jungle:
        SetLevelAndAct(LevelIDs_MysticRuins, 2);
        break;
    case EggCarrier:
        SetLevelAndAct(LevelIDs_EggCarrierOutside, 0);
        break;
    case AngelIsland:
        SetLevelAndAct(LevelIDs_MysticRuins, 1);
        break;
    case NoStatingArea:
        SetLevelAndAct(LevelIDs_StationSquare, 3);
        break;
    }
}

void WorldStateManager::StartAllMissions()
{
    for (int i = 0; i < 60; i++)
    {
        MissionFlags[i] |= MissionFlags_Found;
        MissionFlags[i] |= MissionFlags_Started;
    }
    WriteSaveFile();
}

void WorldStateManager::UpdateLevelEntrances(LevelEntrances levelEntrances)
{
    this->levelEntrances = levelEntrances;
}

typedef struct
{
    int x;
    int y;
    int z;
} NJS_INT_POINT3;

SETEntry CreateSetEntry(const int16_t objectType, const NJS_VECTOR& position, const NJS_INT_POINT3 rotation = {0, 0, 0},
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


void AddSetToLevel(const SETEntry& newSetEntry, const LevelAndActIDs levelAndAct, const Characters character)
{
    if (CurrentCharacter == character && levelact(CurrentLevel, CurrentAct) == levelAndAct)
    {
        SETObjData* setObjData = &SETTable[SETTable_Count];
        setObjData->Flags |= 0x8000u;

        setObjData->SETEntry = new SETEntry(newSetEntry);

        setObjData->LoadCount = 0;
        SETTable_Count += 1;
    }
}

const SETEntry FINAL_EGG_SPRING = CreateSetEntry(1, {-52.21f, -3240.81f, -190.0f});
const SETEntry SEWERS_SPRING = CreateSetEntry(1, {505, -89, 635},
                                              {0, 0, 0}, {0.3f, 0, 51});


const SETEntry COLLISION_CUBE_MR = CreateSetEntry(COLLISION_CUBE_MYSTIC_RUINS, {-393.62f, 120, 890.06f},
                                                  {0xFEFF, 0x4BF1, 0xFD6A}, {60, 80, 10});
const SETEntry RED_MOUNTAIN_SCENE_CHANGE_MR = CreateSetEntry(SCENE_CHANGE_MYSTIC_RUINS, {-2100, -304, 1650},
                                                             {0, 0, 0}, {40, 50, 0});

const SETEntry ICE_CAP_SCENE_CHANGE_MR = CreateSetEntry(SCENE_CHANGE_MYSTIC_RUINS, {-1450, 95, 360},
                                                        {1, 0, 0}, {20, 5, 0});
const SETEntry ICE_CAP_LADDER_MR = CreateSetEntry(LONG_LADDER_MYSTIC_RUINS, {-1450, 40, 360},
                                                  {0, 0XC800, 0}, {0, 0, 0});


const SETEntry RED_MOUNTAIN_DOOR_MR = CreateSetEntry(RED_MOUNTAIN_DOOR_MYSTIC_RUINS, {-1960.7f, -350.19f, 1652.01f},
                                                     {0x1, 0xBEFB, 0xFF6E}, {0.3f, 0, 0});

const SETEntry ICE_CAP_SPRING = CreateSetEntry(1, {-1070, -35, 236},
                                               {0, 0, 0}, {0.3f, -1.25f, 1});

const SETEntry BEACH_GATE_SS = CreateSetEntry(BEACH_GATE_STATION_SQUARE, {-525, -10, 2098},
                                              {0, 0x2000, 0});

const SETEntry CITY_HALL_SCENE_CHANGE_SS = CreateSetEntry(SCENE_CHANGE_STATION_SQUARE, {270, -1, 234},
                                                          {0, 0, 0X402}, {8, 3.2, 0});

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
const SETEntry WARP_SKY_CHASE_1 = CreateSetEntry(WARP_MYSTIC_RUINS, {1561, 191, 900}, {0, 0x1C00, 0});
const SETEntry WARP_SKY_CHASE_2_EC1 = CreateSetEntry(WARP_EGG_CARRIER_OUTSIDE, {0, 700, -1100});
const SETEntry WARP_SKY_CHASE_2_EC2 = CreateSetEntry(WARP_EGG_CARRIER_OUTSIDE, {0, 650, -1100});

//Past
const SETEntry WARP_TO_PAST = CreateSetEntry(WARP_MYSTIC_RUINS, {-2.5f, -240, 2397.5f});
const SETEntry WARP_FROM_PAST = CreateSetEntry(WARP_PAST, {0, 7, 247.5f});

FunctionHook<void> onCountSetItemsMaybe(0x0046BD20, []()-> void
{
    onCountSetItemsMaybe.Original();

    //Warp point
    LoadPVM("EC_ALIFE", ADV01C_TEXLISTS[3]);

    //Buyon enemy
    LoadPVM("E_BUYON", &E_BUYON_TEXLIST);

    //Cop
    LoadPVM("NISEPAT", &NISEPAT_TEXLIST);

    //Freeze trap
    LoadNoNamePVM(&stx_ice0_TEXLIST);

    AddSetToLevel(FINAL_EGG_SPRING, LevelAndActIDs_FinalEgg3, Characters_Sonic);
    AddSetToLevel(SEWERS_SPRING, LevelAndActIDs_StationSquare3, Characters_Sonic);

    AddSetToLevel(COLLISION_CUBE_MR, LevelAndActIDs_MysticRuins1, Characters_Sonic);
    AddSetToLevel(COLLISION_CUBE_MR, LevelAndActIDs_MysticRuins1, Characters_Tails);
    AddSetToLevel(COLLISION_CUBE_MR, LevelAndActIDs_MysticRuins1, Characters_Knuckles);
    AddSetToLevel(COLLISION_CUBE_MR, LevelAndActIDs_MysticRuins1, Characters_Amy);
    AddSetToLevel(COLLISION_CUBE_MR, LevelAndActIDs_MysticRuins1, Characters_Big);
    AddSetToLevel(COLLISION_CUBE_MR, LevelAndActIDs_MysticRuins1, Characters_Gamma);

    AddSetToLevel(RED_MOUNTAIN_SCENE_CHANGE_MR, LevelAndActIDs_MysticRuins2, Characters_Tails);
    AddSetToLevel(RED_MOUNTAIN_DOOR_MR, LevelAndActIDs_MysticRuins2, Characters_Tails);

    AddSetToLevel(ICE_CAP_LADDER_MR, LevelAndActIDs_MysticRuins2, Characters_Knuckles);
    AddSetToLevel(ICE_CAP_SCENE_CHANGE_MR, LevelAndActIDs_MysticRuins2, Characters_Knuckles);
    AddSetToLevel(ICE_CAP_LADDER_MR, LevelAndActIDs_MysticRuins2, Characters_Gamma);
    AddSetToLevel(ICE_CAP_SCENE_CHANGE_MR, LevelAndActIDs_MysticRuins2, Characters_Gamma);

    AddSetToLevel(ICE_CAP_SPRING, LevelAndActIDs_MysticRuins2, Characters_Amy);

    //Emerald Coast
    AddSetToLevel(BEACH_GATE_SS, LevelAndActIDs_StationSquare5, Characters_Sonic);

    //Speed Highway (City Hall)
    AddSetToLevel(CITY_HALL_SCENE_CHANGE_SS, LevelAndActIDs_StationSquare1, Characters_Big);

    if (worldStateManagerPtr->options.bossChecks)
    {
        //Station Square Bosses
        AddSetToLevel(WARP_CHAOS0, LevelAndActIDs_StationSquare1, Characters_Sonic);
        AddSetToLevel(WARP_EGG_WALKER, LevelAndActIDs_StationSquare2, Characters_Tails);

        //Mystic Ruins Bosses
        AddSetToLevel(WARP_EGG_HORNET, LevelAndActIDs_MysticRuins1, Characters_Sonic);
        AddSetToLevel(WARP_EGG_HORNET, LevelAndActIDs_MysticRuins1, Characters_Tails);

        AddSetToLevel(WARP_CHAOS4, LevelAndActIDs_MysticRuins1, Characters_Sonic);
        AddSetToLevel(WARP_CHAOS4, LevelAndActIDs_MysticRuins1, Characters_Tails);
        AddSetToLevel(WARP_CHAOS4, LevelAndActIDs_MysticRuins1, Characters_Knuckles);

        AddSetToLevel(WARP_EGG_VIPER, LevelAndActIDs_MysticRuins4, Characters_Sonic);
        AddSetToLevel(WARP_E101, LevelAndActIDs_MysticRuins4, Characters_Gamma);

        //Egg Carrier Bosses
        AddSetToLevel(WARP_CHAOS6, LevelAndActIDs_EggCarrierOutside1, Characters_Sonic);
        AddSetToLevel(WARP_CHAOS6, LevelAndActIDs_EggCarrierOutside2, Characters_Sonic);

        AddSetToLevel(WARP_CHAOS6, LevelAndActIDs_EggCarrierOutside1, Characters_Knuckles);
        AddSetToLevel(WARP_CHAOS6, LevelAndActIDs_EggCarrierOutside2, Characters_Knuckles);

        AddSetToLevel(WARP_CHAOS6, LevelAndActIDs_EggCarrierOutside1, Characters_Big);
        AddSetToLevel(WARP_CHAOS6, LevelAndActIDs_EggCarrierOutside2, Characters_Big);

        AddSetToLevel(WARP_ZERO, LevelAndActIDs_EggCarrierOutside1, Characters_Amy);
        AddSetToLevel(WARP_ZERO, LevelAndActIDs_EggCarrierOutside2, Characters_Amy);

        AddSetToLevel(WARP_E101_MK2, LevelAndActIDs_EggCarrierOutside1, Characters_Gamma);
        AddSetToLevel(WARP_E101_MK2, LevelAndActIDs_EggCarrierOutside2, Characters_Gamma);
    }
    if (worldStateManagerPtr->options.skyChaseChecks)
    {
        //Sky Chase
        AddSetToLevel(WARP_SKY_CHASE_1, LevelAndActIDs_MysticRuins1, Characters_Sonic);
        AddSetToLevel(WARP_SKY_CHASE_1, LevelAndActIDs_MysticRuins1, Characters_Tails);

        AddSetToLevel(WARP_SKY_CHASE_2_EC1, LevelAndActIDs_EggCarrierOutside1, Characters_Sonic);
        AddSetToLevel(WARP_SKY_CHASE_2_EC2, LevelAndActIDs_EggCarrierOutside2, Characters_Sonic);

        AddSetToLevel(WARP_SKY_CHASE_2_EC1, LevelAndActIDs_EggCarrierOutside1, Characters_Tails);
        AddSetToLevel(WARP_SKY_CHASE_2_EC2, LevelAndActIDs_EggCarrierOutside2, Characters_Tails);
    }

    //Time Travel 
    AddSetToLevel(WARP_TO_PAST, LevelAndActIDs_MysticRuins2, Characters_Sonic);
    AddSetToLevel(WARP_TO_PAST, LevelAndActIDs_MysticRuins2, Characters_Tails);
    AddSetToLevel(WARP_TO_PAST, LevelAndActIDs_MysticRuins2, Characters_Knuckles);
    AddSetToLevel(WARP_TO_PAST, LevelAndActIDs_MysticRuins2, Characters_Amy);
    AddSetToLevel(WARP_TO_PAST, LevelAndActIDs_MysticRuins2, Characters_Gamma);
    AddSetToLevel(WARP_TO_PAST, LevelAndActIDs_MysticRuins2, Characters_Big);

    AddSetToLevel(WARP_FROM_PAST, LevelAndActIDs_Past2, Characters_Sonic);
    AddSetToLevel(WARP_FROM_PAST, LevelAndActIDs_Past2, Characters_Tails);
    AddSetToLevel(WARP_FROM_PAST, LevelAndActIDs_Past2, Characters_Knuckles);
    AddSetToLevel(WARP_FROM_PAST, LevelAndActIDs_Past2, Characters_Amy);
    AddSetToLevel(WARP_FROM_PAST, LevelAndActIDs_Past2, Characters_Gamma);
    AddSetToLevel(WARP_FROM_PAST, LevelAndActIDs_Past2, Characters_Big);
});


// We move the emblem a little higher so Cream can get it.
FunctionHook<void, task*> onEmblemMain(0x4B4940, [](task* tp)-> void
{
    if (levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_StationSquare1)
        if (tp->twp->pos.x > 386 && tp->twp->pos.x < 390
            && tp->twp->pos.y > -6 && tp->twp->pos.y < -5
            && tp->twp->pos.z > 489 && tp->twp->pos.z < 492)
        {
            tp->twp->pos.y = -4;
        }

    onEmblemMain.Original(tp);
});

FunctionHook<void> onMissionSetLoad(0x591A70, []()-> void
{
    if (!worldStateManagerPtr->options.missionModeEnabled)
        return;

    onMissionSetLoad.Original();

    for (int i = 0; i < MissionSetCount; ++i)
    {
        const SETObjData* objData = &MissionSETTable[i];
        if (objData->SETEntry != nullptr)
        {
            const NJS_VECTOR position = objData->SETEntry->Position;
            //We move the mission switch from Big's bed
            if (levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_MysticRuins3 && position.x > 1294 && position.x <
                1298 && position.y > 130 && position.y < 133 && position.z > -729 && position.z < -726)
            {
                objData->SETEntry->Position = {1333, 120, -707};
            }
            //We move the mission card in the sewer, so it doesn't clip with the srping
            if (levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_StationSquare3 && position.x > 506 && position.x <
                507 && position.y > -89 && position.y < -88 && position.z > 635 && position.z < 636)
            {
                objData->SETEntry->Position = {position.x, -70, position.z};
            }
        }
    }
});


//Hook to change the level after beating the boss
FunctionHook<Sint32> onFinishedLevelMaybe(0x414090, []()-> Sint32
{
    const Sint32 response = onFinishedLevelMaybe.Original();
    if (GameState != MD_GAME_END)
        return response;


    if (CurrentLevel == LevelIDs_Chaos0)
    {
        SetNextLevelAndAct(LevelIDs_StationSquare, 0);
        SetEntranceNumber(0);
    }
    else if (CurrentLevel == LevelIDs_Chaos2)
    {
        SetNextLevelAndAct(LevelIDs_StationSquare, 4);
        SetEntranceNumber(5);
    }
    else if (CurrentLevel == LevelIDs_Chaos4)
    {
        SetNextLevelAndAct(LevelIDs_MysticRuins, 0);
        SetEntranceNumber(5);
    }
    else if (CurrentLevel == LevelIDs_Chaos6 || CurrentLevel == LevelIDs_Zero
        || CurrentLevel == LevelIDs_E101R || CurrentLevel == LevelIDs_SkyChase2)
    {
        SetEntranceNumber(0);
        SetNextLevelAndAct(LevelIDs_EggCarrierOutside, LastAct);
    }
    else if (CurrentLevel == LevelIDs_EggHornet || CurrentLevel == LevelIDs_SkyChase1)
    {
        SetNextLevelAndAct(LevelIDs_MysticRuins, 0);
        SetEntranceNumber(0);
    }
    else if (CurrentLevel == LevelIDs_EggWalker)
    {
        SetNextLevelAndAct(LevelIDs_StationSquare, 1);
        SetEntranceNumber(1);
    }
    else if (CurrentLevel == LevelIDs_EggViper || CurrentLevel == LevelIDs_E101)
    {
        SetNextLevelAndAct(LevelIDs_MysticRuins, 3);
        SetEntranceNumber(3);
    }
    return response;
});

FunctionHook<void, task*> onMysticRuinsKey(0x532400, [](task* tp)-> void
{
    // We prevent the wind stone from spawning if the player doesn't have the item
    if (levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_MysticRuins1
        && (!worldStateManagerPtr->unlockStatus.keyWindStone
            || !worldStateManagerPtr->levelEntrances.canEnter(WindyValley, CurrentCharacter)))
        if (tp->twp->pos.x > 1390 && tp->twp->pos.x < 1395
            && tp->twp->pos.y > 190 && tp->twp->pos.y < 193
            && tp->twp->pos.z > 862 && tp->twp->pos.z < 865)
            return;
    // We don't spawn the golden/silver keys for knuckles if he can enter LostWorld
    if (levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_MysticRuins3 && CurrentCharacter == Characters_Knuckles)
    {
        if (!worldStateManagerPtr->levelEntrances.canEnter(LostWorld, CurrentCharacter))
            return;
    }
    onMysticRuinsKey.Original(tp);
});

// We make Big's hud think we are not in the mission mode
FunctionHook<void> onBigHud_DrawWeightAndLife(0x46FB00, []()-> void
{
    const GameModes bufferGameMode = GameMode;
    if (CurrentLevel >= LevelIDs_StationSquare && CurrentLevel <= LevelIDs_Past)
        GameMode = GameModes_Adventure_Field;
    else
        GameMode = GameModes_Adventure_ActionStg;
    onBigHud_DrawWeightAndLife.Original();
    GameMode = bufferGameMode;
});


// Handles the return position
FunctionHook<void, task*> onSetStartPosReturnToField(0x414500, [](task* tp)-> void
{
    if (CurrentLevel < LevelIDs_EmeraldCoast || CurrentLevel > LevelIDs_HotShelter)
    {
        onSetStartPosReturnToField.Original(tp);
        return;
    }

    const short buffer = CurrentLevel;
    CurrentLevel = worldStateManagerPtr->levelEntrances.
                                         getEntranceLevelIdFromLevel(static_cast<LevelIDs>(CurrentLevel));

    onSetStartPosReturnToField.Original(tp);
    CurrentLevel = buffer;
});


FunctionHook<void, task*> onSceneChangeMainStationSquare(0x640850, [](task* tp)-> void
{
    // Emerald Coast Entrance
    const auto& pos = tp->twp->pos;

    if (levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_StationSquare5
        && worldStateManagerPtr->levelEntrances.canEnter(EmeraldCoast, CurrentCharacter)
        && pos.x > -590 && pos.x < -580 && pos.y > -25 && pos.y < -15 && pos.z > 2130 && pos.z < 2140)
    {
        tp->twp->ang.z = worldStateManagerPtr->levelEntrances.getLevelAndActIdFromEntrance(
            EmeraldCoast, CurrentCharacter);
    }
    //  Casinopolis
    if (levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_StationSquare2
        && worldStateManagerPtr->levelEntrances.canEnter(Casinopolis, CurrentCharacter)
        && pos.x > -646 && pos.x < -642 && pos.y > -8 && pos.y < 4 && pos.z > 878 && pos.z < 882)
    {
        tp->twp->ang.z = worldStateManagerPtr->levelEntrances.getLevelAndActIdFromEntrance(
            Casinopolis, CurrentCharacter);
    }

    // TwinklePark
    if (levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_StationSquare6
        && worldStateManagerPtr->levelEntrances.canEnter(TwinklePark, CurrentCharacter)
        && pos.x > 850 && pos.x < 860 && pos.y > 40 && pos.y < 50 && pos.z > 1760 && pos.z < 1780)
    {
        tp->twp->ang.z = worldStateManagerPtr->levelEntrances.getLevelAndActIdFromEntrance(
            TwinklePark, CurrentCharacter);
    }

    // SpeedHighway (City Hall)
    if (levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_StationSquare1
        && worldStateManagerPtr->levelEntrances.canEnter(SpeedHighway, CurrentCharacter)
        && pos.x > 269 && pos.x < 272 && pos.y > -4 && pos.y < 0 && pos.z > 232 && pos.z < 236)
    {
        tp->twp->ang.z = worldStateManagerPtr->levelEntrances.getLevelAndActIdFromEntrance(
            SpeedHighway, CurrentCharacter);
    }

    onSceneChangeMainStationSquare.Original(tp);
});

// SpeedHighway (Mains Area)
static void __cdecl HandleSpeedHighwayEntrance()
{
    if (worldStateManagerPtr->levelEntrances.canEnter(SpeedHighway, CurrentCharacter)
        && levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_StationSquare4)
    {
        const LevelAndActIDs levelAndAct = worldStateManagerPtr->levelEntrances.getLevelAndActIdFromEntrance(
            SpeedHighway, CurrentCharacter);
        SetNextLevelAndAct_CutsceneMode(GET_LEVEL(levelAndAct), GET_ACT(levelAndAct));
    }
}

// WindyValley
static void __cdecl HandleWindyValleyEntrance()
{
    if (worldStateManagerPtr->levelEntrances.canEnter(WindyValley, CurrentCharacter))
    {
        const LevelAndActIDs levelAndAct = worldStateManagerPtr->levelEntrances.getLevelAndActIdFromEntrance(
            WindyValley, CurrentCharacter);
        SetNextLevelAndAct_CutsceneMode(GET_LEVEL(levelAndAct), GET_ACT(levelAndAct));
    }
}

// MysticRuins
static void __cdecl HandleMREntrance(const int newScene)
{
    // Jungle Final Egg tower
    if (levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_MysticRuins3 && newScene == 5)
    {
        SetNextLevelAndAct_CutsceneMode(LevelIDs_MysticRuins, 3);
    }
    else if (levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_MysticRuins4 && newScene == 4)
    {
        SetNextLevelAndAct_CutsceneMode(LevelIDs_MysticRuins, 2);
    }
    // Final Egg
    else if (levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_MysticRuins4
        && worldStateManagerPtr->levelEntrances.canEnter(FinalEgg, CurrentCharacter) && (newScene == 2 || newScene ==
            3))
    {
        const LevelAndActIDs levelAndAct = worldStateManagerPtr->levelEntrances.getLevelAndActIdFromEntrance(
            FinalEgg, CurrentCharacter);
        SetNextLevelAndAct_CutsceneMode(GET_LEVEL(levelAndAct), GET_ACT(levelAndAct));
    }
    // Lost World
    else if (levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_MysticRuins3
        && worldStateManagerPtr->levelEntrances.canEnter(LostWorld, CurrentCharacter) && (newScene == 6 || newScene ==
            7))
    {
        const LevelAndActIDs levelAndAct = worldStateManagerPtr->levelEntrances.getLevelAndActIdFromEntrance(
            LostWorld, CurrentCharacter);
        SetNextLevelAndAct_CutsceneMode(GET_LEVEL(levelAndAct), GET_ACT(levelAndAct));
    }
    // Ice Cap
    else if (levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_MysticRuins2
        && worldStateManagerPtr->levelEntrances.canEnter(IceCap, CurrentCharacter) && newScene == 1)
    {
        const LevelAndActIDs levelAndAct = worldStateManagerPtr->levelEntrances.getLevelAndActIdFromEntrance(
            IceCap, CurrentCharacter);
        SetNextLevelAndAct_CutsceneMode(GET_LEVEL(levelAndAct), GET_ACT(levelAndAct));
    }
    // Red Mountain
    else if (levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_MysticRuins2
        && worldStateManagerPtr->levelEntrances.canEnter(RedMountain, CurrentCharacter) && newScene == 0)
    {
        const LevelAndActIDs levelAndAct = worldStateManagerPtr->levelEntrances.getLevelAndActIdFromEntrance(
            RedMountain, CurrentCharacter);
        SetNextLevelAndAct_CutsceneMode(GET_LEVEL(levelAndAct), GET_ACT(levelAndAct));
    }
    else
    {
        onSceneChangeMr_t.Original(newScene);
    }
}


// HotShelter
void HandleSceneChangeEcInside(int a1, int a2)
{
    if (levelact(CurrentLevel, CurrentAct) != LevelAndActIDs_EggCarrierInside2)
        return _onSceneChangeECInside_t.Original(a1, a2);

    const int doorId = *(_DWORD*)(a1 + 20);
    if (doorId != 512)
        return _onSceneChangeECInside_t.Original(a1, a2);

    const LevelAndActIDs levelAndAct = worldStateManagerPtr->levelEntrances.getLevelAndActIdFromEntrance(
        HotShelter, CurrentCharacter);
    camerahax_adventurefields();
    SetNextLevelAndAct_CutsceneMode(GET_LEVEL(levelAndAct), GET_ACT(levelAndAct));
}


// SkyDeck
void HandleSceneChangeEcOutside(int a1)
{
    if (levelact(CurrentLevel, CurrentAct) != LevelAndActIDs_EggCarrierOutside6 && levelact(CurrentLevel, CurrentAct) !=
        LevelAndActIDs_EggCarrierOutside2)
        return _onSceneChangeECOutside_t.Original(a1);
    const int doorId = *(_DWORD*)(a1 + 20);
    if (doorId != 256)
        return _onSceneChangeECOutside_t.Original(a1);
    const LevelAndActIDs levelAndAct = worldStateManagerPtr->levelEntrances.getLevelAndActIdFromEntrance(
        SkyDeck, CurrentCharacter);
    camerahax_adventurefields();
    SetNextLevelAndAct_CutsceneMode(GET_LEVEL(levelAndAct), GET_ACT(levelAndAct));
}

// Handles the Emerald Coast entrance
FunctionHook<BOOL> isEmeraldCoastOpen(0x639A30, []()-> BOOL
{
    if (CurrentCharacter == Characters_Gamma)
        return false;
    return worldStateManagerPtr->levelEntrances.canEnter(EmeraldCoast, CurrentCharacter);
});

FunctionHook<void, task*> loadEmeraldCoastGateTargets(0x63A0C0, [](task* tp)-> void
{
    if (levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_StationSquare5
        && !worldStateManagerPtr->levelEntrances.canEnter(EmeraldCoast, CurrentCharacter))
        FreeTask(tp);
    else
        loadEmeraldCoastGateTargets.Original(tp);
});

// Handles the Windy Valley entrance
// Makes Sonic, Tails and Gamma use the winds stone
FunctionHook<BOOL> isWindyValleyOpen(0x536E40, []()-> BOOL
{
    if (CurrentCharacter == Characters_Sonic)
        return EventFlagArray[FLAG_SONIC_MR_WINDYSTONE] && worldStateManagerPtr->levelEntrances.canEnter(
            WindyValley, CurrentCharacter);

    if (CurrentCharacter == Characters_Tails)
        return EventFlagArray[FLAG_MILES_MR_WINDYSTONE] && worldStateManagerPtr->levelEntrances.canEnter(
            WindyValley, CurrentCharacter);

    if (CurrentCharacter == Characters_Gamma)
        return EventFlagArray[FLAG_E102_MR_WINDYSTONE] && worldStateManagerPtr->levelEntrances.canEnter(
            WindyValley, CurrentCharacter);
    return worldStateManagerPtr->levelEntrances.canEnter(WindyValley, CurrentCharacter) && worldStateManagerPtr->
        unlockStatus.keyWindStone;
});

// Handles the Casinopolis entrance
FunctionHook<BOOL> isCasinoOpen(0x6383E0, []()-> BOOL
{
    if (CurrentCharacter == Characters_Sonic || CurrentCharacter == Characters_Tails)
        return isCasinoOpen.Original() && worldStateManagerPtr->levelEntrances.canEnter(Casinopolis, CurrentCharacter);

    //We open the casino door for knuckles despite any story flags
    if (CurrentCharacter == Characters_Knuckles)
        return GetEventFlag(static_cast<EventFlags>(FLAG_KNUCKLES_SS_ENTRANCE_CASINO)) && worldStateManagerPtr->
            levelEntrances.canEnter(
                WindyValley, CurrentCharacter);

    return worldStateManagerPtr->levelEntrances.canEnter(Casinopolis, CurrentCharacter);
});


// Handles the Twinkle Park entrance
static bool __cdecl HandleTwinkleParkEntrance(const char character)
{
    return worldStateManagerPtr->levelEntrances.canEnter(TwinklePark, CurrentCharacter);
}

// Speed Highway
FunctionHook<BOOL> isSpeedHighwayShutterOpen(0x63A2A0, []()-> BOOL
{
    return worldStateManagerPtr->levelEntrances.canEnter(SpeedHighway, CurrentCharacter)
        && worldStateManagerPtr->unlockStatus.keyEmployeeCard;
});

FunctionHook<void, task*> loadSpeedHighwayShutter(0x63A530, [](task* tp)-> void
{
    if ((CurrentCharacter == Characters_Gamma || CurrentCharacter == Characters_Amy)
        && worldStateManagerPtr->levelEntrances.canEnter(SpeedHighway, CurrentCharacter)
        && worldStateManagerPtr->unlockStatus.keyEmployeeCard)
        FreeTask(tp);
    else
        loadSpeedHighwayShutter.Original(tp);
});

FunctionHook<BOOL> isSpeedHighwayElevatorOpen(0x638CC0, []()-> BOOL
{
    return worldStateManagerPtr->unlockStatus.keyEmployeeCard;
});

FunctionHook<BOOL> isCityHallDoorOpen(0x636BF0, []()-> BOOL
{
    if (CurrentCharacter == Characters_Big)
        return worldStateManagerPtr->unlockStatus.keyEmployeeCard
            && worldStateManagerPtr->levelEntrances.canEnter(SpeedHighway, CurrentCharacter);

    return worldStateManagerPtr->levelEntrances.canEnter(SpeedHighway, CurrentCharacter) && isCityHallDoorOpen.
        Original();
});

//We don't create Knuckles barricade if he doesn't have access to the level
FunctionHook<void, task*> loadBarricade(0x637580, [](task* tp)-> void
{
    if (CurrentCharacter == Characters_Knuckles && levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_StationSquare1)
        if (!worldStateManagerPtr->levelEntrances.canEnter(SpeedHighway, CurrentCharacter))
            return FreeTask(tp);

    loadBarricade.Original(tp);
});


FunctionHook<BOOL, EntityData1*> isFinalEggGammaDoorOpen(0x53ED30, [](EntityData1* entity)-> BOOL
{
    if (levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_MysticRuins3)
        return true;

    if (levelact(CurrentLevel, CurrentAct) != LevelAndActIDs_MysticRuins4)
        return isFinalEggGammaDoorOpen.Original(entity);

    if (entity->Position.y < 100)
        return isFinalEggGammaDoorOpen.Original(entity);

    if (entity->Position.z < -150)
    {
        if (CurrentCharacter == Characters_Sonic || CurrentCharacter == Characters_Amy)
            return false;
        return worldStateManagerPtr->levelEntrances.canEnter(FinalEgg, CurrentCharacter);
    }
    return true;
});


FunctionHook<void, task*> onLoadSceneChangeMr(0x5394F0, [](task* tp)-> void
{
    // Final Egg
    if ((CurrentCharacter == Characters_Sonic || CurrentCharacter == Characters_Amy)
        && levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_MysticRuins4 && tp->twp->ang.x == 3)
    {
        if (!worldStateManagerPtr->levelEntrances.canEnter(FinalEgg, CurrentCharacter))
        {
            return FreeTask(tp);
        }
    }

    //Ice Cap
    if (levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_MysticRuins2 && tp->twp->ang.x == 1)
    {
        if (!worldStateManagerPtr->levelEntrances.canEnter(IceCap, CurrentCharacter))
        {
            return FreeTask(tp);
        }
    }

    onLoadSceneChangeMr.Original(tp);
});
//
FunctionHook<BOOL> isFinalEggTowerActive(0x538550, []()-> BOOL
{
    return true;
});
FunctionHook<BOOL> isFinalEggDoorActive(0x53EDF0, []()-> BOOL
{
    return true;
});


//Makes knuckles able to enter the lost world using the keys
FunctionHook<BOOL> isLostWorldBackEntranceOpen(0x53B6C0, []()-> BOOL
{
    if (CurrentCharacter == Characters_Knuckles)
        return EventFlagArray[FLAG_KNUCKLES_MR_REDCUBE] && EventFlagArray[
                FLAG_KNUCKLES_MR_BLUECUBE]
            && worldStateManagerPtr->levelEntrances.canEnter(LostWorld, CurrentCharacter);

    return false;
});

//Allows everyone to enter Lost World
FunctionHook<BOOL> isLostWorldFrontEntranceOpen(0x532E60, []()-> BOOL
{
    if (CurrentCharacter == Characters_Knuckles)
        return false;
    return worldStateManagerPtr->levelEntrances.canEnter(LostWorld, CurrentCharacter);
});


//Prevents the monkey from blocking the entrance to Red Mountain for knuckles
FunctionPointer(int, isMonkeyDead, (int a1), 0x53F920);
FunctionHook<BOOL, int> isMonkeyDoorOpen(0x53E5D0, [](int a1)-> BOOL
{
    if (levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_MysticRuins1)
        return true;

    if (CurrentCharacter == Characters_Sonic || CurrentCharacter == Characters_Gamma
        || CurrentCharacter == Characters_Knuckles)
        return isMonkeyDead(1) && worldStateManagerPtr->levelEntrances.canEnter(RedMountain, CurrentCharacter);

    //For everyone else, we return true if we are in the main mystic ruins area
    return worldStateManagerPtr->levelEntrances.canEnter(RedMountain, CurrentCharacter);
});


// We only load the monkey if it's needed for opening the door
FunctionHook<void, task*> onLoadMonkeyCage(0x540730, [](task* tp)-> void
{
    if (levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_MysticRuins2)
    {
        if (CurrentCharacter == Characters_Tails || CurrentCharacter == Characters_Big
            || CurrentCharacter == Characters_Amy)
            return FreeTask(tp);
        if (!worldStateManagerPtr->levelEntrances.canEnter(RedMountain, CurrentCharacter))
            return FreeTask(tp);
    }
    onLoadMonkeyCage.Original(tp);
});

// Removed the ladder on Ice Cap
FunctionHook<void, task*> onLoadLongLadderMr(0x536CB0, [](task* tp)-> void
{
    if (levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_MysticRuins2)
    {
        if (!worldStateManagerPtr->levelEntrances.canEnter(IceCap, CurrentCharacter))
        {
            return FreeTask(tp);
        }
    }
    onLoadLongLadderMr.Original(tp);
});


FunctionHook<BOOL, int> preventKeyStoneFromSpawning(0x53C630, [](int a1)-> BOOL
{
    if (levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_MysticRuins2
        && ((CurrentCharacter == Characters_Amy || CurrentCharacter == Characters_Knuckles
            || CurrentCharacter == Characters_Gamma) && worldStateManagerPtr->levelEntrances.canEnter(
            IceCap, CurrentCharacter)))
    {
        return worldStateManagerPtr->unlockStatus.keyIceStone;
    }

    return preventKeyStoneFromSpawning.Original(a1);
});

// HotShelter
static int __cdecl HandleEggCarrierEggDoor(const int a1)
{
    // Middle door
    if (levelact(CurrentLevel, CurrentAct) != LevelAndActIDs_EggCarrierInside2)
        return onEggCarrierEggDoor_t.Original(a1);

    if (*reinterpret_cast<BYTE*>(a1 + 1) != 6)
        return onEggCarrierEggDoor_t.Original(a1);

    if (!worldStateManagerPtr->levelEntrances.canEnter(HotShelter, CurrentCharacter))
        return false;

    const EntityData1* player = EntityData1Ptrs[0];
    const double dz = player->Position.z - *(float*)(a1 + 40);
    const double dy = player->Position.y - *(float*)(a1 + 36);
    const double dx = player->Position.x - *(float*)(a1 + 32);
    const double distance = dx * dx + dy * dy + dz * dz;
    if (squareroot(distance) > 50.0)
        return false;

    if (CurrentCharacter == Characters_Amy || CurrentCharacter == Characters_Big)
        return IsSwitchPressed(1);
    return true;
}


FunctionHook<void, task*> onLoadPoolWater(0x51DC30, [](task* tp)-> void
{
    if (CurrentCharacter == Characters_Sonic || CurrentCharacter == Characters_Tails)
        return onLoadPoolWater.Original(tp);

    if (!worldStateManagerPtr->levelEntrances.canEnter(SkyDeck, CurrentCharacter))
        return onLoadPoolWater.Original(tp);

    FreeTask(tp);
});

FunctionHook<void, task*> onLoadPoolDoor(0x51E320, [](task* tp)-> void
{
    if (CurrentCharacter == Characters_Sonic || CurrentCharacter == Characters_Tails)
        return onLoadPoolDoor.Original(tp);

    if (!worldStateManagerPtr->levelEntrances.canEnter(SkyDeck, CurrentCharacter))
        return onLoadPoolDoor.Original(tp);
    FreeTask(tp);
});

bool HandleSkyDeckDoor(EntityData1* a1)
{
    const EntityData1* player = EntityData1Ptrs[0];
    const double dz = player->Position.z - a1->Position.z;
    const double dy = player->Position.y - a1->Position.y;
    const double dx = player->Position.x - a1->Position.x;
    const double distance = squareroot(dx * dx + dy * dy + dz * dz);

    PrintDebug("Distance: %f\n", distance);
    return distance <= 50.0;
}
