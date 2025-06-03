#pragma once
#include <queue>

#include "../../pch.h"
#include "sadx-mod-loader/SADXModLoader/include/UsercallFunctionHandler.h"
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

inline void EmptyCall()
{
}

class CharacterManager : public IOnFrame
{
public:
    static CharacterManager& Init(Options& options, Settings& settings, GameStatus& gameStatus,
                                  ReactionManager& reactionManager)
    {
        if (_instance == nullptr)
            _instance = new CharacterManager(options, settings, gameStatus, reactionManager);
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

private:
    explicit CharacterManager(Options& options, Settings& settings, GameStatus& gameStatus,
                              ReactionManager& reactionManager);
    inline static CharacterManager* _instance = nullptr;
    Options& _options;
    Settings& _settings;
    GameStatus& _gameStatus;
    ReactionManager& _reactionManager;


    inline static FunctionHook<void> _set0RingsHook{0x425AB0};
    static void OnSet0Rings();

    inline static FunctionHook<void, char> _giveBarrierHook{0x441EA0};
    static void OnGiveBarrier(char character);

    inline static FunctionHook<void, char> _giveMagneticBarrierHook{0x441E30};
    static void OnGiveMagneticBarrier(char character);

    inline static FunctionHook<void, char> _giveInvincibilityHook{0x441F10};
    static void OnGiveInvincibility(char character);

    inline static FunctionHook<int> _getLureQuantityHook{0x46C870};
    static int OnGetLureQuantity();

    inline static FunctionHook<void> _writeAnalogsHook{0x40F170};
    static void OnWriteAnalogs();

    inline static FunctionHook<void, task*> _freezeTrapDisplayHook{0x4A2240};
    static void OnFreezeTrapDisplay(task* tp);

    inline static FunctionHook<void, task*> _scoreDisplayMainHook{0x42BCC0};
    static void OnScoreDisplayMain(task* tp);

    inline static FunctionHook<void, _SC_NUMBERS*> _drawSNumbersHook{0x427BB0};
    static void OnDrawSNumbers(_SC_NUMBERS* pscn);

    UsercallFuncVoid(_hudDisplayRingsHook, (signed int ringCount, unsigned char digits, NJS_SPRITE* hud),
                        (ringCount, digits, hud), 0x425960, rEAX, rBL, rESI);
    static void __cdecl HandleHudDisplayRings(signed int ringCount, unsigned char digits, NJS_SPRITE* hud);

    static void __cdecl HandleRingLoss();

    void ActivateFiller(FillerType filler);
    void FreezePlayer();
    void IncrementGravity();
    void ReverseControls();
    void SpawnSpring();
    void SpawnEnemies(void (*enemyFunc)(task* tp));

    int _lastRingAmount = 0;
    bool _reverseControlsEnabled = false;

    std::deque<FillerType> _remainingFiller;

    float _fillerDuration = 2.5f;
    std::clock_t _fillerTimer = -1;

    task* _springTask = nullptr;
    float _springDuration = 2.0f;
    std::clock_t _springTimer = -1;

    float _freezeDuration = 2.0f;
    std::clock_t _freezeTimer = -1;

    float _gravityDuration = 7.0f;
    std::clock_t _gravityTimer = -1;

    std::clock_t _reverseControlsTimer = -1;
    
};
