#include "CharacterLoadingDetector.h"


CharacterLoadingDetector::CharacterLoadingDetector(Randomizer& randomizer) : _randomizer(randomizer)
{
}


void CharacterLoadingDetector::OnCharacterLoaded()
{
    //Workaround to load the upgrades after the event flag logics was applied
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
