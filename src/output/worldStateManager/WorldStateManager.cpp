#include "WorldStateManager.h"


void WorldStateManager::SetEventFlags(std::vector<StoryFlags> storyFlags)
{
    for (StoryFlags storyFlag : storyFlags)
        SetEventFlag(static_cast<EventFlags>(storyFlag));
    WriteSaveFile();
    SaveFile.AdventureData[Characters_Sonic].field_4 = -1;
    SaveFile.AdventureData[Characters_Tails].field_4 = -1;
    SaveFile.AdventureData[Characters_Knuckles].field_4 = -1;
    SaveFile.AdventureData[Characters_Amy].field_4 = -1;
    SaveFile.AdventureData[Characters_Big].field_4 = -1;
    SaveFile.AdventureData[Characters_Gamma].field_4 = -1;
}

void WorldStateManager::UnlockSuperSonic()
{
    SetEventFlag(static_cast<EventFlags>(FLAG_SUPERSONIC_PLAYABLE));
    WriteSaveFile();
    SaveFile.AdventureData[Characters_Sonic].field_4 = -1;
    SaveFile.AdventureData[Characters_Tails].field_4 = -1;
    SaveFile.AdventureData[Characters_Knuckles].field_4 = -1;
    SaveFile.AdventureData[Characters_Amy].field_4 = -1;
    SaveFile.AdventureData[Characters_Big].field_4 = -1;
    SaveFile.AdventureData[Characters_Gamma].field_4 = -1;
}

//Creates a spring for sonic in the sewers
FunctionHook<void, char> OnAddSetStage(0x46BF70, [](char Gap)-> void
{
    if (CurrentCharacter == Characters_Sonic && CurrentLevel == LevelIDs_StationSquare && CurrentAct == 0)
    {
        FunctionPointer(task*, CreateElementalTask, (unsigned __int16 im, int level, void(__cdecl* exec)(task*)),
                        0x40B860);
        const auto spring = CreateElementalTask(LoadObj_Data1, 3, ObjectSpring);
        spring->twp->pos.x = 505;
        spring->twp->pos.y = -89;
        spring->twp->pos.z = 635;
    }
    OnAddSetStage.Original(Gap);
});

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

FunctionHook<BOOL> isLostWorldBackEntranceOpen(0x53B6C0, []()-> BOOL
{
    if (CurrentCharacter == Characters_Knuckles)
        return EventFlagArray[FLAG_KNUCKLES_MR_REDCUBE] && EventFlagArray[FLAG_KNUCKLES_MR_BLUECUBE];
    return false;
});
