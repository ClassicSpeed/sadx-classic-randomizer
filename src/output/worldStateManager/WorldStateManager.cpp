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
