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

            for (int i = SSVAR_EGG_ON; i < 512; i++)
                if (i != FLAG_SONIC_SS_LIGHTSHOOSE && i != FLAG_SONIC_SS_CRYSTALRING && i != FLAG_SONIC_MR_ANCIENT_LIGHT
                    && i != FLAG_MILES_SS_JETANKLET && i != FLAG_MILES_MR_RHYTHMBROOCH
                    && i != FLAG_KNUCKLES_MR_SHOVELCLAW && i != FLAG_KNUCKLES_MR_FIGHTINGGROVE
                    && i != FLAG_AMY_MR_FIGHTERSFEATHER && i != FLAG_AMY_EC_LONGHAMMER
                    && i != FLAG_E102_EC_BOOSTER && i != FLAG_E102_EC_TYPE3LASER
                    && i != FLAG_BIG_MR_LIFEBELT && i != FLAG_BIG_MR_POWERROD
                    && i != FLAG_BIG_RUAR_NORMAL && i != FLAG_BIG_RUAR_RED
                    && i != FLAG_BIG_RUAR_GOLD && i != FLAG_BIG_RUAR_BLUE)
                    EventFlagArray[i] = 1;
        }


        WriteSaveFile();
        _loadCharacterNextFrame = 0;
    }
}
