#include "ItemRepository.h"


ItemRepository::ItemRepository(GameStatus& gameStatus) : _gameStatus(gameStatus)
{
    _itemData = {
        {1, ItemData::CharacterItem(FLAG_SONIC_PLAYABLE, "Playable Sonic")},
        {2, ItemData::CharacterItem(FLAG_MILES_PLAYABLE, "Playable Tails")},
        {3, ItemData::CharacterItem(FLAG_KNUCKLES_PLAYABLE, "Playable Knuckles")},
        {4, ItemData::CharacterItem(FLAG_AMY_PLAYABLE, "Playable Amy")},
        {5, ItemData::CharacterItem(FLAG_E102_PLAYABLE, "Playable Gamma")},
        {6, ItemData::CharacterItem(FLAG_BIG_PLAYABLE, "Playable Big")},


        {10, ItemData::UpgradeItem(Upgrades_LightShoes, "Light Shoes (Sonic)")},
        {11, ItemData::UpgradeItem(Upgrades_CrystalRing, "Crystal Ring (Sonic)")},
        {12, ItemData::UpgradeItem(Upgrades_AncientLight, "Ancient Light (Sonic)")},

        {20, ItemData::UpgradeItem(Upgrades_JetAnklet, "Jet Ankle (Tails)")},
        {21, ItemData::UpgradeItem(Upgrades_RhythmBadge, "Rhythm Badge (Tails)")},

        {30, ItemData::UpgradeItem(Upgrades_ShovelClaw, "Shovel Claw (Knuckles)")},
        {31, ItemData::UpgradeItem(Upgrades_FightingGloves, "Fighting Gloves (Knuckles)")},

        {40, ItemData::UpgradeItem(Upgrades_WarriorFeather, "Warrior Feather (Amy)")},
        {41, ItemData::UpgradeItem(Upgrades_LongHammer, "Long Hammer (Amy)")},

        {50, ItemData::UpgradeItem(Upgrades_JetBooster, "Jet Booster (Gamma)")},
        {51, ItemData::UpgradeItem(Upgrades_LaserBlaster, "Laser Blaster (Gamma)")},

        {60, ItemData::UpgradeItem(Upgrades_LifeRing, "Life Belt (Big)")},
        {61, ItemData::UpgradeItem(Upgrades_PowerRod, "Power Rod (Big)")},

        {62, ItemData::LureItem("Lure 1 (Big)")},
        {63, ItemData::LureItem("Lure 2 (Big)")},
        {64, ItemData::LureItem("Lure 3 (Big)")},
        {65, ItemData::LureItem("Lure 4 (Big)")},

        {71, ItemData::FillerItem("Invincibility", Invincibility)},
        {72, ItemData::FillerItem("5 Rings", FiveRings)},
        {73, ItemData::FillerItem("10 Rings", TenRings)},
        {74, ItemData::FillerItem("Shield", Shield)},
        {75, ItemData::FillerItem("Magnetic Shield", MagneticShield)},
        {76, ItemData::FillerItem("Extra Life", ExtraLife)},

        {
            80,
            ItemData::KeyItem({
                                  FLAG_SONIC_TRAIN, FLAG_MILES_TRAIN, FLAG_KNUCKLES_TRAIN,
                                  FLAG_AMY_TRAIN, FLAG_E102_TRAIN, FLAG_BIG_TRAIN
                              }, "Train")
        },
        {
            81, ItemData::KeyItem({
                                      FLAG_SONIC_BOAT, FLAG_MILES_BOAT, FLAG_KNUCKLES_BOAT,
                                      FLAG_AMY_BOAT, FLAG_E102_BOAT, FLAG_BIG_BOAT
                                  }, "Boat")
        },
        {
            82, ItemData::KeyItem({
                                      FLAG_SONIC_RAFT, FLAG_MILES_RAFT, FLAG_KNUCKLES_RAFT,
                                      FLAG_AMY_RAFT, FLAG_E102_RAFT, FLAG_BIG_RAFT
                                  }, "Raft")
        },
        {83, ItemData::KeyItem({}, "Hotel Front Key")},
        {84, ItemData::KeyItem({}, "Hotel Back Key")},
        {
            85, ItemData::KeyItem({
                                      FLAG_SONIC_SS_TPARK_ELEVATOR,
                                      FLAG_MILES_SS_TPARK_ELEVATOR,
                                      FLAG_KNUCKLES_SS_TPARK_ELEVATOR,
                                      FLAG_AMY_SS_TPARK_ELEVATOR,
                                      FLAG_E102_SS_TPARK_ELEVATOR,
                                      FLAG_BIG_SS_TPARK_ELEVATOR
                                  }, "Twinkle Park Ticket")
        },
        {86, ItemData::KeyItem({FLAG_SONIC_SS_CARD, FLAG_MILES_SS_ENTRANCE_HIGHWAY}, "Employee Card")},
        {87, ItemData::KeyItem({FLAG_SONIC_SS_ICESTONE, FLAG_MILES_SS_ICESTONE, FLAG_BIG_SS_ICESTONE}, "Ice Stone")},
        {88, ItemData::KeyItem({}, "Dynamite")},
        {
            89, ItemData::KeyItem({
                                      FLAG_SONIC_MR_TRUCK, FLAG_MILES_MR_TRUCK, FLAG_KNUCKLES_MR_TRUCK,
                                      FLAG_AMY_MR_TRUCK, FLAG_E102_MR_TRUCK, FLAG_BIG_MR_TRUCK
                                  }, "Jungle Cart")
        },

        {90, ItemData::EmblemItem("Emblem")},

        {92, ItemData::ChaosEmeraldItem("White Chaos Emerald")},
        {93, ItemData::ChaosEmeraldItem("Red Chaos Emerald")},
        {94, ItemData::ChaosEmeraldItem("Cyan Chaos Emerald")},
        {95, ItemData::ChaosEmeraldItem("Purple Chaos Emerald")},
        {96, ItemData::ChaosEmeraldItem("Green Chaos Emerald")},
        {97, ItemData::ChaosEmeraldItem("Yellow Chaos Emerald")},
        {98, ItemData::ChaosEmeraldItem("Blue Chaos Emerald")},

        {100, ItemData::FillerItem("Ice Trap", IceTrap)},
        {101, ItemData::FillerItem("Spring Trap", SpringTrap)},
        {102, ItemData::FillerItem("Police Trap", PoliceTrap)},
        {103, ItemData::FillerItem("Buyon Trap", BuyonTrap)},
        {104, ItemData::FillerItem("Reverse Trap", ReverseTrap)},
        {105, ItemData::FillerItem("Gravity Trap", GravityTrap)},


        {120, ItemData::KeyItem({}, "Wind Stone")},
        {121, ItemData::KeyItem({}, "Station Front Key")},
        {122, ItemData::KeyItem({}, "Station Back Key")},
        {
            123, ItemData::KeyItem({
                                       FLAG_SONIC_EC_EGGLIFT, FLAG_MILES_EC_EGGLIFT, FLAG_KNUCKLES_EC_EGGLIFT,
                                       FLAG_AMY_EC_EGGLIFT, FLAG_E102_EC_EGGLIFT, FLAG_BIG_EC_EGGLIFT
                                   }, "Egglift")
        },
        {
            124, ItemData::KeyItem({
                                       FLAG_SONIC_EC_MONORAIL, FLAG_MILES_EC_MONORAIL, FLAG_KNUCKLES_EC_MONORAIL,
                                       FLAG_AMY_EC_MONORAIL, FLAG_E102_EC_MONORAIL, FLAG_BIG_EC_MONORAIL
                                   }, "Monorail")
        },
    };
}


bool ItemRepository::SetObtained(const int64_t itemId)
{
    _itemsReceived++;
    _itemData[itemId].obtained = true;
    UpdateUnlockStatus();
    
    //We save in the save file the number of items received
    if (_itemsReceived > this->GetSavedItemReceived())
        this->UpdateItemsReceived(_itemsReceived);
        //If the item is already processed and filler, we ignore it
    else if (_itemData[itemId].type == ItemFiller)
        return true;


    return false;
}

ItemData ItemRepository::GetItem(const int64_t itemId)
{
    return _itemData[itemId];
}


std::map<int64_t, ItemData> ItemRepository::GetItems()
{
    return _itemData;
}


int ItemRepository::GetEmblemCount()
{
    return _emblemCount;
}

int ItemRepository::AddEmblem()
{
    _emblemCount++;
    return _emblemCount;
}

void ItemRepository::UpdateUnlockStatus()
{

    _gameStatus.unlock.currentEmblems = _emblemCount;

    _gameStatus.unlock.whiteEmerald = _itemData[92].obtained;
    _gameStatus.unlock.redEmerald = _itemData[93].obtained;
    _gameStatus.unlock.cyanEmerald = _itemData[94].obtained;
    _gameStatus.unlock.purpleEmerald = _itemData[95].obtained;
    _gameStatus.unlock.greenEmerald = _itemData[96].obtained;
    _gameStatus.unlock.yellowEmerald = _itemData[97].obtained;
    _gameStatus.unlock.blueEmerald = _itemData[98].obtained;

    _gameStatus.unlock.sonicUnlocked = _itemData[1].obtained;
    _gameStatus.unlock.sonicLightShoesUnlocked = _itemData[10].obtained;
    _gameStatus.unlock.sonicCrystalRingUnlocked = _itemData[11].obtained;
    _gameStatus.unlock.sonicAncientLightUnlocked = _itemData[12].obtained;

    _gameStatus.unlock.tailsUnlocked = _itemData[2].obtained;
    _gameStatus.unlock.tailsJetAnkletUnlocked = _itemData[20].obtained;
    _gameStatus.unlock.tailsRhythmBadgeUnlocked = _itemData[21].obtained;

    _gameStatus.unlock.knucklesUnlocked = _itemData[3].obtained;
    _gameStatus.unlock.knucklesShovelClawUnlocked = _itemData[30].obtained;
    _gameStatus.unlock.knucklesFightingGlovesUnlocked = _itemData[31].obtained;

    _gameStatus.unlock.amyUnlocked = _itemData[4].obtained;
    _gameStatus.unlock.amyWarriorFeatherUnlocked = _itemData[40].obtained;
    _gameStatus.unlock.amyLongHammerUnlocked = _itemData[41].obtained;

    _gameStatus.unlock.gammaUnlocked = _itemData[5].obtained;
    _gameStatus.unlock.gammaJetBoosterUnlocked = _itemData[50].obtained;
    _gameStatus.unlock.gammaLaserBlasterUnlocked = _itemData[51].obtained;

    _gameStatus.unlock.bigUnlocked = _itemData[6].obtained;
    _gameStatus.unlock.bigLifeBeltUnlocked = _itemData[60].obtained;
    _gameStatus.unlock.bigPowerRodUnlocked = _itemData[61].obtained;
    _gameStatus.unlock.bigLureQuantity = _itemData[62].obtained + _itemData[63].obtained + _itemData[64].obtained + _itemData[
        65].obtained;


    _gameStatus.unlock.keyTrain = _itemData[80].obtained;
    _gameStatus.unlock.keyBoat = _itemData[81].obtained;
    _gameStatus.unlock.keyRaft = _itemData[82].obtained;
    _gameStatus.unlock.keyHotelFrontKey = _itemData[83].obtained;
    _gameStatus.unlock.keyHotelBackKey = _itemData[84].obtained;
    _gameStatus.unlock.keyTwinkleParkTicket = _itemData[85].obtained;
    _gameStatus.unlock.keyEmployeeCard = _itemData[86].obtained;
    _gameStatus.unlock.keyIceStone = _itemData[87].obtained;
    _gameStatus.unlock.keyWindStone = _itemData[120].obtained;
    _gameStatus.unlock.keyDynamite = _itemData[88].obtained;
    _gameStatus.unlock.keyJungleCart = _itemData[89].obtained;
    _gameStatus.unlock.keyStationFrontKey = _itemData[121].obtained;
    _gameStatus.unlock.keyStationBackKey = _itemData[122].obtained;
    _gameStatus.unlock.keyEgglift = _itemData[123].obtained;
    _gameStatus.unlock.keyMonorail = _itemData[124].obtained;
}

void ItemRepository::ResetItems()
{
    _emblemCount = 0;
    _itemsReceived = 0;
    for (auto& item : _itemData)
    {
        item.second.obtained = false;
    }
    UpdateUnlockStatus();
}

std::map<std::string, FillerType> itemNameToFillerId = {
    //Native
    {"Ice Trap", IceTrap},
    {"Spring Trap", SpringTrap},
    {"Police Trap", PoliceTrap},
    {"Buyon Trap", BuyonTrap},
    {"Reverse Trap", ReverseTrap},
    {"Gravity Trap", GravityTrap},
    //Extra
    {"Reversal Trap", ReverseTrap},
    {"Confusion Trap", ReverseTrap},
    {"Confuse Trap", ReverseTrap},
    {"Freeze Trap", IceTrap},
    {"Frozen Trap", IceTrap},
    {"Paralyze Trap", IceTrap},
    {"Reversal Trap", ReverseTrap},
    {"Eject Ability", SpringTrap},
    {"Screen Flip Trap", ReverseTrap},
    {"Banana Trap", IceTrap},
    {"Army Trap", PoliceTrap},
};


FillerType ItemRepository::GetFillerFromName(const std::string& trapName)
{
    if (itemNameToFillerId.find(trapName) == itemNameToFillerId.end())
        return NoFiller;

    return itemNameToFillerId[trapName];

}

//We use the metal sonic emblems space
int ItemRepository::GetSavedItemReceived()
{
    return SaveFile.MetalEmblems;
}

void ItemRepository::UpdateItemsReceived(int itemsReceived)
{
    SaveFile.MetalEmblems = itemsReceived;
    WriteSaveFile();
}
