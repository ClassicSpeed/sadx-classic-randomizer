#include "CharacterLoadingDetector.h"
#include "../../pch.h"



CharacterLoadingDetector* characterLoadingDetectorPtr = nullptr;

CharacterLoadingDetector::CharacterLoadingDetector(Randomizer& randomizer)
    : _randomizer(randomizer)
{
    characterLoadingDetectorPtr = this;
}

//Character loaded
FunctionHookAdd(0x4157C0, []
                {
                characterLoadingDetectorPtr->OnCharacterLoaded();
                });

//Character selection screen loaded
FunctionHookAdd(0x512BC0, []
                {
                characterLoadingDetectorPtr->OnCharacterLoaded();
                characterLoadingDetectorPtr->OnCharacterSelectScreenLoaded();
                });


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

void CharacterLoadingDetector::OnPlayingFrame()
{
    if (_loadCharacterNextFrame > 1)
        _loadCharacterNextFrame--;


    if (_loadCharacterNextFrame == 1)
    {
        _randomizer.OnCharacterLoaded();
        _loadCharacterNextFrame = 0;
    }
}
