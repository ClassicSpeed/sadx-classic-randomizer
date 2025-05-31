#include "Options.h"

//TODO: Move to helpers?
int Clamp(const int value, const int min, const int max)
{
    if (value < min) return min;
    if (value > max) return max;
    return value;
}

void Options::GoalRequiresLevels(const int newGoalRequiresLevels)
{
    this->goalRequiresLevels = newGoalRequiresLevels;
}

void Options::GoalRequiresChaosEmeralds(const int newGoalRequiresChaosEmeralds)
{
    this->goalRequiresChaosEmeralds = newGoalRequiresChaosEmeralds;
}

void Options::GoalRequiresEmblems(const int newGoalRequiresEmblems)
{
    this->goalRequiresEmblems = newGoalRequiresEmblems;
}

void Options::GoalRequiresMissions(const int newGoalRequiresMissions)
{
    this->goalRequiresMissions = newGoalRequiresMissions;
}

void Options::GoalRequiresBosses(const int newGoalRequiresBosses)
{
    this->goalRequiresBosses = newGoalRequiresBosses;
}

void Options::GoalRequiresChaoRaces(const int newGoalRequiresChaoRaces)
{
    this->goalRequiresChaoRaces = newGoalRequiresChaoRaces;
}

void Options::LogicLevel(const int logicLevel)
{
    if (logicLevel > 1)
        this->expertMode = true;
    else
        this->expertMode = false;
}

void Options::EmblemsForPerfectChaos(const int newEmblemGoal)
{
    this->emblemGoal = max(1, newEmblemGoal);
}

void Options::LevelForPerfectChaos(const int newLevelGoal)
{
    this->levelGoal = max(1, newLevelGoal);
}

void Options::MissionForPerfectChaos(const int newMissionGoal)
{
    this->missionGoal = max(1, newMissionGoal);
}

void Options::BossesForPerfectChaos(const int newBossesGoal)
{
    this->bossesGoal = max(1, newBossesGoal);
}

void Options::MissionModeChecks(const int newMissionModeEnabled)
{
    this->missionModeEnabled = newMissionModeEnabled;
}

void Options::MissionBlackList(const std::map<int, int>& newMissionBlacklist)
{
    if (newMissionBlacklist.empty())
        return;
    std::vector<int> blacklistedMissions;

    for (const auto& mission : newMissionBlacklist)
        blacklistedMissions.push_back(mission.first);

    this->missionBlacklist = blacklistedMissions;
}

void Options::AutoStartMissions(const int newAutoStartMissions)
{
    this->autoStartMissions = newAutoStartMissions > 0;
}

void Options::EnemySanity(const int newEnemySanity)
{
    this->enemySanity = newEnemySanity;
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

void Options::CapsuleSanity(const int newCapsuleSanity)
{
    this->capsuleSanity = newCapsuleSanity;
}

void Options::PinballCapsules(const int newIncludePinballCapsules)
{
    this->includePinballCapsules = newIncludePinballCapsules;
}

void Options::LifeCapsuleSanity(const int newLifeCapsuleSanity)
{
    this->lifeCapsuleSanity = newLifeCapsuleSanity;
}

void Options::ShieldCapsuleSanity(const int newShieldCapsuleSanity)
{
    this->shieldCapsuleSanity = newShieldCapsuleSanity;
}

void Options::PowerUpCapsuleSanity(const int newPowerUpCapsuleSanity)
{
    this->powerUpCapsuleSanity = newPowerUpCapsuleSanity;
}

void Options::RingCapsuleSanity(const int newRingCapsuleSanity)
{
    this->ringCapsuleSanity = newRingCapsuleSanity;
}

void Options::FishSanity(const int newFishSanity)
{
    this->fishSanity = newFishSanity;
}

void Options::LazyFishing(const int newLazyFishing)
{
    this->lazyFishing = newLazyFishing > 0;
}

void Options::ProgressionItems(const std::map<int, int>& newProgressionItems)
{
    if (newProgressionItems.empty())
        return;
    std::vector<int64_t> progressionItemsList;

    for (const auto& progressionItem : newProgressionItems)
        progressionItemsList.push_back(progressionItem.first - baseId);

    this->progressionItems = progressionItemsList;
}


void Options::StartingCharacter(const int newStartingCharacterIndex)
{
    this->startingCharacterIndex = newStartingCharacterIndex;
}

void Options::LevelEntranceMap(const std::map<int, int>& levelEntrancesValues)
{
    this->levelEntrancesMap = levelEntrancesValues;
}

void Options::SetEntranceRandomizer(const int enableEntranceRandomizer)
{
    this->entranceRandomizer = enableEntranceRandomizer;
}

void Options::SetDeathLink(const int newDeathLinkActive)
{
    if (this->deathLinkOverride == DeathLinkForceEnabled)
        this->deathLinkActive = true;
    else if (this->deathLinkOverride == DeathLinkForceDisabled)
        this->deathLinkActive = false;
    else
        this->deathLinkActive = newDeathLinkActive;
}

void Options::SendDeathLinkChance(const int newSendDeathLinkChance)
{
    this->sendDeathLinkChance = Clamp(newSendDeathLinkChance, 1, 100);
}
void Options::ReceiveDeathLinkChance(const int newReceiveDeathLinkChance)
{
    this->receiveDeathLinkChance = Clamp(newReceiveDeathLinkChance, 1, 100);
}
    
void Options::SetRingLink(const int newRingLinkActive)
{
    if (this->ringLinkOverride == RingLinkForceEnabled
        || this->ringLinkOverride == RingLinkForceEnabledHard)
        this->ringLinkActive = true;
    else if (this->ringLinkOverride == RingLinkForceDisabled)
        this->ringLinkActive = false;
    else
        this->ringLinkActive = newRingLinkActive;
}

void Options::SetCasinopolisRingLink(const int newCasinopolisRingLink)
{
    this->casinopolisRingLink = newCasinopolisRingLink;
}

void Options::SetHardRingLink(const int newHardRingLinkActive)
{
    if (this->ringLinkOverride == RingLinkForceEnabledHard)
        this->hardRingLinkActive = true;
    else if (this->ringLinkOverride == RingLinkForceDisabled
        || this->ringLinkOverride == RingLinkForceEnabled)
        this->hardRingLinkActive = false;
    else
        this->hardRingLinkActive = newHardRingLinkActive;
}

void Options::SetTrapLink(const int newTrapLinkActive)
{
    if (this->trapLinkOverride == TrapLinkForceEnabled)
        this->trapLinkActive = true;
    else if (this->trapLinkOverride == TrapLinkForceDisabled)
        this->trapLinkActive = false;
    else
        this->trapLinkActive = newTrapLinkActive;
}

void Options::SetRingLoss(const int newRingLoss)
{
    if (this->ringLossOverride == RingLossDefault)
        this->ringLoss = static_cast<RingLoss>(newRingLoss);
    else if (this->ringLossOverride == RingLossForceClassic)
        this->ringLoss = Classic;
    else if (this->ringLossOverride == RingLossForceModern)
        this->ringLoss = Modern;
    else if (this->ringLossOverride == RingLossForceOhko)
        this->ringLoss = OneHitKnockOut;
    else if (this->ringLossOverride == RingLossForceOhkoNoShields)
        this->ringLoss = OneHitKnockOutNoShields;
}

void Options::TwinkleCircuitCheck(const int newTwinkleCircuitCheck)
{
    this->twinkleCircuitCheck = newTwinkleCircuitCheck;
}

void Options::MultipleTwinkleCircuitChecks(const int newMultipleTwinkleCircuitChecks)
{
    this->multipleTwinkleCircuitChecks = newMultipleTwinkleCircuitChecks;
}

void Options::SkyChaseChecks(const int newSkyChaseChecks)
{
    this->skyChaseChecks = newSkyChaseChecks;
}

void Options::SkyChaseChecksHard(const int newSkyChaseChecksHard)
{
    this->skyChaseChecksHard = newSkyChaseChecksHard;
}

void Options::BossChecks(const int newBossChecks)
{
    this->bossChecks = newBossChecks;
}

void Options::UnifyChaos4(const int newUnifyChaos4)
{
    this->unifyChaos4 = newUnifyChaos4;
}

void Options::UnifyChaos6(const int newUnifyChaos6)
{
    this->unifyChaos6 = newUnifyChaos6;
}

void Options::UnifyEggHornet(const int newUnifyEggHornet)
{
    this->unifyEggHornet = newUnifyEggHornet;
}

void Options::SetMusicSource(const int newMusicSource)
{
    if (this->musicSource == MusicSourceNone)
        this->musicSource = static_cast<MusicSource>(newMusicSource);
}

void Options::SetMusicShuffle(const int newMusicShuffle)
{
    if (this->musicShuffle == MusicShuffleNone)
        this->musicShuffle = static_cast<MusicShuffle>(newMusicShuffle);
}

void Options::SetMusicShuffleConsistency(const int newMusicShuffleConsistency)
{
    if (this->musicShuffleConsistency == MusicShuffleConsistencyNone)
        this->musicShuffleConsistency = static_cast<MusicShuffleConsistency>(
            newMusicShuffleConsistency);
}

void Options::SetMusicShuffleSeed(const int newMusicShuffleSeed)
{
    this->musicShuffleSeed = newMusicShuffleSeed;
}

void Options::SetLifeCapsulesChangeSongs(const int newLifeCapsulesChangeSongs)
{
    if (this->lifeCapsulesChangeSongs == LifeCapsulesChangeSongsNone)
        this->lifeCapsulesChangeSongs = newLifeCapsulesChangeSongs
                                            ? LifeCapsulesChangeSongsEnabled
                                            : LifeCapsulesChangeSongsDisabled;
}


void Options::SetIceTrapWeight(const int newIceTrapWeight)
{
    this->iceTrapWeight = newIceTrapWeight;
}

void Options::SetSpringTrapWeight(const int newSpringTrapWeight)
{
    this->springTrapWeight = newSpringTrapWeight;
}

void Options::SetPoliceTrapWeight(const int newPoliceTrapWeight)
{
    this->policeTrapWeight = newPoliceTrapWeight;
}

void Options::SetBuyonTrapWeight(const int newBuyonTrapWeight)
{
    this->buyonTrapWeight = newBuyonTrapWeight;
}

void Options::SetReverseTrapWeight(const int newReverseTrapWeight)
{
    this->reverseTrapWeight = newReverseTrapWeight;
}

void Options::SetGravityTrapWeight(const int newGravityTrapWeight)
{
    this->gravityTrapWeight = newGravityTrapWeight;
}

void Options::SetReverseControlTrapDuration(const int reverseControlTrapDuration)
{
    this->reverseControlsDuration = static_cast<float>(reverseControlTrapDuration);
}

void Options::SetTrapsOnAdventureFields(const int trapsOnAdventureFields)
{
    this->trapsOnAdventureFields = trapsOnAdventureFields > 0;
}

void Options::SetTrapsOnBossFights(const int trapsOnBossFights)
{
    this->trapsOnBossFights = trapsOnBossFights > 0;
}

void Options::SetTrapsOnPerfectChaosFight(const int trapsOnPerfectChaosFight)
{
    this->trapsOnPerfectChaosFight = trapsOnPerfectChaosFight > 0;
}


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

void Options::SetCharacterStatingArea(const Characters character, const int startingArea)
{
    switch (character)
    {
    case Characters_Sonic:
        this->sonicStartingArea = static_cast<StartingArea>(startingArea);
        break;
    case Characters_Tails:
        this->tailsStartingArea = static_cast<StartingArea>(startingArea);
        break;
    case Characters_Knuckles:
        this->knucklesStartingArea = static_cast<StartingArea>(startingArea);
        break;
    case Characters_Amy:
        this->amyStartingArea = static_cast<StartingArea>(startingArea);
        break;
    case Characters_Big:
        this->bigStartingArea = static_cast<StartingArea>(startingArea);
        break;
    case Characters_Gamma:
        this->gammaStartingArea = static_cast<StartingArea>(startingArea);
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

bool Options::IsTrapEnabled(const FillerType filler) const
{
    if (filler == NoFiller)
        return false;
    if (filler == IceTrap && iceTrapWeight > 0)
        return true;
    if (filler == SpringTrap && springTrapWeight > 0)
        return true;
    if (filler == PoliceTrap && policeTrapWeight > 0)
        return true;
    if (filler == BuyonTrap && buyonTrapWeight > 0)
        return true;
    if (filler == ReverseTrap && reverseTrapWeight > 0)
        return true;
    if (filler == GravityTrap && gravityTrapWeight > 0)
        return true;

    return false;
}

void Options::SetCharacterVoiceReactions(const bool eggmanCommentOnCharacterUnlock,
                                         const bool currentCharacterCommentOnCharacterUnlock,
                                         const bool unlockedCharacterCommentOnCharacterUnlock,
                                         const bool eggmanCommentOnKeyItems, const bool tikalCommentOnKeyItems,
                                         const bool currentCharacterCommentOnKeyItems,
                                         const bool showCommentsSubtitles)
{
    this->eggmanCommentOnCharacterUnlock = eggmanCommentOnCharacterUnlock;
    this->currentCharacterCommentOnCharacterUnlock = currentCharacterCommentOnCharacterUnlock;
    this->unlockedCharacterCommentOnCharacterUnlock = unlockedCharacterCommentOnCharacterUnlock;
    this->eggmanCommentOnKeyItems = eggmanCommentOnKeyItems;
    this->tikalCommentOnKeyItems = tikalCommentOnKeyItems;
    this->currentCharacterCommentOnKeyItems = currentCharacterCommentOnKeyItems;
    this->showCommentsSubtitles = showCommentsSubtitles;
}


void Options::SetCharacterVoiceReactions(const bool eggmanCommentOnTrap,
                                         const bool otherCharactersCommentOnTrap,
                                         const bool currentCharacterReactToTrap,
                                         const bool showCommentsSubtitles)
{
    this->eggmanCommentOnTrap = eggmanCommentOnTrap;
    this->otherCharactersCommentOnTrap = otherCharactersCommentOnTrap;
    this->currentCharacterReactToTrap = currentCharacterReactToTrap;
    this->showCommentsSubtitles = showCommentsSubtitles;
}

void Options::SetLinksOverrides(const DeathLinkOverride newDeathLinkOverride,
                                     const RingLinkOverride newRingLinkOverride,
                                     const RingLossOverride newRingLossOverride,
                                     const TrapLinkOverride newTrapLinkOverride)
{
    this->deathLinkOverride = newDeathLinkOverride;
    this->ringLinkOverride = newRingLinkOverride;
    this->ringLossOverride = newRingLossOverride;
    this->trapLinkOverride = newTrapLinkOverride;
}

