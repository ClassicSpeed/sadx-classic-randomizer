#include <chrono>

#include "pch.h"

#include "application/Randomizer.h"
#include "input/archipelago/ArchipelagoManager.h"
#include "input/cheatsManager/CheatsManager.h"
#include "input/eventDetector/EventDetector.h"
#include "input/characterLoading/CharacterLoadingDetector.h"
#include "output/archipelagoMessenger/ArchipelagoMessenger.h"
#include "output/locationRepository/LocationRepository.h"
#include "output/saveFileManager/SaveFileManager.h"
#include "output/worldStateManager/WorldStateManager.h"

constexpr int SYNC_RATE = 10;


void LoadArchipelagoSettings(const IniFile* settingsIni);
void LoadDisplayMessageSettings(const IniFile* settingsIni);
void LoadGameSettings(const IniFile* settingsIni);
void ReplaceEmblemImage(const char* path, const HelperFunctions& helperFunctions);

extern "C" {
std::chrono::time_point<std::chrono::system_clock> timestamp = std::chrono::system_clock::now();
const int INSTANCE_ID = std::chrono::duration_cast<std::chrono::seconds>(timestamp.time_since_epoch()).count();
constexpr int64_t BASE_ID = 543800000;
int syncTimer = 0;


DisplayManager displayManager = DisplayManager();
CharacterManager characterManager = CharacterManager();
WorldStateManager worldStateManager = WorldStateManager();
ItemRepository itemRepository = ItemRepository();
LocationRepository checkRepository = LocationRepository();
ArchipelagoMessenger archipelagoMessenger = ArchipelagoMessenger(INSTANCE_ID, BASE_ID);
SaveFileManager saveFileManager = SaveFileManager();

Randomizer randomizer = Randomizer(displayManager,
                                   characterManager,
                                   worldStateManager,
                                   itemRepository,
                                   checkRepository,
                                   archipelagoMessenger,
                                   saveFileManager);

CheatsManager cheatsManager = CheatsManager(randomizer);
ArchipelagoManager archipelagoManager = ArchipelagoManager(randomizer, INSTANCE_ID, BASE_ID);
EventDetector eventDetector = EventDetector(randomizer);
CharacterLoadingDetector characterLoadingDetector = CharacterLoadingDetector(randomizer);


__declspec(dllexport) void __cdecl Init(const char* path, const HelperFunctions& helperFunctions)
{
    if (helperFunctions.Mods->find_by_name("Steam Achievements Mod"))
    {
        MessageBox(WindowHandle,
                   L"The Steam Achievements Mod is not compatible with the SADX Archipelago Randomizer.\n\nPlease disable it and try again.",
                   L"SADX Archipelago Error: Incompatible Mod", MB_OK | MB_ICONERROR);
        exit(0);
    }

    if (helperFunctions.Mods->find_by_name("Fixes, Adds, and Beta Restores"))
    {
        MessageBox(WindowHandle,
                   L"The Fixes, Adds, and Beta Restores Mod is not compatible with the SADX Archipelago Randomizer.\n\nPlease disable it and try again.",
                   L"SADX Archipelago Error: Incompatible Mod", MB_OK | MB_ICONERROR);
        exit(0);
    }

    if (helperFunctions.Mods->find_by_name("SADX:FE"))
    {
        MessageBox(WindowHandle,
                   L"The SADX:FE Mod is not compatible with the SADX Archipelago Randomizer.\n\nPlease disable it and try again.",
                   L"SADX Archipelago Error: Incompatible Mod", MB_OK | MB_ICONERROR);
        exit(0);
    }


    const IniFile* settingsIni = new IniFile(std::string(path) + "\\config.ini");

    if (!settingsIni)
        return randomizer.ShowStatusInformation("Invalid Settings INI");

    LoadArchipelagoSettings(settingsIni);

    LoadDisplayMessageSettings(settingsIni);

    LoadGameSettings(settingsIni);

    ReplaceEmblemImage(path, helperFunctions);
    if (helperFunctions.Mods->find_by_name("Super Sonic"))
    {
        PrintDebug("[SADX Randomizer] Super Sonic Mod detected\n");
        randomizer.SetSuperSonicModRunning(true);
    }
}

__declspec(dllexport) void __cdecl OnFrame()
{
    saveFileManager.OnFrame();
    archipelagoManager.OnFrame();
    displayManager.OnFrame();
    worldStateManager.OnFrame();
    if (Current_CharObj2 != nullptr && EntityData1Ptrs[0] != nullptr)
    {
        eventDetector.OnPlayingFrame();
        characterLoadingDetector.OnPlayingFrame();
        randomizer.OnPlayingFrame();
        characterManager.OnPlayingFrame();
    }
    if (syncTimer == 0)
    {
        randomizer.OnSync();
        syncTimer = SYNC_RATE;
    }
    else
        syncTimer--;
}

bool saveFileSelected = false;
FunctionHook<BOOL> onTrialMenuLoaded(0x506780, []()-> BOOL
{
    if (GameMode == GameModes_Menu && !saveFileSelected)
    {
        saveFileManager.OnSaveFileLoaded();
        archipelagoManager.OnSaveFileLoaded();
        saveFileSelected = true;
    }

    //Blocks trial menu
    return false;
});

//Blocks mission menu
FunctionHook<BOOL> blockMissionMenu(0x506410, []() -> BOOL { return false; });


__declspec(dllexport) ModInfo SADXModInfo = {ModLoaderVer}; // This is needed for the Mod Loader to recognize the DLL.
}


void LoadArchipelagoSettings(const IniFile* settingsIni)
{
    const std::string serverIp = settingsIni->getString("AP", "IP");
    const std::string playerName = settingsIni->getString("AP", "PlayerName");
    const std::string serverPassword = settingsIni->getString("AP", "Password");

    const int deathLinkOverride = settingsIni->getInt("AP", "DeathLinkOverride", 0);
    const int ringLinkOverride = settingsIni->getInt("AP", "RingLinkOverride", 0);
    const int trapLinkOverride = settingsIni->getInt("AP", "TrapLinkOverride", 0);


    const bool showChatMessages = settingsIni->getBool("Messages", "ShowChatMessages", true);
    const bool showGoalReached = settingsIni->getBool("Messages", "ShowGoalReached", true);
    const bool showCountdowns = settingsIni->getBool("Messages", "ShowCountdowns", true);
    const bool showPlayerConnections = settingsIni->getBool("Messages", "ShowPlayerConnections", false);

    archipelagoManager.SetServerConfiguration(serverIp, playerName, serverPassword,
                                              static_cast<DeathLinkOverride>(deathLinkOverride),
                                              static_cast<RingLinkOverride>(ringLinkOverride),
                                              static_cast<TrapLinkOverride>(trapLinkOverride),
                                              showChatMessages, showGoalReached, showCountdowns, showPlayerConnections
    );
}

void LoadDisplayMessageSettings(const IniFile* settingsIni)
{
    const float messageDisplayDuration = settingsIni->getFloat("Messages", "MessageDisplayDuration", 5.0f);
    const int messageFontSize = settingsIni->getInt("Messages", "MessageFontSize", 21);
    const int displayInGameTracker = settingsIni->getInt("Messages", "InGameTracker", 0);
    const int itemMessageColorR = settingsIni->getInt("Messages", "ItemMessageColorR", 33);
    const int itemMessageColorG = settingsIni->getInt("Messages", "ItemMessageColorG", 255);
    const int itemMessageColorB = settingsIni->getInt("Messages", "ItemMessageColorB", 33);


    const int chatMessageColorR = settingsIni->getInt("Messages", "ChatMessageColorR", 255);
    const int chatMessageColorG = settingsIni->getInt("Messages", "ChatMessageColorG", 255);
    const int chatMessageColorB = settingsIni->getInt("Messages", "ChatMessageColorB", 255);


    displayManager.SetMessageConfiguration(messageDisplayDuration, messageFontSize,
                                              static_cast<DisplayInGameTracker>(displayInGameTracker),
                                           (0xFF << 24) | itemMessageColorR << 16 | itemMessageColorG << 8 |
                                           itemMessageColorB,
                                           (0xFF << 24) | chatMessageColorR << 16 | chatMessageColorG << 8 |
                                           chatMessageColorB);
}

void LoadGameSettings(const IniFile* settingsIni)
{
    const int homingAttackIndicator = settingsIni->getInt("GameSettings", "HomingAttackIndicatorEnabled", 0);
    const bool completeMultipleLevelMissions = settingsIni->getBool("GameSettings", "CompleteMultipleLevelMissions",
                                                                    true);
    const bool autoSkipCutscenes = settingsIni->getBool("GameSettings", "AutoSkipCutscenes", true);
    const bool eggCarrierTransformationCutscene = settingsIni->getBool("GameSettings",
                                                                       "EggCarrierTransformationCutscene", true);
    const bool skipCredits = settingsIni->getBool("GameSettings", "SkippableCredits", true);
    const bool noLifeLossOnRestart = settingsIni->getBool("GameSettings", "NoLifeLossOnRestart", true);

    const bool extendRingCapacity = settingsIni->getBool("GameSettings", "ExtendRingCapacity", false);

    const bool showEntranceIndicators = settingsIni->getBool("GameSettings",
                                                             "ShowEntranceIndicators", true);

    const int voiceMenuIndex = settingsIni->getInt("CharacterVoiceReactions", "VoiceMenu", -1);

    const bool showCommentsSubtitles = settingsIni->getBool("CharacterVoiceReactions",
                                                            "DisplaySubtitlesForVoiceReactions", true);
    const bool eggmanCommentOnTrap = settingsIni->getBool("CharacterVoiceReactions", "EggmanOnTrap", true);
    const bool otherCharactersCommentOnTrap = settingsIni->getBool("CharacterVoiceReactions", "OtherCharactersOnTrap",
                                                                   true);
    const bool currentCharacterReactToTrap = settingsIni->getBool("CharacterVoiceReactions", "CurrentCharacterOnTrap",
                                                                  true);

    const bool eggmanCommentOnCharacterUnlock = settingsIni->getBool("CharacterVoiceReactions", "EggmanOnUnlock", true);
    const bool currentCharacterCommentOnCharacterUnlock = settingsIni->getBool(
        "CharacterVoiceReactions", "CurrentCharacterOnUnlock", true);
    const bool unlockedCharacterCommentOnCharacterUnlock = settingsIni->getBool(
        "CharacterVoiceReactions", "UnlockedCharactersOnUnlock", true);
    const bool eggmanCommentOnKeyItems = settingsIni->getBool("CharacterVoiceReactions", "EggmanOnKeyItem", true);
    const bool tikalCommentOnKeyItems = settingsIni->getBool("CharacterVoiceReactions", "TikalOnKeyItem", true);
    const bool currentCharacterCommentOnKeyItems = settingsIni->getBool("CharacterVoiceReactions",
                                                                        "CurrentCharacterOnKeyItem", true);

    const int chaoStatsMultiplier = settingsIni->getInt("Chao", "StatGainMultiplier");

    const bool trackerArrow = settingsIni->getBool("Sanity", "TrackerArrow", true);
    const bool trackerArrowToggleable = settingsIni->getBool("Sanity", "TrackerArrowToggleable", false);
    const bool trackerArrowShowDistance = settingsIni->getBool("Sanity", "TrackerArrowShowDistance", true);
    const bool trackerArrowOverrideColor = settingsIni->getBool("Sanity", "TrackerArrowOverrideColor", false);
    const int trackerArrowR = settingsIni->getInt("Sanity", "TrackerArrowR", 0);
    const int trackerArrowG = settingsIni->getInt("Sanity", "TrackerArrowG", 0);
    const int trackerArrowB = settingsIni->getInt("Sanity", "TrackerArrowB", 255);
    const int trackerArrowColor = 0xFF << 24 | trackerArrowR << 16 | trackerArrowG << 8 | trackerArrowB;

    const bool enemyIndicator = settingsIni->getBool("Sanity", "EnemyIndicator", true);
    const int enemyIndicatorR = settingsIni->getInt("Sanity", "EnemyIndicatorR", 255);
    const int enemyIndicatorG = settingsIni->getInt("Sanity", "EnemyIndicatorG", 0);
    const int enemyIndicatorB = settingsIni->getInt("Sanity", "EnemyIndicatorB", 0);
    const int enemyIndicatorColor = 0xFF << 24 | enemyIndicatorR << 16 | enemyIndicatorG << 8 | enemyIndicatorB;

    const bool capsuleIndicator = settingsIni->getBool("Sanity", "CapsuleIndicator", true);
    const int capsuleIndicatorR = settingsIni->getInt("Sanity", "CapsuleIndicatorR", 0);
    const int capsuleIndicatorG = settingsIni->getInt("Sanity", "CapsuleIndicatorG", 255);
    const int capsuleIndicatorB = settingsIni->getInt("Sanity", "CapsuleIndicatorB", 0);
    const int capsuleIndicatorColor = 0xFF << 24 | capsuleIndicatorR << 16 | capsuleIndicatorG << 8 | capsuleIndicatorB;

    const bool fishIndicator = settingsIni->getBool("Sanity", "FishIndicator", true);
    const int fishIndicatorR = settingsIni->getInt("Sanity", "FishIndicatorR", 0);
    const int fishIndicatorG = settingsIni->getInt("Sanity", "FishIndicatorG", 255);
    const int fishIndicatorB = settingsIni->getInt("Sanity", "FishIndicatorB", 255);
    const int fishIndicatorColor = 0xFF << 24 | fishIndicatorR << 16 | fishIndicatorG << 8 | fishIndicatorB;

    const bool progressionIndicator = settingsIni->getBool("Sanity", "ProgressionItemIndicator", true);
    const int progressionIndicatorR = settingsIni->getInt("Sanity", "ProgressionIndicatorR", 212);
    const int progressionIndicatorG = settingsIni->getInt("Sanity", "ProgressionIndicatorG", 175);
    const int progressionIndicatorB = settingsIni->getInt("Sanity", "ProgressionIndicatorB", 55);
    const int progressionIndicatorColor = 0xFF << 24 | progressionIndicatorR << 16 | progressionIndicatorG << 8 |
        progressionIndicatorB;


    displayManager.UpdateVoiceMenuCharacter(voiceMenuIndex);
    cheatsManager.SetCheatsConfiguration(autoSkipCutscenes, skipCredits, noLifeLossOnRestart);
    eventDetector.SetMultipleMissions(completeMultipleLevelMissions);
    eventDetector.SetSanitySettings(trackerArrow, trackerArrowColor, trackerArrowToggleable,
                                    trackerArrowShowDistance, trackerArrowOverrideColor,
                                    enemyIndicator, enemyIndicatorColor,
                                    capsuleIndicator, capsuleIndicatorColor,
                                    fishIndicator, fishIndicatorColor,
                                    progressionIndicator, progressionIndicatorColor);
    eventDetector.setHomingAttackIndicator(static_cast<HomingAttackIndicator>(homingAttackIndicator));
    worldStateManager.SetShowEntranceIndicators(showEntranceIndicators);
    worldStateManager.SetEggCarrierTransformationCutscene(eggCarrierTransformationCutscene);
    worldStateManager.SetChaoStatsMultiplier(chaoStatsMultiplier);
    characterManager.SetCharacterVoiceReactions(eggmanCommentOnTrap, otherCharactersCommentOnTrap,
                                                currentCharacterReactToTrap, showCommentsSubtitles);
    characterManager.SetExtendRingCapacity(extendRingCapacity);

    randomizer.SetCharacterVoiceReactions(eggmanCommentOnCharacterUnlock, currentCharacterCommentOnCharacterUnlock,
                                          unlockedCharacterCommentOnCharacterUnlock, eggmanCommentOnKeyItems,
                                          tikalCommentOnKeyItems, currentCharacterCommentOnKeyItems,
                                          showCommentsSubtitles);
}

#define ReplacePNG_Common(a) do { \
_snprintf_s(pathbuf, LengthOfArray(pathbuf), "%s\\textures\\pvr_common\\index.txt", path); \
helperFunctions.ReplaceFile("system\\" a ".PVR", pathbuf); \
} while (0)

void ReplaceEmblemImage(const char* path, const HelperFunctions& helperFunctions)
{
    char pathbuf[MAX_PATH];
    ReplacePNG_Common("HYOJI_EMBLEM0");
    ReplacePNG_Common("HYOJI_EMBLEM1");
}
