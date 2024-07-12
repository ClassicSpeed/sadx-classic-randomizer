#include "SaveFileManager.h"

#include "../../pch.h"


void SaveFileManager::OnSaveFileLoaded()
{
    ClearEventFlag(static_cast<EventFlags>(FLAG_SONIC_PLAYABLE));
    ClearEventFlag(static_cast<EventFlags>(FLAG_MILES_PLAYABLE));
    ClearEventFlag(static_cast<EventFlags>(FLAG_KNUCKLES_PLAYABLE));
    ClearEventFlag(static_cast<EventFlags>(FLAG_AMY_PLAYABLE));
    ClearEventFlag(static_cast<EventFlags>(FLAG_E102_PLAYABLE));
    ClearEventFlag(static_cast<EventFlags>(FLAG_BIG_PLAYABLE));
    ClearEventFlag(static_cast<EventFlags>(FLAG_SUPERSONIC_PLAYABLE));

    
    SetEventFlag(static_cast<EventFlags>(FLAG_SONIC_COMPLETE));
    SetEventFlag(static_cast<EventFlags>(FLAG_MILES_COMPLETE));
    SetEventFlag(static_cast<EventFlags>(FLAG_KNUCKLES_COMPLETE));
    SetEventFlag(static_cast<EventFlags>(FLAG_AMY_COMPLETE));
    SetEventFlag(static_cast<EventFlags>(FLAG_E102_COMPLETE));
    SetEventFlag(static_cast<EventFlags>(FLAG_BIG_COMPLETE));


    // ---- Starter flags
    //Station front door
    SetEventFlag(static_cast<EventFlags>(FLAG_SONIC_SS_STATION_FRONT));
    SetEventFlag(static_cast<EventFlags>(FLAG_MILES_SS_STATION_FRONT));
    SetEventFlag(static_cast<EventFlags>(FLAG_KNUCKLES_SS_STATION_FRONT));
    SetEventFlag(static_cast<EventFlags>(FLAG_AMY_SS_STATION_FRONT));
    SetEventFlag(static_cast<EventFlags>(FLAG_E102_SS_STATION_FRONT));
    SetEventFlag(static_cast<EventFlags>(FLAG_BIG_SS_STATION_FRONT));

    //Sonic & tails barricade
    SetEventFlag(static_cast<EventFlags>(FLAG_SONIC_SS_BARRICADE));
    SetEventFlag(static_cast<EventFlags>(FLAG_MILES_SS_BARRICADE));

    //Removes car on top on sewer
    // SetEventFlag(static_cast<EventFlags>(FLAG_SONIC_SS_ENTRANCE_SEWER));
    
    //Sonic & Tails sand hill 
    SetEventFlag(static_cast<EventFlags>(FLAG_SONIC_MR_ENTRANCE_SANDBOARD));
    SetEventFlag(static_cast<EventFlags>(FLAG_MILES_MR_ENTRANCE_SANDBOARD));

    //TODO: Check if it's needed
    SetEventFlag(static_cast<EventFlags>(FLAG_BIG_SS_TPARK_ELEVATOR));

    //Jungle Ruins
    SetEventFlag(static_cast<EventFlags>(FLAG_SONIC_MR_ENTRANCE_RUIN));
    SetEventFlag(static_cast<EventFlags>(FLAG_MILES_MR_ENTRANCE_RUIN));
    // SetEventFlag(static_cast<EventFlags>(FLAG_KNUCKLES_MR_REDCUBE));
    // SetEventFlag(static_cast<EventFlags>(FLAG_KNUCKLES_MR_BLUECUBE));

    //Final Egg
    SetEventFlag(static_cast<EventFlags>(FLAG_SONIC_MR_APPEAR_FINALEGG));
    SetEventFlag(static_cast<EventFlags>(FLAG_KNUCKLES_MR_APPEAR_FINALEGG));
    SetEventFlag(static_cast<EventFlags>(FLAG_AMY_MR_APPEAR_FINALEGG));
    SetEventFlag(static_cast<EventFlags>(FLAG_E102_MR_APPEAR_FINALEGG));

    //All of the egg carrier flags
    SetEventFlag(static_cast<EventFlags>(FLAG_SONIC_EC_MONORAIL));
    SetEventFlag(static_cast<EventFlags>(FLAG_SONIC_EC_EGGLIFT));
    SetEventFlag(static_cast<EventFlags>(FLAG_SONIC_EC_TRANSFORM));
    SetEventFlag(static_cast<EventFlags>(FLAG_SONIC_EC_TORNADO2_LOST));
    SetEventFlag(static_cast<EventFlags>(FLAG_SONIC_EC_SINK));
    SetEventFlag(static_cast<EventFlags>(FLAG_MILES_EC_MONORAIL));
    SetEventFlag(static_cast<EventFlags>(FLAG_MILES_EC_EGGLIFT));
    SetEventFlag(static_cast<EventFlags>(FLAG_MILES_EC_TRANSFORM));
    SetEventFlag(static_cast<EventFlags>(FLAG_MILES_EC_TORNADO2_LOST));
    SetEventFlag(static_cast<EventFlags>(FLAG_MILES_EC_SINK));
    SetEventFlag(static_cast<EventFlags>(FLAG_KNUCKLES_EC_MONORAIL));
    SetEventFlag(static_cast<EventFlags>(FLAG_KNUCKLES_EC_EGGLIFT));
    SetEventFlag(static_cast<EventFlags>(FLAG_KNUCKLES_EC_TRANSFORM));
    SetEventFlag(static_cast<EventFlags>(FLAG_KNUCKLES_EC_PALMSWITCH));
    SetEventFlag(static_cast<EventFlags>(FLAG_KNUCKLES_EC_TORNADO2_LOST));
    SetEventFlag(static_cast<EventFlags>(FLAG_KNUCKLES_EC_SINK));
    SetEventFlag(static_cast<EventFlags>(FLAG_AMY_EC_MONORAIL));
    SetEventFlag(static_cast<EventFlags>(FLAG_AMY_EC_EGGLIFT));
    SetEventFlag(static_cast<EventFlags>(FLAG_AMY_EC_TRANSFORM));
    SetEventFlag(static_cast<EventFlags>(FLAG_AMY_EC_MOGURATATAKI));
    SetEventFlag(static_cast<EventFlags>(FLAG_AMY_EC_TORNADO2_LOST));
    SetEventFlag(static_cast<EventFlags>(FLAG_AMY_EC_SINK));
    SetEventFlag(static_cast<EventFlags>(FLAG_E102_EC_MONORAIL));
    SetEventFlag(static_cast<EventFlags>(FLAG_E102_EC_EGGLIFT));
    SetEventFlag(static_cast<EventFlags>(FLAG_E102_EC_TRANSFORM));
    SetEventFlag(static_cast<EventFlags>(FLAG_E102_EC_TORNADO2_LOST));
    SetEventFlag(static_cast<EventFlags>(FLAG_E102_EC_BOOSTER));
    SetEventFlag(static_cast<EventFlags>(FLAG_E102_EC_TYPE3LASER));
    SetEventFlag(static_cast<EventFlags>(FLAG_E102_EC_SINK));
    SetEventFlag(static_cast<EventFlags>(FLAG_E102_EC_HOTSHELTER));
    SetEventFlag(static_cast<EventFlags>(FLAG_BIG_EC_MONORAIL));
    SetEventFlag(static_cast<EventFlags>(FLAG_BIG_EC_EGGLIFT));
    SetEventFlag(static_cast<EventFlags>(FLAG_BIG_EC_TRANSFORM));
    SetEventFlag(static_cast<EventFlags>(FLAG_BIG_EC_TORNADO2_LOST));
    SetEventFlag(static_cast<EventFlags>(FLAG_BIG_EC_SINK));

    //We mark levels as cleared to let us in for missions A/B

    //Sonic's levels
    SetEventFlag(static_cast<EventFlags>(FLAG_SONIC_CLEAR_BEACH));
    SetEventFlag(static_cast<EventFlags>(FLAG_SONIC_CLEAR_WINDY));
    SetEventFlag(static_cast<EventFlags>(FLAG_SONIC_CLEAR_CASINO));
    SetEventFlag(static_cast<EventFlags>(FLAG_SONIC_CLEAR_TWINKLEPARK));
    SetEventFlag(static_cast<EventFlags>(FLAG_SONIC_CLEAR_HIGHWAY));
    SetEventFlag(static_cast<EventFlags>(FLAG_SONIC_CLEAR_MOUNTAIN));
    SetEventFlag(static_cast<EventFlags>(FLAG_SONIC_CLEAR_SNOW));
    SetEventFlag(static_cast<EventFlags>(FLAG_SONIC_CLEAR_SKYDECK));
    SetEventFlag(static_cast<EventFlags>(FLAG_SONIC_CLEAR_RUIN));
    SetEventFlag(static_cast<EventFlags>(FLAG_SONIC_CLEAR_FINALEGG));

    //Tails' levels
    SetEventFlag(static_cast<EventFlags>(FLAG_MILES_CLEAR_WINDY));
    SetEventFlag(static_cast<EventFlags>(FLAG_MILES_CLEAR_CASINO));
    SetEventFlag(static_cast<EventFlags>(FLAG_MILES_CLEAR_HIGHWAY));
    SetEventFlag(static_cast<EventFlags>(FLAG_MILES_CLEAR_SNOW));
    SetEventFlag(static_cast<EventFlags>(FLAG_MILES_CLEAR_SKYDECK));
    SetEventFlag(static_cast<EventFlags>(FLAG_MILES_CLEAR_SANDBOARD));

    //Knuckles' levels
    SetEventFlag(static_cast<EventFlags>(FLAG_KNUCKLES_CLEAR_CASINO));
    SetEventFlag(static_cast<EventFlags>(FLAG_KNUCKLES_CLEAR_HIGHWAY));
    SetEventFlag(static_cast<EventFlags>(FLAG_KNUCKLES_CLEAR_MOUNTAIN));
    SetEventFlag(static_cast<EventFlags>(FLAG_KNUCKLES_CLEAR_RUIN));
    SetEventFlag(static_cast<EventFlags>(FLAG_KNUCKLES_CLEAR_SKYDECK));

    //Amy's levels
    SetEventFlag(static_cast<EventFlags>(FLAG_AMY_CLEAR_TWINKLEPARK));
    SetEventFlag(static_cast<EventFlags>(FLAG_AMY_CLEAR_HOTSHELTER));
    SetEventFlag(static_cast<EventFlags>(FLAG_AMY_CLEAR_FINALEGG));

    //Gamma's levels
    SetEventFlag(static_cast<EventFlags>(FLAG_E102_CLEAR_BEACH));
    SetEventFlag(static_cast<EventFlags>(FLAG_E102_CLEAR_WINDY));
    SetEventFlag(static_cast<EventFlags>(FLAG_E102_CLEAR_MOUNTAIN));
    SetEventFlag(static_cast<EventFlags>(FLAG_E102_CLEAR_HOTSHELTER));
    SetEventFlag(static_cast<EventFlags>(FLAG_E102_CLEAR_FINALEGG));

    //Big's levels
    SetEventFlag(static_cast<EventFlags>(FLAG_BIG_CLEAR_BEACH));
    SetEventFlag(static_cast<EventFlags>(FLAG_BIG_CLEAR_HOTSHELTER));
    SetEventFlag(static_cast<EventFlags>(FLAG_BIG_CLEAR_TWINKLEPARK));
    SetEventFlag(static_cast<EventFlags>(FLAG_BIG_CLEAR_SNOW));

    //Set sequence to -1 so it's just open world
    // SaveFile.AdventureData[Characters_Sonic].field_4 = -1;
    // SaveFile.AdventureData[Characters_Tails].field_4 = -1;
    // SaveFile.AdventureData[Characters_Knuckles].field_4 = -1;
    // SaveFile.AdventureData[Characters_Amy].field_4 = -1;
    // SaveFile.AdventureData[Characters_Big].field_4 = -1;
    // SaveFile.AdventureData[Characters_Gamma].field_4 = -1;
    SaveFile.AdventureData[Characters_Sonic].LevelAct = LevelAndActIDs_StationSquare1;
    SaveFile.AdventureData[Characters_Tails].LevelAct = LevelAndActIDs_StationSquare1;
    SaveFile.AdventureData[Characters_Knuckles].LevelAct = LevelAndActIDs_StationSquare1;
    SaveFile.AdventureData[Characters_Amy].LevelAct = LevelAndActIDs_StationSquare1;
    SaveFile.AdventureData[Characters_Big].LevelAct = LevelAndActIDs_StationSquare1;
    SaveFile.AdventureData[Characters_Gamma].LevelAct = LevelAndActIDs_StationSquare1;
    WriteSaveFile();
    //This doesn't save for some reason, so we set it manually
    SaveFile.AdventureData[Characters_Sonic].field_4 = -1;
    SaveFile.AdventureData[Characters_Tails].field_4 = -1;
    SaveFile.AdventureData[Characters_Knuckles].field_4 = -1;
    SaveFile.AdventureData[Characters_Amy].field_4 = -1;
    SaveFile.AdventureData[Characters_Big].field_4 = -1;
    SaveFile.AdventureData[Characters_Gamma].field_4 = -1;


    //DataArray(char, LevelClearCounts, 0x3B18250, 344);
    for (unsigned int i = 0; i < LevelClearCounts.size(); i++)
        LevelClearCounts[i] = 1;
    
}

// void SaveFileManager::OnFrame()
// {
//     for (const auto& button : PressedButtons)
//
//         if (button & WhistleButtons && Current_CharObj2 != nullptr)
//         {
//             SetEventFlag(static_cast<EventFlags>(0x00));
//         }
// }
