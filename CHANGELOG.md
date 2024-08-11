# Change Log

All notable changes to this project will be documented in this file.

## [v0.5.0] - 2024-08-?

### Added

- Added the monkey killer switch for knuckles.
    - Now to enter Red Mountain, you have to kill the monkey.

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



