#pragma once

#include "../../pch.h"
#include "../../application/structs/Options.h"
#include "../../application/structs/LevelEntrances.h"
#include "../../application/structs/UnlockStatus.h"
#include "../../application/structs/VisitedLevels.h"

class WorldStateManager
{
public:
    WorldStateManager();
    void SetEventFlags(std::vector<StoryFlags> storyFlags);
    void UnlockSuperSonic();
    void UpdateOptions(Options newOptions);
    void UpdateUnlockStatus(UnlockStatus unlockStatus);
    void OnFrame();
    void SetStartingArea();
    void StartAllMissions();
    void UpdateLevelEntrances(LevelEntrances levelEntrances);
    VisitedLevels GetVisitedLevels(int visitedLevel);
    Options options;
    UnlockStatus unlockStatus;
    LevelEntrances levelEntrances = {
        {EmeraldCoast, EmeraldCoast},
        {WindyValley, WindyValley},
        {Casinopolis, Casinopolis},
        {IceCap, IceCap},
        {TwinklePark, TwinklePark},
        {SpeedHighway, SpeedHighway},
        {RedMountain, RedMountain},
        {SkyDeck, SkyDeck},
        {LostWorld, LostWorld},
        {FinalEgg, FinalEgg},
        {HotShelter, HotShelter},
    };
private:
    VisitedLevels _visitedLevels;
};
