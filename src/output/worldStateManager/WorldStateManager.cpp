#include "WorldStateManager.h"

#include <algorithm>

#include "sadx-mod-loader/SADXModLoader/include/UsercallFunctionHandler.h"

WorldStateManager* worldStateManagerPtr;


constexpr int WARP_EGG_CARRIER_INSIDE = 35;

constexpr int WARP_STATION_SQUARE = 17;
constexpr int WARP_MYSTIC_RUINS = 6;
constexpr int WARP_EGG_CARRIER_OUTSIDE = 6;


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

    else if (levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_MysticRuins1 && (CurrentCharacter == Characters_Sonic
        || CurrentCharacter == Characters_Tails) && EntityData1Ptrs[0]->Position.y > 0)
        SetNextLevelAndAct_CutsceneMode(LevelIDs_EggHornet, 0);

    else if (CurrentLevel == LevelIDs_EggCarrierOutside && CurrentCharacter == Characters_Gamma)
        SetNextLevelAndAct_CutsceneMode(LevelIDs_E101R, 0);

    else if (CurrentLevel == LevelIDs_EggCarrierOutside && CurrentCharacter == Characters_Amy)
        SetNextLevelAndAct_CutsceneMode(LevelIDs_Zero, 0);

    else if (CurrentLevel == LevelIDs_EggCarrierOutside && (CurrentCharacter == Characters_Sonic || CurrentCharacter ==
        Characters_Knuckles || CurrentCharacter == Characters_Big))
        SetNextLevelAndAct_CutsceneMode(LevelIDs_Chaos6, 0);

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

WorldStateManager::WorldStateManager()
{
    WriteCall(reinterpret_cast<void*>(0x5264C5), &HandleWarp);
    WriteCall(reinterpret_cast<void*>(0x528271), &HandleHedgehoHammer);

    worldStateManagerPtr = this;

    //We replace the checkpoint for a warp object from the Egg Carrier
    ObjList_SSquare[WARP_STATION_SQUARE] = ObjList_ECarrier3[WARP_EGG_CARRIER_INSIDE];
    ObjList_MRuins[WARP_MYSTIC_RUINS] = ObjList_ECarrier3[WARP_EGG_CARRIER_INSIDE];
    ObjList_ECarrier0[WARP_EGG_CARRIER_OUTSIDE] = ObjList_ECarrier3[WARP_EGG_CARRIER_INSIDE];
}

void WorldStateManager::SetEventFlags(std::vector<StoryFlags> storyFlags)
{
    for (StoryFlags storyFlag : storyFlags)
    {
        SetEventFlag(static_cast<EventFlags>(storyFlag));
        //We open the door between the hotel and the casino if you have both keys
        if ((storyFlag == FLAG_SONIC_SS_STATION_BACK &&
                GetEventFlag(static_cast<EventFlags>(FLAG_SONIC_SS_HOTEL_FRONT))) ||
            (storyFlag == FLAG_SONIC_SS_HOTEL_FRONT &&
                GetEventFlag(static_cast<EventFlags>(FLAG_SONIC_SS_STATION_BACK))))
        {
            SetEventFlag(static_cast<EventFlags>(FLAG_SONIC_SS_HOTEL_BACK));
            SetEventFlag(static_cast<EventFlags>(FLAG_MILES_SS_HOTEL_BACK));
            SetEventFlag(static_cast<EventFlags>(FLAG_KNUCKLES_SS_HOTEL_BACK));
            SetEventFlag(static_cast<EventFlags>(FLAG_AMY_SS_HOTEL_BACK));
            SetEventFlag(static_cast<EventFlags>(FLAG_BIG_SS_HOTEL_BACK));
        }
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

//We open the casino door for knuckles despite any story flags
FunctionHook<BOOL> isCasinoOpen(0x6383E0, []()-> BOOL
{
    if (CurrentCharacter == Characters_Knuckles)
        return GetEventFlag(static_cast<EventFlags>(FLAG_KNUCKLES_SS_ENTRANCE_CASINO));
    return isCasinoOpen.Original();
});

//Makes the Casino keys open the Casino for all the characters
FunctionHook<int> isStationToCasinoDoorOpen(0x638880, []()-> int
{
    return EventFlagArray[FLAG_SONIC_SS_STATION_BACK];
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
const SETEntry WARP_CHAOS6 = CreateSetEntry(WARP_EGG_CARRIER_OUTSIDE, {0, 749, -385.69f});

const SETEntry WARP_ZERO = CreateSetEntry(WARP_EGG_CARRIER_OUTSIDE, {0, 749, -385.69f});

const SETEntry WARP_E101_MK2 = CreateSetEntry(WARP_EGG_CARRIER_OUTSIDE, {0, 749, -385.69f});


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
    else if (CurrentLevel == LevelIDs_Chaos6)
    {
        SetLevelAndAct(LevelIDs_EggCarrierOutside, 0);
        SetEntranceNumber(0);
    }
    else if (CurrentLevel == LevelIDs_EggHornet)
    {
        SetNextLevelAndAct(LevelIDs_MysticRuins, 0);
        SetEntranceNumber(0);
    }
    else if (CurrentLevel == LevelIDs_EggWalker)
    {
        SetNextLevelAndAct(LevelIDs_StationSquare, 1);
        SetEntranceNumber(1);
    }
    else if (CurrentLevel == LevelIDs_EggViper)
    {
        SetNextLevelAndAct(LevelIDs_MysticRuins, 3);
        SetEntranceNumber(3);
    }
    else if (CurrentLevel == LevelIDs_Zero)
    {
        SetLevelAndAct(LevelIDs_EggCarrierOutside, 0);
        SetEntranceNumber(0);
    }
    else if (CurrentLevel == LevelIDs_E101)
    {
        SetNextLevelAndAct(LevelIDs_MysticRuins, 3);
        SetEntranceNumber(3);
    }
    else if (CurrentLevel == LevelIDs_E101R)
    {
        SetLevelAndAct(LevelIDs_EggCarrierOutside, 0);
        SetEntranceNumber(0);
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
