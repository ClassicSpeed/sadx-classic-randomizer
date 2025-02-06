# Change Log

All notable changes to this project will be documented in this file.

## [v1.1.0] - 2025-??-??

### Added

- Chat messages are now shown in the bottom left corner of the screen.
    - You can change the color, and disable some types of messages in the mod settings.
- Subtitles will be shown when characters comment on items/traps.
    - You can disable this on the mod settings.
- Mod version is now shown in the bottom right corner when pausing.
- Game Gear unlock messages are no longer shown.
- Replaced Casino District Keys with Hotel Back Key and Station Back Key.
- Renamed Hotel/Station Key to Hotel/Station Front Key.
- Added two new key items: Egglift and Monorail.
- The inside of the Egg Carrier is now one of the starting locations.
- Tails' workshop runway will open if Sky Chase is enabled.
    - After getting the check(s) from Act 1, the runway will close.
- You no longer need the YAML in the players folder to use UT.
- Added an option to extend Ring Capacity to 5 digits. This mod setting is disabled by default.
- Separated Ring Link and Hard Ring link packets. Perfect Chaos/end of the level updates are treated as "hard" updates.
    - This means that only players with Hard Ring Link enabled will be affected by the Hard Ring Link updates.
- Added an extra option for Ring Link Override in the mod settings for Hard Ring Link.
- Added indicator for level entrances. This can be disabled in the mod settings.
    - Red cross means the level is not for your character.
    - Orange side arrow means the level is accessible, but you need to use the other entrance.
    - Green upward arrow means the level is accessible.
- Every character will now use Sonic's entrance for each level (except for vanilla alternative entrances).
    - Big no longer uses Knuckles' entrance for Speed Highway.
    - Gamma no longer uses Knuckles' entrance for Lost World.
        - Mission 51 card was moved to the side of the snake head to make it accessible even when the door is open.
    - Tails, Knuckles and Big no longer use Gamma's entrance for Final Egg.
        - Solving the door puzzle with any character will save the solved state.
    - Amy and Gamma no longer use Sonic's entrance for Sky Deck.
- Everyone can transform the Egg Carrier now.
    - The Hidden Bed Emblem is now in logic for everyone on hard+ logic.
    - The Main Platform Emblem is now in logic for Knuckles on hard+ logic.
- Added 5 unused extra circuits to the Twinkle Circuit checks. You can do just the original or one for each character.
- The Twinkle Circuit door will be closed when the Twinkle Circuit checks are disabled.

### Fixed

- Fixed incorrect lines playing when getting a trap as Amy
- Some enemies with Progression items where not marked correctly when the item was also Useful or other type.
- Emblem are now Progression Skip Balancing to prevent them from clogging up the balancing process.

### Logic

#### Hard

- Sand Hill entrance is no longer in logic for Sonic (only in expert).
- All Gamma's Windy Valley's level missions, enemies and capsules are now in logic without the Jet Booster.

#### Expert (DC)

- Added skip from Hotel to SSMain for Sonic, Tails, Knuckles, Amy and Gamma.
- Added skip from SSMain to Station for Tails.

#### Expert (DX)

- Added skip from Hotel to SSMain for Sonic.
- Added skip from Hotel to Casino for Sonic.
- Added skip from SSMain to TP Lobby for Sonic.
- Added skip from TP Lobby to SSMain for Big and Gamma.

## [v1.0.1] - 2025-01-17

### Added

- When an enemy/capsule contains a progression item, the indicator will be yellow.
    - The color (and the feature itself) can be changed in the mod settings.
- The arrow will be smaller and more transparent when the next target is far away.
    - This can be disabled in the mod settings.
- The arrow will now rotate with the character (especially noticeable when running on walls).
- Added option in the mod settings to prevent losing a life when restarting a level.
- Separated expert logic into expert logic DC (DC Conversion) and expert logic DX (Vanilla).

### Changed

- Fixed Speed Highway entrance not working for random entrances after entering the Chao Garden.
- Fixed Ring Link sending duplicate rings when transitioning between adventure field areas.
- Updated installation guide to include information about supported mods.
- Added a warning about enemy-sanity not working correctly with SADX:FE.
- Removed the Jet Booster requirements from Gamma's Windy Valley life capsules.
- Knuckles is no longer in logic for the Hidden Bed or Spinning Platform emblems.
- Knuckles no longer requires the Shovel Claw for the City Hall emblem in DC expert logic.
- Tails' Speed Highway entrance is now in logic without the Employee Key only in DX expert logic.
- Sonic's Red Mountain two life capsules are now in logic without the Light Shoes in hard and expert logic.
- Added missing Light Shoes requirement in multiple Sonic's Windy Valley capsules for normal logic.
- Added missing Life Belt requirement for some Big's Hot Shelter enemies.
- Removed Knuckles, Amy, Big, and Gamma exiting Twinkle Park Lobby without the ticket in expert DX logic.
- Added Sonic and Tails exiting Twinkle Park Lobby without the ticket in expert DC logic.
- Added Knuckles and Amy entering the station without the keys in expert DX logic.
- Added Sonic and Tails entering the hotel from the casino without keys in both expert logics.
- Removed Tails skip from hotel to casino from expert logic.
- Added Tails going from station to casino without the casino keys for both expert logics.

## [v1.0.0c] - 2025-01-13

### Changed

- Fixed the mod mixing up enemies locations.
- Fixed Ice Ball not spawning in SADX version of Ice Cap.
- Fixed Cop Speeder not spawning in SADX version of Speed Highway.
- Fixed Leon and Rhinotank not spawning in Windy Valley for Sonic and Tails in SADX.
- Fixed Gola not spawning in SADX version of Red Mountain.
- Fixed Arrow following pinball capsules even when disabled.

## [v1.0.0b] - 2025-01-11

### Changed

- Fixed Sweep not spawning in SADX version of Twinkle Park.
- Fixed some enemies not being identified correctly in Final Egg and other levels.
- Fixed Leon not spawning correctly in SADX.
- Fixed multiple enemies not spawning in SADX.

## [v1.0.0] - 2025-01-11

### Added

- Added Enemy-sanity (710 checks in total).
- Added Capsule-sanity (692 checks in total).
- When playing Enemy or Capsule sanity, things that would grant a check will be marked with a triangle.
    - The triangle will be red/green (default) if the check is available, and gray if it's already collected.
    - You can disable it and change its color in the mod's settings.
- An arrow will be shown over the player that points towards the next capsule.
    - You can disable it, change its color, and make it toggleable in the mod's settings.
- The in-game tracker will show the number of collected capsules and enemies.
    - The progress will also be shown by act if applicable.
- Added Sky Deck location group.

### Changed

- Changed name format of level checks:
    - Now it's "Level (Character) - Location" instead of "Level (Character - Location)".
- Updated wiki to use the actual location names for the field emblems.
- The traps/filler option for adventure field now applies to the Chao Garden as well.
- Sand Hill entrance will start closed for Sonic from the start (like Tails).
    - This also means that Sand Hill is no longer in logic for Sonic in normal level logic.
- The Casino Emblem is now in logic for Sonic in hard/expert logic.
- Added multiple changes in expert logic. (Credit to Labrys for the footage).

### Removed

- Removed life-sanity (in favor of adding capsule-sanity).
- Removed auto-win button from the mod and settings.

### Enemy-sanity

- Enemy-sanity can be enabled separately for different characters.
- The location name will include the enemy number and what enemy it is.
- Some enemies won't count as a check:
    - Every enemy that is not in both SADX and SADC.
    - Enemies that only spawn during missions.
    - Enemies spawned by traps.
    - Enemy-karts in Twinkle Park.
    - Rhinos attached to the bridges for Gamma's Windy Valley.
    - Pirates in Knuckles' Casinopolis.
    - Beats (the infinite-spawning enemy) in Sonic's Final Egg.
    - Spinners in the wrong paths at the end of Amy's Final Egg.
    - Dolls in Gamma's Final Egg.
- Sometimes, enemies won't spawn; most of the time, restarting from the last checkpoint will fix it.

### Capsule-sanity

- Capsule-sanity can be enabled separately for different characters.
- The location name will include the capsule number and what kind of capsule it is.
- You can toggle the 5 capsules in Sonic's Pinball (off by default).
- Capsules are divided into 4 groups, each can be toggled separately:
    - Life capsules: extra lives (103 checks).
    - Shield capsules: shields and magnetic shields (78 checks).
    - Power-up capsules: invincibility, speed up and bombs (70 checks).
    - Ring capsules: 5 rings, 10 rings and ? rings (441 checks).
- If Capsule-sanity is enabled but all capsule types are disabled, life capsules will be enabled as a failsafe.
- Some capsules won't count as a check:
    - Capsules that are not in both SADX and SADC.
    - Capsules in Twinkle Circuit.
    - Capsules found when digging as Knuckles.
- Sonic can break capsules while playing as Tails and that won't count as a check.
    - Keep in mind that capsules won't respawn until you leave and enter the level again.

## [v0.9.1] - 2024-12-21

### Fixed

- Fixed item link adding random important items into the pool instead of filler.
- Fixed non-deterministic behavior when generating the same seed multiple times.
- Fixed Chao Races not sending checks.

## [v0.9.0b] - 2024-12-01

### Fixed

- Fixed problems with collisions in multiple levels.
- Removed Gamma from Silver Egg's logic.
- Fixed Golden Egg's logic. It now requires either the Hotel Keys, the Station Keys, or the Casino District Keys.
- Fixed Black and Silver Egg logic.

## [v0.9.0] - 2024-11-30

### Added

- All 3 secret *Chao Eggs* are now location checks. You have to bring them to the Chao Garden to get the check.
- Added the 5 *Chao Races* emblems as checks.
    - You can select what percentage of action stages you have access to before the races are in logic.
- *Chao stats multiplier* in the mod's settings (default is 1, up to 50).
    - To use a separate save file for the Chao Garden when playing AP, set `RedirectChaoSave` to true in the `mod.ini`.
- Added location groups for "Chao Races" and "Chao Eggs".
- The goal setting is now separated into multiple goal requirements, with the goal always being the Perfect Chaos fight.
    - The requirements can be levels, emblems, Chaos Emeralds, missions, bosses, and Chao Races.
- Options to force enable/disable both Death Link and Ring Link in the mod's settings.
- Setting in the world configuration to guarantee a number of checks in the starting location.

### Changed

- The settings for the logic will now be checked early to ensure that a world is able to generate correctly:
    - With all characters disabled, Sonic will be enabled as a failsafe with a warning message.
    - If there is no goal requirement set, the goal will be set to levels with a warning message.
    - If the goal requires levels and there are no levels in the settings, they will be enabled with a warning message.
    - If the goal requires missions and the missions are disabled, they will be enabled with a warning message.
    - If the goal requires Chao Races and they are disabled, they will be enabled with a warning message.
    - If the Chao Races are enabled with no levels in the settings, they will be enabled with a warning message.
- Changed example YAML accessibility setting to Locations (0).
- Removed extra collision from City Hall in the DC conversion to allow Sonic to do the same skip as in DX.

### Fixed

- Logic regarding level/mission goals not working correctly.

## [v0.8.8] - 2024-11-03

### Added

- Reverse controls trap that inverts the player's movement.
- Option to set the duration of the reverse controls trap in the settings. A value of 0 will make the trap last until
  the player dies or changes levels.
- Gravity trap that increases the player's gravity.
- Option to disable filler/traps while in the adventure field.
- Option to disable filler/traps during boss fights.
- Option to disable filler/traps during the Perfect Chaos fight.
- All traps function like they do in normal levels, except for enemy traps, which subtract 5 rings from the player.
- Support for The Super Sonic mod:
    - Disable the "Remove limitations" option in the Super Sonic mod settings to restrict playing as Super Sonic until
      after collecting all the Chaos Emeralds in Archipelago.
    - If your goal doesn’t include the emeralds, you can play as Super Sonic from the start.
- Option to control the chance of dying when receiving a Death Link.
    - When surviving, the player will see a "You survived a Death Link!" message.
- Option to control the chance of sending a Death Link when dying.
    - If no Death Link is sent, the player will see a "Death Link not sent!" message.

### Changed

- When activating a spring trap, the player's velocity is stopped to ensure they interact with the spring properly.
- If all traps are disabled, the trap percentage will be converted to filler items.
- Gamma's entrance in Lost World is now the same as Knuckles'.
    - This change was made because opening the snake prevents the player from obtaining the mission 51 card.

### Fixed

- Fixed an error that prevented the A mission check from occurring if the player failed the B mission.

## [v0.8.7b] - 2024-10-12

### Removed

- Removed object draw distance since it was causing issues with the game.

## [v0.8.7] - 2024-10-11

### Added

- Added support for Universal Tracker's map feature.
- Added "Casino Keys" alias for the Casino District Keys.
- Improved objects' draw distance: there is now a 5x multiplier to each object's draw distance.
    - This can be changed in the mod configuration. Setting the multiplier to 1 will result in vanilla draw distance.

### Changed

- Tails can now go from the main station square area to the hotel without the keys in expert logic.
- Knuckles can now enter Lost World without the shovel claw in expert logic.
- Sonic can now enter Speed Highway without the employee card in expert logic (using Knuckles' entrance).
- Fixed every Ice Cap entrance and Knuckles' Red Mountain entrance not requiring the dynamite.
- Knuckles, Big, and Gamma can now get out of the Twinkle Park lobby area without the ticket in expert logic.
- Removed Big's life belt requirement for mission 22 in all logic levels.

## [v0.8.6] - 2024-09-14

### Added

- Added option to select which character's voice will be used for the menus.
    - The option is in the mod configuration; you can select a specific character or random.
- Blacklisted missions won't spawn their cards in the adventure fields anymore.
    - They will be marked as completed in the pause menu (but won't count towards the goal).

### Changed

- The Employee Card won't spawn for Sonic if the level is not accessible for him.
- Fixed Sonic's Speed Highway entrance not needing the in-game Employee Card.
- Speed Highway's shutter will open as soon as you get the Employee Card for Amy and Gamma.
    - Previously, you had to leave Station Square if you got the card in the main area.
- Losing as Tails will now send a death link.
- Fixed Death link related crash.
- Fixed Ring link related crash.
- Fixed the game crashing when transitioning between stages with a police trap active.
- Fixed Hard Ring link not working during the Perfect Chaos fight.
- Gamma can now get every Hot Shelter check without the Jet Booster in hard/expert logic.

## [v0.8.5] - 2024-09-08

### Added

- Created [Location Wiki](https://github.com/ClassicSpeed/SADX-Archipelago-Locations-Wiki/blob/main/README.md) for the
  locations of the life capsules and field emblems. (Credit to DementisXYZ & Roukles).
- Added voice lines when getting a trap, a key item, or a new character.
    - The voice lines are from Eggman or the current character.
    - There are settings in the mod configuration to disable them.
- Re-enabled the Egg Carrier transformation cutscene to help players know that the switch worked.
    - The cutscene is unskippable, so an option in the mod configuration was added to disable it.
- When starting on Angel Island, the player will spawn near the Red Mountain entrance.
    - The door to the cave will be closed until you get the dynamite.
- Added a 5-second grace period after sending or receiving a death link where the game won't process any more links.
- Pausing is now disabled for 2.5 seconds after getting a trap (the same time as the trap's cooldown).
- Options that affect logic are passed through for Universal Tracker now.
    - This means that weighted values won't break UT anymore.

### Changed

- Fixed Red Mountain entrance not appearing for Big without the DC conversion.
- Fixed Final Egg Tower exiting spawning the character in the wrong place.
- Fixed automatic mission start re-starting the mission after resetting the game.
- The Angel Island Shrine Emblem is now in logic for Gamma with the Jet Booster in hard and expert logic.
- Sonic's Red Mountain entrance is now in logic without any upgrades in expert logic.
- Sonic going from the station to the casino without the keys is now in logic for expert logic.
- Tails going from the casino to the station without the keys is now in logic for expert logic.
- Amy getting out of Twinkle Park Lobby without the ticket is now in logic for expert logic.
- Amy is now in logic for the pool emblem in hard and expert logic.

## [v0.8.4] - 2024-09-05

### Added

- Added mission completion as a goal.
- Added level percentage for the level completion goal.
- Added mission percentage for the mission completion goal.
- Added tracker for random level entrances.
    - It will update as soon as you enter a level, but you need to finish the level for the change to persist after a
      restart.

### Changed

- Every of Big's Mission A now requires all the lure upgrades in expert logic.

## [v0.8.3] - 2024-09-03

### Added

- Big now has to use Sonic and Tails' entrance to Sky Deck so he can use the pool for mission 44.
    - Since he can transform the Egg Carrier now, the hidden bed emblem and the Chaos 6 main platform emblem are in
      hard/expert logic for Big.
- Added Sonic to the hard/expert logic for the Pool Emblem and Tree Stump Emblem.
- Added an explanation for entrance randomizer in the options.
- Guaranteed level now supports entrance randomizer.
    - Be aware that without a random starting location, the guaranteed level option will probably fail to generate.
- Added level entrance plando, which only works if random level entrance is enabled.
    - It supports partial plando, so you can choose which levels you want to be randomized.
- If pinball's life capsules are disabled, they won't show up in the in-game tracker.
- Added an option to disable Ring Link while playing Sonic's Casinopolis.

### Changed

- Fixed the returning position from Hot Shelter for Sonic, Tails, and Knuckles.
- Improved Field Emblem draw distance in Mystic Ruins.
- The City Hall Emblem is now higher only for Tails (so Cream can get it) to prevent other characters from getting it.
- Fixed Amy's mission 19 logic.
- Random level entrances are now taken into account for the random starting location logic.
- Fixed Game Over not sending death links.
- The death link is now sent as soon as the player dies instead of waiting for the animation/fade out.
- The warp point for the past is now Tails only.
- Fixed the mod changing the character to your starter character if the connection is lost.

## [v0.8.2] - 2024-08-31

### Added

- Pause is no longer disabled after completing a mission.
- Added Sonic for the Pool Emblem's hard logic.
- Changed the returning position after a finishing a level to match the original level's one.

### Changed

- Fixed Sky Deck entrance being open despite not having an accessible level.
- Removed wall that prevented Tails from entering Emerald Coast.
- Fixed the wind for angel island cave not being present for Amy.
- Fixed the angel island door not opening for Amy.
- Renamed logic levels to Normal, Hard and Expert, with Expert containing Out of Bounds jumps.
- Improved the wording for the option and default player yaml.
- Added default archipelago options values to the default player yaml.

## [v0.8.1] - 2024-08-29

### Changed

- Fixed Tails, Knuckles, and Big not being able to enter the Final Egg Tower in the Jungle.
- Fixed hotel elevators not working.
- Added Light Shoes requirement for two Life Capsules in Sonic's Red Mountain.
- Updated `PlayerExample.yaml` to include goals information.
- Fixed Amy's Angel Island cave not opening.
- Fixed Knuckles' Casinopolis entrance not opening.

## [v0.8.0] - 2024-08-28

### Added

- Level completion as a goal.
- Completing all the action stages enables the Perfect Chaos fight.
- Added an option to auto-start missions.
- Added Angel Island area as a starting location.
- Added Twinkle Park Lobby as a starting location.
    - You will need the Twinkle Park ticket to exit the lobby, even as Big.
- Your starting character will now be selected on the character select screen when starting the game.
- Added a warning message for version mismatch when connecting to Archipelago.
- Separated the sublevel checks options into two:
    - One for Twinkle Circuit and Sand Hill, and another for Sky Chase Act 1 and 2.
- Added error messages when generating with very low settings. There is now a minimum of 5 emblems for the goal.
- Level entrances can now be randomized.
- The adventure field was modified to allow some characters to use level entrances they wouldn't normally use.
- Some level entrances are now closed if the corresponding level is not accessible for the character.

#### Level Entrance Changes

- Gamma won't be able to shoot the Emerald Coast's gate targets if the level is not accessible for him.
- Windy Valley won't open if the level is not accessible for the character.
    - For Sonic, Tails, and Gamma, the Wind Stone won't spawn if the level is not accessible for the character.
    - For Amy, Knuckles, and Big, it will open as soon as you get the Wind Stone.
- Casinopolis button won't open the casino door if the level is not accessible for the character.
- Speed Highway's shutter and elevator will open for Amy and Gamma when the player gets the Employee Card.
- Big's Speed Highway entrance is at the city hall; he still needs the Employee Card to enter.
- Knuckles' City Hall barricade won't spawn if the level is not accessible for him.
- Big, Knuckles, and Tails can use Gamma's Final Egg entrance.
- Tails, Amy, Gamma, and Big can now use Sonic's Lost World entrance.
    - Knuckles' Gold/Silver Key won't spawn if the level is not accessible for him.
- Red Mountain's door will stay closed if the level is not accessible for the character.
    - Red Mountain's Monkey will only spawn if it's needed to open the door.
    - For Tails, Amy, and Big, it won't spawn if the level is not accessible for the character.
- The Ice Cap door will be open for Knuckles, Amy, and Gamma as soon as you get the Ice Stone.
    - For Sonic, Tails, and Big, you still have to fetch the actual Ice Stone.
    - The ladder (and the load zone) won't spawn if the level is not accessible for the character.
- Big, Amy, and Gamma can now use Knuckles' Sky Deck entrance.

- TL;DR: Every character can use every level entrance if the level is accessible for the character.
    - Wind/Ice Stone will open the level/cave directly for characters that don't normally use them.

### Changed

- Fixed normal/hard logic for missions not working correctly.
- Added an 80% maximum for the emblem percentage goal.
- Twinkle Circuit is now in logic if you have access to the Twinkle Park Lobby.
- Improved emblem requirements calculation.
    - It should hopefully fix the issue with the wrong emblem percentage goal.
- Fixed soft lock when losing any race as Tails.
- Moved the City Hall emblem a little higher so you can get it when using the Cream the Rabbit mod.
- Changed LR (Life Ring) to LB (Life Belt) in the pause menu.
- Casual Logic for Big's mission 29 now requires the Life Belt.
- Fixed logic for Knuckles' Chaos 6 when unified.
- Fixed Big's logic requiring the Twinkle Park Ticket to enter the lobby.

## [v0.7.1] - 2024-08-22

### Added

- You'll now go directly to the character select screen when quitting the game. (Changed in v0.6.0)
- Death Link will now work between players in the same slot.
- Removed invisible wall in Sonic's Casinopolis sewer that prevented the player from getting the life capsule in SADX.

### Changed

- Mission cards no longer spawn if you have missions disabled.
- Moved Chaos 4 entrance to the place where you encounter Knuckles in the story.
- Fixed spawning in Station Square after a game over.
- Fixed the randomizer status info not showing on the character select screen when quitting the game.
- Big's HUD is now hidden in the adventure fields again.
- The character select screen won't load until the game is connected to Archipelago.

## [v0.7.0] - 2024-08-20

### Added

- Reworked logic to be able to import from
  the [Google Sheet](https://docs.google.com/spreadsheets/d/1CfBZ_pLGm3YTWwEwBLbk67e4iSrOE5vbcu0UkFej0pY).
- Added option for logic level: Casual, Normal, and Hard.
- Added option to enable playable characters separated from the action stage missions.
    - You can now enable a character without their levels and still do missions, bosses, etc.
- Added option set to blacklist missions. The previous non-stop missions option was removed.
- Added location group for missions.
- Added random starting location per character.

### Changed

- Removed `apworld` from committed files and added a link to its repository in the README.
- Tails' workshop emblem is now in logic for Gamma with the Jet Booster.
- Fixed issue with the monkey door on Mystic Ruins not being open for Big to start mission 35.
- Fixed issue with mission 35 being in logic without dynamite.
- Fixed soft lock when dying during level transitions.
- Restored the normal level result screen.
    - This fixes Gamma not adding the extra time at the end and sublevel problems.

## [v0.6.2] - 2024-08-20

### Changed

- Fixed bug that prevented the ice stone from spawning in mystic ruins.

## [v0.6.1] - 2024-08-17

### Added

- Unlocked all the Game Gear games in the main menu.

### Changed

- Fixed sublevels crashing when completing the level.
- Moved the mission switch in Big's House to allow the player to get the power rod upgrade.
- Moved up the Sonic's mission card in the sewers, so it doesn't clip with the spring.
- Fixed Perfect Chaos fight not being soft locked.

## [v0.6.0] - 2024-08-16

### Added

- Added Mission mode.
- Activating a mission card no longer prevents you from moving.
- Finishing a mission no longer prevents you from moving.
- Random starting locations now take life capsules into account.

### Changed

- Fixed Station Square starting location not working correctly when guaranteed action stage was disabled.

## [v0.5.2] - 2024-08-15

### Added

- Added Item groups: "Chaos Emeralds", "Playable Characters", "Upgrades", "Key Items", "Fillers" and "Traps".
- Added Location groups: "Upgrade Points", "Field Emblems", "Levels", "Sublevels", "Bosses", "Life Capsules".
- There is also a location group for each of the 11 levels that include every level mission and life capsules.
- Added a 2.5-second delay for processing traps/filler items.

### Changed

- Fixed Sky Chase crash.
- You can no longer activate filler items during Sky Chase or Twinkle Circuit.
- Fixed crash when leaving the menu after winning the game.
- Fixed Egg Carrier being transformed when starting in it.
- Fixed Knuckles' life capsules in Red Mountain not requiring the shovel claw.
- Fixed every check in Big's Ice Cap not requiring the station keys.
- Sonic is now in logic for the Egg Carrier Hidden Bed Emblem.
- Hints are no longer shown for already found items.
- Removed emblems from the item pool when the goal is set to Emerald Hunt.
- Fixed non-randomized upgrades not working correctly.
- Fixed some spelling mistakes in the mod configuration file.
- Fixed some checks getting triggered while in preview/demo mode.

## [v0.5.1] - 2024-08-13

### Changed

- Fixed setting station square as the starting location.
- Fixed wind stone not being in the item pool.
- Reverted Egg Carrier transformation from the start.
    - The boss fights will still remember the transformation state.
- Sky Chase warp points won't spawn if sublevels are off
- Chaos Emerald now have their respective colors in the pause menu.

## [v0.5.0] - 2024-08-13

### Added

- Added a Goal setting:
    - Emblems: You have to collect a certain number of emblems to unlock the Perfect Chaos Fight.
    - Chaos Emerald Hunt: You have to collect all 7 Chaos Emeralds to unlock the Perfect Chaos Fight.
    - Emblems and Chaos Emerald Hunt: You have to collect both emblems and the emeralds to fight Perfect Chaos.
- Added Station Keys to the item pool.
    - The Casino District Keys now open the casino-hotel door and the station-hotel door.
- Added the inside of the Station as a starting location.
- Changed the starting location logic.
    - You can now choose to randomize the starting location or start in Station Square.
    - You can now guarantee access to an action stage, even if it means giving you an item.
    - The possible starting locations now take into account the logic for your options.
    - For example, the inside of the station is only available if you have field emblems enabled.
- Added the Wind Stone to the item pool.
- Knuckles can now dig for the monkey killer switch in Mystic Ruins.
    - To enter Red Mountain, you now have to kill the monkey.
- Simplified key item information on the pause menu.
- Knuckles' Chaos 6 fight now takes place in his version of the arena.
- Added Sky Chase Act 1 and 2 as location checks.
    - Act 1 entrance is located inside Tails' workshop.
    - Act 2 entrance is located on the Egg Carrier runway.
- Added an extra option for sublevels to enable the harder A mission (off by default).
    - The current sublevels are: Twinkle Circuit, Sand Hill, and Sky Chase Act 1 and 2.
- The Egg Carrier is now transformed from the start.
- Egg Carrier's bosses and Sky Chase now remember the Egg Carrier's transformation state.
- Tails now needs to press the button to open the Sand Hill entrance.
- When exiting Sand Hill, you'll spawn in the cave.
- Tails' Rhythm Badge upgrade point is part of the randomizer.
    - A warp point near the Master Emerald shrine was added to travel to the past.
    - There is no other location check in the past, but you can still explore it with any character.

### Changed

- Bosses' warp points won't show up if the boss checks are disabled.
- Fixed Egg Carrier boss gate clipping through the floor.
- Added trap weight information to the configuration file.
- Traps will no longer activate during the result screen; they will queue up and activate after exiting the level.

## [v0.4.5] - 2024-08-11

### Changed

- Removed player name in hedgehog hammer since it caused crashes and texture corruption.
- Change traps classification to trap.

## [v0.4.4] - 2024-08-10

### Added

- Added trap items:
    - Ice Trap: Freezes the player for a few seconds.
    - Spring Trap: Sends the player to the opposite direction they were going.
    - Police Trap: Spawns a bunch of police cars that will chase the player.
    - Buyon Trap: Spawns a bunch of Buyons that will chase the player.
- Separated Hedgehog Hammer's checks for amy.
- Hedgehog Hammer's high score will show the player's name instead of Amy's.
- Added configuration for archipelago messages
    - You can change the display duration, font size, and color.
- Added target time for mission A and B in the pause screen.
    - This is specially important for tails, since the target time for mission A is an approximation of the real target.
- Added character name to the death link message.

### Changed

- Fixed hint text being backwards.
- Fixed death link not working properly.

## [v0.4.3] - 2024-08-05

### Added

- Added filler items:
    - Invincibility, 5 Rings, 10 rings, Shield, Magnetic Shield, Extra life.
- Added Gamma's Hot shelter 4th life capsule
- Added error message when generating without any character.
- Added separate life-sanity option for each character.
    - Only works if the life-sanity is enabled.
    - The level status won't track life capsules for characters with life-sanity off.

### Changed

- Fixed death link and ring link not working together.
- Fixed crash when receiving a death link while in the main menu.
- Fixed receiving extra items after reconnecting to the server.

## [v0.4.2] - 2024-08-04

### Changed

- Fixed crash while picking up life capsules in the kart section of twinkle park.
- Removed APCpp.dll from the installation process.
- Improving the project's dependencies and build configuration.

## [v0.4.1] - 2024-08-03

### Added

- Added life capsules status for the current level.
- Life capsules won't respawn after getting them with life-sanity on.
- Added Hard Ring Link option.
    - If enabled ring link will work during the Perfect Chaos fight.
    - Also, you'll send ring losses after finishing a level.

### Changed

- Made boss warp points work faster.
- Fix generation error when starting with gamma on station square.
- Fix sewer spring sending Sonic too far.

## [v0.4.0] - 2024-08-02

### Added

- Added boss fights as location checks.
    - You can unify the Chaos 4, Chaos 6 and Egg Hornet fights in the options, so you'll have to fight them only once.
    - Every entrance is located near the location of the boss in the story.
    - Every entrance is represented by a warp platform (Chaos 2 entrance is 2nd elevator in the hotel).
- Added option for starting locations.
    - The possible options are: random, random with no item, Station Square and Station Square with no item.
- Added Big's Emerald Coast life capsule as a location check.
- Added Sonic's 3rd Life Capsule in the Casino sewer (Credit to TerraFrost).
- Added Tails' 4th Life Capsule in Sky Deck.

### Changed

- Improved handling of the spawned objects in the levels.
- Updated capitalization for upgrade names (Credit to Knux).
- Renamed Jungle Kart to Jungle Cart.
- Removed Amy from City Hall emblem logic.
- Removed Life Belt for Big's Ice Cap life capsule.
- The mod now correctly handles external checks.
- Ring Link no longer depletes rings after finishing a level.
- Ring Link no longer depletes rings during the Perfect Chaos fight.

## [v0.3.3] - 2024-07-28

### Added

- Graving a field emblem no longer prevents you from moving.

### Changed

- Fix Big and Gamma being stuck on the Casino Area.
- Amy's Final Egg entrance no longer open from the start.
- Added Jet Anklet for Tails' A missions logic.
- Removed Shovel Claw requirements for knuckles' life capsules.

## [v0.3.2] - 2024-07-27

### Added

- Randomized starting locations.
    - You will start in a random location with a guaranteed action level access.
    - To ensure the access to that level, sometimes you'll receive a key item.
- Added Death Link
- Added Ring Link
- Added option to handle ring loss: Classic (lose all rings), Modern (lose 20 rings) and One Hit K.O.
- Big's lure upgrades are now randomized.
    - Keep in mind that if you get the lure during a level, the fish won't change.
    - You have to reenter/restart the level for the fish to respawn.
- Replaced Super Sonic "Hmph" with "I'll show you what the Chaos Emeralds can really do!" in the character select
  screen.
- Removed 10 second penalty at the end of Sonic and Tails levels.
- Added options to randomize each character's upgrades.
- Added Universal tracker Support.
- Added starting setup info to the spoilers.

### Changed

- Fixed crash when dying in the last act of final egg.
- Removed the character name from the upgrade items.
- Not needed emblems are marked as filler in the logic.
- Twinkle Park's elevator is no longer open from the start for Big.
    - You have to enter using the sewer entrance.
    - It will open after getting the Twinkle Park C mission.
    - You still need the Twinkle Park Ticket for Twinkle circuit.
- Improved logic for the area access and the emblems
    - This should improve the Universal Tracker compatibility

## [v0.3.1] - 2024-07-23

### Changed

- Fixed zip file generation that messed up the folder on linux systems.
- Fixed Big's hot shelter life capsule not working correctly.
- Removed Big's hot shelter locations life belt requirement.
- Fixed Amy's last hot shelter life capsule not working correctly.
- Default emblem percentage for Perfect Chaos is now 80%.
- Removed light shoes requirement for sky deck (and its life capsules).
- Removed light shoes requirement final egg life capsules (and one from Lost world).

### Added

- Added error message if the fixes, adds and beta restores mod is loaded.
- Added spring on Sonic's Final Egg for the last 4 life capsules.
- Added option to disable the pinball's life capsules.

## [v0.3.0] - 2024-07-20

### Added

- Added life capsules as a check.
    - The option is off by default.
- Added current level information on the pause screen.
    - It shows the current level and mission.
    - Also, what missions you have completed.

### Changed

- Big starts with all the lures.
- Gamma and tails have to open the wind vally entrances with the wind stone.
- Fixed watching credits granting a victory.
- Fixed losing the final boss fight granting a victory.
- Knuckles now requires the shovel claw for the city hall emblem
- Fixed the mission A check for twinkle circuit

## [v0.2.3] - 2024-07-16

### Added

- The mod will check for the requirements of other missions after finishing the level and give you the extra location
  checks.
- Also works on twinkle circuit and sand hill.
- This option can be disabled in the mod configuration.
- Added error message if the steam achievement mod is loaded.

### Changed

- Getting 3000 points on hedgehog hammer will give you both the check for Warrior's Feather and Long Hammer.
- The door between the hotel and the casino area will be open after getting both keys.

## [v0.2.2] - 2024-07-15

### Added

- Added Archipelago model replacing the field emblem.
- Added Archipelago textures replacing emblems in UI.
- Added spring in the sewer for Sonic (and removed the car).
- Re-added Knuckles' Red Mountain as a location again.
- Re-added Gamma's upgrades locations check

### Changed

- Fixed weird state for NPCs (like duplicated or nonsensical dialogues).
- Removed cutscenes from the supersonic fight.
- Fixed Amy/Gamma's upgrades being inverted on the status information.
- Fixed Gamma stuck after Final Egg.
- Fixed Amy stuck after Hedgehog Hammer.
- Fixed Chao garden's warp gates not working.
- Windy Valley now requires the wind stone again.
- Knuckles' lost worlds requires the silver and gold key again.
- Sonic and Gamma's Red Mountains require the monkey to be destroyed again.
- Fixed Twinkle park elevator not working for Tails, knuckles and Gamma.

## [v0.2.1] - 2024-07-13

### Added

- Added more information in the player configuration file.
- Fade out effect on new messages.

### Changed

- Fixed chao related crash.
- Added Big's pool door to the hotel keys item.
- Fixed Twinkle Circuit and Sand hill not giving a check.
- Removed Gamma's upgrades from logic.
- Disabled warrior's feather from logic (Long Hammer is still accessible).
- Disabled trial menu (since allows you to skip logic).

## [v0.2.0] - 2024-07-12

### Added

- The whole game is now "open" from the start.
- You'll get a random character when starting the game.
- Added key items to open up the adventure fields.
- Key items will show on the unlocked items' menu.
- Emblems as checks.
- Sublevels as checks.

## [v0.1.0] - 2024-07-08

### Changed

- Re-enabled mission/trial options on the menu.
- Last Story takes the player directly to the Perfect Chaos fight.
- The demo cutscenes no longer give checks.
- Unlocks are shown on the character select screen and pause menu.
    - It only shows the characters that are playable in the randomizer.
- Prevent Supersonic for being selected early.
- Fixed logic issue with missions A/B not being accessible after C

### Added

- Added message to check your configs if the connection takes too long.
- Cutscenes are skipped automatically.
- Skipping credits is enabled.
- Configuration for skipping scenes/credits and auto-win button.

## [v0.0.5] - 2024-07-07

### Added

- Added level emblems as locations.
    - You can configure how many missions types for each character.
    - You can choose 0 (except for sonic).
- Added emblem requirement for Perfect Chaos.
    - You can select the percentage of emblems needed to fight Perfect Chaos.
- Added option to randomize or not the story unlocks.
- Automated the release files generation.

## [v0.0.4] - 2024-07-04

### Added

- Added hash on the save file.
- Archipelago item received, sent and hint messages.

### Changed

- Improved the connection handling with archipelago.

## [v0.0.3] - 2024-07-03

### Added

- Goal check for ending the game.
- Disabled the Trial and Mission menu.

### Changed

- Improving the project build with release configuration
- Fixed mod configuration schema

## [v0.0.2] - 2024-07-02

### Added

- First connection with archipelago.
- Items and location for upgrades and story unlocks.

## [v0.0.1] - 2024-06-28

### Added

- Initial experimental version.



