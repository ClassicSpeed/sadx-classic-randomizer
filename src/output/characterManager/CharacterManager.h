#pragma once
#include <queue>

#include "../../pch.h"
#include "../../application/structs/Options.h"
#include "../../application/structs/UnlockStatus.h"
#include "../../application/structs/ItemData.h"
#include "../../application/structs/WeightedRandomSelector.h"


#define RING_LOSS_SOUND_ID 0
#define RING_GAIN_SOUND_ID 7

class CharacterManager
{
public:
    CharacterManager();

    void GiveUpgrade(Upgrades upgrade);
    void RemoveUpgrade(Upgrades upgrade);
    void UpdateOptions(Options newOptions);
    void UpdateUnlockStatus(UnlockStatus unlockStatus);
    void KillPlayer();
    void ProcessRings(Sint16 amount);
    int GetRingDifference();
    void GiveFillerItem(FillerType filler);
    void OnPlayingFrame();
    void SetStartingCharacter(int startingCharacterIndex);
    void SetCharacterVoiceReactions(bool eggmanCommentOnTrap, bool otherCharactersCommentOnTrap,
                                    bool currentCharacterReactToTrap);
    void SetReverseControlTrapDuration(int reverseControlTrapDuration);
    void SetTrapsOnAdventureFields(bool trapsOnAdventureFields);
    void SetTrapsOnBossFights(bool trapsOnBossFights);
    void SetTrapsOnPerfectChaosFight(bool trapsOnPerfectChaosFight);
    void RemoveStatusEffects();
    Options options;
    UnlockStatus unlockStatus;
    int lastRingAmount;
    bool reverseControlsEnabled = false;

private:
    void ActivateFiller(FillerType filler);
    void PlayRandomTrapVoice(FillerType filler);
    void FreezePlayer();
    void IncrementGravity();
    void ReverseControls();
    void SpawnSpring();
    void SpawnEnemies(void (*enemyFunc)(task* tp));
    std::queue<FillerType> _remainingFiller;

    float _fillerDuration = 2.5f;
    std::clock_t _fillerTimer = -1;

    task* _springTask;
    float _springDuration = 2.0f;
    std::clock_t _springTimer = -1;

    float _freezeDuration = 2.0f;
    std::clock_t _freezeTimer = -1;

    float _gravityDuration = 7.0f;
    std::clock_t _gravityTimer = -1;

    float _reverseControlsDuration = 7.0f;
    std::clock_t _reverseControlsTimer = -1;

    bool _eggmanCommentOnTrap = true;
    bool _otherCharactersCommentOnTrap = true;
    bool _currentCharacterReactToTrap = true;
    
    bool _trapsOnBossFights= true;
    bool _trapsOnAdventureFields= true;
    bool _trapsOnPerfectChaosFight = false;
};
