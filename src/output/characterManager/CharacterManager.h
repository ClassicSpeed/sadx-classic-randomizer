#pragma once
#include "../../pch.h"
#include "../../application/structs/Options.h"

class CharacterManager
{
public:
    CharacterManager();

    void GiveUpgrade(Upgrades upgrade);
    void RemoveUpgrade(Upgrades upgrade);
    void UpdateOptions(Options newOptions);
    Options options;
};
