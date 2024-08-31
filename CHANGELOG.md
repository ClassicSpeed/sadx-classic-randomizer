# Change Log

All notable changes to this project will be documented in this file.

## [v0.8.2] - 2024-08-?

### Added

- Pause is no longer disabled during after completing a mission.

### Changed

- Fixed Sky Deck entrance being open despite not having an accessible level.
- Removed wall that prevented Tails from entering Emerald Coast.

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



