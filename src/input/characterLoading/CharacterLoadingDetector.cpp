#include "CharacterLoadingDetector.h"


CharacterLoadingDetector::CharacterLoadingDetector(Randomizer& randomizer)
    : _randomizer(randomizer)
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


        //Windy Valley
        ClearEventFlag(static_cast<EventFlags>(FLAG_SONIC_MR_ENTRANCE_WINDY));
        ClearEventFlag(static_cast<EventFlags>(FLAG_SONIC_MR_WINDYSTONE));
        ClearEventFlag(static_cast<EventFlags>(FLAG_MILES_MR_ENTRANCE_WINDY));
        ClearEventFlag(static_cast<EventFlags>(FLAG_MILES_MR_WINDYSTONE));
        ClearEventFlag(static_cast<EventFlags>(FLAG_E102_MR_ENTRANCE_WINDY));
        ClearEventFlag(static_cast<EventFlags>(FLAG_E102_MR_WINDYSTONE));


        WriteSaveFile();
        //Windy Valley
        ClearEventFlag(static_cast<EventFlags>(FLAG_SONIC_MR_ENTRANCE_WINDY));
        ClearEventFlag(static_cast<EventFlags>(FLAG_SONIC_MR_WINDYSTONE));
        ClearEventFlag(static_cast<EventFlags>(FLAG_MILES_MR_ENTRANCE_WINDY));
        ClearEventFlag(static_cast<EventFlags>(FLAG_MILES_MR_WINDYSTONE));
        ClearEventFlag(static_cast<EventFlags>(FLAG_E102_MR_ENTRANCE_WINDY));
        ClearEventFlag(static_cast<EventFlags>(FLAG_E102_MR_WINDYSTONE));

        _loadCharacterNextFrame = 0;
    }
}
