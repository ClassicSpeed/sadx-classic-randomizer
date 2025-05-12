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

struct SongData
{
    int id;
    std::string codename;
    std::string fullName;
    std::vector<std::string> possibleCodenames;
};

class SongMap
{
    mutable std::mt19937 gen{std::random_device{}()}; // Declare the generator as a class member

public:
    void AddSong(int id, const std::string& codename, const std::string& fullName,
                 const std::vector<std::string>& possibleCodenames)
    {
        SongData songData = {id, codename, fullName, possibleCodenames};
        _idMap[id] = songData;
        _codenameMap[codename] = id;
    }

    const SongData* FindById(int id) const
    {
        auto it = _idMap.find(id);
        if (it != _idMap.end())
        {
            return &it->second;
        }
        return nullptr;
    }

    const SongData* FindByCodename(const std::string& codename) const
    {
        PrintDebug("Finding song by codename: %s\n", codename.c_str());
        auto it = _codenameMap.find(codename);
        if (it != _codenameMap.end())
        {
            auto song = &(_idMap.at(it->second));
            PrintDebug("Found song: %s\n", song->codename.c_str());
            return song;
        }
        return nullptr;
    }

    int GetRandomSongId(const int id) const
    {
        auto it = _idMap.find(id);
        if (it == _idMap.end())
        {
            PrintDebug("Song ID %d not found\n", id);
            return 255; // Return an empty string if the ID is not found
        }

        const SongData& songData = it->second;

        // Combine the base codename with the filtered possible codenames
        std::vector<std::string> allCodenames;
        for (const auto& codename : songData.possibleCodenames)
        {
            if (!codename.empty())
            {
                allCodenames.push_back(codename);
            }
        }
        allCodenames.push_back(songData.codename);

        // Generate a random index
        std::uniform_int_distribution<> dist(0, allCodenames.size() - 1);

        const auto song = FindByCodename(allCodenames[dist(gen)]);
        // Return a random codename
        PrintDebug("Randomized song ID: %d\n", song->id);
        return song->id;
    }

private:
    std::map<int, SongData> _idMap;
    std::unordered_map<std::string, int> _codenameMap;
};

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

        _songMap.AddSong(0, "advamy", "Instruction: Amy", {""});
        _songMap.AddSong(1, "advbig", "Instruction: Big", {""});
        _songMap.AddSong(2, "adve102", "Instruction: E-102", {""});
        _songMap.AddSong(3, "advknkls", "Instruction: Knuckles", {""});
        _songMap.AddSong(4, "advmiles", "Instruction: Tails", {""});
        _songMap.AddSong(5, "advsonic", "Instruction: Sonic", {""});
        _songMap.AddSong(6, "amy", "My Sweet Passion", {""});
        _songMap.AddSong(7, "big", "Lazy Days~Livin' In Paradise", {""});
        _songMap.AddSong(8, "bossall", "Egg Mobile ...Boss: Egg Hornet", {
                             "evtbgm01", "adve102", "bossall", "bosse101", "bossevnt", "bosstrgt", "chaos", "chaos_6",
                             "chaos_p1", "chaos_p2", "eggman", "eggmbl23", "eggrobo"
                         });
        _songMap.AddSong(9, "bosse101", "Crazy Robo ...Boss: E-101R", {
                             "adve102", "bossall", "bosse101", "bossevnt", "bosstrgt", "chaos", "chaos_6", "chaos_p1",
                             "chaos_p2", "eggman", "eggmbl23", "eggrobo"
                         });
        _songMap.AddSong(10, "bossevnt", "Fight for My Own Way ...Boss: Event", {
                             "adve102", "bossall", "bosse101", "bossevnt", "bosstrgt", "chaos", "chaos_6", "chaos_p1",
                             "chaos_p2", "eggman", "eggmbl23", "eggrobo"
                         });
        _songMap.AddSong(11, "bosstrgt", "Heartless Colleague ...Boss: E-Series Targets", {
                             "evtbgm01", "adve102", "bossall", "bosse101", "bossevnt", "bosstrgt", "chaos", "chaos_6",
                             "chaos_p1", "chaos_p2", "eggman", "eggmbl23", "eggrobo"
                         });
        _songMap.AddSong(12, "casino1", "The Dreamy Stage ...for Casinopolis", {
                             "amy", "casino1", "casino2", "casino3", "casino4", "chaohall", "circuit", "twnklpk1",
                             "twnklpk2"
                         });
        _songMap.AddSong(13, "casino2", "Dilapidated Way ...for Casinopolis",
                         {"casino1", "casino3", "casino4", "redmntn2", "shelter1"});
        _songMap.AddSong(14, "casino3", "Blue Star ...for Casinopolis", {
                             "amy", "casino1", "casino2", "casino3", "casino4", "chaohall", "circuit", "twnklpk1",
                             "twnklpk2"
                         });
        _songMap.AddSong(15, "casino4", "Message from Nightopia", {
                             "amy", "casino1", "casino2", "casino3", "casino4", "chaohall", "circuit", "twnklpk1",
                             "twnklpk2"
                         });
        _songMap.AddSong(16, "chao", "Theme of \"CHAO\"", {
                             "chaorace", "chao", "chaohall", "ecoast3", "highway3", "icecap1", "s_square", "twnklpk1",
                             "twnklpk2", "chao_r_e", "c_btl_cv", "chao_k_m"
                         });
        _songMap.AddSong(17, "chaogoal", "Chao Race Goal", {
                             "chaogoal", "evtbgm02", "evtbgm03", "fishget", "item1", "one_up", "rndclear", "mclear_44",
                             "mstart_44", "chao_k_net_fine", "chao_r_gate_open", "chao_g_born_h", "chao_g_born_d",
                             "chao_g_born_h2", "chao_g_born_d2", "chao_g_dance"
                         });
        _songMap.AddSong(18, "chaohall", "Letz Get This Party Started ...for CHAO Race Entrance", {
                             "chaorace", "chao", "chaohall", "ecoast3", "highway3", "icecap1", "s_square", "twnklpk1",
                             "twnklpk2", "chao_r_e", "c_btl_cv", "chao_k_m"
                         });
        _songMap.AddSong(19, "chaorace", "Join Us 4 Happy Time ...for CHAO Race",
                         {"chaohall", "circuit", "hammer", "scramble"});
        _songMap.AddSong(20, "chaos", "Boss: CHAOS ver.0, 2, 4", {
                             "evtbgm01", "adve102", "bossall", "bosse101", "bossevnt", "bosstrgt", "chaos", "chaos_6",
                             "chaos_p1", "chaos_p2", "eggman", "eggmbl23", "eggrobo"
                         });
        _songMap.AddSong(21, "chaos_6", "Boss: CHAOS ver.6", {
                             "adve102", "bossall", "bosse101", "bossevnt", "bosstrgt", "chaos", "chaos_6", "chaos_p1",
                             "chaos_p2", "eggman", "eggmbl23", "eggrobo"
                         });
        _songMap.AddSong(22, "chaos_p1", "Boss: Perfect CHAOS", {
                             "adve102", "bossall", "bosse101", "bossevnt", "bosstrgt", "chaos", "chaos_6", "chaos_p1",
                             "chaos_p2", "eggman", "eggmbl23", "eggrobo"
                         });
        _songMap.AddSong(23, "chaos_p2", "Perfect CHAOS Revival! ...Boss: Perfect CHAOS", {
                             "adve102", "bossall", "bosse101", "bossevnt", "bosstrgt", "chaos", "chaos_6", "chaos_p1",
                             "chaos_p2", "eggman", "eggmbl23", "eggrobo"
                         });
        _songMap.AddSong(24, "charactr", "Choose Your Buddy!", {
                             "chaohall", "charactr", "jingle_1", "jingle_2", "jingle_3", "jingle_5", "option", "title",
                             "title2", "trial", "chao_r_e", "c_btl_cv", "chao_k_m"
                         });
        _songMap.AddSong(25, "circuit", "Twinkle Circuit", {
                             "casino2", "chaohall", "hammer", "highway1", "shelter2", "skydeck2", "twnklpk1"
                         });
        _songMap.AddSong(26, "continue", "Will You Continue?", {
                             "continue", "evtbgm00", "fishmiss", "titl_egg", "titl_mr1", "titl_mr2", "titl_ss",
                             "chao_g_iede", "chao_g_born_c", "chao_g_dead"
                         });
        _songMap.AddSong(27, "e102", "Theme of \"E-102g\"", {""});
        _songMap.AddSong(28, "ecoast1", "Azure Blue World ...for Emerald Coast", {
                             "chaorace", "ecoast1", "ecoast2", "ecoast3", "egcarer2", "highway3", "wndyvly1", "wndyvly3"
                         });
        _songMap.AddSong(29, "ecoast2", "Windy and Ripply ...for Emerald Coast", {
                             "chaorace", "ecoast1", "ecoast2", "ecoast3", "egcarer2", "highway3", "wndyvly1", "wndyvly3"
                         });
        _songMap.AddSong(30, "ecoast3", "BIG Fishes at Emerald Coast...", {
                             "big", "chaorace", "ecoast1", "ecoast2", "ecoast3", "egcarer2", "highway3", "wndyvly1",
                             "wndyvly3"
                         });
        _songMap.AddSong(31, "egcarer1", "Egg Carrier - A Song That Keeps Us On The Move", {
                             "bosse101", "e102", "egcarer1", "egcarer2", "finaleg1", "hammer", "scramble", "shelter2"
                         });
        _songMap.AddSong(32, "egcarer2", "Calm After the Storm ...Egg Carrier -the ocean-", {
                             "bosse101", "e102", "egcarer1", "egcarer2", "finaleg1", "hammer", "scramble", "shelter2"
                         });
        _songMap.AddSong(33, "eggman", "Theme of \"Dr.EGGMAN\"", {""});
        _songMap.AddSong(34, "eggmbl23", "Militant Missionary ...Boss: Egg Walker & Egg Viper", {
                             "adve102", "bossall", "bosse101", "bossevnt", "bosstrgt", "chaos", "chaos_6", "chaos_p1",
                             "chaos_p2", "eggman", "eggmbl23", "eggrobo"
                         });
        _songMap.AddSong(35, "eggrobo", "ZERO The Chase-master ...Boss: Eggman Robot -ZERO-", {
                             "adve102", "bossall", "bosse101", "bossevnt", "bosstrgt", "chaos", "chaos_6", "chaos_p1",
                             "chaos_p2", "eggman", "eggmbl23", "eggrobo"
                         });
        _songMap.AddSong(36, "evtbgm00", "Event: Sadness", {""});
        _songMap.AddSong(37, "evtbgm01", "Event: Strain", {""});
        _songMap.AddSong(38, "evtbgm02", "Event: Unbound", {""});
        _songMap.AddSong(39, "evtbgm03", "Event: Good-bye!", {""});
        _songMap.AddSong(40, "evtbgm04", "Event: The Past", {""});
        _songMap.AddSong(41, "evtbgm05", "Event: Fanfare for \"Dr.EGGMAN\"", {""});
        _songMap.AddSong(42, "finaleg1", "Mechanical Resonance ...for Final Egg", {
                             "bosse101", "e102", "finaleg1", "finaleg2", "shelter1", "shelter2", "skydeck1", "twnklpk3"
                         });
        _songMap.AddSong(43, "finaleg2", "Crank the Heat Up!! ...for Final Egg", {
                             "bosse101", "e102", "finaleg1", "finaleg2", "shelter1", "shelter2", "skydeck1", "twnklpk3"
                         });
        _songMap.AddSong(44, "fishget", "Fish Get!", {
                             "chaogoal", "evtbgm02", "evtbgm03", "fishget", "item1", "one_up", "rndclear", "mclear_44",
                             "mstart_44", "chao_k_net_fine", "chao_r_gate_open", "chao_g_born_h", "chao_g_born_d",
                             "chao_g_born_h2", "chao_g_born_d2", "chao_g_dance"
                         });
        _songMap.AddSong(45, "fishing", "and... Fish Hits!", {""});
        _songMap.AddSong(46, "fishmiss", "Fish Miss!", {
                             "continue", "evtbgm00", "fishmiss", "titl_egg", "titl_mr1", "titl_mr2", "titl_ss",
                             "chao_g_iede", "chao_g_born_c", "chao_g_dead"
                         });
        _songMap.AddSong(47, "hammer", "Sweet Punch ...for Hedgehog Hammer", {"amy", "casino3", "casino4"});
        _songMap.AddSong(48, "highway1", "Run Through the Speed Highway ...for Speed Highway", {
                             "circuit", "finaleg2", "redmntn2", "shelter1", "twnklpk1"
                         });
        _songMap.AddSong(49, "highway2", "Goin' Down!? ...for Speed Highway", {"icecap3", "skydeck1", "skydeck2"});
        _songMap.AddSong(50, "highway3", "At Dawn ...for Speed Highway", {"casino1", "s_square"});
        _songMap.AddSong(51, "hurryup", "Danger is Imminent", {"timer"});
        _songMap.AddSong(52, "icecap1", "Snowy Mountain ...for Icecap", {"icecap1", "icecap2", "wndyvly1"});
        _songMap.AddSong(53, "icecap2", "Limestone Cave ...for Icecap", {"icecap1", "icecap2", "wndyvly1"});
        _songMap.AddSong(54, "icecap3", "Be Cool, Be Wild and Be Groovy ...for Icecap",
                         {"scramble", "skydeck1", "wndyvly2"});
        _songMap.AddSong(55, "invncibl", "Invincible ...No Fear!", {
                             "sprsonic", "advamy", "advbig", "adve102", "advmiles", "advsonic", "advknkls"
                         });
        _songMap.AddSong(56, "item1", "Item", {""});
        _songMap.AddSong(57, "jingle_1", "Jingle A", {
                             "chaohall", "charactr", "jingle_1", "jingle_2", "jingle_3", "jingle_5", "option", "title",
                             "title2", "trial", "chao_r_e", "c_btl_cv", "chao_k_m"
                         });
        _songMap.AddSong(58, "jingle_2", "Jingle B", {
                             "chaohall", "charactr", "jingle_1", "jingle_2", "jingle_3", "jingle_5", "option", "title",
                             "title2", "trial", "chao_r_e", "c_btl_cv", "chao_k_m"
                         });
        _songMap.AddSong(59, "jingle_3", "Jingle C", {
                             "chaohall", "charactr", "jingle_1", "jingle_2", "jingle_3", "jingle_5", "option", "title",
                             "title2", "trial", "chao_r_e", "c_btl_cv", "chao_k_m"
                         });
        _songMap.AddSong(60, "jingle_4", "Jingle D", {
                             "chaohall", "charactr", "jingle_1", "jingle_2", "jingle_3", "jingle_5", "option", "title",
                             "title2", "trial", "chao_r_e", "c_btl_cv", "chao_k_m"
                         });
        _songMap.AddSong(61, "jingle_5", "Jingle E", {
                             "chaohall", "charactr", "jingle_1", "jingle_2", "jingle_3", "jingle_5", "option", "title",
                             "title2", "trial", "chao_r_e", "c_btl_cv", "chao_k_m"
                         });
        _songMap.AddSong(62, "knuckles", "Unknown from M.E.", {""});
        _songMap.AddSong(63, "lstwrld1", "Tricky Maze ...for Lost World", {
                             "lstwrld1", "lstwrld2", "lstwrld3", "mstcln", "sandhill", "tical"
                         });
        _songMap.AddSong(64, "lstwrld2", "Danger! Chased by Rock ...for Lost World", {
                             "lstwrld1", "lstwrld2", "lstwrld3", "mstcln", "sandhill", "tical"
                         });
        _songMap.AddSong(65, "lstwrld3", "Leading Lights ...for Lost World", {
                             "chaos_p2", "lstwrld1", "lstwrld2", "lstwrld3", "mstcln", "sandhill", "tical"
                         });
        _songMap.AddSong(66, "mainthem", "Open your Heart -Main Theme of \"SONIC Adventure\"-", {""});
        _songMap.AddSong(67, "mstcln", "Mystic Ruin", {
                             "knuckles", "chao", "chaorace", "icecap1", "lstwrld1", "lstwrld3", "tical"
                         });
        _songMap.AddSong(71, "one_up", "Extend", {
                             "chaogoal", "evtbgm02", "evtbgm03", "fishget", "item1", "one_up", "rndclear", "mclear_44",
                             "mstart_44", "chao_k_net_fine", "chao_r_gate_open", "chao_g_born_h", "chao_g_born_d",
                             "chao_g_born_h2", "chao_g_born_d2", "chao_g_dance"
                         });
        _songMap.AddSong(72, "option", "Funky Groove Makes U Hot!? ...for Options", {
                             "chaohall", "charactr", "jingle_1", "jingle_2", "jingle_3", "jingle_5", "option", "title",
                             "title2", "trial", "chao_r_e", "c_btl_cv", "chao_k_m"
                         });
        _songMap.AddSong(73, "redmntn1", "Mt. Red: a Symbol of Thrill ...for Red Mountain",
                         {"egcarer2", "knuckles", "lstwrld1", "redmntn2"});
        _songMap.AddSong(74, "redmntn2", "Red Hot Skull ...for Red Mountain", {"shelter1", "redmntn1"});
        _songMap.AddSong(75, "rndclear", "Round Clear", {
                             "chaogoal", "evtbgm02", "evtbgm03", "fishget", "item1", "one_up", "rndclear", "mclear_44",
                             "mstart_44", "chao_k_net_fine", "chao_r_gate_open", "chao_g_born_h", "chao_g_born_d",
                             "chao_g_born_h2", "chao_g_born_d2", "chao_g_dance"
                         });
        _songMap.AddSong(76, "s_square", "Welcome to Station Square!", {
                             "casino1", "casino2", "chao", "chaorace", "ecoast3", "highway3", "chao_r_e"
                         });
        _songMap.AddSong(77, "sandhill", "Sand Hill", {"icecap3", "lstwrld1", "lstwrld2", "redmntn1"});
        _songMap.AddSong(78, "scramble", "Tornado Scramble ...for Sky Chase",
                         {"tails", "scramble", "shelter2", "skydeck1", "wndyvly2"});
        _songMap.AddSong(79, "shelter1", "Bad Taste Aquarium ...for Hot Shelter", {
                             "bosse101", "e102", "finaleg1", "finaleg2", "redmntn2", "shelter1", "shelter2", "skydeck1"
                         });
        _songMap.AddSong(80, "shelter2", "Red Barrage Area ...for Hot Shelter", {
                             "bosse101", "e102", "finaleg1", "finaleg2", "redmntn2", "shelter1", "shelter2", "skydeck1"
                         });
        _songMap.AddSong(81, "skydeck1", "Skydeck A Go! Go! ...for Sky Deck", {
                             "scramble", "wndyvly2", "casino2", "finaleg1", "skydeck1", "skydeck2"
                         });
        _songMap.AddSong(82, "skydeck2", "General Offensive ...for Sky Deck",
                         {"casino2", "finaleg1", "skydeck1", "skydeck2"});
        _songMap.AddSong(83, "sonic", "It Doesn't Matter", {""});
        _songMap.AddSong(85, "speedup", "Hey You! It's Time to Speed Up!!!", {
                             "sprsonic", "advamy", "advbig", "adve102", "advmiles", "advsonic", "advknkls"
                         });
        _songMap.AddSong(86, "sprsonic", "Theme of \"SUPER SONIC\"", {""});
        _songMap.AddSong(88, "tails", "Believe in Myself", {""});
        _songMap.AddSong(89, "theamy", "Appearance: AMY", {""});
        _songMap.AddSong(90, "thebig", "Appearance: BIG", {""});
        _songMap.AddSong(91, "thee102", "Appearance: E-102", {""});
        _songMap.AddSong(92, "theknkls", "Appearance: KNUCKLES", {""});
        _songMap.AddSong(93, "themiles", "Appearance: MILES", {""});
        _songMap.AddSong(94, "thesonic", "Appearance: SONIC", {""});
        _songMap.AddSong(95, "tical", "Theme of \"TIKAL\"", {""});
        _songMap.AddSong(96, "timer", "Drowning", {"hurryup"});
        _songMap.AddSong(97, "titl_egg", "Egg Carrier Transform", {
                             "continue", "evtbgm00", "fishmiss", "titl_egg", "titl_mr1", "titl_mr2", "titl_ss",
                             "chao_g_iede", "chao_g_born_c", "chao_g_dead"
                         });
        _songMap.AddSong(98, "titl_mr1", "", {
                             "continue", "evtbgm00", "fishmiss", "titl_egg", "titl_mr1", "titl_mr2", "titl_ss",
                             "chao_g_iede", "chao_g_born_c", "chao_g_dead"
                         });
        _songMap.AddSong(99, "titl_mr2", "", {
                             "continue", "evtbgm00", "fishmiss", "titl_egg", "titl_mr1", "titl_mr2", "titl_ss",
                             "chao_g_iede", "chao_g_born_c", "chao_g_dead"
                         });
        _songMap.AddSong(100, "titl_ss", "Trial Version Quit", {""});
        _songMap.AddSong(101, "title", "Main Menu", {
                             "chaohall", "charactr", "jingle_1", "jingle_2", "jingle_3", "jingle_5", "option", "title",
                             "title2", "trial", "chao_r_e", "c_btl_cv", "chao_k_m"
                         });
        _songMap.AddSong(102, "title2", "Title Screen", {
                             "chaohall", "charactr", "jingle_1", "jingle_2", "jingle_3", "jingle_5", "option", "title",
                             "title2", "trial", "chao_r_e", "c_btl_cv", "chao_k_m"
                         });
        _songMap.AddSong(103, "trial", "Trial", {
                             "chaohall", "charactr", "jingle_1", "jingle_2", "jingle_3", "jingle_5", "option", "title",
                             "title2", "trial", "chao_r_e", "c_btl_cv", "chao_k_m"
                         });
        _songMap.AddSong(104, "twnklpk1", "Twinkle Cart ...for Twinkle Park", {
                             "amy", "circuit", "highway1", "highway3", "shelter1", "twnklpk1", "twnklpk2", "twnklpk3"
                         });
        _songMap.AddSong(105, "twnklpk2", "Pleasure Castle ...for Twinkle Park", {
                             "amy", "circuit", "highway1", "highway3", "shelter1", "twnklpk1", "twnklpk2", "twnklpk3"
                         });
        _songMap.AddSong(106, "twnklpk3", "Fakery Way ...for Twinkle Park", {"eggmbl23", "lstwrld3"});
        _songMap.AddSong(107, "wndyvly1", "Windy Hill ...for Windy Valley", {
                             "chaorace", "ecoast1", "ecoast2", "ecoast3", "egcarer2", "jingle_5", "redmntn1",
                             "twnklpk1", "wndyvly1", "wndyvly2", "wndyvly3"
                         });
        _songMap.AddSong(108, "wndyvly2", "Tornado ...for Windy Valley", {"scramble", "skydeck1"});
        _songMap.AddSong(109, "wndyvly3", "The Air ...for Windy Valley", {
                             "big", "tails", "chaorace", "ecoast1", "ecoast2", "ecoast3", "egcarer2", "jingle_5",
                             "redmntn1", "twnklpk1", "wndyvly1", "wndyvly2", "wndyvly3"
                         });
        _songMap.AddSong(110, "mstart_44", "Mission Start!", {
                             "chaogoal", "evtbgm02", "evtbgm03", "fishget", "item1", "one_up", "rndclear", "mclear_44",
                             "mstart_44", "chao_k_net_fine", "chao_r_gate_open", "chao_g_born_h", "chao_g_born_d",
                             "chao_g_born_h2", "chao_g_born_d2", "chao_g_dance"
                         });
        _songMap.AddSong(111, "mclear_44", "Mission Clear!", {
                             "chaogoal", "evtbgm02", "evtbgm03", "fishget", "item1", "one_up", "rndclear", "mclear_44",
                             "mstart_44", "chao_k_net_fine", "chao_r_gate_open", "chao_g_born_h", "chao_g_born_d",
                             "chao_g_born_h2", "chao_g_born_d2", "chao_g_dance"
                         });
        _songMap.AddSong(112, "chao_k_net_fine", "Chao: Level Up!", {
                             "chaogoal", "evtbgm02", "evtbgm03", "fishget", "item1", "one_up", "rndclear", "mclear_44",
                             "mstart_44", "chao_k_net_fine", "chao_r_gate_open", "chao_g_born_h", "chao_g_born_d",
                             "chao_g_born_h2", "chao_g_born_d2", "chao_g_dance"
                         });
        _songMap.AddSong(113, "chao_g_iede", "Chao: Goodbye!", {""});
        _songMap.AddSong(114, "chao_r_e", "Chao: Naming", {
                             "chaorace", "chao", "chaohall", "ecoast3", "highway3", "icecap1", "s_square", "twnklpk1",
                             "twnklpk2", "chao_r_e", "c_btl_cv", "chao_k_m"
                         });
        _songMap.AddSong(115, "c_btl_cv", "Chao Race Entry", {
                             "chaohall", "charactr", "jingle_1", "jingle_2", "jingle_3", "jingle_5", "option", "title",
                             "title2", "trial", "chao_r_e", "c_btl_cv", "chao_k_m"
                         });
        _songMap.AddSong(116, "chao_r_gate_open", "Chao Race Gate Open", {
                             "chaogoal", "evtbgm02", "evtbgm03", "fishget", "item1", "one_up", "rndclear", "mclear_44",
                             "mstart_44", "chao_k_net_fine", "chao_r_gate_open", "chao_g_born_h", "chao_g_born_d",
                             "chao_g_born_h2", "chao_g_born_d2", "chao_g_dance"
                         });
        _songMap.AddSong(117, "chao_g_born_h2", "Hero Chaos Chao Born 2", {
                             "chaogoal", "evtbgm02", "evtbgm03", "fishget", "item1", "one_up", "rndclear", "mclear_44",
                             "mstart_44", "chao_k_net_fine", "chao_r_gate_open", "chao_g_born_h", "chao_g_born_d",
                             "chao_g_born_h2", "chao_g_born_d2", "chao_g_dance"
                         });
        _songMap.AddSong(118, "chao_g_born_d2", "Dark Chaos Chao Born 2", {
                             "chaogoal", "evtbgm02", "evtbgm03", "fishget", "item1", "one_up", "rndclear", "mclear_44",
                             "mstart_44", "chao_k_net_fine", "chao_r_gate_open", "chao_g_born_h", "chao_g_born_d",
                             "chao_g_born_h2", "chao_g_born_d2", "chao_g_dance"
                         });
        _songMap.AddSong(119, "chao_g_born_c", "Chaos Chao Born", {
                             "chaogoal", "evtbgm02", "evtbgm03", "fishget", "item1", "one_up", "rndclear", "mclear_44",
                             "mstart_44", "chao_k_net_fine", "chao_r_gate_open", "chao_g_born_h", "chao_g_born_d",
                             "chao_g_born_h2", "chao_g_born_d2", "chao_g_dance"
                         });
        _songMap.AddSong(120, "chao_g_born_h", "Hero Chaos Chao Born", {
                             "chaogoal", "evtbgm02", "evtbgm03", "fishget", "item1", "one_up", "rndclear", "mclear_44",
                             "mstart_44", "chao_k_net_fine", "chao_r_gate_open", "chao_g_born_h", "chao_g_born_d",
                             "chao_g_born_h2", "chao_g_born_d2", "chao_g_dance"
                         });
        _songMap.AddSong(121, "chao_g_born_d", "Dark Chaos Chao Born", {
                             "chaogoal", "evtbgm02", "evtbgm03", "fishget", "item1", "one_up", "rndclear", "mclear_44",
                             "mstart_44", "chao_k_net_fine", "chao_r_gate_open", "chao_g_born_h", "chao_g_born_d",
                             "chao_g_born_h2", "chao_g_born_d2", "chao_g_dance"
                         });
        _songMap.AddSong(122, "chao_g_dead", "Chao Died", {
                             "continue", "evtbgm00", "fishmiss", "titl_egg", "titl_mr1", "titl_mr2", "titl_ss",
                             "chao_g_iede", "chao_g_born_c", "chao_g_dead"
                         });
        _songMap.AddSong(123, "chao_g_dance", "Chao Dance", {
                             "chaogoal", "evtbgm02", "evtbgm03", "fishget", "item1", "one_up", "rndclear", "mclear_44",
                             "mstart_44", "chao_k_net_fine", "chao_r_gate_open", "chao_g_born_h", "chao_g_born_d",
                             "chao_g_born_h2", "chao_g_born_d2", "chao_g_dance"
                         });
        _songMap.AddSong(124, "chao_k_m", "Chao: Black Market", {
                             "chaohall", "charactr", "jingle_1", "jingle_2", "jingle_3", "jingle_5", "option", "title",
                             "title2", "trial", "chao_r_e", "c_btl_cv", "chao_k_m"
                         });
        for (size_t id = 0; id < MusicList.size(); ++id)
        {
            PrintDebug("-----Randomizing song id %d\n", id);
            const int randomSongCode = _songMap.GetRandomSongId(static_cast<int>(id));
            if (randomSongCode != 255)
            {
                songRandomizationMap[id] = randomSongCode;
            }
        }
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
    void SetTrapLink(bool trapLinkActive);
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
    void ProcessTrapLink(std::string itemName, std::string message);
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
    void OnPlaySong(MusicIDs songId);
    std::unordered_map<int, int> songRandomizationMap;

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
        {1868, "The Egg Carrier has crashed and is floating\nsomewhere in the ocean. Use this boat to get to it."},
        {1927, "Take this boat to get to the Egg Carrier."},
        {1921, "Something good may happen at the Casino area."},
        {1922, "Why don't you try going to the Casino?"},
        {1558, "You can go to the Casino area at nighttime."},
        {1928, "Why don't you try going to Angel Island?"},
        {1955, "You can break through the wall if you use dynamite."},
        {1561, "You can get into a certain building\nusing the Employee Card."},
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

    struct SongData
    {
        int id;
        std::string codename;
        std::string fullName;
        std::vector<std::string> possibleCodenames;
    };

    SongMap _songMap;
};
