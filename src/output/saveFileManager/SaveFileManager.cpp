#include "SaveFileManager.h"

#include "../../pch.h"


void SaveFileManager::OnSaveFileLoaded()
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

    ClearEventFlag(static_cast<EventFlags>(FLAG_AMY_MR_FIGHTERSFEATHER));
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

    //Jungle Kart
    ClearEventFlag(static_cast<EventFlags>(FLAG_SONIC_MR_TRUCK));
    ClearEventFlag(static_cast<EventFlags>(FLAG_MILES_MR_TRUCK));
    ClearEventFlag(static_cast<EventFlags>(FLAG_KNUCKLES_MR_TRUCK));
    ClearEventFlag(static_cast<EventFlags>(FLAG_AMY_MR_TRUCK));
    ClearEventFlag(static_cast<EventFlags>(FLAG_E102_MR_TRUCK));
    ClearEventFlag(static_cast<EventFlags>(FLAG_BIG_MR_TRUCK));


    WriteSaveFile();
}
