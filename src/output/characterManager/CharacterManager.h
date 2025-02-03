#pragma once
#include <queue>

#include "../../pch.h"
#include "../../application/structs/Options.h"
#include "../../application/structs/UnlockStatus.h"
#include "../../application/structs/ItemData.h"
#include "../../application/structs/WeightedRandomSelector.h"


#define RING_LOSS_SOUND_ID 0
#define RING_GAIN_SOUND_ID 7

struct RingDifference
{
    int ringDifference;
    int hardRingDifference;
};

     

class CharacterManager
{
public:
    CharacterManager();
    void SetExtendRingCapacity(bool extendRingCapacity);

    void GiveUpgrade(Upgrades upgrade);
    void RemoveUpgrade(Upgrades upgrade);
    void UpdateOptions(Options newOptions);
    void UpdateUnlockStatus(UnlockStatus unlockStatus);
    void KillPlayer();
    void ProcessRings(Sint16 amount);
    RingDifference GetRingDifference();
    void GiveFillerItem(FillerType filler);
    void OnPlayingFrame();
    void SetStartingCharacter(int startingCharacterIndex);
    void SetCharacterVoiceReactions(bool eggmanCommentOnTrap, bool otherCharactersCommentOnTrap,
                                    bool currentCharacterReactToTrap, bool showCommentsSubtitles);
    void SetReverseControlTrapDuration(int reverseControlTrapDuration);
    void SetTrapsOnAdventureFields(bool trapsOnAdventureFields);
    void SetTrapsOnBossFights(bool trapsOnBossFights);
    void SetTrapsOnPerfectChaosFight(bool trapsOnPerfectChaosFight);
    void RemoveStatusEffects();
    Options options;
    UnlockStatus unlockStatus;
    int lastRingAmount;
    bool reverseControlsEnabled = false;
    bool extendRingCapacity = false;

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
    bool _showCommentsSubtitles = true;

    bool _trapsOnBossFights = true;
    bool _trapsOnAdventureFields = true;
    bool _trapsOnPerfectChaosFight = false;

    std::map<int, std::string> _trapCommentMap = {
        {174, "Get a load of this!"},
        {171, "All systems; full power!"},
        {173, "Ah-ha!"},
        {178, "Ho ho! It's no use. Give up!"},
        {221, "Wha ha ha ha ha ha ha ha ha!"},
        {413, "Ha ha ha ha ha ha ha ha ha ha ha!"},
        {443, "Aha!"},
        {449, "Ha ha ha ha ha!"},
        {463, "Oh no; you don't!"},
        {465, "Ha ha ha ha ha ha ha ha ha!"},
        {474, "Ha ha ha ha ha ha!"},
        {562, "Ha ha ha ha ha!"},
        {569, "Ha ha ha ha ha!"},
        {650, "Gotcha!"},
        {924, "You can't get away this easily!"},
        {926, "Too late; buddy!"},
        {1059, "Ah ha hahahaha!"},
        {1072, "Mwuahahahahahahahahaha!"},
        {1376, "Ha ha ha ha ha ha!"},
        {1518, "Get a load of this!"},
        {1522, "Hahahahaha! I bet you weren't expecting this!"},
        {1525, "Haha hahahahaha!"},
        {1542, "I guess you weren't expecting that; were you?"},
        {1680, "You're not going to get away that easily. Huhahahaha."},
        {1903, "Take this!"},
        {1986, "Huhaha! Why don't you give up?"},
        {1987, "Ha ha! It's no use! Give up!"},
        {222, "Goodbye; Tails!"},
        {226, "Give up now; Tails!"},
        {217, "I've got you now; Tails."},
        {563, "Oh yes! Attack Sonic now!"},
        {922, "Where do you think you're going; Amy?"},
        {1436, "Ready men? Charge!"},
        {404, "You are completely surrounded!"},
        {405, "Surrender yourself!"},
        {407, "Lock on target men. Ready? Fire!"},
        {384, "You're gonna pay for what you've done!"},
        {849, "Hey; are you alright? You look kind of hurt."},
        {885, "Now; now; calm down."},
        {902, "I pity you."},
        {952, "Uh; you okay?"},
        {988, "Oh no! Are you okay?"},
        {990, "Now you're gonna get it!"},
        {1258, "I feel sorry for you."},
        {1493, "Here; take this!"},
        {888, "Nope!"},
        {365, "Are you guys okay?"},
        {1336, "Uh oh..."},
        {241, "The ice looks kinda tasty!"},
        {169, "Resistance is futile."},
        {385, "Target confirmed."},
        {1777, "Running impossible."},
        {1779, "Ha. Ha. Ha."},
        {269, "Blue hedgehog: enemy."},
        {386, "Blue hedgehog: enemy."},
        {382, "When will you ever learn?"},
        {383, "This time; you're finished!"},
        {1159, "Yeah! You're finished!"},
        {1981, "What's the matter? What're you waiting for?"},
        {496, "Ah; I wonder if he's okay."},
        {605, "Something buggin' you?"},
        {211, "See you later; Tails!"},
        {229, "What a nice breeze!"},
        {240, "Man; everything's frozen!"},
        {618, "Uh oh; what's this?"},
        {731, "Oops!"},
        {828, "Oops!"},
        {1333, "Oops!"},
        {1511, "All's well that ends well; right?"},
        {347, "Hey; come on!"},
        {506, "Whoa!!"},
        {517, "Ahh! Sonic! Help!"},
        {524, "Sonic; help me!"},
        {847, "Aahh!! Watch it; watch it!"},
        {851, "Ah! Uh oh!"},
        {872, "*shouts*"},
        {881, "*scream*"},
        {916, "*gasp*"},
        {923, "Eggman; no!"},
        {987, "*gasp*"},
        {1739, "Oo-oo-ooh!"},
        {1740, "Oh no!"},
        {1741, "Whoa!"},
        {1743, "Wah!"},
        {1742, "Bbrrr!"},
        {747, "Wwhooa!"},
        {1330, "Whoaaaa!!"},
        {1331, "Ouh!"},
        {1752, "*inhales*"},
        {1753, "Oh no."},
        {1755, "Oof!"},
        {1756, "Oh no!"},
        {1757, "Wah!!"},
        {1764, "Whooaa!!"},
        {164, "Oh no!"},
        {332, "Why?"},
        {380, "That's it. I've had enough!"},
        {475, "Ahh; Eggman!"},
        {1004, "What the!?"},
        {1006, "Oh no!"},
        {1010, "Ooph!"},
        {1011, "Auh! Euh! Hey; no fair!"},
        {1789, "Whoa!"},
        {1795, "Ohh!"},
        {1796, "I'm a goner."},
        {1799, "Whooa!"},
        {165, "Oh no!"},
        {167, "I've had enough!"},
        {170, "Oh no!"},
        {402, "Huh?"},
        {444, "Oh no!"},
        {460, "Hyyeeh!"},
        {464, "Aw; geesh!"},
        {476, "Uh oh!"},
        {502, "You must be kidding!"},
        {523, "Stop!"},
        {561, "Oh no! Not again!"},
        {582, "Agh; I hate Eggman!"},
        {1461, "What?!"},
        {1854, "Wwhoa!"},
        {1855, "Whoa!"},
        {239, "It's getting cold!"},
        {376, "H-hey; wait a minute!"},
        {619, "Noooo!"},
        {620, "Ahhhh!"},
        {623, "Ahhhh!"},
        {671, "Ahhhhh!"},
        {728, "Sstop!"},
        {748, "Yikes!!"},
        {802, "Oh no!"},
        {1801, "Whoo!"},
        {1814, "Augh!"}
    };
};
