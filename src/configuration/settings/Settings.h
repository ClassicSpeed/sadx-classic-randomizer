#pragma once
#include "../../pch.h"
#include <random>


enum DeathLinkOverride
{
    DeathLinkDefault = 0,
    DeathLinkForceEnabled = 1,
    DeathLinkForceDisabled = 2,
};

enum RingLinkOverride
{
    RingLinkDefault = 0,
    RingLinkForceEnabled = 1,
    RingLinkForceEnabledHard = 2,
    RingLinkForceDisabled = 3,
};

enum RingLossOverride
{
    RingLossDefault = 0,
    RingLossForceClassic = 1,
    RingLossForceModern = 2,
    RingLossForceOhko = 3,
    RingLossForceOhkoNoShields = 4,
};

enum TrapLinkOverride
{
    TrapLinkDefault = 0,
    TrapLinkForceEnabled = 1,
    TrapLinkForceDisabled = 2,
};

enum DisplayInGameTracker
{
    DisplayTrackerWhenPaused = 0,
    DisplayTrackerAlwaysOn = 1,
    DisplayTrackerAlwaysOff = 2,
};

enum ShowSongName
{
    ShowSongNameWithSongShuffle = 0,
    ShowSongNameAlwaysOn,
    ShowSongNameAlwaysOff
};

enum ShowSongNameForType
{
    ShowSongNameForTypeEverything,
    ShowSongNameForTypeEverythingButJingles,
    ShowSongNameForTypeOnlyActionLevels
};


enum MusicSource
{
    MusicSourceNone = -1,
    MusicSourceSadx = 0,
    MusicSourceSa2B,
    MusicSourceCustom,
    MusicSourceSadxSa2B,
    MusicSourceSadxCustom,
    MusicSourceSa2BCustom,
    MusicSourceSadxSa2BCustom
};

enum MusicShuffle
{
    MusicShuffleNone = -1,
    MusicShuffleDisabled = 0,
    MusicShuffleCurated,
    MusicShuffleByType,
    MusicShuffleFull,
    MusicShuffleSingularity,
};

enum MusicShuffleConsistency
{
    MusicShuffleConsistencyNone = -1,
    MusicShuffleConsistencyStatic = 0,
    MusicShuffleConsistencyOnRestart,
    MusicShuffleConsistencyPerPlay,
};


enum LifeCapsulesChangeSongs
{
    LifeCapsulesChangeSongsNone = -1,
    LifeCapsulesChangeSongsEnabled = 0,
    LifeCapsulesChangeSongsDisabled = 1,
};

enum HomingAttackIndicator
{
    HomingAttackIndicatorDisabled = 0,
    HomingAttackIndicatorEnabled = 1,
    HomingAttackIndicatorEnabledNoSound = 2,
};

// TODO: Move to helpers
static std::string LeftTrim(std::string s)
{
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch)
    {
        return !std::isspace(ch);
    }));
    return s;
}

static std::string RightTrim(std::string s)
{
    s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch)
    {
        return !std::isspace(ch);
    }).base(), s.end());
    return s;
}

static std::string Trim(std::string s)
{
    return LeftTrim(RightTrim(std::move(s)));
}


class Settings
{
public:
    static Settings& Init(const char* path, const HelperFunctions& helperFunctions)
    {
        if (_instance == nullptr)
            _instance = new Settings(path, helperFunctions);
        return *_instance;
    }


    std::string playerName;
    std::string serverIp;
    std::string serverPassword;

    bool showChatMessages = true;
    bool showGoalReached = true;
    bool showCountdowns = true;
    bool showPlayerConnections = false;

    DeathLinkOverride deathLinkOverride;
    RingLinkOverride ringLinkOverride;
    RingLossOverride ringLossOverride;
    TrapLinkOverride trapLinkOverride;


    float displayDuration = 6.0f;
    unsigned __int16 debugFontSize = 21;
    DisplayInGameTracker displayInGameTracker = DisplayTrackerWhenPaused;
    int displayMessageColor = 0xFF33FF33; //Green
    int chatMessageColor = 0xFFFFFFFF;


    bool eggmanCommentOnCharacterUnlock = true;
    bool currentCharacterCommentOnCharacterUnlock = true;
    bool unlockedCharacterCommentOnCharacterUnlock = true;

    bool eggmanCommentOnKeyItems = true;
    bool tikalCommentOnKeyItems = true;
    bool currentCharacterCommentOnKeyItems = true;

    bool eggmanCommentOnTrap = true;
    bool otherCharactersCommentOnTrap = true;
    bool currentCharacterReactToTrap = true;

    bool showCommentsSubtitles = true;

    std::string songsPath = "mods/SADX_Archipelago/";
    std::string sa2BAdxPath = "../../../../Sonic Adventure 2/resource/gd_PC/ADX/";
    std::string customAdxPath = "custom/";
    ShowSongName showSongName = ShowSongNameWithSongShuffle;
    ShowSongNameForType showSongNameForType = ShowSongNameForTypeEverything;
    bool includeVanillaSongs = true;
    bool showWarningForMissingFiles = false;

    MusicSource musicSource = MusicSourceNone;
    MusicShuffle musicShuffle = MusicShuffleNone;
    MusicShuffleConsistency musicShuffleConsistency = MusicShuffleConsistencyNone;
    LifeCapsulesChangeSongs lifeCapsulesChangeSongs = LifeCapsulesChangeSongsNone;
    int musicShuffleSeed = -1;

    int voiceMenuCharacter = 0;

    bool autoSkipCutscenes = true;
    bool skipCredits = true;
    bool noLifeLossOnRestart = true;


    bool completeMultipleLevelMissions = true;
    HomingAttackIndicator homingAttackIndicator = HomingAttackIndicatorDisabled;

    bool showEntranceIndicators = true;
    bool eggCarrierTransformationCutscene = true;
    int chaoStatsMultiplier = 1;

    bool extendRingCapacity = false;

    mutable bool trackerArrow = true;
    bool trackerArrowToggleable = false;
    bool trackerArrowOverrideColor = true;
    bool trackerArrowShowDistance = true;


    bool enemyIndicator = true;
    bool capsuleIndicator = true;
    bool fishIndicator = true;
    bool progressionIndicator = true;

    NJS_COLOR arrowColor[6] = {
        {0xFF00FF00},
        {0xFF00FF00},
        {0xFF00FF00},
        {0xFF00FF00},
        {0xFF00FF00},
        {0xFF00FF00},
    };

    NJS_COLOR enemyIndicatorColor[3] = {
        {0xFFFF1400},
        {0xFFFF1400},
        {0xFFFF1400},
    };
    NJS_COLOR capsuleIndicatorColor[3] = {
        {0xFFFF1400},
        {0xFFFF1400},
        {0xFFFF1400},
    };
    NJS_COLOR fishIndicatorColor[3] = {
        {0xFFFF1400},
        {0xFFFF1400},
        {0xFFFF1400},
    };
    NJS_COLOR disabledIndicatorColor[3] = {
        {0xFF222222},
        {0xFF222222},
        {0xFF222222},
    };
    NJS_COLOR progressionItemIndicatorColor[3] = {
        {0xFFD4AF37},
        {0xFFD4AF37},
        {0xFFD4AF37},
    };
    


    bool _superSonicModRunning = false;

private:
    explicit Settings(const char* path, const HelperFunctions& helperFunctions);
    inline static Settings* _instance = nullptr;
};
