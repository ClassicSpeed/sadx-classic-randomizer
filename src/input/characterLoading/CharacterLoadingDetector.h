#pragma once
#include <vector>

#include "../../application/Randomizer.h"
#include "SADXModLoader.h"


class CharacterLoadingDetector
{
public:
    explicit CharacterLoadingDetector(Randomizer& randomizer)
        : _randomizer(randomizer)
    {
    }

    void OnCharacterLoaded();
    void OnPlayingFrame();

private:
    Randomizer& _randomizer;
    int _loadCharacterNextFrame = 0;
};
