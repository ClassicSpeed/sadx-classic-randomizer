#include "WorldStateManager.h"

WorldStateManager* worldStateManagerPtr;

WorldStateManager::WorldStateManager()
{
    worldStateManagerPtr = this;
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

bool CheckIfCharacterInRange(task* tp)
{
    Characters v1; // edi
    double v2; // st7
    double v3; // st6
    double v4; // st5
    float v6; // [esp+0h] [ebp-8h]
    auto position = EntityData1Ptrs[0]->Position;
    v2 = position.x - tp->twp->pos.x;
    v4 = position.y - tp->twp->pos.y;
    v3 = position.z - tp->twp->pos.z;
    v6 = v4 * v4 + v3 * v3 + v2 * v2;
    if (squareroot(v6) > 20.0)
    {
        return false;
    }
    return true;
}

// FunctionPointer(void, SceneChange, (char act, signed int levelId), 0x640600);
void CustomSceneChangeFunction(task* tp)
{
    if (CheckIfCharacterInRange(tp))
    {
        PrintDebug("In Range\n");
        // SceneChange(2201 & 0xF, LevelIDs_EmeraldCoast);
        camerahax_adventurefields();
        SetLevelEntrance(0);
        j_SetNextLevelAndAct_CutsceneMode(LevelIDs_Past, 0);
        PrintDebug("Changing Scene\n");
        tp->exec = DestroyTask;
    }
}

TaskFunc(ObjectSnake, 0x5E2B80);
TaskFunc(ObjectRlight, 0x5E8960);


// FunctionPointer(BOOL, CheckRangeOut, (task* tp), 0x46C360);
FunctionHook<BOOL, task*> OnCheckRangeOut(0x4159A0, [](task* tp)-> BOOL
{
    OnCheckRangeOut.Original(tp);
    return true;
});

//VoidFunc(LoadLevel, 0x4159A0);
FunctionHook<void> OnLoadLevel(0x4159A0, []()-> void
{
    OnLoadLevel.Original();


    if (levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_StationSquare4)
    {
        const auto timeTravel = CreateElementalTask(LoadObj_Data1, 2, CustomSceneChangeFunction);
        // const auto spring = CreateElementalTask(LoadObj_Data1, 3, ObjectSpring);
        timeTravel->twp->pos.x = -69;
        timeTravel->twp->pos.y = 10;
        timeTravel->twp->pos.z = 1469;
        timeTravel->twp->scl.x = 6;
        timeTravel->twp->scl.y = 6;
        timeTravel->twp->scl.z = 6;
    }
    if (levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_Past1)
    {
        //Spawn 4 snakes and light
        PrintDebug("Creating snakes\n");
        // ObjectFunc(O_mrsna, 0x5E2B80);
        const auto snake1 = CreateElementalTask(LoadObj_Data1, 2, ObjectSnake);
        snake1->twp->pos.x = 820; //+-30
        snake1->twp->pos.y = 100;
        snake1->twp->pos.z = 450; //+-30

        snake1->twp->ang.x = 0xEE00;
        snake1->twp->ang.y = 0x3900;

        const auto snake2 = CreateElementalTask(LoadObj_Data1, 2, ObjectSnake);
        snake2->twp->pos.x = 760; //+-30
        snake2->twp->pos.y = 100;
        snake2->twp->pos.z = 450; //+-30

        snake2->twp->ang.x = 0xEE00;
        snake2->twp->ang.y = 0x7A00;

        const auto snake3 = CreateElementalTask(LoadObj_Data1, 2, ObjectSnake);
        snake3->twp->pos.x = 760; //+-30
        snake3->twp->pos.y = 100;
        snake3->twp->pos.z = 390; //+-30

        snake3->twp->ang.x = 0xEE00;
        snake3->twp->ang.y = 0xB900;

        const auto snake4 = CreateElementalTask(LoadObj_Data1, 2, ObjectSnake);
        snake4->twp->pos.x = 820; //+-30
        snake4->twp->pos.y = 100;
        snake4->twp->pos.z = 390; //+-30

        snake4->twp->ang.x = 0xEE00;
        snake4->twp->ang.y = 0xF800;


        const auto light = CreateElementalTask(LoadObj_Data1, 2, ObjectRlight);
        light->twp->pos.x = 790; //+-30
        light->twp->pos.y = 350;
        light->twp->pos.z = 420; //+-30

        light->twp->ang.y = 0xAC2D;
    }
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

//Opens the Casino for all the characters
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

SETEntry CreateSetEntry(const int16_t objectType, const Float x, const Float y, const Float z)
{
    SETEntry setEntry;
    setEntry.ObjectType = objectType;
    setEntry.XRotation = 0;
    setEntry.YRotation = 0;
    setEntry.ZRotation = 0;
    setEntry.Position.x = x;
    setEntry.Position.y = y;
    setEntry.Position.z = z;
    setEntry.Properties.x = 0;
    setEntry.Properties.y = 0;
    setEntry.Properties.z = 0;
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

const SETEntry final_egg_spring = CreateSetEntry(1, -52.21f, -3240.81f, -190.0f);
const SETEntry sewers_spring = CreateSetEntry(1, 505, -89, 635);

FunctionHook<void> onCountSetItemsMaybe(0x0046BD20, []()-> void
{
    onCountSetItemsMaybe.Original();

    AddSetToLevel(final_egg_spring, LevelAndActIDs_FinalEgg3, Characters_Sonic);

    AddSetToLevel(sewers_spring, LevelAndActIDs_StationSquare3, Characters_Sonic);
});
