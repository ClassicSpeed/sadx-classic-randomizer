#include "Options.h"


Options::Options(Settings& settings) : _settings(settings)
{
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

void Options::SetGatingMode(const int gatingMode)
{
    this->gatingMode = static_cast<GatingMode>(gatingMode);
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

void Options::EnemySanityList(const std::map<int, int>& newEnemySanityList)
{
    if (newEnemySanityList.empty())
        return;
    std::vector<EnemySanityCategory> enemySanityCategories;

    for (const auto& enemySanityCategory : newEnemySanityList)
        enemySanityCategories.push_back(static_cast<EnemySanityCategory>(enemySanityCategory.first));

    this->enemySanityList = enemySanityCategories;
}

void Options::MissableEnemies(const int newMissableEnemies)
{
    this->missableEnemies = newMissableEnemies;
}


void Options::CapsuleSanity(const int newCapsuleSanity)
{
    this->capsuleSanity = newCapsuleSanity;
}

void Options::CapsuleSanityList(const std::map<int, int>& newCapsuleSanityList)
{
    if (newCapsuleSanityList.empty())
        return;
    std::vector<CapsuleSanityCategory> capsuleSanityCategories;

    for (const auto& enemySanityCategory : newCapsuleSanityList)
        capsuleSanityCategories.push_back(static_cast<CapsuleSanityCategory>(enemySanityCategory.first));

    this->capsuleSanityList = capsuleSanityCategories;
}

void Options::MissableCapsules(const int newMissableCapsules)
{
    this->missableCapsules = newMissableCapsules;
}

void Options::PinballCapsules(const int newIncludePinballCapsules)
{
    this->includePinballCapsules = newIncludePinballCapsules;
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

void Options::SetEntranceEmblemValueMap(const std::map<int, int>& entranceEmblemValueMap)
{
    this->entranceEmblemValueMap = entranceEmblemValueMap;
}


void Options::SetEntranceRandomizer(const int enableEntranceRandomizer)
{
    this->entranceRandomizer = enableEntranceRandomizer;
}

void Options::SetDeathLink(const int newDeathLinkActive)
{
    if (_settings.deathLinkOverride == DeathLinkForceEnabled)
        this->deathLinkActive = true;
    else if (_settings.deathLinkOverride == DeathLinkForceDisabled)
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
    if (_settings.ringLinkOverride == RingLinkDefault)
        this->ringLink = static_cast<RingLink>(newRingLinkActive);
    else
        this->ringLink = static_cast<RingLink>(_settings.ringLinkOverride - 1);
}

void Options::SetTrapLink(const int newTrapLinkActive)
{
    if (_settings.trapLinkOverride == TrapLinkForceEnabled)
        this->trapLinkActive = true;
    else if (_settings.trapLinkOverride == TrapLinkForceDisabled)
        this->trapLinkActive = false;
    else
        this->trapLinkActive = newTrapLinkActive;
}

void Options::SetRingLoss(const int newRingLoss)
{
    if (_settings.ringLossOverride == RingLossDefault)
        this->ringLoss = static_cast<RingLoss>(newRingLoss);
    else if (_settings.ringLossOverride == RingLossForceClassic)
        this->ringLoss = Classic;
    else if (_settings.ringLossOverride == RingLossForceModern)
        this->ringLoss = Modern;
    else if (_settings.ringLossOverride == RingLossForceOhko)
        this->ringLoss = OneHitKnockOut;
    else if (_settings.ringLossOverride == RingLossForceOhkoNoShields)
        this->ringLoss = OneHitKnockOutNoShields;
}

void Options::TwinkleCircuitCheck(const int newTwinkleCircuitCheck)
{
    this->twinkleCircuitChecks = newTwinkleCircuitCheck;
}

void Options::SkyChaseChecks(const int newSkyChaseChecks)
{
    this->skyChaseChecks = newSkyChaseChecks;
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
    if (_settings.musicSource == MusicSourceNone)
        this->musicSource = static_cast<MusicSource>(newMusicSource);
    else
        this->musicSource = _settings.musicSource;
}

void Options::SetMusicShuffle(const int newMusicShuffle)
{
    if (_settings.musicShuffle == MusicShuffleNone)
        this->musicShuffle = static_cast<MusicShuffle>(newMusicShuffle);
    else
        this->musicShuffle = _settings.musicShuffle;
}

void Options::SetMusicShuffleConsistency(const int newMusicShuffleConsistency)
{
    if (_settings.musicShuffleConsistency == MusicShuffleConsistencyNone)
        this->musicShuffleConsistency = static_cast<MusicShuffleConsistency>(
            newMusicShuffleConsistency);
    else
        this->musicShuffleConsistency = _settings.musicShuffleConsistency;
}

void Options::SetMusicShuffleSeed(const int newMusicShuffleSeed)
{
    this->musicShuffleSeed = newMusicShuffleSeed;
}

void Options::SetLifeCapsulesChangeSongs(const int newLifeCapsulesChangeSongs)
{
    if (_settings.lifeCapsulesChangeSongs == LifeCapsulesChangeSongsNone)
        this->lifeCapsulesChangeSongs = newLifeCapsulesChangeSongs
                                            ? LifeCapsulesChangeSongsEnabled
                                            : LifeCapsulesChangeSongsDisabled;
    else
        this->lifeCapsulesChangeSongs = _settings.lifeCapsulesChangeSongs;
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

void Options::SetTrapsOnAdventureFields(const int newTrapsOnAdventureFields)
{
    this->trapsOnAdventureFields = newTrapsOnAdventureFields > 0;
}

void Options::SetTrapsOnBossFights(const int newTrapsOnBossFights)
{
    this->trapsOnBossFights = newTrapsOnBossFights > 0;
}

void Options::SetTrapsOnPerfectChaosFight(const int newTrapsOnPerfectChaosFight)
{
    this->trapsOnPerfectChaosFight = newTrapsOnPerfectChaosFight > 0;
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
        return std::find(enemySanityList.begin(), enemySanityList.end(), SonicEnemySanity) != enemySanityList.end();
    case Characters_Tails:
        return std::find(enemySanityList.begin(), enemySanityList.end(), TailsEnemySanity) != enemySanityList.end();
    case Characters_Knuckles:
        return std::find(enemySanityList.begin(), enemySanityList.end(), KnucklesEnemySanity) != enemySanityList.end();
    case Characters_Amy:
        return std::find(enemySanityList.begin(), enemySanityList.end(), AmyEnemySanity) != enemySanityList.end();
    case Characters_Big:
        return std::find(enemySanityList.begin(), enemySanityList.end(), BigEnemySanity) != enemySanityList.end();
    case Characters_Gamma:
        return std::find(enemySanityList.begin(), enemySanityList.end(), GammaEnemySanity) != enemySanityList.end();
    case Characters_Eggman:
    case Characters_Tikal:
    case Characters_MetalSonic:
        break;
    }
    return false;
}

bool Options::GetCapsuleSanityByType(const Characters character, const CapsuleType capsuleType) const
{
    switch (capsuleType)
    {
    case ExtraLifeCapsule:
        switch (character)
        {
        case Characters_Sonic:
            return std::find(capsuleSanityList.begin(), capsuleSanityList.end(), SonicLife) != capsuleSanityList.end();
        case Characters_Tails:
            return std::find(capsuleSanityList.begin(), capsuleSanityList.end(), TailsLife) != capsuleSanityList.end();
        case Characters_Knuckles:
            return std::find(capsuleSanityList.begin(), capsuleSanityList.end(), KnucklesLife) != capsuleSanityList.
                end();
        case Characters_Amy:
            return std::find(capsuleSanityList.begin(), capsuleSanityList.end(), AmyLife) != capsuleSanityList.end();
        case Characters_Big:
            return std::find(capsuleSanityList.begin(), capsuleSanityList.end(), BigLife) != capsuleSanityList.end();
        case Characters_Gamma:
            return std::find(capsuleSanityList.begin(), capsuleSanityList.end(), GammaLife) != capsuleSanityList.end();
        case Characters_Eggman:
        case Characters_Tikal:
        case Characters_MetalSonic:
            break;
        }
        return false;
    case ShieldCapsule:
    case MagneticShieldCapsule:
        switch (character)
        {
        case Characters_Sonic:
            return std::find(capsuleSanityList.begin(), capsuleSanityList.end(), SonicShield) != capsuleSanityList.
                end();
        case Characters_Tails:
            return std::find(capsuleSanityList.begin(), capsuleSanityList.end(), TailsShield) != capsuleSanityList.
                end();
        case Characters_Knuckles:
            return std::find(capsuleSanityList.begin(), capsuleSanityList.end(), KnucklesShield) != capsuleSanityList.
                end();
        case Characters_Amy:
            return std::find(capsuleSanityList.begin(), capsuleSanityList.end(), AmyShield) != capsuleSanityList.end();
        case Characters_Big:
            return std::find(capsuleSanityList.begin(), capsuleSanityList.end(), BigShield) != capsuleSanityList.end();
        case Characters_Gamma:
            return std::find(capsuleSanityList.begin(), capsuleSanityList.end(), GammaShield) != capsuleSanityList.
                end();
        case Characters_Eggman:
        case Characters_Tikal:
        case Characters_MetalSonic:
            break;
        }
        return false;
    case SpeedUpCapsule:
    case InvincibilityCapsule:
    case BombCapsule:
        switch (character)
        {
        case Characters_Sonic:
            return std::find(capsuleSanityList.begin(), capsuleSanityList.end(), SonicPowerUp) != capsuleSanityList.
                end();
        case Characters_Tails:
            return std::find(capsuleSanityList.begin(), capsuleSanityList.end(), TailsPowerUp) != capsuleSanityList.
                end();
        case Characters_Knuckles:
            return std::find(capsuleSanityList.begin(), capsuleSanityList.end(), KnucklesPowerUp) != capsuleSanityList.
                end();
        case Characters_Amy:
            return std::find(capsuleSanityList.begin(), capsuleSanityList.end(), AmyPowerUp) != capsuleSanityList.end();
        case Characters_Big:
            return std::find(capsuleSanityList.begin(), capsuleSanityList.end(), BigPowerUp) != capsuleSanityList.end();
        case Characters_Gamma:
            return std::find(capsuleSanityList.begin(), capsuleSanityList.end(), GammaPowerUp) != capsuleSanityList.
                end();
        case Characters_Eggman:
        case Characters_Tikal:
        case Characters_MetalSonic:
            break;
        }
        return false;
    case FiveRingsCapsule:
    case TenRingsCapsule:
    case RandomRingsCapsule:
        switch (character)
        {
        case Characters_Sonic:
            return std::find(capsuleSanityList.begin(), capsuleSanityList.end(), SonicRing) != capsuleSanityList.end();
        case Characters_Tails:
            return std::find(capsuleSanityList.begin(), capsuleSanityList.end(), TailsRing) != capsuleSanityList.end();
        case Characters_Knuckles:
            return std::find(capsuleSanityList.begin(), capsuleSanityList.end(), KnucklesRing) != capsuleSanityList.
                end();
        case Characters_Amy:
            return std::find(capsuleSanityList.begin(), capsuleSanityList.end(), AmyRing) != capsuleSanityList.end();
        case Characters_Big:
            return std::find(capsuleSanityList.begin(), capsuleSanityList.end(), BigRing) != capsuleSanityList.end();
        case Characters_Gamma:
            return std::find(capsuleSanityList.begin(), capsuleSanityList.end(), GammaRing) != capsuleSanityList.end();
        case Characters_Eggman:
        case Characters_Tikal:
        case Characters_MetalSonic:
            break;
        }
        return false;
    }
    return false;
}

void Options::SetCharacterStatingArea(const Characters character, const int startingArea)
{
    switch (character)
    {
    case Characters_Sonic:
        this->sonicStartingArea = static_cast<Area>(startingArea);
        break;
    case Characters_Tails:
        this->tailsStartingArea = static_cast<Area>(startingArea);
        break;
    case Characters_Knuckles:
        this->knucklesStartingArea = static_cast<Area>(startingArea);
        break;
    case Characters_Amy:
        this->amyStartingArea = static_cast<Area>(startingArea);
        break;
    case Characters_Big:
        this->bigStartingArea = static_cast<Area>(startingArea);
        break;
    case Characters_Gamma:
        this->gammaStartingArea = static_cast<Area>(startingArea);
        break;
    case Characters_Eggman:
    case Characters_Tikal:
    case Characters_MetalSonic:
        break;
    }
}

Area Options::GetCharacterStartingArea(const Characters character) const
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
    return SSMain;
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
