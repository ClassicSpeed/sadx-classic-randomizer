#include "Options.h"


void Options::SetActionStageMissions(const Characters character, const int missions)
{
    switch (character)
    {
    case Characters_Sonic:
        this->sonicActionStageMissions = missions;
        break;
    case Characters_Tails:
        this->tailsActionStageMissions = missions;
        break;
    case Characters_Knuckles:
        this->knucklesActionStageMissions = missions;
        break;
    case Characters_Amy:
        this->amyActionStageMissions = missions;
        break;
    case Characters_Big:
        this->bigActionStageMissions = missions;
        break;
    case Characters_Gamma:
        this->gammaActionStageMissions = missions;
        break;
    case Characters_Eggman:
    case Characters_Tikal:
    case Characters_MetalSonic:
        break;
    }
}

void Options::SetCharacterEnemySanity(const Characters character, const bool characterEnemySanity)
{
    switch (character)
    {
    case Characters_Sonic:
        this->sonicEnemySanity = characterEnemySanity;
        break;
    case Characters_Tails:
        this->tailsEnemySanity = characterEnemySanity;
        break;
    case Characters_Knuckles:
        this->knucklesEnemySanity = characterEnemySanity;
        break;
    case Characters_Amy:
        this->amyEnemySanity = characterEnemySanity;
        break;
    case Characters_Big:
        this->bigEnemySanity = characterEnemySanity;
        break;
    case Characters_Gamma:
        this->gammaEnemySanity = characterEnemySanity;
        break;
    case Characters_Eggman:
    case Characters_Tikal:
    case Characters_MetalSonic:
        break;
    }
}

bool Options::GetCharacterEnemySanity(const Characters character) const
{
    switch (character)
    {
    case Characters_Sonic:
        return this->sonicEnemySanity;
    case Characters_Tails:
        return this->tailsEnemySanity;
    case Characters_Knuckles:
        return this->knucklesEnemySanity;
    case Characters_Amy:
        return this->amyEnemySanity;
    case Characters_Big:
        return this->bigEnemySanity;
    case Characters_Gamma:
        return this->gammaEnemySanity;
    case Characters_Eggman:
    case Characters_Tikal:
    case Characters_MetalSonic:
        break;
    }
    return false;
}

void Options::SetCharacterCapsuleSanity(const Characters character, const bool characterCapsuleSanity)
{
    switch (character)
    {
    case Characters_Sonic:
        this->sonicCapsuleSanity = characterCapsuleSanity;
        break;
    case Characters_Tails:
        this->tailsCapsuleSanity = characterCapsuleSanity;
        break;
    case Characters_Knuckles:
        this->knucklesCapsuleSanity = characterCapsuleSanity;
        break;
    case Characters_Amy:
        this->amyCapsuleSanity = characterCapsuleSanity;
        break;
    case Characters_Big:
        this->bigCapsuleSanity = characterCapsuleSanity;
        break;
    case Characters_Gamma:
        this->gammaCapsuleSanity = characterCapsuleSanity;
        break;
    case Characters_Eggman:
    case Characters_Tikal:
    case Characters_MetalSonic:
        break;
    }
}

bool Options::GetCharacterCapsuleSanity(const Characters character) const
{
    switch (character)
    {
    case Characters_Sonic:
        return this->sonicCapsuleSanity;
    case Characters_Tails:
        return this->tailsCapsuleSanity;
    case Characters_Knuckles:
        return this->knucklesCapsuleSanity;
    case Characters_Amy:
        return this->amyCapsuleSanity;
    case Characters_Big:
        return this->bigCapsuleSanity;
    case Characters_Gamma:
        return this->gammaCapsuleSanity;
    case Characters_Eggman:
    case Characters_Tikal:
    case Characters_MetalSonic:
        break;
    }
    return false;
}

bool Options::GetSpecificCapsuleSanity(const CapsuleType capsuleType) const
{
    switch (capsuleType)
    {
    case ExtraLifeCapsule:
        return this->lifeCapsuleSanity;
    case ShieldCapsule:
    case MagneticShieldCapsule:
        return this->shieldCapsuleSanity;
    case SpeedUpCapsule:
    case InvincibilityCapsule:
    case BombCapsule:
        return this->powerUpCapsuleSanity;
    case FiveRingsCapsule:
    case TenRingsCapsule:
    case RandomRingsCapsule:
        return this->ringCapsuleSanity;
    }
    return false;
}

void Options::SetCharacterStatingArea(const Characters character, const StartingArea startingArea)
{
    switch (character)
    {
    case Characters_Sonic:
        this->sonicStartingArea = startingArea;
        break;
    case Characters_Tails:
        this->tailsStartingArea = startingArea;
        break;
    case Characters_Knuckles:
        this->knucklesStartingArea = startingArea;
        break;
    case Characters_Amy:
        this->amyStartingArea = startingArea;
        break;
    case Characters_Big:
        this->bigStartingArea = startingArea;
        break;
    case Characters_Gamma:
        this->gammaStartingArea = startingArea;
        break;
    case Characters_Eggman:
    case Characters_Tikal:
    case Characters_MetalSonic:
        break;
    }
}

StartingArea Options::GetCharacterStartingArea(const Characters character) const
{
    switch (character)
    {
    case Characters_Sonic:
        return this->sonicStartingArea;
    case Characters_Tails:
        return this->tailsStartingArea;
    case Characters_Knuckles:
        return this->knucklesStartingArea;
    case Characters_Amy:
        return this->amyStartingArea;
    case Characters_Big:
        return this->bigStartingArea;
    case Characters_Gamma:
        return this->gammaStartingArea;
    case Characters_Eggman:
    case Characters_Tikal:
    case Characters_MetalSonic:
        break;
    }
    return StationSquareMain;
}

void Options::SetPlayableCharacter(const Characters character, const bool playable)
{
    switch (character)
    {
    case Characters_Sonic:
        this->playableSonic = playable;
        break;
    case Characters_Tails:
        this->playableTails = playable;
        break;
    case Characters_Knuckles:
        this->playableKnuckles = playable;
        break;
    case Characters_Amy:
        this->playableAmy = playable;
        break;
    case Characters_Big:
        this->playableBig = playable;
        break;
    case Characters_Gamma:
        this->playableGamma = playable;
        break;
    case Characters_Eggman:
    case Characters_Tikal:
    case Characters_MetalSonic:
        break;
    }
}

bool Options::GetPlayableCharacter(const Characters character) const
{
    switch (character)
    {
    case Characters_Sonic:
        return this->playableSonic;
    case Characters_Tails:
        return this->playableTails;
    case Characters_Knuckles:
        return this->playableKnuckles;
    case Characters_Amy:
        return this->playableAmy;
    case Characters_Big:
        return this->playableBig;
    case Characters_Gamma:
        return this->playableGamma;
    case Characters_Eggman:
    case Characters_Tikal:
    case Characters_MetalSonic:
        break;
    }
    return false;
}

bool Options::LocationHasProgressiveItem(int locationId)
{
    return std::find(progressionItems.begin(), progressionItems.end(), locationId) != progressionItems.end();
}

bool Options::MusicSourceIncludeSadx() const
{
    return this->musicSource == MusicSourceSadx || this->musicSource == MusicSourceSadxCustom || this->musicSource
        == MusicSourceSadxSa2B ||
        this->musicSource == MusicSourceSadxSa2BCustom;
}

bool Options::MusicSourceIncludeSa2B() const
{
    return this->musicSource == MusicSourceSa2B || this->musicSource == MusicSourceSa2BCustom || this->musicSource
        == MusicSourceSadxSa2B ||
        this->musicSource == MusicSourceSadxSa2BCustom;
}

bool Options::MusicSourceIncludeCustom() const
{
    return this->musicSource == MusicSourceSadxCustom || this->musicSource == MusicSourceSa2BCustom || this->
        musicSource == MusicSourceSadxSa2BCustom || this->musicSource == MusicSourceCustom;
}
