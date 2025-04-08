#include "Randomizer.h"

#include <random>

const char* subtitleBuffer[] = {NULL, NULL};

void Randomizer::OnCheckFound(const int checkId) const
{
    const LocationData check = _locationRepository.GetLocation(checkId);

    if (check.type == LocationUpgrade)
    {
        const ItemData item = _itemRepository.GetItem(check.originalItemId);
        if (!item.obtained)
            _characterManager.RemoveUpgrade(item.upgrade);
    }

    _locationRepository.SetLocationChecked(checkId);
    _archipelagoMessenger.CheckLocation(checkId);

    _displayManager.UpdateChecks(_locationRepository.GetLocations());
    _worldStateManager.UpdateChecks(_locationRepository.GetLocations());
    if (check.type == LocationLevel && check.levelMission == MISSION_C && _options.goalRequiresLevels)
    {
        const LevelStatus levelStatus = _locationRepository.GetLevelStatus(_options);
        _displayManager.UpdateLevelStatus(levelStatus);
        _displayManager.ShowGoalStatus();
        if (_options.levelGoal == levelStatus.levelsCompleted
            && AreLastStoryRequirementsCompleted())
            _displayManager.QueueItemMessage("You can now fight Perfect Chaos!");
    }
    if (check.type == LocationMission && _options.goalRequiresMissions)
    {
        const MissionStatus missionStatus = _locationRepository.GetMissionStatus(_options);
        _displayManager.UpdateMissionStatus(missionStatus);
        _displayManager.ShowGoalStatus();
        if (_options.missionGoal == missionStatus.missionsCompleted
            && AreLastStoryRequirementsCompleted())
            _displayManager.QueueItemMessage("You can now fight Perfect Chaos!");
    }
    if (check.type == LocationBossFight && _options.goalRequiresBosses)
    {
        const BossesStatus bossesStatus = _locationRepository.GetBossesStatus(_options);
        _displayManager.UpdateBossesStatus(bossesStatus);
        _displayManager.ShowGoalStatus();
        if (_options.bossesGoal == bossesStatus.bossesCompleted
            && AreLastStoryRequirementsCompleted())
            _displayManager.QueueItemMessage("You can now fight Perfect Chaos!");
    }
    PrintDebug("Check found: %d %s, and type: %d\n", checkId, check.displayName.c_str(), check.type);
    if (check.type == LocationChaoRace && _options.goalRequiresChaoRaces)
    {
        const ChaoStatus chaoStatus = _locationRepository.GetChaoStatus();
        _displayManager.UpdateChaoStatus(chaoStatus);
        _displayManager.ShowGoalStatus();
        if (chaoStatus.racesTotal >= chaoStatus.racesCompleted && AreLastStoryRequirementsCompleted())
            _displayManager.QueueItemMessage("You can now fight Perfect Chaos!");
    }
}

void Randomizer::MarkCheckedLocation(const int64_t checkId) const
{
    LocationData locationData = _locationRepository.SetLocationChecked(checkId);
    if (locationData.type == LocationMission)
        _saveFileManager.SetMissionCompleted(locationData.missionNumber);

    const LevelStatus levelStatus = _locationRepository.GetLevelStatus(_options);
    _displayManager.UpdateLevelStatus(levelStatus);
    const MissionStatus missionStatus = _locationRepository.GetMissionStatus(_options);
    _displayManager.UpdateMissionStatus(missionStatus);
    const BossesStatus bossesStatus = _locationRepository.GetBossesStatus(_options);
    _displayManager.UpdateBossesStatus(bossesStatus);
    const ChaoStatus chaoStatus = _locationRepository.GetChaoStatus();
    _displayManager.UpdateChaoStatus(chaoStatus);
    _displayManager.UpdateChecks(_locationRepository.GetLocations());
    _worldStateManager.UpdateChecks(_locationRepository.GetLocations());
}


void Randomizer::OnItemReceived(const int64_t itemId) const
{
    const bool ignore = _itemRepository.SetObtained(itemId);
    if (ignore)
        return;

    const ItemData item = _itemRepository.GetItem(itemId);

    if (item.type == ItemUpgrade)
        _characterManager.GiveUpgrade(item.upgrade);
    else if (item.type == ItemCharacter || item.type == ItemKey)
        _worldStateManager.SetEventFlags(item.eventFlags);
    else if (item.type == ItemEmblem)
        _itemRepository.AddEmblem();
    else if (item.type == ItemFiller)
    {
        _characterManager.GiveFillerItem(item.fillerType, false);
        if (_options.trapLinkActive)
        {
            _archipelagoMessenger.SendTrapLink(item.displayName);
            _displayManager.QueueItemMessage("Linked " + item.displayName + " sent");
        }
    }

    const UnlockStatus unlockStatus = _itemRepository.GetUnlockStatus();
    _characterManager.UpdateUnlockStatus(unlockStatus);
    _displayManager.UpdateUnlockStatus(unlockStatus);
    _worldStateManager.UpdateUnlockStatus(unlockStatus);

    if (item.type == ItemChaosEmerald)
    {
        _displayManager.ShowGoalStatus();

        if (this->_superSonicModRunning)
        {
            if (_itemRepository.GetUnlockStatus().GotAllChaosEmeralds())
            {
                SetEventFlag(static_cast<EventFlags>(FLAG_SUPERSONIC_COMPLETE));
                _displayManager.QueueItemMessage("You can now transform into Super Sonic!");
            }
        }

        if (AreLastStoryRequirementsCompleted())
            _displayManager.QueueItemMessage("You can now fight Perfect Chaos!");
    }

    else if (item.type == ItemEmblem)
    {
        _displayManager.ShowGoalStatus();
        if (unlockStatus.currentEmblems == _options.emblemGoal && AreLastStoryRequirementsCompleted())
            _displayManager.QueueItemMessage("You can now fight Perfect Chaos!");
    }

    this->PlayRandomVoiceForItem(item, itemId);
}

void Randomizer::PlayRandomVoiceForItem(const ItemData& item, const int64_t itemId) const
{
    WeightedRandomSelector selector;
    if (item.type == ItemCharacter)
    {
        if (_currentCharacterCommentOnCharacterUnlock)
        {
            if (CurrentCharacter == Characters_Amy)
            {
                selector.addNumber(498, 1); //Long time no see.
                selector.addNumber(860, 1); //Long time; no see!
            }
            else if (CurrentCharacter == Characters_Big)
            {
                selector.addNumber(364, 1); //Looking good; buddy!
            }
            else if (CurrentCharacter == Characters_Gamma)
            {
                selector.addNumber(363, 1); //Sensors detecting life.
            }
            else if (CurrentCharacter == Characters_Knuckles)
            {
                selector.addNumber(2013, 1); //Hmm... I wonder what those guys are doing?
            }
        }

        if (itemId == 4)
        {
            if (_unlockedCharacterCommentOnCharacterUnlock)
            {
                selector.addNumber(277, 1); //I wanna go shopping!
                selector.addNumber(324, 1); //I'm going to do my best; Sonic.
                selector.addNumber(1730, 1); //It's my turn now!
            }
            if (_currentCharacterCommentOnCharacterUnlock)
            {
                if (CurrentCharacter == Characters_Sonic)
                {
                    selector.addNumber(499, 2); //Uhhh eh; Amy!
                    selector.addNumber(512, 2); //Aw; man! That girl is such a pain!
                    selector.addNumber(861, 2); //Y-ah-uhh... Amy!
                    selector.addNumber(1492, 2); //Amy!
                }
                else if (CurrentCharacter == Characters_Tails)
                {
                    selector.addNumber(959, 3); //Amy; come on; let's get going!
                }
            }
        }
        else if (itemId == 6)
        {
            if (_unlockedCharacterCommentOnCharacterUnlock)
            {
                selector.addNumber(367, 1); //I wanna go fishing!
                selector.addNumber(566, 1); //I must save Froggy!
                selector.addNumber(1335, 1); //Froggy?
                selector.addNumber(1342, 1); //Mm; smells like Froggy's around somewhere...
                selector.addNumber(1744, 1); //Hold on Froggy! I'm coming!
                selector.addNumber(1876, 1); //Okay! One more time!
                selector.addNumber(2012, 1); //Froggy? Where are you?
            }
            if (_currentCharacterCommentOnCharacterUnlock)
            {
                if (CurrentCharacter == Characters_Tails)
                {
                    selector.addNumber(2024, 3); //Hope you find Froggy soon!
                }
            }
        }
        else if (itemId == 5)
        {
            if (_unlockedCharacterCommentOnCharacterUnlock)
            {
                selector.addNumber(394, 1); //Combat system activated.
                selector.addNumber(543, 1); //What is your wish; master Robotnik?
                selector.addNumber(775, 1); //What is your wish; Master?
                selector.addNumber(932, 1); //At your service; sir.
                selector.addNumber(1276, 1); //How can I serve you; Dr. Robotnik?
                selector.addNumber(1767, 1); //Preperation complete.
            }
            if (_currentCharacterCommentOnCharacterUnlock)
            {
                if (CurrentCharacter == Characters_Amy)
                {
                    selector.addNumber(504, 2); //Look! One of Eggman's robots.
                    selector.addNumber(551, 2); //This robot is my friend. He helped me!
                    selector.addNumber(870, 2); //Aahh; look! Eggman's robot's on the loose!
                    selector.addNumber(911, 2); //You're different from the other robots.
                    selector.addNumber(943, 2); //This robot is different.
                    selector.addNumber(1292, 2); //And how are you; my metal friend?
                }
                else if (CurrentCharacter == Characters_Knuckles)
                {
                    selector.addNumber(1008, 3); //Huh? Who are you?
                    selector.addNumber(1121, 3); //Hey; isn't that one of Eggman's robots?
                }
                else if (CurrentCharacter == Characters_Sonic)
                {
                    selector.addNumber(265, 3); //I smell oil.
                }
                else if (CurrentCharacter == Characters_Tails)
                {
                    selector.addNumber(378, 3); //Something's different about this robot.
                }
            }
            if (_eggmanCommentOnCharacterUnlock)
            {
                selector.addNumber(542, 1); //GAMMA!!
                selector.addNumber(779, 1); //I'll leave it up to you; Gamma.
                selector.addNumber(931, 1); //Gamma!
                selector.addNumber(1174, 1); //E-102; Codename: Gamma!
                selector.addNumber(1179, 1); //Enter; Gamma!
                selector.addNumber(1186, 1); //Okay then; Gamma. Here's your test!
                selector.addNumber(1280, 1); //I'm counting on you Gamma!
            }
        }
        else if (itemId == 3)
        {
            if (_unlockedCharacterCommentOnCharacterUnlock)
            {
                selector.addNumber(261, 1); //Okay now; where's the treasure?
                selector.addNumber(308, 1); //I've got to find the Master Emerald.
                selector.addNumber(709, 1); //I have some unfinished business to take care of.
                selector.addNumber(1123, 1); //Here I come; Eggman!
                selector.addNumber(1787, 1); //Okay! Let's go!
            }
            if (_currentCharacterCommentOnCharacterUnlock)
            {
                if (CurrentCharacter == Characters_Sonic)
                {
                    selector.addNumber(370, 2); //What's up; Knuckles?
                    selector.addNumber(579, 2);
                    //Hey there; Knuckles. Glad you finally made it! I thought you got lost or something.
                    selector.addNumber(604, 2); //What's up; Knuckles?
                    selector.addNumber(1148, 2); //There you are Knuckles! About time.
                    selector.addNumber(238, 2); //What's the smell? Smells like trash!
                }
                else if (CurrentCharacter == Characters_Tails)
                {
                    selector.addNumber(679, 3); //Hey Knuckles; what's up?
                }
            }
            if (_eggmanCommentOnCharacterUnlock)
            {
                selector.addNumber(1036, 1); //Kn- Knuckles!
            }
        }
        else if (itemId == 1)
        {
            if (_unlockedCharacterCommentOnCharacterUnlock)
            {
                selector.addNumber(206, 1); //Hey; hey; hey!
                selector.addNumber(242, 1); //Watch and learn!
                selector.addNumber(248, 3); //Time for some supersonic speed!
                selector.addNumber(349, 1); //Yo! Have you guys been good?
                selector.addNumber(374, 1); //You've had your fun. Now it's my turn!
                selector.addNumber(410, 1); //This could be fun!
                selector.addNumber(568, 1); //Just leave it to me!
            }
            if (_currentCharacterCommentOnCharacterUnlock)
            {
                if (CurrentCharacter == Characters_Amy)
                {
                    selector.addNumber(247, 1); //I wonder where Sonic went.
                    selector.addNumber(360, 1); //If only Sonic were here.
                    selector.addNumber(857, 1); //Oh; Sonic!
                    selector.addNumber(858, 1); //(dreamy sigh) My hero!
                    selector.addNumber(964, 1); //I wonder what Sonic is doing.
                    selector.addNumber(1491, 1); //Hey; Sonic!
                }
                else if (CurrentCharacter == Characters_Knuckles)
                {
                    selector.addNumber(1147, 1); //Hey Sonic!
                }
                else if (CurrentCharacter == Characters_Tails)
                {
                    selector.addNumber(417, 1); //Hey; Sonic! Long time no see; huh?
                    selector.addNumber(455, 1); //Sonic!
                    selector.addNumber(471, 1); //Come on; Sonic; we need to get busy!
                    selector.addNumber(525, 1); //Hey; Sonic!
                    selector.addNumber(760, 1); //There's Sonic!
                    selector.addNumber(1091, 1); //Hurry Sonic! What're we waiting for?
                    selector.addNumber(1408, 1); //Sonic!
                    selector.addNumber(1451, 1); //Sonic; wake up!
                    selector.addNumber(1512, 1); //Sonic?
                    selector.addNumber(235, 1); //I wonder where Sonic is.
                }
            }
            if (_eggmanCommentOnCharacterUnlock)
            {
                selector.addNumber(431, 1); //Ha ha ha ha! If it isn't Sonic!
                selector.addNumber(601, 1); //Well; if it isn't my pal; Sonic.
                selector.addNumber(1392, 1); //Ooh; I hate that Sonic!
                selector.addNumber(1713, 1); //Sonic! It's up to you now.
                selector.addNumber(1714, 1); //Be brave; blue hedgehog.
            }
        }
        else if (itemId == 2)
        {
            if (_unlockedCharacterCommentOnCharacterUnlock)
            {
                selector.addNumber(243, 1); //Time to jam!
                selector.addNumber(275, 1); //Boy; I'm hungry.
                selector.addNumber(352, 1); //How's it goin' guys?
                selector.addNumber(375, 1); //C'mon Tails; you can do it!
                selector.addNumber(528, 1); //Roger!
                selector.addNumber(617, 1); //All systems go; full speed ahead!
                selector.addNumber(753, 1); //The time has come at last.
                selector.addNumber(757, 1); //Ready Sonic? Here I come!
                selector.addNumber(1800, 1); //Here I come; Sonic!
            }
            if (_currentCharacterCommentOnCharacterUnlock)
            {
                if (CurrentCharacter == Characters_Sonic)
                {
                    selector.addNumber(205, 1); //Come on; Tails!
                    selector.addNumber(207, 1); //All right; Tails!
                    selector.addNumber(208, 1); //Hey; Tails!
                    selector.addNumber(414, 1); //Wha? Tails?!
                    selector.addNumber(526, 1); //Tails! I'm glad you're okay.
                    selector.addNumber(527, 1); //Ready to roll; champ? Let's go!
                }
            }
            if (_eggmanCommentOnCharacterUnlock)
            {
                selector.addNumber(219, 2); //You little fox!
            }
        }
    }
    else if (item.type == ItemChaosEmerald)
    {
        if (_currentCharacterCommentOnKeyItems)
        {
            if (CurrentCharacter == Characters_Knuckles)
            {
                selector.addNumber(478, 1); //That's a Chaos Emerald!
                selector.addNumber(1076, 1); //(gasp) That's... a Chaos Emerald!
                selector.addNumber(1142, 1); //Look! It's the Emerald!
            }
            else if (CurrentCharacter == Characters_Sonic)
            {
                selector.addNumber(425, 1); //Whoa! A Chaos Emerald!
                selector.addNumber(632, 1); //It's a Chaos Emerald! No way!
            }
            else if (CurrentCharacter == Characters_Tails)
            {
                selector.addNumber(427, 1); //This thing's got unlimited power; ya know.
                selector.addNumber(539, 1); //A Chaos Emerald!
                selector.addNumber(633, 1); //I was lucky to find one of the seven Chaos Emeralds.
                selector.addNumber(670, 1); //The Chaos Emerald!
                selector.addNumber(726, 1); //Wow! There's a Chaos Emerald!
                selector.addNumber(751, 1); //Oh yeah; the Chaos Emerald. Perfect!
                selector.addNumber(771, 1); //That's a Chaos Emerald!
                selector.addNumber(928, 1); //It's a Chaos Emerald!
            }
        }
        if (_eggmanCommentOnKeyItems)
        {
            selector.addNumber(438, 1); //I want all of the Chaos Emeralds.
            selector.addNumber(445, 1); //Come on Chaos; time to eat!
            selector.addNumber(450, 1); //His strength increases every time I feed him a Chaos Emerald!
            selector.addNumber(487, 1); //These are for you; my friend!
            selector.addNumber(652, 1); //Chaos could use a little snack!

            if (_itemRepository.GetUnlockStatus().CountChaosEmeralds() == 4)
            {
                selector.addNumber(485, 5); //Now I have four lovely Emeralds!
                selector.addNumber(697, 5); //Ha ha ha ha! Four! Count them; four Emeralds!
                selector.addNumber(1083, 5); //Hahahahaha! I've got four Emeralds now.
            }
            if (_itemRepository.GetUnlockStatus().CountChaosEmeralds() == 6)
            {
                selector.addNumber(570, 5); //Now I have six of the Chaos Emeralds!
                selector.addNumber(571, 5); //There's only one more left to find!
            }
        }
        if (_tikalCommentOnKeyItems)
        {
            if (_itemRepository.GetUnlockStatus().CountChaosEmeralds() == 7)
            {
                selector.addNumber(1355, 1); //So these are the seven Emeralds.
            }
        }
    }
    else if (item.type == ItemKey)
    {
        if (_eggmanCommentOnKeyItems)
        {
            selector.addNumber(1231, 1); //Ahh! There it is! Right there!!
        }
        if (_tikalCommentOnKeyItems)
        {
            selector.addNumber(1352, 1); //Wow...
            //Boat
            if (itemId == 81)
            {
                selector.addNumber(1632, 2); //Take the boat to get to the Egg Carrier.
                selector.addNumber(1868, 2);
                //The Egg Carrier has crashed and is floating somewhere in the ocean. Use this boat to get to it.
                selector.addNumber(1927, 2); //Take this boat to get to the Egg Carrier.
            }
            //Casino District Keys
            else if (itemId == 84 || itemId == 122)
            {
                selector.addNumber(1921, 2); //Something good may happen at the Casino area.
                selector.addNumber(1922, 2); //Why don't you try going to the Casino?
                selector.addNumber(1558, 2); //You can go to the Casino area at nighttime.
            }
            //Dynamite
            else if (itemId == 88)
            {
                selector.addNumber(1928, 2); //Why don't you try going to Angel Island?
                selector.addNumber(1955, 2); //You can break through the wall if you use dynamite.
            }
            //Employee Card
            else if (itemId == 86)
            {
                selector.addNumber(1561, 3); //You can get into a certain building using the Employee Card.
            }

            //Hotel Keys
            else if (itemId == 83)
            {
                selector.addNumber(1872, 3); //Get to the beach by going through the hotel.
            }

            //Ice Stone
            else if (itemId == 87)
            {
                selector.addNumber(1559, 2); //Use the Ice Stone in the Mystic Ruins.
                selector.addNumber(1641, 2); //Didn't you see a stone with an ice pattern on it?
            }
            //Jungle Cart
            else if (itemId == 89)
            {
                selector.addNumber(1634, 3); //The trolley car seems to be working. It leads to the jungle.
            }
            //Train
            else if (itemId == 80)
            {
                selector.addNumber(1572, 1); //A train will be arriving soon. Please stand back.
                selector.addNumber(1654, 1); //Passengers are requested to wait onboard the train.
                selector.addNumber(1656, 1); //A train will be arriving soon. Please stand back.
                selector.addNumber(1630, 1); //The train for Station Square has arrived.
                selector.addNumber(1869, 1); //Go to the station to catch the train.
                selector.addNumber(1918, 1); //The train seems to be moving now.
            }

            //Wind Stone
            else if (itemId == 120)
            {
                selector.addNumber(1639, 3);
                //If you have the Stone of Wind; gusts of strong wind are known to blow in the caves.
            }
        }
        if (_currentCharacterCommentOnKeyItems)
        {
            if (CurrentCharacter == Characters_Amy)
            {
                selector.addNumber(510, 1); //Let's go!
                selector.addNumber(995, 1); //I'm so happy!
                selector.addNumber(1731, 1); //Alright!
                selector.addNumber(1732, 1); //Yay!
                selector.addNumber(1733, 1); //Alright!

                //Boat
                if (itemId == 81)
                {
                    selector.addNumber(291, 3); //It's nice to have an ocean nearby.
                }
                //Hotel Keys
                else if (itemId == 83)
                {
                    selector.addNumber(297, 3); //I'd love to vacation here!
                }

                //Twinkle Park Ticket
                else if (itemId == 85)
                {
                    selector.addNumber(303, 2); //I'm getting excited!
                    selector.addNumber(509, 2); //Look here! It says; 'Cute couples get in free'!
                    selector.addNumber(875, 2); //Look! It says cute couples can get in free!
                    selector.addNumber(876, 2); //What are we waiting for?
                }
            }
            else if (CurrentCharacter == Characters_Gamma)
            {
                //Dynamite
                if (itemId == 88)
                {
                    selector.addNumber(314, 2); //Arriving at Angel Island.
                }
                //Train
                else if (itemId == 80)
                {
                    selector.addNumber(285, 5); //Train to Mystic Ruins confirmed.
                }
                //Twinkle Park Ticket
                else if (itemId == 85)
                {
                    selector.addNumber(305, 3); //Bumper car area confirmed.
                }
            }
            else if (CurrentCharacter == Characters_Big)
            {
                selector.addNumber(1346, 1); //Yes!
                selector.addNumber(1383, 1); //Hurray!
                selector.addNumber(1386, 1); //Oh. Okay! Thanks.
                selector.addNumber(1389, 1); //Hey; maybe we could use this.
                selector.addNumber(1745, 1); //Wow; it's big!
                selector.addNumber(1751, 1); //Not too bad!
                selector.addNumber(1760, 1); //Super!
                selector.addNumber(1765, 1); //What's this?
                selector.addNumber(1766, 1); //Allright!

                //Jungle Cart
                if (itemId == 89)
                {
                    selector.addNumber(319, 3); //Maybe I'll go home.
                }

                //Twinkle Park Ticket
                else if (itemId == 85)
                {
                    selector.addNumber(304, 5); //Twinkle Park?
                }
            }
            else if (CurrentCharacter == Characters_Knuckles)
            {
                selector.addNumber(1112, 1); //This is beginning to blow my mind.
                selector.addNumber(1788, 1); //Yeeah!
                selector.addNumber(1790, 1); //Found it!
                selector.addNumber(1794, 1); //Heh. Good enough.

                //Dynamite
                if (itemId == 88)
                {
                    selector.addNumber(313, 3); //I've got to get this island airborne again.
                }
                //Hotel Keys
                else if (itemId == 83)
                {
                    selector.addNumber(296, 3); //Great; a resort hotel.
                }
            }
            else if (CurrentCharacter == Characters_Sonic)
            {
                selector.addNumber(213, 1); //Horray!
                selector.addNumber(214, 1); //I got it!
                selector.addNumber(315, 1); //Now this is more like it!
                selector.addNumber(372, 1); //Not bad; not bad at all!
                selector.addNumber(400, 1); //Aw; yeah!
                selector.addNumber(401, 1); //This is happenin'!
                selector.addNumber(406, 1); //Aw; yeah!
                selector.addNumber(587, 1); //Wow; what's this?
                selector.addNumber(1835, 1); //Hurray!
                selector.addNumber(1837, 1); //Let's get 'em!
                selector.addNumber(1838, 1); //Yes!
                selector.addNumber(1839, 1); //Woohoo!
                selector.addNumber(1840, 1); //Yes.
                selector.addNumber(1842, 1); //*whistles* Sweet!
                selector.addNumber(1844, 1); //Yeah; not bad!
                selector.addNumber(1849, 1); //Yes!
                selector.addNumber(1852, 1); //Yeah!
                selector.addNumber(1853, 1); //Oh-kay!

                //Dynamite
                if (itemId == 88)
                {
                    selector.addNumber(312, 2); //So; this is Angel Island!
                }
                //Twinkle Park Ticket
                else if (itemId == 85)
                {
                    selector.addNumber(300, 3); //I'm not too fond of places like this.
                }
                //Wind Stone
                else if (itemId == 120)
                {
                    selector.addNumber(231, 4); //I can hear the wind in the distance.
                }
            }
            else if (CurrentCharacter == Characters_Tails)
            {
                selector.addNumber(424, 1); //Tada!
                selector.addNumber(1802, 1); //Allright!
                selector.addNumber(1803, 1); //Yeeaah!
                selector.addNumber(1812, 1); //Cool.
                //Hotel Keys
                if (itemId == 83)
                {
                    selector.addNumber(295, 2); //This hotel is nice!
                }
                //Train
                else if (itemId == 80)
                {
                    selector.addNumber(289, 5); //Trains are cool; too!
                }
            }
        }
    }
    if (!selector.isEmpty())
    {
        const int voice = selector.getRandomNumber();
        PlayVoice(voice);
        if (_showCommentsSubtitles)
        {
            auto it = _commentMap.find(voice);
            if (it != _commentMap.end() && GameMode != GameModes_Menu)
            {
                subtitleBuffer[0] = it->second.c_str();
                DisplayHintText(subtitleBuffer, 60 + 5 * it->second.length());
            }
        }
    }
}


void Randomizer::ResetItems()
{
    _itemRepository.ResetItems();
    const UnlockStatus unlockStatus = _itemRepository.GetUnlockStatus();
    _characterManager.UpdateUnlockStatus(unlockStatus);
    _displayManager.UpdateUnlockStatus(unlockStatus);
    _worldStateManager.UpdateUnlockStatus(unlockStatus);
}

void Randomizer::SetMissionMode(const int missionModeEnabled)
{
    _options.missionModeEnabled = missionModeEnabled;
    _worldStateManager.UpdateOptions(_options);
    _displayManager.UpdateOptions(_options);
}

void Randomizer::SetAutoStartMissions(const int autoStartMissions)
{
    if (autoStartMissions)
        _saveFileManager.StartAllMissions();
}

void Randomizer::OnCheckVersion(int serverVersion)
{
    const int serverMajor = serverVersion / 100;
    const int serverMinor = (serverVersion / 10) % 10;
    const int serverPatch = serverVersion % 10;

    const std::string modVer = std::to_string(SADX_AP_VERSION_MAJOR)
        + "." + std::to_string(SADX_AP_VERSION_MINOR)
        + "." + std::to_string(SADX_AP_VERSION_PATCH);
    const std::string serverVer = std::to_string(serverMajor)
        + "." + std::to_string(serverMinor)
        + "." + std::to_string(serverPatch);
    if (serverMajor != SADX_AP_VERSION_MAJOR || serverMinor != SADX_AP_VERSION_MINOR)
    {
        std::string errorMessage = "Error: Major version mismatch!\n\nServer: v" + serverVer + "\nMod: v" + modVer;
        MessageBox(WindowHandle, std::wstring(errorMessage.begin(), errorMessage.end()).c_str(),
                   L"SADX Archipelago Error: Version mismatch", MB_OK | MB_ICONERROR);
        exit(0);
    }
    if (serverPatch != SADX_AP_VERSION_PATCH)
    {
        _displayManager.QueueItemMessage("Warning: version mismatch! Server: v" + serverVer + " Mod: v" + modVer);
    }
}

void Randomizer::SetStartingCharacter(const int startingCharacterIndex)
{
    _characterManager.SetStartingCharacter(startingCharacterIndex);
}

void Randomizer::UpdateLevelEntrances(LevelEntrances levelEntrances)
{
    _worldStateManager.UpdateLevelEntrances(levelEntrances);

    for (const auto& location : _locationRepository.GetLocations())
    {
        if (location.second.type == LocationLevel && location.second.checked && location.second.level >=
            LevelIDs_EmeraldCoast && location.second.level <= LevelIDs_HotShelter)
            _displayManager.UpdateVisitedLevels(_worldStateManager.GetVisitedLevels(location.second.level));
    }
}

void Randomizer::UpdateMissionBlacklist(const std::vector<int>& missionBlacklist)
{
    _options.missionBlacklist = missionBlacklist;
    _worldStateManager.UpdateOptions(_options);
    _displayManager.UpdateOptions(_options);
    if (_options.goalRequiresMissions)
    {
        const MissionStatus missionStatus = _locationRepository.GetMissionStatus(_options);
        _displayManager.UpdateMissionStatus(missionStatus);
    }
    _worldStateManager.MarkBlacklistedMissionsAsCompleted(_options.missionBlacklist);
}

void Randomizer::UpdateProgressionItemsList(const std::vector<int>& progressionItemsList)
{
    _options.progressionItems = progressionItemsList;
    _worldStateManager.UpdateOptions(_options);
    _displayManager.UpdateOptions(_options);
}

void Randomizer::SetEntranceRandomizer(const bool enableEntranceRandomizer)
{
    _options.entranceRandomizer = enableEntranceRandomizer;
}

void Randomizer::SetCharacterVoiceReactions(const bool eggmanCommentOnCharacterUnlock,
                                            const bool currentCharacterCommentOnCharacterUnlock,
                                            const bool unlockedCharacterCommentOnCharacterUnlock,
                                            const bool eggmanCommentOnKeyItems, const bool tikalCommentOnKeyItems,
                                            const bool currentCharacterCommentOnKeyItems,
                                            const bool showCommentsSubtitles)
{
    _eggmanCommentOnCharacterUnlock = eggmanCommentOnCharacterUnlock;
    _currentCharacterCommentOnCharacterUnlock = currentCharacterCommentOnCharacterUnlock;
    _unlockedCharacterCommentOnCharacterUnlock = unlockedCharacterCommentOnCharacterUnlock;
    _eggmanCommentOnKeyItems = eggmanCommentOnKeyItems;
    _tikalCommentOnKeyItems = tikalCommentOnKeyItems;
    _currentCharacterCommentOnKeyItems = currentCharacterCommentOnKeyItems;
    _showCommentsSubtitles = showCommentsSubtitles;
}

void Randomizer::SetReverseControlTrapDuration(const int reverseControlTrapDuration)
{
    _characterManager.SetReverseControlTrapDuration(reverseControlTrapDuration);
}

void Randomizer::SetTrapsOnAdventureFields(bool trapsOnAdventureFields)
{
    _characterManager.SetTrapsOnAdventureFields(trapsOnAdventureFields);
}

void Randomizer::SetTrapsOnBossFights(bool trapsOnBossFights)
{
    _characterManager.SetTrapsOnBossFights(trapsOnBossFights);
}

void Randomizer::SetTrapsOnPerfectChaosFight(bool trapsOnPerfectChaosFight)
{
    _characterManager.SetTrapsOnPerfectChaosFight(trapsOnPerfectChaosFight);
}

void Randomizer::SetSuperSonicModRunning(const bool isModRunning)
{
    _superSonicModRunning = isModRunning;
}

int Clamp(const int value, const int min, const int max)
{
    if (value < min) return min;
    if (value > max) return max;
    return value;
}

void Randomizer::SetSendDeathLinkChance(const int sendDeathLinkChance)
{
    _sendDeathLinkChance = Clamp(sendDeathLinkChance, 1, 100);
}

void Randomizer::SetReceiveDeathLinkChance(const int receiveDeathLinkChance)
{
    _receiveDeathLinkChance = Clamp(receiveDeathLinkChance, 1, 100);
}


bool Randomizer::AreLastStoryRequirementsCompleted() const
{
    bool levelsCompleted = true;
    bool emblemsCompleted = true;
    bool chaosEmeraldsCompleted = true;
    bool missionsCompleted = true;
    bool bossesCompleted = true;
    bool chaoRacesCompleted = true;

    if (_options.goalRequiresLevels)
        levelsCompleted = _locationRepository.GetLevelStatus(_options).levelsCompleted >= _options.levelGoal;

    if (_options.goalRequiresEmblems)
        emblemsCompleted = _itemRepository.GetEmblemCount() >= _options.emblemGoal;

    if (_options.goalRequiresMissions)
        missionsCompleted = _locationRepository.GetMissionStatus(_options).missionsCompleted >= _options.missionGoal;

    if (_options.goalRequiresChaosEmeralds)
        chaosEmeraldsCompleted = _itemRepository.GetUnlockStatus().GotAllChaosEmeralds();

    if (_options.goalRequiresBosses)
        bossesCompleted = _locationRepository.GetBossesStatus(_options).bossesCompleted >= _options.bossesGoal;

    if (_options.goalRequiresChaoRaces)
        chaoRacesCompleted = _locationRepository.GetChaoStatus().racesCompleted >= _locationRepository.GetChaoStatus().
            racesTotal;

    return levelsCompleted && emblemsCompleted && chaosEmeraldsCompleted && missionsCompleted && bossesCompleted &&
        chaoRacesCompleted;
}


void Randomizer::OnCharacterLoaded() const
{
    _characterManager.RemoveStatusEffects();
    for (const auto& item : _itemRepository.GetItems())
    {
        if (item.second.type != ItemUpgrade)
            continue;

        if (item.second.obtained)
            _characterManager.GiveUpgrade(item.second.upgrade);
        else
            _characterManager.RemoveUpgrade(item.second.upgrade);
    }
    if (_options.entranceRandomizer && CurrentLevel >= LevelIDs_EmeraldCoast && CurrentLevel <= LevelIDs_HotShelter)
        _displayManager.UpdateVisitedLevels(_worldStateManager.GetVisitedLevels(CurrentLevel));
}


void Randomizer::OnCharacterSelectScreenLoaded() const
{
    for (const auto& item : _itemRepository.GetItems())
    {
        if (item.second.type == ItemEmblem)
        {
            if (AreLastStoryRequirementsCompleted())
                _worldStateManager.UnlockSuperSonic();
        }

        if (item.second.type == ItemCharacter && item.second.obtained)
            _worldStateManager.SetEventFlags(item.second.eventFlags);
    }
}


std::map<int, LocationData> Randomizer::GetCheckData() const
{
    return _locationRepository.GetLocations();
}

std::vector<CapsuleLocationData> Randomizer::GetCapsules()
{
    return _locationRepository.GetCapsuleLocations();
}

std::vector<EnemyLocationData> Randomizer::GetEnemies()
{
    return _locationRepository.GetEnemyLocations();
}


bool CheckDeathLinkChance(const int chance)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 100);

    return dis(gen) <= chance;
}

void Randomizer::ProcessDeath(const std::string& deathCause)
{
    const double timePassed = (std::clock() - _deathLinkCooldownTimer) / static_cast<double>(CLOCKS_PER_SEC);
    if (_deathLinkCooldownTimer < 0 || timePassed > _deathLinkCooldown)
    {
        if (!CheckDeathLinkChance(_receiveDeathLinkChance))
        {
            _displayManager.QueueItemMessage("You survived a Death Link!");
            return;
        }

        //Processing a death won't restart the cooldown timer
        _pendingDeathCause = deathCause;
        _deathPending = true;
    }
}

void Randomizer::OnPlayingFrame()
{
    if (!_options.deathLinkActive)
        return;
    if (!_deathPending)
        return;
    if (GameMode != GameModes_Mission)
        return;
    if (GameState != MD_GAME_MAIN)
        return;
    if (!IsControllerEnabled(0))
        return;


    const double timePassed = (std::clock() - _deathLinkCooldownTimer) / static_cast<double>(CLOCKS_PER_SEC);

    if (_deathLinkCooldownTimer < 0 || timePassed > _deathLinkCooldown)
    {
        _deathLinkCooldownTimer = std::clock();
        _characterManager.KillPlayer();
        _displayManager.QueueItemMessage(_pendingDeathCause);
        _pendingDeathCause.clear();
        _deathPending = false;
    }
}

void Randomizer::OnSync()
{
    if (!_options.ringLinkActive)
        return;
    const RingDifference ringDifference = _characterManager.GetRingDifference();

    _archipelagoMessenger.SendRingUpdate(ringDifference.ringDifference);
    _archipelagoMessenger.SendHardRingUpdate(ringDifference.hardRingDifference);
}

void Randomizer::OnDeath()
{
    if (!_options.deathLinkActive)
        return;

    const double timePassed = (std::clock() - _deathLinkCooldownTimer) / static_cast<double>(CLOCKS_PER_SEC);

    if (_deathLinkCooldownTimer < 0 || timePassed > _deathLinkCooldown)
    {
        _deathLinkCooldownTimer = std::clock();

        if (!CheckDeathLinkChance(_sendDeathLinkChance))
        {
            _displayManager.QueueItemMessage("Death Link not sent!");
            return;
        }
        _archipelagoMessenger.SendDeath(_options.playerName);
        _displayManager.QueueItemMessage("Death Sent");
    }
}

void Randomizer::ProcessRings(const Sint16 amount)
{
    _characterManager.ProcessRings(amount);
}

void Randomizer::ProcessTrapLink(std::string itemName, std::string message)
{
    _displayManager.QueueItemMessage(message);

    FillerType filler = _itemRepository.GetFillerFromName(itemName);

    if (filler != NoFiller)
        _characterManager.GiveFillerItem(filler, false);
}

void Randomizer::OnConnected(std::string playerName)
{
    _options.playerName = playerName;
    _worldStateManager.UpdateOptions(_options);
    _displayManager.UpdateOptions(_options);
    _displayManager.QueueItemMessage("Connected to Archipelago");
}

void Randomizer::OnGameCompleted()
{
    _displayManager.QueueItemMessage("Victory!");
    _archipelagoMessenger.GameCompleted();
}

void Randomizer::ShowStatusInformation(std::string information)
{
    _displayManager.ShowStatusInformation(information);
}

void Randomizer::QueueNewItemMessage(std::string information)
{
    _displayManager.QueueItemMessage(information);
    _worldStateManager.UpdateOptions(_options);
    _displayManager.UpdateOptions(_options);
}

void Randomizer::QueueNewChatMessage(std::string information)
{
    _displayManager.QueueChatMessage(information);
    _worldStateManager.UpdateOptions(_options);
    _displayManager.UpdateOptions(_options);
}

void Randomizer::OnGoalRequiresLevelsSet(const bool goalRequiresLevels)
{
    _options.goalRequiresLevels = goalRequiresLevels;
    _worldStateManager.UpdateOptions(_options);
    _displayManager.UpdateOptions(_options);

    const LevelStatus levelStatus = _locationRepository.GetLevelStatus(_options);
    _displayManager.UpdateLevelStatus(levelStatus);

    if (!_options.goalRequiresChaosEmeralds)
        SetEventFlag(static_cast<EventFlags>(FLAG_SUPERSONIC_COMPLETE));
}

void Randomizer::OnGoalRequiresChaosEmeraldsSet(const bool goalRequiresChaosEmeralds)
{
    _options.goalRequiresChaosEmeralds = goalRequiresChaosEmeralds;
    _worldStateManager.UpdateOptions(_options);
    _displayManager.UpdateOptions(_options);
}

void Randomizer::OnGoalRequiresEmblems(const bool goalRequiresEmblems)
{
    _options.goalRequiresEmblems = goalRequiresEmblems;
    _worldStateManager.UpdateOptions(_options);
    _displayManager.UpdateOptions(_options);

    if (!_options.goalRequiresChaosEmeralds)
        SetEventFlag(static_cast<EventFlags>(FLAG_SUPERSONIC_COMPLETE));
}

void Randomizer::OnGoalRequiresMissionsSet(const bool goalRequiresMissions)
{
    _options.goalRequiresMissions = goalRequiresMissions;
    _worldStateManager.UpdateOptions(_options);
    _displayManager.UpdateOptions(_options);
    const MissionStatus missionStatus = _locationRepository.GetMissionStatus(_options);
    _displayManager.UpdateMissionStatus(missionStatus);

    if (!_options.goalRequiresChaosEmeralds)
        SetEventFlag(static_cast<EventFlags>(FLAG_SUPERSONIC_COMPLETE));
}

void Randomizer::OnGoalRequiresBossesSet(const bool goalRequiresBosses)
{
    _options.goalRequiresBosses = goalRequiresBosses;
    _worldStateManager.UpdateOptions(_options);
    _displayManager.UpdateOptions(_options);

    const BossesStatus bossesStatus = _locationRepository.GetBossesStatus(_options);
    _displayManager.UpdateBossesStatus(bossesStatus);

    if (!_options.goalRequiresChaosEmeralds)
        SetEventFlag(static_cast<EventFlags>(FLAG_SUPERSONIC_COMPLETE));
}

void Randomizer::OnGoalRequiresChaoRacesSet(const bool goalRequiresChaoRaces)
{
    _options.goalRequiresChaoRaces = goalRequiresChaoRaces;
    _worldStateManager.UpdateOptions(_options);
    _displayManager.UpdateOptions(_options);

    const ChaoStatus chaoStatus = _locationRepository.GetChaoStatus();
    _displayManager.UpdateChaoStatus(chaoStatus);

    if (!_options.goalRequiresChaosEmeralds)
        SetEventFlag(static_cast<EventFlags>(FLAG_SUPERSONIC_COMPLETE));
}

void Randomizer::OnSetLogicLevel(int logicLevel)
{
    if (logicLevel > 1)
        _options.expertMode = true;
    else
        _options.expertMode = false;
    _worldStateManager.UpdateOptions(_options);
    _displayManager.UpdateOptions(_options);
}


void Randomizer::OnEmblemGoalSet(const int emblemGoal)
{
    _options.emblemGoal = max(1, emblemGoal);
    _worldStateManager.UpdateOptions(_options);
    _displayManager.UpdateOptions(_options);
}

void Randomizer::OnLevelGoalSet(const int levelGoal)
{
    _options.levelGoal = max(1, levelGoal);
    _worldStateManager.UpdateOptions(_options);
    _displayManager.UpdateOptions(_options);
}

void Randomizer::OnMissionGoalSet(const int missionGoal)
{
    _options.missionGoal = max(1, missionGoal);
    _worldStateManager.UpdateOptions(_options);
    _displayManager.UpdateOptions(_options);
}

void Randomizer::OnBossesGoalSet(const int bossesGoal)
{
    _options.bossesGoal = max(1, bossesGoal);
    _worldStateManager.UpdateOptions(_options);
    _displayManager.UpdateOptions(_options);
}


void Randomizer::OnEnemySanitySet(const bool enemySanity)
{
    _options.enemySanity = enemySanity;
    _worldStateManager.UpdateOptions(_options);
    _displayManager.UpdateOptions(_options);
}

void Randomizer::OnFishSanitySet(const bool fishSanity)
{
    _options.fishSanity = fishSanity;
    _worldStateManager.UpdateOptions(_options);
    _displayManager.UpdateOptions(_options);
}

void Randomizer::OnLazyFishingSet(const bool lazyFishing)
{
    _options.lazyFishing = lazyFishing;
    _worldStateManager.UpdateOptions(_options);
    _displayManager.UpdateOptions(_options);
    _characterManager.UpdateOptions(_options);
}

void Randomizer::SetCharacterEnemySanity(const Characters character, const bool characterEnemySanity)
{
    _options.SetCharacterEnemySanity(character, characterEnemySanity);
    _worldStateManager.UpdateOptions(_options);
    _displayManager.UpdateOptions(_options);
}


void Randomizer::OnCapsuleSanitySet(const bool capsuleSanity)
{
    _options.capsuleSanity = capsuleSanity;
    _worldStateManager.UpdateOptions(_options);
    _displayManager.UpdateOptions(_options);
}

void Randomizer::OnPinballCapsulesSet(const bool includePinballCapsules)
{
    _options.includePinballCapsules = includePinballCapsules;
    _worldStateManager.UpdateOptions(_options);
    _displayManager.UpdateOptions(_options);
}

void Randomizer::SetCharacterCapsuleSanity(const Characters character, const bool characterCapsuleSanity)
{
    _options.SetCharacterCapsuleSanity(character, characterCapsuleSanity);
    _worldStateManager.UpdateOptions(_options);
    _displayManager.UpdateOptions(_options);
}


void Randomizer::OnLifeCapsuleSanitySet(const bool lifeCapsuleSanity)
{
    _options.lifeCapsuleSanity = lifeCapsuleSanity;
    _worldStateManager.UpdateOptions(_options);
    _displayManager.UpdateOptions(_options);
}

void Randomizer::OnShieldCapsuleSanitySet(const bool shieldCapsuleSanity)
{
    _options.shieldCapsuleSanity = shieldCapsuleSanity;
    _worldStateManager.UpdateOptions(_options);
    _displayManager.UpdateOptions(_options);
}

void Randomizer::OnPowerUpCapsuleSanitySet(const bool powerUpCapsuleSanity)
{
    _options.powerUpCapsuleSanity = powerUpCapsuleSanity;
    _worldStateManager.UpdateOptions(_options);
    _displayManager.UpdateOptions(_options);
}

void Randomizer::OnRingCapsuleSanitySet(const bool ringCapsuleSanity)
{
    _options.ringCapsuleSanity = ringCapsuleSanity;
    _worldStateManager.UpdateOptions(_options);
    _displayManager.UpdateOptions(_options);
}


void Randomizer::SetCharacterStatingArea(const Characters character, const StartingArea startingArea)
{
    _options.SetCharacterStatingArea(character, startingArea);
    _worldStateManager.UpdateOptions(_options);
    _worldStateManager.UpdateOptions(_options);
}

void Randomizer::SetPlayableCharacter(const Characters character, const bool playable)
{
    _options.SetPlayableCharacter(character, playable);
    _worldStateManager.UpdateOptions(_options);
    _displayManager.UpdateOptions(_options);
}

void Randomizer::SetActionStageMissions(const Characters characters, const int missions)
{
    _options.SetActionStageMissions(characters, missions);
    _worldStateManager.UpdateOptions(_options);
    _displayManager.UpdateOptions(_options);
    if (_options.goalRequiresLevels)
    {
        const LevelStatus levelStatus = _locationRepository.GetLevelStatus(_options);
        _displayManager.UpdateLevelStatus(levelStatus);
    }
}


void Randomizer::SetDeathLink(const bool deathLinkActive)
{
    _options.deathLinkActive = deathLinkActive;
    _archipelagoMessenger.UpdateTags(_options);
}

void Randomizer::SetRingLink(const bool ringLinkActive)
{
    _options.ringLinkActive = ringLinkActive;
    _archipelagoMessenger.UpdateTags(_options);
}

void Randomizer::SetCasinopolisRingLink(const bool casinopolisRingLink)
{
    _options.casinopolisRingLink = casinopolisRingLink;
}

void Randomizer::SetHardRingLink(const bool hardRingLinkActive)
{
    _options.hardRingLinkActive = hardRingLinkActive;
    _archipelagoMessenger.UpdateTags(_options);
}

void Randomizer::SetTrapLink(const bool trapLinkActive)
{
    _options.trapLinkActive = trapLinkActive;
    _archipelagoMessenger.UpdateTags(_options);
}

void Randomizer::SetRingLoss(const RingLoss ringLoss)
{
    _options.ringLoss = ringLoss;
    _worldStateManager.UpdateOptions(_options);
    _characterManager.UpdateOptions(_options);
}

void Randomizer::SetTwinkleCircuitCheck(int twinkleCircuitCheck)
{
    _options.twinkleCircuitCheck = twinkleCircuitCheck;
    _worldStateManager.UpdateOptions(_options);
    _characterManager.UpdateOptions(_options);
}

void Randomizer::SetMultipleTwinkleCircuitChecks(int multipleTwinkleCircuitChecks)
{
    _options.multipleTwinkleCircuitChecks = multipleTwinkleCircuitChecks;
    _worldStateManager.UpdateOptions(_options);
    _characterManager.UpdateOptions(_options);
}

void Randomizer::SetSkyChaseChecks(const bool skyChaseChecks)
{
    _options.skyChaseChecks = skyChaseChecks;
    _worldStateManager.UpdateOptions(_options);
    _characterManager.UpdateOptions(_options);
}

void Randomizer::SetSkyChaseChecksHard(const bool skyChaseChecksHard)
{
    _options.skyChaseChecksHard = skyChaseChecksHard;
    _worldStateManager.UpdateOptions(_options);
    _characterManager.UpdateOptions(_options);
}

void Randomizer::SetBossChecks(const bool bossChecks)
{
    _options.bossChecks = bossChecks;
    _worldStateManager.UpdateOptions(_options);
    _characterManager.UpdateOptions(_options);
}

void Randomizer::SetUnifyChaos4(const bool unifyChaos4)
{
    _options.unifyChaos4 = unifyChaos4;
    _worldStateManager.UpdateOptions(_options);
    _displayManager.UpdateOptions(_options);

    const BossesStatus bossesStatus = _locationRepository.GetBossesStatus(_options);
    _displayManager.UpdateBossesStatus(bossesStatus);
}

void Randomizer::SetUnifyChaos6(const bool unifyChaos6)
{
    _options.unifyChaos6 = unifyChaos6;
    _worldStateManager.UpdateOptions(_options);
    _displayManager.UpdateOptions(_options);

    const BossesStatus bossesStatus = _locationRepository.GetBossesStatus(_options);
    _displayManager.UpdateBossesStatus(bossesStatus);
}

void Randomizer::SetUnifyEggHornet(const bool unifyEggHornet)
{
    _options.unifyEggHornet = unifyEggHornet;
    _worldStateManager.UpdateOptions(_options);
    _displayManager.UpdateOptions(_options);

    const BossesStatus bossesStatus = _locationRepository.GetBossesStatus(_options);
    _displayManager.UpdateBossesStatus(bossesStatus);
}

Options Randomizer::GetOptions() const
{
    return _options;
}
