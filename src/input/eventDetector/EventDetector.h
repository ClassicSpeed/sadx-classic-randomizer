#pragma once
#include <vector>

#include "../../application/randomizer/Randomizer.h"
#include "../../application/link/Link.h"
#include "../../application/structs/LocationData.h"
#include <unordered_map>

enum LastStoryState
{
    LastStoryNotStarted,
    LastStoryStarted,
    LastStoryCompleted
};

struct ArrowTarget
{
    NJS_POINT3 point;
    LocationType type;
};

constexpr double MIN_ARROW_DISTANCE = 300.0;
constexpr double MAX_ARROW_DISTANCE = 1000.0;

constexpr double ARROW_HEIGHT = 2.5;
constexpr double EXTRA_ARROW_HEIGHT = 2.5;
constexpr double ARROW_BASE_WIDTH = 1.25;
constexpr double EXTRA_BASE_WIDTH = 1.25;

constexpr double MIN_INDICATOR_DISTANCE = 130.0;
constexpr double MAX_INDICATOR_DISTANCE = 170.0;

constexpr int INDICATOR_HEIGHT = 15;
constexpr int EXTRA_INDICATOR_HEIGHT = 20;

constexpr int HEIGHT_SIZE = 4;
constexpr int EXTRA_HEIGHT_SIZE = 7;

constexpr int ENEMY_STARTING_ID = 10000;
constexpr int ENEMY_INVALID_ID = -1;
constexpr int ENEMY_SEARCHING_ID = -2;


enum IndicatorType
{
    EnemyIndicator,
    CapsuleIndicator,
    FishIndicator,
};


class EventDetector : public IOnFrame
{
public:
    static EventDetector& Init(Options& options, Settings& settings, Randomizer& randomizer, Link& link)
    {
        if (_instance == nullptr)
            _instance = new EventDetector(options, settings, randomizer, link);
        return *_instance;
    }

    void OnFrame() override;

    bool IsTargetableCheck(const LocationData& location) const;
    void OnLevelEmblem(int character, int level, int mission);
    void OnGenericEmblem(int index);
    void OnTwinkleCircuitCompleted(int character);
    void ShuffleSong();

    LastStoryState lastStoryState = LastStoryNotStarted;
    std::vector<CapsuleLocationData> capsules;
    std::vector<EnemyLocationData> enemies;
    mutable std::map<int, LocationData> checkData;
    mutable std::vector<ArrowTarget> possibleChecks;
    float deathDetectionCooldown = 0.5f;
    std::clock_t deathCooldownTimer = -1;

    int lastRealSongId = -1;
    int lastShuffledSongId = -1;

private:
    explicit EventDetector(Options& options, Settings& settings, Randomizer& randomizer, Link& link);
    inline static EventDetector* _instance = nullptr;

    Options& _options;
    Settings& _settings;
    Randomizer& _randomizer;
    Link& _link;

    void CheckCapsule(const EntityData1* entity, CapsuleType capsuleType);
    void CheckEnemy(task* tp);
    int GetEnemyFromPosition(const NJS_VECTOR& position);
    void DrawIndicator(const task* tp, bool tallElement, bool checked, IndicatorType indicatorType, int locationId);
    CapsuleType GetCapsuleTypeOption(Float type);
    int GetCapsuleCapsuleFromPosition(const NJS_VECTOR& position);
    void CheckDestroyedEnemy(task* tp);

    static bool HandleCheckMissionRequirements(int mission, int character, int level);
    static bool HandleCheckMissionRequirementsSubgame(int level, int character, int mission);
    static void HandlePlayCharacterDeathSound(task* tp, int pid);
    static void HandleOnBoaBoaPartDestroyed(task* tp);

    inline static FunctionHook<void, SaveFileData*, int, signed int, int> _onLevelEmblemCollectedHook{0x4B4640};
    static void OnLevelEmblemCollected(SaveFileData* saveFile, const int character, const signed int level,
                                       const int mission);

    inline static FunctionHook<void, SaveFileData*, signed int> _onGenericEmblemCollectedHook{0x4B3F30};
    static void OnGenericEmblemCollected(SaveFileData* savefile, signed int index);

    inline static FunctionHook<void, task*> _onSonicMainHook{0x49A9B0};
    static void OnSonicMain(task* tp);

    inline static FunctionHook<SEQ_SECTIONTBL*, int> _seqGetSectionListHook{0x44EAF0};
    static SEQ_SECTIONTBL* OnSeqGetSectionList(int playerno);

    inline static FunctionHook<void, short> _startLevelCutsceneHook{0x413C90};
    static void OnStartLevelCutscene(short scene);

    inline static FunctionHook<BOOL> _onMissionMenuRenderHook{0x506410};
    static BOOL OnMissionMenuRender();

    inline static FunctionHook<void, EntityData1*> _onSpeedUpCapsuleBrokenHook{0x4D6BF0};
    static void OnSpeedUpCapsuleBroken(EntityData1* entity);

    inline static FunctionHook<void, EntityData1*> _onInvincibilityCapsuleBrokenHook{0x4D6D80};
    static void OnInvincibilityCapsuleBroken(EntityData1* entity);

    inline static FunctionHook<void, EntityData1*> _onFiveRingsCapsuleBrokenHook{0x4D6C50};
    static void OnFiveRingsCapsuleBroken(EntityData1* entity);

    inline static FunctionHook<void, EntityData1*> _onTenRingsCapsuleHook{0x4D6C90};
    static void OnTenRingsCapsule(EntityData1* entity);

    inline static FunctionHook<void, EntityData1*> _onRandomRingsCapsuleBrokenHook{0x4D6CD0};
    static void OnRandomRingsCapsuleBroken(EntityData1* entity);

    inline static FunctionHook<void, EntityData1*> _onShieldCapsuleBrokenHook{0x4D6DC0};
    static void OnShieldCapsuleBroken(EntityData1* entity);

    inline static FunctionHook<void, EntityData1*> _onExtraLifeCapsuleBrokenHook{0x4D6D40};
    static void OnExtraLifeCapsuleBroken(EntityData1* entity);

    inline static FunctionHook<void, EntityData1*> _onBombCapsuleBrokenHook{0x4D6E00};
    static void OnBombCapsuleBroken(EntityData1* entity);

    inline static FunctionHook<void, EntityData1*> _onElectricShieldCapsuleBrokenHook{0x4D6E40};
    static void OnElectricShieldCapsuleBroken(EntityData1* entity);

    inline static FunctionHook<void, unsigned short> _onKillHimPHook{0x440CD0};
    static void OnKillHimP(unsigned short a1);

    inline static FunctionHook<void> _onKillHimByFallingDownPHook{0x446AD0};
    static void OnKillHimByFallingDownP();

    inline static FunctionHook<void, task*> _onScoreDisplayMainHook{0x42BCC0};
    static void OnScoreDisplayMain(task* tp);

    inline static FunctionHook<void> _onLoadLevelResultsHook{0x415540};
    static void OnLoadLevelResults();

    inline static FunctionHook<void, ObjectMaster*> _onClearMissionHook{0x5923C0};
    static void OnClearMission(ObjectMaster* obj);

    inline static FunctionHook<void, task*> _onItemBoxMainHook{0x4D6F10};
    static void OnItemBoxMain(task* tp);

    inline static FunctionHook<void, task*> _onAirItemBoxMainHook{0x4C07D0};
    static void OnAirItemBoxMain(task* tp);

    inline static FunctionHook<void, task*> _onRhinotankLoadHook{0x7A1380};
    static void OnRhinotankLoad(task* tp);

    inline static FunctionHook<void, task*> _onKikiLoadHook{0x4AD140};
    static void OnKikiLoad(task* tp);

    inline static FunctionHook<void, task*> _onKikiMainHook{0x4ACF80};
    static void OnKikiMain(task* tp);

    inline static FunctionHook<void, task*> _onWaterSpiderLoadHook{0x7AA960};
    static void OnWaterSpiderLoad(task* tp);

    inline static FunctionHook<void, task*> _onWaterSpiderMainHook{0x7AA870};
    static void OnWaterSpiderMain(task* tp);

    inline static FunctionHook<void, task*> _onBuyonMainHook{0x7B2E00};
    static void OnBuyonMain(task* tp);

    inline static FunctionHook<void, task*> _onBoaBoaHeadLoadHook{0x7A00F0};
    static void OnBoaBoaHeadLoad(task* tp);

    inline static FunctionHook<void, task*> _onLeonLoadHook{0x4A85C0};
    static void OnLeonLoad(task* tp);

    inline static FunctionHook<void, task*> _onLeonMainHook{0x4A83D0};
    static void OnLeonMain(task* tp);

    inline static FunctionHook<void, task*> _onSpinnerAMainHook{0x4B0DF0};
    static void OnSpinnerAMain(task* tp);

    inline static FunctionHook<void, task*> _onSpinnerBMainHook{0x4B0F40};
    static void OnSpinnerBMain(task* tp);

    inline static FunctionHook<void, task*> _onSpinnerCMainHook{0x4B1090};
    static void OnSpinnerCMain(task* tp);

    inline static FunctionHook<void, task*> _onPoliceLoadHook{0x4B3210};
    static void OnPoliceLoad(task* tp);

    inline static FunctionHook<void, task*> _onPoliceMainHook{0x4B30E0};
    static void OnPoliceMain(task* tp);

    inline static FunctionHook<void, task*> _onSpikeBallSpinnerALoadHook{0x4AF190};
    static void OnSpikeBallSpinnerALoad(task* tp);

    inline static FunctionHook<void, task*> _onSpikeBallSpinnerAMainHook{0x4AF030};
    static void OnSpikeBallSpinnerAMain(task* tp);

    inline static FunctionHook<void, task*> _onSpikeBallSpinnerBLoadHook{0x4AF500};
    static void OnSpikeBallSpinnerBLoad(task* tp);

    inline static FunctionHook<void, task*> _onSpikeBallSpinnerBMainHook{0x4AF3D0};
    static void OnSpikeBallSpinnerBMain(task* tp);

    inline static FunctionHook<void, task*> _onSpikeBallSpinnerCLoadHook{0x4AF860};
    static void OnSpikeBallSpinnerCLoad(task* tp);

    inline static FunctionHook<void, task*> _onSpikeBallSpinnerCMainHook{0x4AF770};
    static void OnSpikeBallSpinnerCMain(task* tp);

    inline static FunctionHook<void, task*> _onIceBallLoadHook{0x4C8FB0};
    static void OnIceBallLoad(task* tp);

    inline static FunctionHook<void, task*> _onIceBallMainAHook{0x4C8AC0};
    static void OnIceBallMainA(task* tp);

    inline static FunctionHook<void, task*> _onIceBallMainBHook{0x4C8DD0};
    static void OnIceBallMainB(task* tp);

    inline static FunctionHook<void, task*> _onEggKeeperLoadHook{0x4A6700};
    static void OnEggKeeperLoad(task* tp);

    inline static FunctionHook<void, task*> _onEggKeeperMainHook{0x4A6420};
    static void OnEggKeeperMain(task* tp);

    inline static FunctionHook<void, task*> _onDeadOutHook{0x46C150};
    static void OnDeadOut(task* tp);

    inline static FunctionHook<void, task*> _onBuyonDestroyChildrenHook{0x7B1500};
    static void OnBuyonDestroyChildren(task* tp);

    inline static FunctionHook<signed int> _onSaveTwinkleCircuitRecordHook{0x4B5BC0};
    static signed int OnSaveTwinkleCircuitRecord();

    inline static FunctionHook<void, task*> _onFishMainHook{0x597010};
    static void OnFishMain(task* tp);

    inline static FunctionHook<void, task*> _onFishCaughtHook{0x470160};
    static void OnFishCaught(task* tp);

    inline static FunctionHook<void> _onCheckEggHoldHook{0x7151A0};
    static void OnCheckEggHold();

    inline static FunctionHook<void, task*> _onMissionStatueDeleteHook{0x5934C0};
    static void OnMissionStatueDelete(task* tp);

    inline static FunctionHook<void, int> _onPlayMusicHook{0x425690};
    static void OnPlayMusic(int songId);

    inline static FunctionHook<void, int> _onPlayMusic2Hook{0x425800};
    static void OnPlayMusic2(int songId);

    inline static FunctionHook<void, int> _onPlayJingleHook{0x425860};
    static void OnPlayJingle(int songId);

    inline static FunctionHook<void, int> _addSecondsHook{0x426640};
    static void OnAddSeconds(int seconds);
};
