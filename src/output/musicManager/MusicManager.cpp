#include "MusicManager.h"

MusicManager::MusicManager()
{
    this->ProcessSongFile();
}

int MusicManager::GetRandomSongId(int id)
{
    return _songMap.GetRandomSongId(id);
}

const SongData* MusicManager::FindSongById(MusicIDs songId)
{
    return _songMap.FindById(songId);
}


void MusicManager::ProcessSongFile()
{
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
}
