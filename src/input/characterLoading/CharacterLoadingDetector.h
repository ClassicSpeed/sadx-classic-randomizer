#pragma once

#include "../../application/Randomizer.h"


class CharacterLoadingDetector
{
public:
    explicit CharacterLoadingDetector(Randomizer& randomizer);

    void OnCharacterSelectScreenLoaded() const;
    void OnCharacterLoaded();
    void OnPlayingFrame();

private:
    Randomizer& _randomizer;
    int _loadCharacterNextFrame = 0;
};
