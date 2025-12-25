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
        WriteSaveFile();
        _loadCharacterNextFrame = 0;
    }
}
