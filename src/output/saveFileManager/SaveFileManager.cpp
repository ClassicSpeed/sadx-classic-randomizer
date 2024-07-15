#include "SaveFileManager.h"

#include "../../pch.h"

void SaveFileManager::OnSaveFileLoaded()
{
    if (LevelClearCounts[0] == 0)
        OnSaveFileCreated();
}

void SaveFileManager::OnFrame()
{
    // These doesn't save for some reason, so we set it manually
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

    //Upgrades
    ClearEventFlag(static_cast<EventFlags>(FLAG_SONIC_SS_LIGHTSHOOSE));
    ClearEventFlag(static_cast<EventFlags>(FLAG_SONIC_SS_CRYSTALRING));
    ClearEventFlag(static_cast<EventFlags>(FLAG_SONIC_MR_ANCIENT_LIGHT));

    ClearEventFlag(static_cast<EventFlags>(FLAG_MILES_SS_JETANKLET));
    ClearEventFlag(static_cast<EventFlags>(FLAG_MILES_MR_RHYTHMBROOCH));

    ClearEventFlag(static_cast<EventFlags>(FLAG_KNUCKLES_MR_SHOVELCLAW));
    ClearEventFlag(static_cast<EventFlags>(FLAG_KNUCKLES_MR_FIGHTINGGROVE));

    // ClearEventFlag(static_cast<EventFlags>(FLAG_AMY_MR_FIGHTERSFEATHER));
    ClearEventFlag(static_cast<EventFlags>(FLAG_AMY_EC_LONGHAMMER));

    ClearEventFlag(static_cast<EventFlags>(FLAG_E102_EC_BOOSTER));
    ClearEventFlag(static_cast<EventFlags>(FLAG_E102_EC_TYPE3LASER));

    ClearEventFlag(static_cast<EventFlags>(FLAG_BIG_MR_LIFEBELT));
    ClearEventFlag(static_cast<EventFlags>(FLAG_BIG_MR_POWERROD));
    ClearEventFlag(static_cast<EventFlags>(FLAG_BIG_RUAR_BLUE));
    ClearEventFlag(static_cast<EventFlags>(FLAG_BIG_RUAR_GOLD));
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

    //Hotel Door
    ClearEventFlag(static_cast<EventFlags>(FLAG_SONIC_SS_HOTEL_FRONT));
    ClearEventFlag(static_cast<EventFlags>(FLAG_MILES_SS_HOTEL_FRONT));
    ClearEventFlag(static_cast<EventFlags>(FLAG_KNUCKLES_SS_HOTEL_FRONT));
    ClearEventFlag(static_cast<EventFlags>(FLAG_AMY_SS_HOTEL_FRONT));
    ClearEventFlag(static_cast<EventFlags>(FLAG_E102_SS_HOTEL_FRONT));
    ClearEventFlag(static_cast<EventFlags>(FLAG_BIG_SS_HOTEL_FRONT));

    //Casino-Station Door
    ClearEventFlag(static_cast<EventFlags>(FLAG_SONIC_SS_STATION_BACK));
    ClearEventFlag(static_cast<EventFlags>(FLAG_MILES_SS_STATION_BACK));
    ClearEventFlag(static_cast<EventFlags>(FLAG_KNUCKLES_SS_STATION_BACK));
    ClearEventFlag(static_cast<EventFlags>(FLAG_AMY_SS_STATION_BACK));
    //Casino-Hotel door
    ClearEventFlag(static_cast<EventFlags>(FLAG_SONIC_SS_HOTEL_BACK));
    ClearEventFlag(static_cast<EventFlags>(FLAG_MILES_SS_HOTEL_BACK));
    ClearEventFlag(static_cast<EventFlags>(FLAG_KNUCKLES_SS_HOTEL_BACK));
    ClearEventFlag(static_cast<EventFlags>(FLAG_AMY_SS_HOTEL_BACK));
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

    //Angel Island
    ClearEventFlag(static_cast<EventFlags>(FLAG_SONIC_MR_WESTROCK));
    ClearEventFlag(static_cast<EventFlags>(FLAG_MILES_MR_WESTROCK));
    ClearEventFlag(static_cast<EventFlags>(FLAG_KNUCKLES_MR_WESTROCK));
    ClearEventFlag(static_cast<EventFlags>(FLAG_E102_MR_WESTROCK));
    ClearEventFlag(static_cast<EventFlags>(FLAG_BIG_MR_WESTROCK));
    ClearEventFlag(static_cast<EventFlags>(FLAG_AMY_MR_ISLANDDOOR));

    //Red Mountain
    ClearEventFlag(static_cast<EventFlags>(FLAG_SONIC_MR_ENTRANCE_MOUNTAIN));
    ClearEventFlag(static_cast<EventFlags>(FLAG_E102_MR_ENTRANCE_MOUNTAIN));

    //Jungle Kart
    ClearEventFlag(static_cast<EventFlags>(FLAG_SONIC_MR_TRUCK));
    ClearEventFlag(static_cast<EventFlags>(FLAG_MILES_MR_TRUCK));
    ClearEventFlag(static_cast<EventFlags>(FLAG_KNUCKLES_MR_TRUCK));
    ClearEventFlag(static_cast<EventFlags>(FLAG_AMY_MR_TRUCK));
    ClearEventFlag(static_cast<EventFlags>(FLAG_E102_MR_TRUCK));
    ClearEventFlag(static_cast<EventFlags>(FLAG_BIG_MR_TRUCK));

    //Lost World
    ClearEventFlag(static_cast<EventFlags>(FLAG_KNUCKLES_MR_REDCUBE));
    ClearEventFlag(static_cast<EventFlags>(FLAG_KNUCKLES_MR_BLUECUBE));

    //FinalEgg
    ClearEventFlag(static_cast<EventFlags>(FLAG_SONIC_MR_ENTRANCE_FINALEGG));

    //Chao Garden
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
