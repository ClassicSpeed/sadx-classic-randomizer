#pragma once
#include <queue>

#include "../../pch.h"
#include "../../configuration/options/Options.h"
#include "../../application/structs/ItemData.h"
#include "../../application/structs/WeightedRandomSelector.h"
#include "../reactionManager/ReactionManager.h"


#define RING_LOSS_SOUND_ID 0
#define RING_GAIN_SOUND_ID 7

struct RingDifference
{
    int ringDifference;
    int hardRingDifference;
};


class CharacterManager : public IOnFrame
{
public:
    static CharacterManager& Init(Options& options, Settings& settings, GameStatus& gameStatus, ReactionManager& reactionManager)
    {
        if (_instance == nullptr)
            _instance = new CharacterManager(options, settings,gameStatus,  reactionManager);
        return *_instance;
    }

    void OnFrame() override;

    void GiveUpgrade(Upgrades upgrade);
    void RemoveUpgrade(Upgrades upgrade);
    void KillPlayer();
    void ProcessRings(Sint16 amount);
    RingDifference GetRingDifference();
    void GiveFillerItem(FillerType filler, bool priority);
    void SetStartingCharacter(int startingCharacterIndex);
    void RemoveStatusEffects();
    Options& options;
    Settings& settings;
    GameStatus& gameStatus;
    ReactionManager& reactionManager;
    int lastRingAmount;
    bool reverseControlsEnabled = false;

private:
    explicit CharacterManager(Options& options,  Settings& settings, GameStatus& gameStatus,ReactionManager& reactionManager);
    inline static CharacterManager* _instance = nullptr;

    void ActivateFiller(FillerType filler);
    void FreezePlayer();
    void IncrementGravity();
    void ReverseControls();
    void SpawnSpring();
    void SpawnEnemies(void (*enemyFunc)(task* tp));
    std::deque<FillerType> _remainingFiller;

    float _fillerDuration = 2.5f;
    std::clock_t _fillerTimer = -1;

    task* _springTask;
    float _springDuration = 2.0f;
    std::clock_t _springTimer = -1;

    float _freezeDuration = 2.0f;
    std::clock_t _freezeTimer = -1;

    float _gravityDuration = 7.0f;
    std::clock_t _gravityTimer = -1;

    std::clock_t _reverseControlsTimer = -1;
};
