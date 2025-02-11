#pragma once
#include "../pch.h"
#include "../output/locationRepository/LocationRepository.h"
#include "../output/displayManager/DisplayManager.h"
#include "../output/itemRepository/ItemRepository.h"
#include "../output/characterManager/CharacterManager.h"
#include "../output/worldStateManager/WorldStateManager.h"
#include "../output/archipelagoMessenger/ArchipelagoMessenger.h"
#include "../output/saveFileManager/SaveFileManager.h"
#include "structs/LocationData.h"
#include "structs/Options.h"

class Randomizer
{
public:
    Randomizer(DisplayManager& displayManager, CharacterManager& characterManager, WorldStateManager& menuManager,
               ItemRepository& itemRepository, LocationRepository& locationRepository,
               ArchipelagoMessenger& archipelagoMessenger, SaveFileManager& saveFileManager)
        : _displayManager(displayManager),
          _characterManager(characterManager),
          _worldStateManager(menuManager),
          _itemRepository(itemRepository),
          _locationRepository(locationRepository),
          _archipelagoMessenger(archipelagoMessenger),
          _saveFileManager(saveFileManager), _deathPending(false)

    {
        _displayManager.UpdateChecks(locationRepository.GetLocations());
    }

    void OnCheckFound(int checkId) const;
    void PlayRandomVoiceForItem(const ItemData& item, const int64_t itemId) const;
    void OnItemReceived(int64_t itemId) const;
    void MarkCheckedLocation(int64_t checkId) const;
    void OnCharacterLoaded() const;
    void OnCharacterSelectScreenLoaded() const;
    std::map<int, LocationData> GetCheckData() const;
    void OnConnected(std::string playerName);
    void OnGameCompleted();
    void ShowStatusInformation(std::string information);
    void QueueNewItemMessage(std::string information);
    void QueueNewChatMessage(std::string information);
    void OnEmblemGoalSet(int emblemGoal);
    void OnLevelGoalSet(int levelGoal);
    void OnMissionGoalSet(int missionGoal);
    void OnBossesGoalSet(int bossesGoal);
    void SetCharacterStatingArea(Characters characters, StartingArea startingArea);
    void SetPlayableCharacter(Characters character, bool playable);
    void SetActionStageMissions(Characters characters, int missions);
    void OnEnemySanitySet(bool enemySanity);
    void OnFishSanitySet(bool fishSanity);
    void OnLazyFishingSet(bool lazyFishing);
    void SetCharacterEnemySanity(Characters character, bool characterEnemySanity);
    void OnCapsuleSanitySet(bool capsuleSanity);
    void OnPinballCapsulesSet(bool includePinballCapsules);
    void SetCharacterCapsuleSanity(Characters character, bool characterCapsuleSanity);
    void OnLifeCapsuleSanitySet(bool lifeCapsuleSanity);
    void OnShieldCapsuleSanitySet(bool shieldCapsuleSanity);
    void OnPowerUpCapsuleSanitySet(bool powerUpCapsuleSanity);
    void OnRingCapsuleSanitySet(bool ringCapsuleSanity);
    void SetDeathLink(bool deathLinkActive);
    void SetRingLink(bool ringLinkActive);
    void SetCasinopolisRingLink(bool casinopolisRingLink);
    void SetHardRingLink(bool hardRingLinkActive);
    void SetRingLoss(RingLoss ringLoss);
    void SetTwinkleCircuitCheck(int twinkleCircuitCheck);
    void SetMultipleTwinkleCircuitChecks(int multipleTwinkleCircuitChecks);
    void SetSkyChaseChecks(bool skyChaseChecks);
    void SetSkyChaseChecksHard(bool skyChaseChecksHard);
    void SetBossChecks(bool bossChecks);
    void SetUnifyChaos4(bool unifyChaos4);
    void SetUnifyChaos6(bool unifyChaos6);
    void SetUnifyEggHornet(bool unifyEggHornet);
    Options GetOptions() const;
    std::vector<CapsuleLocationData> GetCapsules();
    std::vector<EnemyLocationData> GetEnemies();
    void ProcessDeath(const std::string& deathCause);
    void OnPlayingFrame();
    void OnSync();
    void OnDeath();
    void ProcessRings(Sint16 amount);
    void ResetItems();
    void SetMissionMode(int missionModeEnabled);
    void SetAutoStartMissions(int autoStartMissions);
    void OnCheckVersion(int serverVersion);
    void SetStartingCharacter(int startingCharacterIndex);
    void UpdateLevelEntrances(LevelEntrances levelEntrances);
    void UpdateMissionBlacklist(const std::vector<int>& missionBlacklist);
    void UpdateProgressionItemsList(const std::vector<int>& progressionItemsList);
    void SetEntranceRandomizer(bool enableEntranceRandomizer);
    void SetCharacterVoiceReactions(bool eggmanCommentOnCharacterUnlock, bool currentCharacterCommentOnCharacterUnlock,
                                    bool unlockedCharacterCommentOnCharacterUnlock, bool eggmanCommentOnKeyItems,
                                    bool tikalCommentOnKeyItems,
                                    bool currentCharacterCommentOnKeyItems,
                                    bool showCommentsSubtitles);
    void SetReverseControlTrapDuration(int reverseControlTrapDuration);
    void SetTrapsOnAdventureFields(bool trapsOnAdventureFields);
    void SetTrapsOnBossFights(bool trapsOnBossFights);
    void SetTrapsOnPerfectChaosFight(bool trapsOnPerfectChaosFight);
    void SetSuperSonicModRunning(bool isModRunning);
    void SetSendDeathLinkChance(int sendDeathLinkChance);
    void SetReceiveDeathLinkChance(int receiveDeathLinkChance);
    void OnGoalRequiresLevelsSet(bool goalRequiresLevels);
    void OnGoalRequiresChaosEmeraldsSet(bool goalRequiresChaosEmeralds);
    void OnGoalRequiresEmblems(bool goalRequiresEmblems);
    void OnGoalRequiresMissionsSet(bool goalRequiresMissions);
    void OnGoalRequiresBossesSet(bool goalRequiresBosses);
    void OnGoalRequiresChaoRacesSet(bool goalRequiresChaoRaces);
    void OnSetLogicLevel(int logicLevel);

private:
    bool AreLastStoryRequirementsCompleted() const;
    DisplayManager& _displayManager;
    CharacterManager& _characterManager;
    WorldStateManager& _worldStateManager;
    ItemRepository& _itemRepository;
    LocationRepository& _locationRepository;
    ArchipelagoMessenger& _archipelagoMessenger;
    SaveFileManager& _saveFileManager;

    Options _options;
    std::string _pendingDeathCause;
    bool _deathPending;

    float _deathLinkCooldown = 5.0f;
    std::clock_t _deathLinkCooldownTimer = -1;

    int _sendDeathLinkChance = 100;
    int _receiveDeathLinkChance = 100;


    bool _eggmanCommentOnCharacterUnlock = true;
    bool _currentCharacterCommentOnCharacterUnlock = true;
    bool _unlockedCharacterCommentOnCharacterUnlock = true;

    bool _eggmanCommentOnKeyItems = true;
    bool _tikalCommentOnKeyItems = true;
    bool _currentCharacterCommentOnKeyItems = true;
    bool _showCommentsSubtitles = true;
    
    bool _superSonicModRunning = false;


    std::map<int, std::string> _commentMap = {
        {498, "Long time no see."},
        {860, "Long time; no see!"},
        {364, "Looking good; buddy!"},
        {363, "Sensors detecting life."},
        {2013, "Hmm... I wonder what those guys are doing?"},
        {277, "I wanna go shopping!"},
        {324, "I'm going to do my best; Sonic."},
        {1730, "It's my turn now!"},
        {499, "Uhhh eh; Amy!"},
        {512, "Aw; man! That girl is such a pain!"},
        {861, "Y-ah-uhh... Amy!"},
        {1492, "Amy!"},
        {959, "Amy; come on; let's get going!"},
        {367, "I wanna go fishing!"},
        {566, "I must save Froggy!"},
        {1335, "Froggy?"},
        {1342, "Mm; smells like Froggy's around somewhere..."},
        {1744, "Hold on Froggy! I'm coming!"},
        {1876, "Okay! One more time!"},
        {2012, "Froggy? Where are you?"},
        {2024, "Hope you find Froggy soon!"},
        {394, "Combat system activated."},
        {543, "What is your wish; master Robotnik?"},
        {775, "What is your wish; Master?"},
        {932, "At your service; sir."},
        {1276, "How can I serve you; Dr. Robotnik?"},
        {1767, "Preperation complete."},
        {504, "Look! One of Eggman's robots."},
        {551, "This robot is my friend. He helped me!"},
        {870, "Aahh; look! Eggman's robot's on the loose!"},
        {911, "You're different from the other robots."},
        {943, "This robot is different."},
        {1292, "And how are you; my metal friend?"},
        {1008, "Huh? Who are you?"},
        {1121, "Hey; isn't that one of Eggman's robots?"},
        {265, "I smell oil."},
        {378, "Something's different about this robot."},
        {542, "GAMMA!!"},
        {779, "I'll leave it up to you; Gamma."},
        {931, "Gamma!"},
        {1174, "E-102; Codename: Gamma!"},
        {1179, "Enter; Gamma!"},
        {1186, "Okay then; Gamma. Here's your test!"},
        {1280, "I'm counting on you Gamma!"},
        {261, "Okay now; where's the treasure?"},
        {308, "I've got to find the Master Emerald."},
        {709, "I have some unfinished business to take care of."},
        {1123, "Here I come; Eggman!"},
        {1787, "Okay! Let's go!"},
        {370, "What's up; Knuckles?"},
        {579, "Hey there; Knuckles. Glad you finally made it!\nI thought you got lost or something."},
        {604, "What's up; Knuckles?"},
        {1148, "There you are Knuckles! About time."},
        {238, "What's the smell? Smells like trash!"},
        {679, "Hey Knuckles; what's up?"},
        {1036, "Kn- Knuckles!"},
        {206, "Hey; hey; hey!"},
        {242, "Watch and learn!"},
        {248, "Time for some supersonic speed!"},
        {349, "Yo! Have you guys been good?"},
        {374, "You've had your fun. Now it's my turn!"},
        {410, "This could be fun!"},
        {568, "Just leave it to me!"},
        {247, "I wonder where Sonic went."},
        {360, "If only Sonic were here."},
        {857, "Oh; Sonic!"},
        {858, "(dreamy sigh) My hero!"},
        {964, "I wonder what Sonic is doing."},
        {1491, "Hey; Sonic!"},
        {1147, "Hey Sonic!"},
        {417, "Hey; Sonic! Long time no see; huh?"},
        {455, "Sonic!"},
        {471, "Come on; Sonic; we need to get busy!"},
        {525, "Hey; Sonic!"},
        {760, "There's Sonic!"},
        {1091, "Hurry Sonic! What're we waiting for?"},
        {1408, "Sonic!"},
        {1451, "Sonic; wake up!"},
        {1512, "Sonic?"},
        {235, "I wonder where Sonic is."},
        {431, "Ha ha ha ha! If it isn't Sonic!"},
        {601, "Well; if it isn't my pal; Sonic."},
        {1392, "Ooh; I hate that Sonic!"},
        {1713, "Sonic! It's up to you now."},
        {1714, "Be brave; blue hedgehog."},
        {243, "Time to jam!"},
        {275, "Boy; I'm hungry."},
        {352, "How's it goin' guys?"},
        {375, "C'mon Tails; you can do it!"},
        {528, "Roger!"},
        {617, "All systems go; full speed ahead!"},
        {753, "The time has come at last."},
        {757, "Ready Sonic? Here I come!"},
        {1800, "Here I come; Sonic!"},
        {205, "Come on; Tails!"},
        {207, "All right; Tails!"},
        {208, "Hey; Tails!"},
        {414, "Wha? Tails?!"},
        {526, "Tails! I'm glad you're okay."},
        {527, "Ready to roll; champ? Let's go!"},
        {219, "You little fox!"},
        {478, "That's a Chaos Emerald!"},
        {1076, "(gasp) That's... a Chaos Emerald!"},
        {1142, "Look! It's the Emerald!"},
        {425, "Whoa! A Chaos Emerald!"},
        {632, "It's a Chaos Emerald! No way!"},
        {427, "This thing's got unlimited power; ya know."},
        {539, "A Chaos Emerald!"},
        {633, "I was lucky to find one of the seven Chaos Emeralds."},
        {670, "The Chaos Emerald!"},
        {726, "Wow! There's a Chaos Emerald!"},
        {751, "Oh yeah; the Chaos Emerald. Perfect!"},
        {771, "That's a Chaos Emerald!"},
        {928, "It's a Chaos Emerald!"},
        {438, "I want all of the Chaos Emeralds."},
        {445, "Come on Chaos; time to eat!"},
        {450, "His strength increases every time\n I feed him a Chaos Emerald!"},
        {487, "These are for you; my friend!"},
        {652, "Chaos could use a little snack!"},
        {485, "Now I have four lovely Emeralds!"},
        {697, "Ha ha ha ha! Four! Count them; four Emeralds!"},
        {1083, "Hahahahaha! I've got four Emeralds now."},
        {570, "Now I have six of the Chaos Emeralds!"},
        {571, "There's only one more left to find!"},
        {1355, "So these are the seven Emeralds."},
        {1231, "Ahh! There it is! Right there!!"},
        {1352, "Wow..."},
        {1632, "Take the boat to get to the Egg Carrier."},
        {1868, "The Egg Carrier has crashed and is floating somewhere in the ocean.\nUse this boat to get to it."},
        {1927, "Take this boat to get to the Egg Carrier."},
        {1921, "Something good may happen at the Casino area."},
        {1922, "Why don't you try going to the Casino?"},
        {1558, "You can go to the Casino area at nighttime."},
        {1928, "Why don't you try going to Angel Island?"},
        {1955, "You can break through the wall if you use dynamite."},
        {1561, "You can get into a certain building\n using the Employee Card."},
        {1872, "Get to the beach by going through the hotel."},
        {1559, "Use the Ice Stone in the Mystic Ruins."},
        {1641, "Didn't you see a stone with an ice pattern on it?"},
        {1634, "The trolley car seems to be working.\nIt leads to the jungle."},
        {1572, "A train will be arriving soon. Please stand back."},
        {1654, "Passengers are requested to wait onboard the train."},
        {1656, "A train will be arriving soon. Please stand back."},
        {1630, "The train for Station Square has arrived."},
        {1869, "Go to the station to catch the train."},
        {1918, "The train seems to be moving now."},
        {1639, "If you have the Stone of Wind\ngusts of strong wind are known to blow in the caves."},
        {510, "Let's go!"},
        {995, "I'm so happy!"},
        {1731, "Alright!"},
        {1732, "Yay!"},
        {1733, "Alright!"},
        {291, "It's nice to have an ocean nearby."},
        {297, "I'd love to vacation here!"},
        {303, "I'm getting excited!"},
        {509, "Look here! It says; 'Cute couples get in free'!"},
        {875, "Look! It says cute couples can get in free!"},
        {876, "What are we waiting for?"},
        {314, "Arriving at Angel Island."},
        {285, "Train to Mystic Ruins confirmed."},
        {305, "Bumper car area confirmed."},
        {1346, "Yes!"},
        {1383, "Hurray!"},
        {1386, "Oh. Okay! Thanks."},
        {1389, "Hey; maybe we could use this."},
        {1745, "Wow; it's big!"},
        {1751, "Not too bad!"},
        {1760, "Super!"},
        {1765, "What's this?"},
        {1766, "Allright!"},
        {319, "Maybe I'll go home."},
        {304, "Twinkle Park?"},
        {1112, "This is beginning to blow my mind."},
        {1788, "Yeeah!"},
        {1790, "Found it!"},
        {1794, "Heh. Good enough."},
        {313, "I've got to get this island airborne again."},
        {296, "Great; a resort hotel."},
        {213, "Horray!"},
        {214, "I got it!"},
        {315, "Now this is more like it!"},
        {372, "Not bad; not bad at all!"},
        {400, "Aw; yeah!"},
        {401, "This is happenin'!"},
        {406, "Aw; yeah!"},
        {587, "Wow; what's this?"},
        {1835, "Hurray!"},
        {1837, "Let's get 'em!"},
        {1838, "Yes!"},
        {1839, "Woohoo!"},
        {1840, "Yes."},
        {1842, "*whistles* Sweet!"},
        {1844, "Yeah; not bad!"},
        {1849, "Yes!"},
        {1852, "Yeah!"},
        {1853, "Oh-kay!"},
        {312, "So; this is Angel Island!"},
        {300, "I'm not too fond of places like this."},
        {231, "I can hear the wind in the distance."},
        {424, "Tada!"},
        {1802, "Allright!"},
        {1803, "Yeeaah!"},
        {1812, "Cool."},
        {295, "This hotel is nice!"},
        {289, "Trains are cool; too!"}
    };
};
