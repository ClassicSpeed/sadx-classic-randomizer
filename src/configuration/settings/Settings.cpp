#include "Settings.h"

Settings::Settings(const IniFile* settingsIni)
{
    this->playerName = Trim(settingsIni->getString("AP", "PlayerName"));
    this->_serverIP = Trim(settingsIni->getString("AP", "IP"));
    this->_serverPassword = settingsIni->getString("AP", "Password");

    this->deathLinkOverride = static_cast<DeathLinkOverride>(settingsIni->getInt("AP", "DeathLinkOverride", 0));
    this->ringLinkOverride = static_cast<RingLinkOverride>(settingsIni->getInt("AP", "RingLinkOverride", 0));
    this->ringLossOverride = static_cast<RingLossOverride>(settingsIni->getInt("AP", "RingLossOverride", 0));
    this->trapLinkOverride = static_cast<TrapLinkOverride>(settingsIni->getInt("AP", "TrapLinkOverride", 0));


    this->_displayDuration = settingsIni->getFloat("Messages", "MessageDisplayDuration", 5.0f);
    this->_debugFontSize = settingsIni->getInt("Messages", "MessageFontSize", 21);
    this->_displayInGameTracker = static_cast<DisplayInGameTracker>(settingsIni->
        getInt("Messages", "InGameTracker", 0));
    const int itemMessageColorR = settingsIni->getInt("Messages", "ItemMessageColorR", 33);
    const int itemMessageColorG = settingsIni->getInt("Messages", "ItemMessageColorG", 255);
    const int itemMessageColorB = settingsIni->getInt("Messages", "ItemMessageColorB", 33);
    this->_displayMessageColor = (0xFF << 24) | itemMessageColorR << 16 | itemMessageColorG << 8 | itemMessageColorB;

    const int chatMessageColorR = settingsIni->getInt("Messages", "ChatMessageColorR", 255);
    const int chatMessageColorG = settingsIni->getInt("Messages", "ChatMessageColorG", 255);
    const int chatMessageColorB = settingsIni->getInt("Messages", "ChatMessageColorB", 255);
    this->_chatMessageColor = (0xFF << 24) | chatMessageColorR << 16 | chatMessageColorG << 8 | chatMessageColorB;


    this->_showChatMessages = settingsIni->getBool("Messages", "ShowChatMessages", true);
    this->_showGoalReached = settingsIni->getBool("Messages", "ShowGoalReached", true);
    this->_showCountdowns = settingsIni->getBool("Messages", "ShowCountdowns", true);
    this->_showPlayerConnections = settingsIni->getBool("Messages", "ShowPlayerConnections", false);


    this->showCommentsSubtitles = settingsIni->getBool("CharacterVoiceReactions",
                                                       "DisplaySubtitlesForVoiceReactions", true);
    this->eggmanCommentOnTrap = settingsIni->getBool("CharacterVoiceReactions", "EggmanOnTrap", true);
    this->otherCharactersCommentOnTrap = settingsIni->getBool("CharacterVoiceReactions", "OtherCharactersOnTrap",
                                                              true);
    this->currentCharacterReactToTrap = settingsIni->getBool("CharacterVoiceReactions", "CurrentCharacterOnTrap",
                                                             true);

    this->eggmanCommentOnCharacterUnlock = settingsIni->getBool("CharacterVoiceReactions", "EggmanOnUnlock", true);
    this->currentCharacterCommentOnCharacterUnlock = settingsIni->getBool(
        "CharacterVoiceReactions", "CurrentCharacterOnUnlock", true);
    this->unlockedCharacterCommentOnCharacterUnlock = settingsIni->getBool(
        "CharacterVoiceReactions", "UnlockedCharactersOnUnlock", true);
    this->eggmanCommentOnKeyItems = settingsIni->getBool("CharacterVoiceReactions", "EggmanOnKeyItem", true);
    this->tikalCommentOnKeyItems = settingsIni->getBool("CharacterVoiceReactions", "TikalOnKeyItem", true);


    this->songsPath = settingsIni->getString("MusicShuffle", "SongsPath", "mods/SADX_Archipelago/");
    this->sa2BAdxPath = settingsIni->getString("MusicShuffle", "Sa2bADXpath",
                                               "../Sonic Adventure 2/resource/gd_PC/ADX/");
    this->customAdxPath = settingsIni->getString("MusicShuffle", "CustomADXpath", "songs/custom/");
    this->showSongName = static_cast<ShowSongName>(settingsIni->getInt("MusicShuffle", "ShowSongName", 0));
    this->showSongNameForType = static_cast<ShowSongNameForType>(settingsIni->getInt(
        "MusicShuffle", "ShowSongNameForType", 0));
    this->includeVanillaSongs = settingsIni->getBool("MusicShuffle", "IncludeVanilla", false);
    this->showWarningForMissingFiles = settingsIni->getBool("MusicShuffle", "ShowWarningForMissingFiles", false);
    this->musicSource = static_cast<MusicSource>(settingsIni->getInt("MusicShuffle", "MusicSourceOverride", -1));
    this->musicShuffle = static_cast<MusicShuffle>(settingsIni->getInt("MusicShuffle", "MusicShuffleOverride", -1));
    this->musicShuffleConsistency = static_cast<MusicShuffleConsistency>(settingsIni->getInt(
        "MusicShuffle", "MusicShuffleConsistencyOverride", -1));
    this->lifeCapsulesChangeSongs = static_cast<LifeCapsulesChangeSongs>(settingsIni->getInt(
        "MusicShuffle", "LifeCapsulesChangeSongsOverride", -1));


    
                                                                  
    this->autoSkipCutscenes = settingsIni->getBool("GameSettings", "AutoSkipCutscenes", true);
    this->skipCredits = settingsIni->getBool("GameSettings", "SkippableCredits", true);
    this->noLifeLossOnRestart = settingsIni->getBool("GameSettings", "NoLifeLossOnRestart", true);
    
    this->extendRingCapacity = settingsIni->getBool("GameSettings", "ExtendRingCapacity", false);

    
    this->eggCarrierTransformationCutscene = settingsIni->getBool("GameSettings",
                                                                       "EggCarrierTransformationCutscene", true);


    this-> _showEntranceIndicators = settingsIni->getBool("GameSettings",
                                                             "ShowEntranceIndicators", true);

    this-> chaoStatsMultiplier = settingsIni->getInt("Chao", "StatGainMultiplier", 1);

    const int characterVoiceIndex = settingsIni->getInt("CharacterVoiceReactions", "VoiceMenu", -1);
    if (characterVoiceIndex == -1)
    {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(0, 8);
        this->_voiceMenuCharacter = dis(gen);
    }
    else
    {
        this->_voiceMenuCharacter = characterVoiceIndex;
    }



    this->completeMultipleLevelMissions = settingsIni->getBool("GameSettings", "CompleteMultipleLevelMissions", true);
    this->homingAttackIndicator = static_cast<HomingAttackIndicator>(settingsIni->getInt(
        "GameSettings", "HomingAttackIndicatorEnabled", 0));


    this->trackerArrow = settingsIni->getBool("Sanity", "TrackerArrow", true);
    this->trackerArrowToggleable = settingsIni->getBool("Sanity", "TrackerArrowToggleable", false);
    this->trackerArrowShowDistance = settingsIni->getBool("Sanity", "TrackerArrowShowDistance", true);
    this->trackerArrowOverrideColor = settingsIni->getBool("Sanity", "TrackerArrowOverrideColor", false);
    const int trackerArrowR = settingsIni->getInt("Sanity", "TrackerArrowR", 0);
    const int trackerArrowG = settingsIni->getInt("Sanity", "TrackerArrowG", 0);
    const int trackerArrowB = settingsIni->getInt("Sanity", "TrackerArrowB", 255);
    const int trackerArrowColor = 0xFF << 24 | trackerArrowR << 16 | trackerArrowG << 8 | trackerArrowB;
    this->arrowColor[0].color = trackerArrowColor;
    this->arrowColor[1].color = trackerArrowColor;
    this->arrowColor[2].color = trackerArrowColor;
    this->arrowColor[3].color = trackerArrowColor;
    this->arrowColor[4].color = trackerArrowColor;
    this->arrowColor[5].color = trackerArrowColor;

    this->enemyIndicator = settingsIni->getBool("Sanity", "EnemyIndicator", true);
    const int enemyIndicatorR = settingsIni->getInt("Sanity", "EnemyIndicatorR", 255);
    const int enemyIndicatorG = settingsIni->getInt("Sanity", "EnemyIndicatorG", 0);
    const int enemyIndicatorB = settingsIni->getInt("Sanity", "EnemyIndicatorB", 0);
    const int trackerEnemyIndicatorColor = 0xFF << 24 | enemyIndicatorR << 16 | enemyIndicatorG << 8 | enemyIndicatorB;
    this->enemyIndicatorColor[0].color = trackerEnemyIndicatorColor;
    this->enemyIndicatorColor[1].color = trackerEnemyIndicatorColor;
    this->enemyIndicatorColor[2].color = trackerEnemyIndicatorColor;

    this->capsuleIndicator = settingsIni->getBool("Sanity", "CapsuleIndicator", true);
    const int capsuleIndicatorR = settingsIni->getInt("Sanity", "CapsuleIndicatorR", 0);
    const int capsuleIndicatorG = settingsIni->getInt("Sanity", "CapsuleIndicatorG", 255);
    const int capsuleIndicatorB = settingsIni->getInt("Sanity", "CapsuleIndicatorB", 0);
    const int trackerCapsuleIndicatorColor = 0xFF << 24 | capsuleIndicatorR << 16 | capsuleIndicatorG << 8 |
        capsuleIndicatorB;
    this->capsuleIndicatorColor[0].color = trackerCapsuleIndicatorColor;
    this->capsuleIndicatorColor[1].color = trackerCapsuleIndicatorColor;
    this->capsuleIndicatorColor[2].color = trackerCapsuleIndicatorColor;

    this->fishIndicator = settingsIni->getBool("Sanity", "FishIndicator", true);
    const int fishIndicatorR = settingsIni->getInt("Sanity", "FishIndicatorR", 0);
    const int fishIndicatorG = settingsIni->getInt("Sanity", "FishIndicatorG", 255);
    const int fishIndicatorB = settingsIni->getInt("Sanity", "FishIndicatorB", 255);
    const int trackerFishIndicatorColor = 0xFF << 24 | fishIndicatorR << 16 | fishIndicatorG << 8 | fishIndicatorB;
    this->fishIndicatorColor[0].color = trackerFishIndicatorColor;
    this->fishIndicatorColor[1].color = trackerFishIndicatorColor;
    this->fishIndicatorColor[2].color = trackerFishIndicatorColor;

    this->progressionIndicator = settingsIni->getBool("Sanity", "ProgressionItemIndicator", true);
    const int progressionIndicatorR = settingsIni->getInt("Sanity", "ProgressionIndicatorR", 212);
    const int progressionIndicatorG = settingsIni->getInt("Sanity", "ProgressionIndicatorG", 175);
    const int progressionIndicatorB = settingsIni->getInt("Sanity", "ProgressionIndicatorB", 55);
    const int progressionIndicatorColor = 0xFF << 24 | progressionIndicatorR << 16 | progressionIndicatorG << 8 |
        progressionIndicatorB;
    this->progressionItemIndicatorColor[0].color = progressionIndicatorColor;
    this->progressionItemIndicatorColor[1].color = progressionIndicatorColor;
    this->progressionItemIndicatorColor[2].color = progressionIndicatorColor;
}
