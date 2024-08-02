#pragma once

#include "../../pch.h"
#include "../../application/structs/Options.h"
class WorldStateManager
{
public:
    WorldStateManager();
    void SetEventFlags(std::vector<StoryFlags> storyFlags);
    void UnlockSuperSonic();
    void UpdateOptions(Options newOptions);
    Options options;
};
