#pragma once

#include "../../pch.h"
#include "../../application/structs/Options.h"
#include "../../application/structs/UnlockStatus.h"

class WorldStateManager
{
public:
    WorldStateManager();
    void SetEventFlags(std::vector<StoryFlags> storyFlags);
    void UnlockSuperSonic();
    void UpdateOptions(Options newOptions);
    void UpdateUnlockStatus(UnlockStatus unlockStatus);
    Options options;
    UnlockStatus unlockStatus;
};
