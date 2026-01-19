#include "CharacterLoadingDetector.h"


CharacterLoadingDetector::CharacterLoadingDetector(Randomizer& randomizer, Settings& settings)
    : _randomizer(randomizer), _settings(settings)
{
    _loadCharacterHook.Hook(OnLoadCharacter);
    _loadCharacterSelectScreenHook.Hook(OnLoadCharacterSelectScreen);
}

void CharacterLoadingDetector::OnLoadCharacter()
{
    _instance->OnCharacterLoaded();
    _loadCharacterHook.Original();
}

void CharacterLoadingDetector::OnLoadCharacterSelectScreen()
{
    _instance->OnCharacterLoaded();
    _instance->OnCharacterSelectScreenLoaded();
    _loadCharacterSelectScreenHook.Original();
}


void CharacterLoadingDetector::OnCharacterSelectScreenLoaded() const
{
    _randomizer.OnCharacterSelectScreenLoaded();
}

void CharacterLoadingDetector::OnCharacterLoaded()
{
    if (DemoPlaying > 0)
        return;
    //Workaround to load the upgrades after the event flags logic was applied
    _loadCharacterNextFrame = 5;
}

void CharacterLoadingDetector::OnFrame()
{
    if (Current_CharObj2 == nullptr || EntityData1Ptrs[0] == nullptr)
        return;

    if (_loadCharacterNextFrame > 1)
        _loadCharacterNextFrame--;


    if (_loadCharacterNextFrame == 1)
    {
        _randomizer.OnCharacterLoaded();


        if (_settings.adventureFieldDoorOverride == AdventureFieldDoorOverrideAllOpened)
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

            //Casino Door
            ClearEventFlag(static_cast<EventFlags>(FLAG_SONIC_SS_ENTRANCE_CASINO));
            ClearEventFlag(static_cast<EventFlags>(FLAG_MILES_SS_ENTRANCE_CASINO));
            ClearEventFlag(static_cast<EventFlags>(FLAG_KNUCKLES_SS_ENTRANCE_CASINO));

            //Speed Highway
            ClearEventFlag(static_cast<EventFlags>(FLAG_SONIC_SS_CARD));
            ClearEventFlag(static_cast<EventFlags>(FLAG_SONIC_SS_ENTRANCE_HIGHWAY));
            ClearEventFlag(static_cast<EventFlags>(FLAG_MILES_SS_ENTRANCE_HIGHWAY));

            //Red Mountain
            ClearEventFlag(static_cast<EventFlags>(FLAG_SONIC_MR_ENTRANCE_MOUNTAIN));
            ClearEventFlag(static_cast<EventFlags>(FLAG_E102_MR_ENTRANCE_MOUNTAIN));

            //Lost World
            ClearEventFlag(static_cast<EventFlags>(FLAG_KNUCKLES_MR_REDCUBE));
            ClearEventFlag(static_cast<EventFlags>(FLAG_KNUCKLES_MR_BLUECUBE));

            //Sand Hill
            ClearEventFlag(static_cast<EventFlags>(FLAG_SONIC_MR_ENTRANCE_SANDBOARD));
            ClearEventFlag(static_cast<EventFlags>(FLAG_MILES_MR_ENTRANCE_SANDBOARD));

            //FinalEgg
            ClearEventFlag(static_cast<EventFlags>(FLAG_SONIC_MR_ENTRANCE_FINALEGG));

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

            ClearEventFlag(static_cast<EventFlags>(FLAG_SONIC_EC_TRANSFORM));
            ClearEventFlag(static_cast<EventFlags>(FLAG_MILES_EC_TRANSFORM));
            ClearEventFlag(static_cast<EventFlags>(FLAG_KNUCKLES_EC_TRANSFORM));
            ClearEventFlag(static_cast<EventFlags>(FLAG_AMY_EC_TRANSFORM));
            ClearEventFlag(static_cast<EventFlags>(FLAG_E102_EC_TRANSFORM));
            ClearEventFlag(static_cast<EventFlags>(FLAG_BIG_EC_TRANSFORM));
        }


        WriteSaveFile();
        _loadCharacterNextFrame = 0;
    }
}
