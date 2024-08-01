#include "WorldStateManager.h"

WorldStateManager* worldStateManagerPtr;

constexpr int SCENE_CHANGE_STATION_SQUARE = 19;
constexpr int SCENE_CHANGE_MYSTIC_RUINS = 6;
constexpr int SCENE_CHANGE_PAST = 10;
constexpr int SCENE_CHANGE_EGG_CARRIER_OUTSIDE = 6;


constexpr int TIKAL_STATION_SQUARE = 105;
constexpr int TIKAL_MYSTIC_RUINS = 61;
constexpr int TIKAL_EGG_CARRIER = 22;

WorldStateManager::WorldStateManager()
{
    worldStateManagerPtr = this;
    //We replace the checkpoint for a Scene change object from Station Square
    ObjList_Past[10] = ObjList_SSquare[SCENE_CHANGE_STATION_SQUARE];
    ObjList_MRuins[SCENE_CHANGE_MYSTIC_RUINS] = ObjList_SSquare[SCENE_CHANGE_STATION_SQUARE];
    ObjList_ECarrier0[SCENE_CHANGE_EGG_CARRIER_OUTSIDE] = ObjList_SSquare[SCENE_CHANGE_STATION_SQUARE];
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
    if (CurrentCharacter == Characters_Knuckles)
        return true;
    if (CurrentCharacter == Characters_Sonic || CurrentCharacter == Characters_Gamma)
        return isMonkeyDead(1);
    return false;
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
    case None:
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

const SETEntry final_egg_spring = CreateSetEntry(1, {-52.21f, -3240.81f, -190.0f});
const SETEntry sewers_spring = CreateSetEntry(1, {505, -89, 635});

// const SETEntry time_travel = CreateSetEntry(19, {-69, 10, 1469}, {0, 0, 0x2200}, {2, 2, 2});

//Station Square Bosses
const SETEntry tikalChaos0 = CreateSetEntry(TIKAL_STATION_SQUARE, {270, 0, 390}, {0, 0, 0x96F6}, {0, 0, 18});
const SETEntry Chaos0 = CreateSetEntry(SCENE_CHANGE_STATION_SQUARE, {270, 10, 390}, {0, 0, 0x0F00}, {1.5f, 1.5f, 1.5f});

const SETEntry tikalEggWalker = CreateSetEntry(TIKAL_STATION_SQUARE, {-390, 0, 945}, {0, 0, 0x96F6}, {0, 0, 18});
const SETEntry EggWalker = CreateSetEntry(SCENE_CHANGE_STATION_SQUARE, {-390, 10, 945}, {0, 0, 0x1500},
                                          {1.5f, 1.5f, 1.5f});


//Mystic Ruins Bosses
const SETEntry tikalEggHornet = CreateSetEntry(TIKAL_MYSTIC_RUINS, {950, 123.92f, 950}, {0, 0xCA7F, 2}, {1.9f, 0, 18});
const SETEntry EggHornet = CreateSetEntry(SCENE_CHANGE_MYSTIC_RUINS, {950, 133.92f, 950}, {0, 0, 0x1400},
                                          {1.5f, 1.5f, 1.5f});

const SETEntry tikalChaos4 = CreateSetEntry(TIKAL_MYSTIC_RUINS, {88.62f, -33.99f, -140.96f}, {0, 0xCA7F, 2},
                                            {1.9f, 0, 18});
const SETEntry Chaos4 = CreateSetEntry(SCENE_CHANGE_MYSTIC_RUINS, {88.62f, -23.99f, -140.96f}, {0, 0, 0x1100},
                                       {1.5f, 1.5f, 1.5f});

const SETEntry tikalEggViper = CreateSetEntry(TIKAL_MYSTIC_RUINS, {0, 0, 0}, {0, 0xCA7F, 2}, {1.9f, 0, 18});
const SETEntry EggViper = CreateSetEntry(SCENE_CHANGE_MYSTIC_RUINS, {0, 10, 0}, {0, 0, 0x1600}, {1.5f, 1.5f, 1.5f});

const SETEntry tikalE101 = CreateSetEntry(TIKAL_MYSTIC_RUINS, {0, 0, 0}, {0, 0xCA7F, 2}, {1.9f, 0, 18});
const SETEntry E101 = CreateSetEntry(SCENE_CHANGE_MYSTIC_RUINS, {0, 10, 0}, {0, 0, 0x1800}, {1.5f, 1.5f, 1.5f});

//Egg Carrier Bosses
const SETEntry tikalChaos6 = CreateSetEntry(TIKAL_EGG_CARRIER, {0, 770, -385.69f}, {0, 0x4E4A, 0}, {50, 10, 22});
const SETEntry Chaos6 = CreateSetEntry(SCENE_CHANGE_EGG_CARRIER_OUTSIDE, {0, 760, -385.69f}, {0, 0, 0x1200},
                                       {1.5f, 1.5f, 1.5f});

const SETEntry tikalZero = CreateSetEntry(TIKAL_EGG_CARRIER, {0, 770, -385.69f}, {0, 0x4E4A, 0}, {50, 10, 22});
const SETEntry Zero = CreateSetEntry(SCENE_CHANGE_EGG_CARRIER_OUTSIDE, {0, 760, -385.69f}, {0, 0, 0x1700},
                                     {1.5f, 1.5f, 1.5f});

const SETEntry tikalE101Mk2 = CreateSetEntry(TIKAL_EGG_CARRIER, {0, 770, -385.69f}, {0, 0x4E4A, 0}, {50, 10, 22});
const SETEntry E101Mk2 = CreateSetEntry(SCENE_CHANGE_EGG_CARRIER_OUTSIDE, {0, 760, -385.69f}, {0, 0, 0x1900},
                                        {1.5f, 1.5f, 1.5f});

FunctionHook<void> onCountSetItemsMaybe(0x0046BD20, []()-> void
{
    onCountSetItemsMaybe.Original();

    AddSetToLevel(final_egg_spring, LevelAndActIDs_FinalEgg3, Characters_Sonic);
    AddSetToLevel(sewers_spring, LevelAndActIDs_StationSquare3, Characters_Sonic);


    // AddSetToLevel(time_travel, LevelAndActIDs_StationSquare4, Characters_Sonic);

    //Station Square Bosses
    AddSetToLevel(tikalChaos0, LevelAndActIDs_StationSquare1, Characters_Sonic);
    AddSetToLevel(Chaos0, LevelAndActIDs_StationSquare1, Characters_Sonic);

    AddSetToLevel(tikalEggWalker, LevelAndActIDs_StationSquare2, Characters_Tails);
    AddSetToLevel(EggWalker, LevelAndActIDs_StationSquare2, Characters_Tails);


    //Mystic Ruins Bosses
    AddSetToLevel(tikalEggHornet, LevelAndActIDs_MysticRuins1, Characters_Sonic);
    AddSetToLevel(EggHornet, LevelAndActIDs_MysticRuins1, Characters_Sonic);
    AddSetToLevel(tikalEggHornet, LevelAndActIDs_MysticRuins1, Characters_Tails);
    AddSetToLevel(EggHornet, LevelAndActIDs_MysticRuins1, Characters_Tails);

    AddSetToLevel(tikalChaos4, LevelAndActIDs_MysticRuins1, Characters_Sonic);
    AddSetToLevel(Chaos4, LevelAndActIDs_MysticRuins1, Characters_Sonic);
    AddSetToLevel(tikalChaos4, LevelAndActIDs_MysticRuins1, Characters_Tails);
    AddSetToLevel(Chaos4, LevelAndActIDs_MysticRuins1, Characters_Tails);
    AddSetToLevel(tikalChaos4, LevelAndActIDs_MysticRuins1, Characters_Knuckles);
    AddSetToLevel(Chaos4, LevelAndActIDs_MysticRuins1, Characters_Knuckles);

    AddSetToLevel(tikalEggViper, LevelAndActIDs_MysticRuins4, Characters_Sonic);
    AddSetToLevel(EggViper, LevelAndActIDs_MysticRuins4, Characters_Sonic);
    AddSetToLevel(tikalE101, LevelAndActIDs_MysticRuins4, Characters_Gamma);
    AddSetToLevel(E101, LevelAndActIDs_MysticRuins4, Characters_Gamma);

    //Egg Carrier Bosses
    AddSetToLevel(tikalChaos6, LevelAndActIDs_EggCarrierOutside1, Characters_Sonic);
    AddSetToLevel(Chaos6, LevelAndActIDs_EggCarrierOutside1, Characters_Sonic);
    AddSetToLevel(tikalChaos6, LevelAndActIDs_EggCarrierOutside2, Characters_Sonic);
    AddSetToLevel(Chaos6, LevelAndActIDs_EggCarrierOutside2, Characters_Sonic);

    AddSetToLevel(tikalChaos6, LevelAndActIDs_EggCarrierOutside1, Characters_Knuckles);
    AddSetToLevel(Chaos6, LevelAndActIDs_EggCarrierOutside1, Characters_Knuckles);
    AddSetToLevel(tikalChaos6, LevelAndActIDs_EggCarrierOutside2, Characters_Knuckles);
    AddSetToLevel(Chaos6, LevelAndActIDs_EggCarrierOutside2, Characters_Knuckles);

    AddSetToLevel(tikalChaos6, LevelAndActIDs_EggCarrierOutside1, Characters_Big);
    AddSetToLevel(Chaos6, LevelAndActIDs_EggCarrierOutside1, Characters_Big);
    AddSetToLevel(tikalChaos6, LevelAndActIDs_EggCarrierOutside2, Characters_Big);
    AddSetToLevel(Chaos6, LevelAndActIDs_EggCarrierOutside2, Characters_Big);

    AddSetToLevel(tikalZero, LevelAndActIDs_EggCarrierOutside1, Characters_Amy);
    AddSetToLevel(Zero, LevelAndActIDs_EggCarrierOutside1, Characters_Amy);
    AddSetToLevel(tikalZero, LevelAndActIDs_EggCarrierOutside2, Characters_Amy);
    AddSetToLevel(Zero, LevelAndActIDs_EggCarrierOutside2, Characters_Amy);

    AddSetToLevel(tikalE101Mk2, LevelAndActIDs_EggCarrierOutside1, Characters_Gamma);
    AddSetToLevel(E101Mk2, LevelAndActIDs_EggCarrierOutside1, Characters_Gamma);
    AddSetToLevel(tikalE101Mk2, LevelAndActIDs_EggCarrierOutside2, Characters_Gamma);
    AddSetToLevel(E101Mk2, LevelAndActIDs_EggCarrierOutside2, Characters_Gamma);
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
