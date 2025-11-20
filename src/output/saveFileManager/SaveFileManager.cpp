#include "SaveFileManager.h"


SaveFileManager::SaveFileManager()
{
    _howManyGameGearGamesHook.Hook(OnHowManyGameGearGames);
    _isGameGearMenuEnabledHook.Hook(OnIsGameGearMenuEnabled);
    _showRecapHook.Hook(OnShowRecap);
}


void SaveFileManager::OnSaveFileLoaded()
{
    if (LevelClearCounts[0] == 0)
        _instance->OnSaveFileCreated();
}


void SaveFileManager::OnFrame()
{
    // These don't save for some reason, so we set it manually
    // For some reason, some functions override these fields, we force them off
    // Maybe I'll search for a better way later
    SaveFile.AdventureData[Characters_Sonic].field_4 = -1;
    SaveFile.AdventureData[Characters_Tails].field_4 = -1;
    SaveFile.AdventureData[Characters_Knuckles].field_4 = -1;
    SaveFile.AdventureData[Characters_Amy].field_4 = -1;
    SaveFile.AdventureData[Characters_Big].field_4 = -1;
    SaveFile.AdventureData[Characters_Gamma].field_4 = -1;
}

void SaveFileManager::OnSaveFileCreated()
{
    for (unsigned int i = 0; i < LevelClearCounts.size(); i++)
        LevelClearCounts[i] = 1;

    for (int i = 0; i < 512; i++)
        CutsceneFlagArray[i] = 1;

    for (int i = 0; i < 512; i++)
        EventFlagArray[i] = 1;

    //Playable Characters
    ClearEventFlag(static_cast<EventFlags>(FLAG_SONIC_PLAYABLE));
    ClearEventFlag(static_cast<EventFlags>(FLAG_MILES_PLAYABLE));
    ClearEventFlag(static_cast<EventFlags>(FLAG_KNUCKLES_PLAYABLE));
    ClearEventFlag(static_cast<EventFlags>(FLAG_AMY_PLAYABLE));
    ClearEventFlag(static_cast<EventFlags>(FLAG_E102_PLAYABLE));
    ClearEventFlag(static_cast<EventFlags>(FLAG_BIG_PLAYABLE));
    ClearEventFlag(static_cast<EventFlags>(FLAG_SUPERSONIC_PLAYABLE));
    ClearEventFlag(static_cast<EventFlags>(FLAG_SUPERSONIC_COMPLETE));

    //Upgrades
    ClearEventFlag(static_cast<EventFlags>(FLAG_SONIC_SS_LIGHTSHOOSE));
    ClearEventFlag(static_cast<EventFlags>(FLAG_SONIC_SS_CRYSTALRING));
    ClearEventFlag(static_cast<EventFlags>(FLAG_SONIC_MR_ANCIENT_LIGHT));

    ClearEventFlag(static_cast<EventFlags>(FLAG_MILES_SS_JETANKLET));
    ClearEventFlag(static_cast<EventFlags>(FLAG_MILES_MR_RHYTHMBROOCH));

    ClearEventFlag(static_cast<EventFlags>(FLAG_KNUCKLES_MR_SHOVELCLAW));
    ClearEventFlag(static_cast<EventFlags>(FLAG_KNUCKLES_MR_FIGHTINGGROVE));

    ClearEventFlag(static_cast<EventFlags>(FLAG_AMY_MR_FIGHTERSFEATHER));
    ClearEventFlag(static_cast<EventFlags>(FLAG_AMY_EC_LONGHAMMER));

    ClearEventFlag(static_cast<EventFlags>(FLAG_E102_EC_BOOSTER));
    ClearEventFlag(static_cast<EventFlags>(FLAG_E102_EC_TYPE3LASER));

    ClearEventFlag(static_cast<EventFlags>(FLAG_BIG_MR_LIFEBELT));
    ClearEventFlag(static_cast<EventFlags>(FLAG_BIG_MR_POWERROD));
    ClearEventFlag(static_cast<EventFlags>(FLAG_BIG_RUAR_BLUE));
    ClearEventFlag(static_cast<EventFlags>(FLAG_BIG_RUAR_GOLD));
    ClearEventFlag(static_cast<EventFlags>(FLAG_BIG_RUAR_NORMAL));
    ClearEventFlag(static_cast<EventFlags>(FLAG_BIG_RUAR_RED));
    ClearEventFlag(static_cast<EventFlags>(FLAG_BIG_RUAR_SILVER));

    //Train
    ClearEventFlag(static_cast<EventFlags>(FLAG_SONIC_TRAIN));
    ClearEventFlag(static_cast<EventFlags>(FLAG_MILES_TRAIN));
    ClearEventFlag(static_cast<EventFlags>(FLAG_KNUCKLES_TRAIN));
    ClearEventFlag(static_cast<EventFlags>(FLAG_AMY_TRAIN));
    ClearEventFlag(static_cast<EventFlags>(FLAG_E102_TRAIN));
    ClearEventFlag(static_cast<EventFlags>(FLAG_BIG_TRAIN));

    //Boat
    ClearEventFlag(static_cast<EventFlags>(FLAG_SONIC_BOAT));
    ClearEventFlag(static_cast<EventFlags>(FLAG_MILES_BOAT));
    ClearEventFlag(static_cast<EventFlags>(FLAG_KNUCKLES_BOAT));
    ClearEventFlag(static_cast<EventFlags>(FLAG_AMY_BOAT));
    ClearEventFlag(static_cast<EventFlags>(FLAG_E102_BOAT));
    ClearEventFlag(static_cast<EventFlags>(FLAG_BIG_BOAT));

    //Raft
    ClearEventFlag(static_cast<EventFlags>(FLAG_SONIC_RAFT));
    ClearEventFlag(static_cast<EventFlags>(FLAG_MILES_RAFT));
    ClearEventFlag(static_cast<EventFlags>(FLAG_KNUCKLES_RAFT));
    ClearEventFlag(static_cast<EventFlags>(FLAG_AMY_RAFT));
    ClearEventFlag(static_cast<EventFlags>(FLAG_E102_RAFT));
    ClearEventFlag(static_cast<EventFlags>(FLAG_BIG_RAFT));


    //Casino Door
    ClearEventFlag(static_cast<EventFlags>(FLAG_SONIC_SS_ENTRANCE_CASINO));
    ClearEventFlag(static_cast<EventFlags>(FLAG_MILES_SS_ENTRANCE_CASINO));
    ClearEventFlag(static_cast<EventFlags>(FLAG_KNUCKLES_SS_ENTRANCE_CASINO));

    //Twinkle Park Elevator
    ClearEventFlag(static_cast<EventFlags>(FLAG_SONIC_SS_TPARK_ELEVATOR));
    ClearEventFlag(static_cast<EventFlags>(FLAG_MILES_SS_TPARK_ELEVATOR));
    ClearEventFlag(static_cast<EventFlags>(FLAG_KNUCKLES_SS_TPARK_ELEVATOR));
    ClearEventFlag(static_cast<EventFlags>(FLAG_AMY_SS_TPARK_ELEVATOR));
    ClearEventFlag(static_cast<EventFlags>(FLAG_E102_SS_TPARK_ELEVATOR));
    ClearEventFlag(static_cast<EventFlags>(FLAG_BIG_SS_TPARK_ELEVATOR));

    //Speed Highway
    ClearEventFlag(static_cast<EventFlags>(FLAG_SONIC_SS_CARD));
    ClearEventFlag(static_cast<EventFlags>(FLAG_SONIC_SS_ENTRANCE_HIGHWAY));
    ClearEventFlag(static_cast<EventFlags>(FLAG_MILES_SS_ENTRANCE_HIGHWAY));

    //Windy Valley
    ClearEventFlag(static_cast<EventFlags>(FLAG_SONIC_MR_ENTRANCE_WINDY));
    ClearEventFlag(static_cast<EventFlags>(FLAG_SONIC_MR_WINDYSTONE));
    ClearEventFlag(static_cast<EventFlags>(FLAG_MILES_MR_ENTRANCE_WINDY));
    ClearEventFlag(static_cast<EventFlags>(FLAG_MILES_MR_WINDYSTONE));
    ClearEventFlag(static_cast<EventFlags>(FLAG_E102_MR_ENTRANCE_WINDY));
    ClearEventFlag(static_cast<EventFlags>(FLAG_E102_MR_WINDYSTONE));

    //Ice Cap Stone
    ClearEventFlag(static_cast<EventFlags>(FLAG_SONIC_SS_ICESTONE));
    ClearEventFlag(static_cast<EventFlags>(FLAG_MILES_SS_ICESTONE));
    ClearEventFlag(static_cast<EventFlags>(FLAG_BIG_SS_ICESTONE));
    //Ice Entrance
    ClearEventFlag(static_cast<EventFlags>(FLAG_SONIC_MR_ICESTONE));
    ClearEventFlag(static_cast<EventFlags>(FLAG_SONIC_MR_ENTRANCE_ICECAP));
    ClearEventFlag(static_cast<EventFlags>(FLAG_MILES_MR_ICESTONE));
    ClearEventFlag(static_cast<EventFlags>(FLAG_MILES_MR_ENTRANCE_ICECAP));
    ClearEventFlag(static_cast<EventFlags>(FLAG_BIG_MR_ICESTONE));
    ClearEventFlag(static_cast<EventFlags>(FLAG_BIG_MR_ENTRANCE_ICECAP));

    //Red Mountain
    ClearEventFlag(static_cast<EventFlags>(FLAG_SONIC_MR_ENTRANCE_MOUNTAIN));
    ClearEventFlag(static_cast<EventFlags>(FLAG_E102_MR_ENTRANCE_MOUNTAIN));
    ClearEventFlag(static_cast<EventFlags>(FLAG_KNUCKLES_MR_ENTRANCE_MOUNTAIN));
    ClearEventFlag(static_cast<EventFlags>(FLAG_KNUCKLES_MR_MONKEYDOOR_ENTER));
    ClearEventFlag(static_cast<EventFlags>(FLAG_KNUCKLES_MR_MONKEYCAGEA_BOMB));
    ClearEventFlag(static_cast<EventFlags>(FLAG_KNUCKLES_CLEAR_MOUNTAIN));

    //Lost World
    ClearEventFlag(static_cast<EventFlags>(FLAG_KNUCKLES_MR_REDCUBE));
    ClearEventFlag(static_cast<EventFlags>(FLAG_KNUCKLES_MR_BLUECUBE));

    //Sand Hill
    ClearEventFlag(static_cast<EventFlags>(FLAG_SONIC_MR_ENTRANCE_SANDBOARD));
    ClearEventFlag(static_cast<EventFlags>(FLAG_MILES_MR_ENTRANCE_SANDBOARD));

    //FinalEgg
    ClearEventFlag(static_cast<EventFlags>(FLAG_SONIC_MR_ENTRANCE_FINALEGG));

    //EggCarrier
    ClearEventFlag(static_cast<EventFlags>(FLAG_SONIC_EC_EGGLIFT));
    ClearEventFlag(static_cast<EventFlags>(FLAG_MILES_EC_EGGLIFT));
    ClearEventFlag(static_cast<EventFlags>(FLAG_KNUCKLES_EC_EGGLIFT));
    ClearEventFlag(static_cast<EventFlags>(FLAG_AMY_EC_EGGLIFT));
    ClearEventFlag(static_cast<EventFlags>(FLAG_E102_EC_EGGLIFT));
    ClearEventFlag(static_cast<EventFlags>(FLAG_BIG_EC_EGGLIFT));
    ClearEventFlag(static_cast<EventFlags>(FLAG_SONIC_EC_MONORAIL));
    ClearEventFlag(static_cast<EventFlags>(FLAG_MILES_EC_MONORAIL));
    ClearEventFlag(static_cast<EventFlags>(FLAG_KNUCKLES_EC_MONORAIL));
    ClearEventFlag(static_cast<EventFlags>(FLAG_AMY_EC_MONORAIL));
    ClearEventFlag(static_cast<EventFlags>(FLAG_E102_EC_MONORAIL));
    ClearEventFlag(static_cast<EventFlags>(FLAG_BIG_EC_MONORAIL));
    ClearEventFlag(static_cast<EventFlags>(FLAG_SONIC_EC_TRANSFORM));
    ClearEventFlag(static_cast<EventFlags>(FLAG_MILES_EC_TRANSFORM));
    ClearEventFlag(static_cast<EventFlags>(FLAG_KNUCKLES_EC_TRANSFORM));
    ClearEventFlag(static_cast<EventFlags>(FLAG_AMY_EC_TRANSFORM));
    ClearEventFlag(static_cast<EventFlags>(FLAG_E102_EC_TRANSFORM));
    ClearEventFlag(static_cast<EventFlags>(FLAG_BIG_EC_TRANSFORM));

    //Chao Garden
    ClearEventFlag(static_cast<EventFlags>(FLAG_GET_GOLDEGG));
    ClearEventFlag(static_cast<EventFlags>(FLAG_GET_SILVEREGG));
    ClearEventFlag(static_cast<EventFlags>(FLAG_GET_BLACKEGG));

    ClearEventFlag(static_cast<EventFlags>(FLAG_SONIC_ARRIVE_IN_SS));
    ClearEventFlag(static_cast<EventFlags>(FLAG_SONIC_ARRIVE_IN_MR));
    ClearEventFlag(static_cast<EventFlags>(FLAG_SONIC_ARRIVE_IN_EC));
    ClearEventFlag(static_cast<EventFlags>(FLAG_MILES_ARRIVE_IN_SS));
    ClearEventFlag(static_cast<EventFlags>(FLAG_MILES_ARRIVE_IN_MR));
    ClearEventFlag(static_cast<EventFlags>(FLAG_MILES_ARRIVE_IN_EC));
    ClearEventFlag(static_cast<EventFlags>(FLAG_KNUCKLES_ARRIVE_IN_SS));
    ClearEventFlag(static_cast<EventFlags>(FLAG_KNUCKLES_ARRIVE_IN_MR));
    ClearEventFlag(static_cast<EventFlags>(FLAG_KNUCKLES_ARRIVE_IN_EC));
    ClearEventFlag(static_cast<EventFlags>(FLAG_AMY_ARRIVE_IN_SS));
    ClearEventFlag(static_cast<EventFlags>(FLAG_AMY_ARRIVE_IN_MR));
    ClearEventFlag(static_cast<EventFlags>(FLAG_AMY_ARRIVE_IN_EC));
    ClearEventFlag(static_cast<EventFlags>(FLAG_E102_ARRIVE_IN_SS));
    ClearEventFlag(static_cast<EventFlags>(FLAG_E102_ARRIVE_IN_MR));
    ClearEventFlag(static_cast<EventFlags>(FLAG_E102_ARRIVE_IN_EC));
    ClearEventFlag(static_cast<EventFlags>(FLAG_BIG_ARRIVE_IN_SS));
    ClearEventFlag(static_cast<EventFlags>(FLAG_BIG_ARRIVE_IN_MR));
    ClearEventFlag(static_cast<EventFlags>(FLAG_BIG_ARRIVE_IN_EC));
    WriteSaveFile();
}

void SaveFileManager::StartAllMissions()
{
    for (int i = 0; i < 60; i++)
    {
        if (!(MissionFlags[i] & MissionFlags_Complete))
        {
            MissionFlags[i] |= MissionFlags_Found;
            MissionFlags[i] |= MissionFlags_Started;
        }
    }
    WriteSaveFile();
}

void SaveFileManager::SetMissionCompleted(const int mission)
{
    MissionFlags[mission - 1] |= MissionFlags_Found;
    MissionFlags[mission - 1] &= ~MissionFlags_Started;
    MissionFlags[mission - 1] |= MissionFlags_Complete;
    WriteSaveFile();
}

void SaveFileManager::SetEventFlags(std::vector<StoryFlags> storyFlags)
{
    for (StoryFlags storyFlag : storyFlags)
    {
        SetEventFlag(static_cast<EventFlags>(storyFlag));
    }
    WriteSaveFile();
}

void SaveFileManager::UnlockSuperSonic()
{
    SetEventFlag(static_cast<EventFlags>(FLAG_SUPERSONIC_PLAYABLE));
    WriteSaveFile();
}

void SaveFileManager::MarkBlacklistedMissionsAsCompleted(const std::vector<int>& missionBlacklist)
{
    for (const int mission : missionBlacklist)
    {
        MissionFlags[mission - 1] |= MissionFlags_Found;
        MissionFlags[mission - 1] &= ~MissionFlags_Started;
        MissionFlags[mission - 1] |= MissionFlags_Complete;
    }
    WriteSaveFile();
}

// Enable all GameGear Games
int SaveFileManager::OnHowManyGameGearGames()
{
    return 12;
}

bool SaveFileManager::OnIsGameGearMenuEnabled()
{
    return true;
}

// Prevents the recap screen from showing on the last story
int SaveFileManager::OnShowRecap(int _)
{
    return -1;
}
