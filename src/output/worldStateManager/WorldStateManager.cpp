#include "WorldStateManager.h"


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


FunctionHook<void> onSetRoundMaster(0x4143C0, []()-> void
{
    //Creates a spring for sonic in the sewers
    if (CurrentCharacter == Characters_Sonic && levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_StationSquare3)
    {
        const auto spring = CreateElementalTask(LoadObj_Data1, 3, ObjectSpring);
        spring->twp->pos.x = 505;
        spring->twp->pos.y = -89;
        spring->twp->pos.z = 635;
    }

    //Creates a spring for sonic in final egg for the 4 life capsules room
    if (CurrentCharacter == Characters_Sonic && levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_FinalEgg3)
    {
        const auto spring = CreateElementalTask(LoadObj_Data1, 3, ObjectSpring);
        spring->twp->pos.x = -52.21f;
        spring->twp->pos.y = -3240.81f;
        spring->twp->pos.z = -190.0f;
    }
    onSetRoundMaster.Original();
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

//Prevents the recap screen from showing on the last story
FunctionHook<int, int> showRecap(0x643C00, [](int _)-> int
{
    return -1;
});
