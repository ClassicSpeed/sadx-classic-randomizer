#include "WorldStateManager.h"

#include <algorithm>

#include "sadx-mod-loader/SADXModLoader/include/UsercallFunctionHandler.h"

WorldStateManager* worldStateManagerPtr;


constexpr int WARP_EGG_CARRIER_INSIDE = 35;

constexpr int WARP_STATION_SQUARE = 17;
constexpr int WARP_MYSTIC_RUINS = 6;
constexpr int WARP_EGG_CARRIER_OUTSIDE = 6;
constexpr int WARP_PAST = 10;


// //We pretend that the egg carrier is sunk so that the hedgehog hammer is works
static bool __cdecl HandleHedgehoHammer()
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
        && EntityData1Ptrs[0]->Position.y < 0)
        SetNextLevelAndAct_CutsceneMode(LevelIDs_Chaos4, 0);

    else if (levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_MysticRuins1
        && (CurrentCharacter == Characters_Sonic || CurrentCharacter == Characters_Tails)
        && EntityData1Ptrs[0]->Position.y > 0 && EntityData1Ptrs[0]->Position.y < 150)
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
    if (GameMode == GameModes_Adventure_ActionStg)
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
    else
        onCollisionCube.Original(tp);
});

WorldStateManager::WorldStateManager()
{
    WriteCall(reinterpret_cast<void*>(0x5264C5), &HandleWarp);
    WriteCall(reinterpret_cast<void*>(0x528271), &HandleHedgehoHammer);

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

//Allow Knuckles to fight Chaos 2
FunctionHook<BOOL> isChaos2DoorOpen(0x638D50, []()-> BOOL
{
    return CurrentCharacter == Characters_Knuckles;
});

//Makes Sonic, Tails and Gamma use the winds stone
FunctionHook<BOOL> isWindyValleyOpen(0x536E40, []()-> BOOL
{
    if (CurrentCharacter == Characters_Sonic)
        return EventFlagArray[FLAG_SONIC_MR_WINDYSTONE];

    if (CurrentCharacter == Characters_Tails)
        return EventFlagArray[FLAG_MILES_MR_WINDYSTONE];

    if (CurrentCharacter == Characters_Gamma)
        return EventFlagArray[FLAG_E102_MR_WINDYSTONE];
    return false;
});

//Makes knuckles able to enter the lost world using the keys
FunctionHook<BOOL> isLostWorldBackEntranceOpen(0x53B6C0, []()-> BOOL
{
    if (CurrentCharacter == Characters_Knuckles)
        return EventFlagArray[FLAG_KNUCKLES_MR_REDCUBE] && EventFlagArray[FLAG_KNUCKLES_MR_BLUECUBE];
    return false;
});

//Prevents the monkey from blocking the entrance to Red Mountain for knuckles
FunctionPointer(int, isMonkeyDead, (int a1), 0x53F920);
FunctionHook<BOOL, int> isRedMountainOpen(0x53E5D0, [](int a1)-> BOOL
{
    if (CurrentCharacter == Characters_Knuckles && levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_MysticRuins1)
        return true;
    if (CurrentCharacter == Characters_Knuckles && levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_MysticRuins2)
        return isMonkeyDead(1);
    if (CurrentCharacter == Characters_Sonic || CurrentCharacter == Characters_Gamma)
        return isMonkeyDead(1);
    return false;
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

//We open the casino door for knuckles despite any story flags
FunctionHook<BOOL> isCasinoOpen(0x6383E0, []()-> BOOL
{
    if (CurrentCharacter == Characters_Knuckles)
        return GetEventFlag(static_cast<EventFlags>(FLAG_KNUCKLES_SS_ENTRANCE_CASINO));
    return isCasinoOpen.Original();
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

//Set starting location
FunctionHook<void> onAdventureSetLevelAndAct(0x4133E0, []()-> void
{
    onAdventureSetLevelAndAct.Original();
    if (LastStoryFlag == 1)
        return;
    switch (worldStateManagerPtr->options.startingArea)
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
    case MysticRuinsMain:
        SetLevelAndAct(LevelIDs_MysticRuins, 0);
        break;
    case Jungle:
        SetLevelAndAct(LevelIDs_MysticRuins, 2);
        break;
    case EggCarrier:
        SetLevelAndAct(LevelIDs_EggCarrierOutside, 0);
        break;
    case NoStatingArea:
        break;
    }
});

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
const SETEntry SEWERS_SPRING = CreateSetEntry(1, {505, -89, 635}, {0, 0, 0}, {0.3f, 0, 51});


//Station Square Bosses
const SETEntry WARP_CHAOS0 = CreateSetEntry(WARP_STATION_SQUARE, {270, 0, 450});

const SETEntry WARP_EGG_WALKER = CreateSetEntry(WARP_STATION_SQUARE, {-400, -3, 955});


//Mystic Ruins Bosses
const SETEntry WARP_EGG_HORNET = CreateSetEntry(WARP_MYSTIC_RUINS, {950, 127, 950});

const SETEntry WARP_CHAOS4 = CreateSetEntry(WARP_MYSTIC_RUINS, {88.62f, -33.99f, -140.96f});

const SETEntry WARP_EGG_VIPER = CreateSetEntry(WARP_MYSTIC_RUINS, {0, 0, 0});

const SETEntry WARP_E101 = CreateSetEntry(WARP_MYSTIC_RUINS, {0, 0, 0});

//Egg Carrier Bosses
const SETEntry WARP_CHAOS6 = CreateSetEntry(WARP_EGG_CARRIER_OUTSIDE, {0, 750.5f, -385.69f});

const SETEntry WARP_ZERO = CreateSetEntry(WARP_EGG_CARRIER_OUTSIDE, {0, 750.5f, -385.69f});

const SETEntry WARP_E101_MK2 = CreateSetEntry(WARP_EGG_CARRIER_OUTSIDE, {0, 750.5f, -385.69f});

//Sky Chase
const SETEntry WARP_SKY_CHASE_1 = CreateSetEntry(WARP_MYSTIC_RUINS, {1473, 201, 776});
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
    if(worldStateManagerPtr->options.sublevelsChecks)
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

//We prevent the wind stone from spawning if the player doesn't have the item
FunctionHook<void, task*> onMysticRuinsKey(0x532400, [](task* tp)-> void
{
    if (levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_MysticRuins1
        && !worldStateManagerPtr->unlockStatus.keyWindStone)
        return;

    onMysticRuinsKey.Original(tp);
});
