#include "ReactionManager.h"

const char* subtitleBuffer[] = {NULL, NULL};


ReactionManager::ReactionManager(Options& options): _options(options)
{
}

void ReactionManager::UpdateUnlockStatus(UnlockStatus newUnlockStatus)
{
    this->_unlockStatus = newUnlockStatus;
}

void ReactionManager::PlayRandomVoiceForItem(const ItemData& item, const int64_t itemId) const
{
    WeightedRandomSelector selector;
    if (item.type == ItemCharacter)
    {
        if (_options.currentCharacterCommentOnCharacterUnlock)
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
            if (_options.unlockedCharacterCommentOnCharacterUnlock)
            {
                selector.addNumber(277, 1); //I wanna go shopping!
                selector.addNumber(324, 1); //I'm going to do my best; Sonic.
                selector.addNumber(1730, 1); //It's my turn now!
            }
            if (_options.currentCharacterCommentOnCharacterUnlock)
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
            if (_options.unlockedCharacterCommentOnCharacterUnlock)
            {
                selector.addNumber(367, 1); //I wanna go fishing!
                selector.addNumber(566, 1); //I must save Froggy!
                selector.addNumber(1335, 1); //Froggy?
                selector.addNumber(1342, 1); //Mm; smells like Froggy's around somewhere...
                selector.addNumber(1744, 1); //Hold on Froggy! I'm coming!
                selector.addNumber(1876, 1); //Okay! One more time!
                selector.addNumber(2012, 1); //Froggy? Where are you?
            }
            if (_options.currentCharacterCommentOnCharacterUnlock)
            {
                if (CurrentCharacter == Characters_Tails)
                {
                    selector.addNumber(2024, 3); //Hope you find Froggy soon!
                }
            }
        }
        else if (itemId == 5)
        {
            if (_options.unlockedCharacterCommentOnCharacterUnlock)
            {
                selector.addNumber(394, 1); //Combat system activated.
                selector.addNumber(543, 1); //What is your wish; master Robotnik?
                selector.addNumber(775, 1); //What is your wish; Master?
                selector.addNumber(932, 1); //At your service; sir.
                selector.addNumber(1276, 1); //How can I serve you; Dr. Robotnik?
                selector.addNumber(1767, 1); //Preperation complete.
            }
            if (_options.currentCharacterCommentOnCharacterUnlock)
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
            if (_options.eggmanCommentOnCharacterUnlock)
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
            if (_options.unlockedCharacterCommentOnCharacterUnlock)
            {
                selector.addNumber(261, 1); //Okay now; where's the treasure?
                selector.addNumber(308, 1); //I've got to find the Master Emerald.
                selector.addNumber(709, 1); //I have some unfinished business to take care of.
                selector.addNumber(1123, 1); //Here I come; Eggman!
                selector.addNumber(1787, 1); //Okay! Let's go!
            }
            if (_options.currentCharacterCommentOnCharacterUnlock)
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
            if (_options.eggmanCommentOnCharacterUnlock)
            {
                selector.addNumber(1036, 1); //Kn- Knuckles!
            }
        }
        else if (itemId == 1)
        {
            if (_options.unlockedCharacterCommentOnCharacterUnlock)
            {
                selector.addNumber(206, 1); //Hey; hey; hey!
                selector.addNumber(242, 1); //Watch and learn!
                selector.addNumber(248, 3); //Time for some supersonic speed!
                selector.addNumber(349, 1); //Yo! Have you guys been good?
                selector.addNumber(374, 1); //You've had your fun. Now it's my turn!
                selector.addNumber(410, 1); //This could be fun!
                selector.addNumber(568, 1); //Just leave it to me!
            }
            if (_options.currentCharacterCommentOnCharacterUnlock)
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
            if (_options.eggmanCommentOnCharacterUnlock)
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
            if (_options.unlockedCharacterCommentOnCharacterUnlock)
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
            if (_options.currentCharacterCommentOnCharacterUnlock)
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
            if (_options.eggmanCommentOnCharacterUnlock)
            {
                selector.addNumber(219, 2); //You little fox!
            }
        }
    }
    else if (item.type == ItemChaosEmerald)
    {
        if (_options.currentCharacterCommentOnKeyItems)
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
        if (_options.eggmanCommentOnKeyItems)
        {
            selector.addNumber(438, 1); //I want all of the Chaos Emeralds.
            selector.addNumber(445, 1); //Come on Chaos; time to eat!
            selector.addNumber(450, 1); //His strength increases every time I feed him a Chaos Emerald!
            selector.addNumber(487, 1); //These are for you; my friend!
            selector.addNumber(652, 1); //Chaos could use a little snack!

            if (_unlockStatus.CountChaosEmeralds() == 4)
            {
                selector.addNumber(485, 5); //Now I have four lovely Emeralds!
                selector.addNumber(697, 5); //Ha ha ha ha! Four! Count them; four Emeralds!
                selector.addNumber(1083, 5); //Hahahahaha! I've got four Emeralds now.
            }
            if (_unlockStatus.CountChaosEmeralds() == 6)
            {
                selector.addNumber(570, 5); //Now I have six of the Chaos Emeralds!
                selector.addNumber(571, 5); //There's only one more left to find!
            }
        }
        if (_options.tikalCommentOnKeyItems)
        {
            if (_unlockStatus.CountChaosEmeralds() == 7)
            {
                selector.addNumber(1355, 1); //So these are the seven Emeralds.
            }
        }
    }
    else if (item.type == ItemKey)
    {
        if (_options.eggmanCommentOnKeyItems)
        {
            selector.addNumber(1231, 1); //Ahh! There it is! Right there!!
        }
        if (_options.tikalCommentOnKeyItems)
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
        if (_options.currentCharacterCommentOnKeyItems)
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
        if (_options.showCommentsSubtitles)
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


void ReactionManager::PlayRandomTrapVoice(const FillerType filler)
{
    WeightedRandomSelector selector;
    selector.addNumber(174, 1); //Get a load of this!
    if (_options.eggmanCommentOnTrap)
    {
        selector.addNumber(171, 2); //All systems; full power!
        selector.addNumber(173, 3); //Ah-ha!
        selector.addNumber(178, 1); //Ho ho! It's no use. Give up!
        selector.addNumber(221, 1); //Wha ha ha ha ha ha ha ha ha!
        selector.addNumber(413, 1); //Ha ha ha ha ha ha ha ha ha ha ha!
        selector.addNumber(443, 1); //Aha!
        selector.addNumber(449, 1); //Ha ha ha ha ha!		
        selector.addNumber(463, 5); //Oh no; you don't!
        selector.addNumber(465, 1); //Ha ha ha ha ha ha ha ha ha!
        selector.addNumber(474, 1); //Ha ha ha ha ha ha!
        selector.addNumber(562, 1); //Ha ha ha ha ha!
        selector.addNumber(569, 1); //Ha ha ha ha ha!
        selector.addNumber(650, 3); //Gotcha!
        selector.addNumber(924, 1); //You can't get away this easily!
        selector.addNumber(926, 1); //Too late; buddy!
        selector.addNumber(1059, 1); //Ah ha hahahaha!
        selector.addNumber(1072, 1); //Mwuahahahahahahahahaha!
        selector.addNumber(1376, 1); //Ha ha ha ha ha ha!
        selector.addNumber(1518, 10); //Get a load of this!
        selector.addNumber(1522, 3); //Hahahahaha! I bet you wern't expecting this!
        selector.addNumber(1525, 1); //Haha hahahahaha!
        selector.addNumber(1542, 1); //I guess you wern't expecting that; were you?
        selector.addNumber(1680, 1); //You're not going to get away that easily. Huhahahaha.
        selector.addNumber(1903, 5); //Take this!
        selector.addNumber(1986, 1); //Huhaha! Why don't you give up?
        selector.addNumber(1987, 1); //Ha ha! It's no use! Give up!
        if (CurrentCharacter == Characters_Tails)
        {
            selector.addNumber(222, 3); //Goodbye; Tails!
            selector.addNumber(226, 3); //Give up now; Tails!
            selector.addNumber(217, 3); //I've got you now; Tails.
        }
        else if (CurrentCharacter == Characters_Sonic)
        {
            selector.addNumber(563, 3); //Oh yes! Attack Sonic now!
        }
        else if (CurrentCharacter == Characters_Amy)
        {
            selector.addNumber(922, 3); //Where do you think you're going; Amy?
        }
        if (filler == PoliceTrap)
        {
            selector.addNumber(1436, 3); //Ready men? Charge!
            selector.addNumber(404, 3); //You are completely surrounded!
            selector.addNumber(405, 3); //Surrender yourself!
            selector.addNumber(407, 3); //Lock on target men. Ready? Fire!
        }
    }
    if (_options.otherCharactersCommentOnTrap)
    {
        if (CurrentCharacter != Characters_Amy)
        {
            selector.addNumber(384, 1); //You're gonna pay for what you've done!
            selector.addNumber(849, 1); //Hey; are you alright? You look kind of hurt.
            selector.addNumber(885, 1); //Now; now; calm down.
            selector.addNumber(902, 1); //I pity you.
            selector.addNumber(952, 1); //Uh; you okay?
            selector.addNumber(988, 1); //Oh no! Are you okay?
            selector.addNumber(990, 1); //Now you're gonna get it!
            selector.addNumber(1258, 1); //I feel sorry for you.
            selector.addNumber(1493, 1); //Here; take this!
            if (filler == IceTrap || filler == SpringTrap)
            {
                selector.addNumber(888, 3); //Nope!
            }
        }
        if (CurrentCharacter != Characters_Big)
        {
            selector.addNumber(365, 1); //Are you guys okay?
            selector.addNumber(1336, 1); //Uh oh...
            if (filler == IceTrap)
            {
                selector.addNumber(241, 3); //The ice looks kinda tasty!
            }
        }
        if (CurrentCharacter != Characters_Gamma)
        {
            selector.addNumber(169, 1); //Resistance is futile.
            selector.addNumber(385, 1); //Target confirmed.
            selector.addNumber(1777, 1); //Running impossible.
            selector.addNumber(1779, 1); //Ha. Ha. Ha.
            if (CurrentCharacter == Characters_Sonic)
            {
                selector.addNumber(269, 3); //Blue hedgehog: enemy.
                selector.addNumber(386, 3); //Blue hedgehog: enemy.
            }
        }

        if (CurrentCharacter != Characters_Knuckles)
        {
            selector.addNumber(382, 1); //When will you ever learn?
            selector.addNumber(383, 1); //This time; you're finished!
            selector.addNumber(1159, 1); //Yeah! You're finished!
            selector.addNumber(1981, 1); //What's the matter? What're you waiting for?
        }
        if (CurrentCharacter != Characters_Sonic)
        {
            selector.addNumber(496, 1); //Ah; I wonder if he's okay.
            selector.addNumber(605, 1); //Something buggin' you?
            if (CurrentCharacter == Characters_Tails)
            {
                selector.addNumber(211, 3); //See you later; Tails!
            }
            if (filler == IceTrap)
            {
                selector.addNumber(229, 3); //What a nice breeze!
                selector.addNumber(240, 3); //Man; everything's frozen!
            }
        }
        if (CurrentCharacter != Characters_Tails)
        {
            selector.addNumber(618, 1); //Uh oh; what's this?
            selector.addNumber(731, 1); //Oops!
            selector.addNumber(828, 1); //Oops!
            selector.addNumber(1333, 1); //Oops!
            selector.addNumber(1511, 1); //All's well that ends well; right?
        }
    }
    if (_options.currentCharacterReactToTrap)
    {
        if (CurrentCharacter == Characters_Amy)
        {
            selector.addNumber(347, 1); //Hey; come on!
            selector.addNumber(506, 1); //Whoa!!
            selector.addNumber(517, 1); //Ahh! Sonic! Help!
            selector.addNumber(524, 1); //Sonic; help me!
            selector.addNumber(847, 1); //Aahh!! Watch it; watch it!
            selector.addNumber(851, 1); //Ah! Uh oh!
            selector.addNumber(872, 1); //*shouts*
            selector.addNumber(881, 1); //*scream*
            selector.addNumber(916, 1); //*gasp*
            selector.addNumber(923, 1); //Eggman; no!
            selector.addNumber(987, 1); //*gasp*
            selector.addNumber(1739, 1); //Oo-oo-ooh!
            selector.addNumber(1740, 1); //Oh no!
            selector.addNumber(1741, 1); //Whoa!
            selector.addNumber(1743, 1); //Wah!
            if (filler == IceTrap)
            {
                selector.addNumber(1742, 3); //Bbrrr!
            }
        }
        else if (CurrentCharacter == Characters_Big)
        {
            selector.addNumber(747, 1); //Wwhooa!
            selector.addNumber(1330, 1); //Whoaaaa!!
            selector.addNumber(1331, 1); //Ouh!
            selector.addNumber(1752, 1); //*inhales*
            selector.addNumber(1753, 1); //Oh no.
            selector.addNumber(1755, 1); //Oof!
            selector.addNumber(1756, 1); //Oh no!
            selector.addNumber(1757, 1); //Wah!!
            selector.addNumber(1764, 1); //Whooaa!!
        }
        else if (CurrentCharacter == Characters_Knuckles)
        {
            selector.addNumber(164, 1); //Oh no!
            selector.addNumber(332, 1); //Why?
            selector.addNumber(380, 1); //That's it. I've had enough!
            selector.addNumber(475, 1); //Ahh; Eggman!
            selector.addNumber(1004, 1); //What the!?
            selector.addNumber(1006, 1); //Oh no!
            selector.addNumber(1010, 1); //Ooph!
            selector.addNumber(1011, 1); //Auh! Euh! Hey; no fair!
            selector.addNumber(1789, 1); //Whoa!
            selector.addNumber(1795, 1); //Ohh!
            selector.addNumber(1796, 1); //I'm a goner.
            selector.addNumber(1799, 1); //Whooa!
        }
        else if (CurrentCharacter == Characters_Sonic)
        {
            selector.addNumber(165, 1); //Oh no!
            selector.addNumber(167, 1); //I've had enough!
            selector.addNumber(170, 1); //Oh no!
            selector.addNumber(402, 1); //Huh?
            selector.addNumber(444, 1); //Oh no!
            selector.addNumber(460, 1); //Hyyeeh!
            selector.addNumber(464, 1); //Aw; geesh!
            selector.addNumber(476, 1); //Uh oh!
            selector.addNumber(502, 1); //You must be kidding!
            selector.addNumber(523, 1); //Stop!
            selector.addNumber(561, 1); //Oh no! Not again!
            selector.addNumber(582, 1); //Agh; I hate Eggman!
            selector.addNumber(1461, 1); //What?!
            selector.addNumber(1854, 1); //Wwhoa!
            selector.addNumber(1855, 1); //Whoa!
            if (filler == IceTrap)
            {
                selector.addNumber(239, 3); //It's getting cold!
            }
        }
        else if (CurrentCharacter == Characters_Tails)
        {
            selector.addNumber(376, 1); //H-hey; wait a minute!
            selector.addNumber(619, 1); //Noooo!
            selector.addNumber(620, 1); //Ahhhh!
            selector.addNumber(623, 1); //Ahhhh!
            selector.addNumber(671, 1); //Ahhhhh!
            selector.addNumber(728, 1); //Sstop!
            selector.addNumber(748, 1); //Yikes!!
            selector.addNumber(802, 1); //Oh no!
            selector.addNumber(1801, 1); //Whoo!
            selector.addNumber(1814, 1); //Augh!
        }
    }
    if (!selector.isEmpty())
    {
        const int voice = selector.getRandomNumber();
        PlayVoice(voice);
        if (_options.showCommentsSubtitles)
        {
            auto it = _trapCommentMap.find(voice);
            if (it != _trapCommentMap.end() && GameMode != GameModes_Menu)
            {
                subtitleBuffer[0] = it->second.c_str();
                DisplayHintText(subtitleBuffer, 60 + 5 * it->second.length());
            }
        }
    }
}
