#pragma once
#include "../../pch.h"


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
    static Settings& Init(const IniFile* settingsIni)
    {
        if (_instance == nullptr)
            _instance = new Settings(settingsIni);
        return *_instance;
    }

    void SetCharacterVoiceReactions(bool newEggmanCommentOnCharacterUnlock,
                                    bool newCurrentCharacterCommentOnCharacterUnlock,
                                    bool newUnlockedCharacterCommentOnCharacterUnlock, bool newEggmanCommentOnKeyItems,
                                    bool newTikalCommentOnKeyItems, bool newCurrentCharacterCommentOnKeyItems,
                                    bool newShowCommentsSubtitles);
    void SetCharacterVoiceReactions(bool newEggmanCommentOnTrap, bool newOtherCharactersCommentOnTrap,
                                    bool newCurrentCharacterReactToTrap, bool newShowCommentsSubtitles);
    void SetLinksOverrides(DeathLinkOverride newDeathLinkOverride, RingLinkOverride newRingLinkOverride,
                           RingLossOverride newRingLossOverride, TrapLinkOverride newTrapLinkOverride);
    void SetServerConfiguration(const std::string& serverIp, const std::string& newPlayerName,
                                const std::string& serverPassword, bool showChatMessages, bool showGoalReached,
                                bool showCountdowns, bool showPlayerConnections);


    //Mod Settings    
    std::string playerName;
    std::string _serverIP;
    std::string _serverPassword;

    bool _showChatMessages = true;
    bool _showGoalReached = true;
    bool _showCountdowns = true;
    bool _showPlayerConnections = false;

    DeathLinkOverride deathLinkOverride;
    RingLinkOverride ringLinkOverride;
    RingLossOverride ringLossOverride;
    TrapLinkOverride trapLinkOverride;


    float _displayDuration = 6.0f;
    unsigned __int16 _debugFontSize = 21;
    DisplayInGameTracker _displayInGameTracker = DisplayTrackerWhenPaused;
    int _displayMessageColor = 0xFF33FF33; //Green
    int _chatMessageColor = 0xFFFFFFFF;

    

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

private:
    explicit Settings(const IniFile* settingsIni);
    inline static Settings* _instance = nullptr;
};
