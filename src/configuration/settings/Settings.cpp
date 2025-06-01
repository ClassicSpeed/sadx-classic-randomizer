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
}
