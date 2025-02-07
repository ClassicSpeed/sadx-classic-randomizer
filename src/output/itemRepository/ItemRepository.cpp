#include "ItemRepository.h"


ItemRepository::ItemRepository()
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
        {83, ItemData::KeyItem({}, "Hotel Front Keys")},
        {84, ItemData::KeyItem({}, "Hotel Back Keys")},
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
        {121, ItemData::KeyItem({}, "Station Front Keys")},
        {122, ItemData::KeyItem({}, "Station Back Keys")},
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


UnlockStatus ItemRepository::GetUnlockStatus()
{
    auto unlockStatus = UnlockStatus();

    unlockStatus.currentEmblems = _emblemCount;

    unlockStatus.whiteEmerald = _itemData[92].obtained;
    unlockStatus.redEmerald = _itemData[93].obtained;
    unlockStatus.cyanEmerald = _itemData[94].obtained;
    unlockStatus.purpleEmerald = _itemData[95].obtained;
    unlockStatus.greenEmerald = _itemData[96].obtained;
    unlockStatus.yellowEmerald = _itemData[97].obtained;
    unlockStatus.blueEmerald = _itemData[98].obtained;

    unlockStatus.sonicUnlocked = _itemData[1].obtained;
    unlockStatus.sonicLightShoesUnlocked = _itemData[10].obtained;
    unlockStatus.sonicCrystalRingUnlocked = _itemData[11].obtained;
    unlockStatus.sonicAncientLightUnlocked = _itemData[12].obtained;

    unlockStatus.tailsUnlocked = _itemData[2].obtained;
    unlockStatus.tailsJetAnkletUnlocked = _itemData[20].obtained;
    unlockStatus.tailsRhythmBadgeUnlocked = _itemData[21].obtained;

    unlockStatus.knucklesUnlocked = _itemData[3].obtained;
    unlockStatus.knucklesShovelClawUnlocked = _itemData[30].obtained;
    unlockStatus.knucklesFightingGlovesUnlocked = _itemData[31].obtained;

    unlockStatus.amyUnlocked = _itemData[4].obtained;
    unlockStatus.amyWarriorFeatherUnlocked = _itemData[40].obtained;
    unlockStatus.amyLongHammerUnlocked = _itemData[41].obtained;

    unlockStatus.gammaUnlocked = _itemData[5].obtained;
    unlockStatus.gammaJetBoosterUnlocked = _itemData[50].obtained;
    unlockStatus.gammaLaserBlasterUnlocked = _itemData[51].obtained;

    unlockStatus.bigUnlocked = _itemData[6].obtained;
    unlockStatus.bigLifeBeltUnlocked = _itemData[60].obtained;
    unlockStatus.bigPowerRodUnlocked = _itemData[61].obtained;
    unlockStatus.bigLureQuantity = _itemData[62].obtained + _itemData[63].obtained + _itemData[64].obtained + _itemData[
        65].obtained;


    unlockStatus.keyTrain = _itemData[80].obtained;
    unlockStatus.keyBoat = _itemData[81].obtained;
    unlockStatus.keyRaft = _itemData[82].obtained;
    unlockStatus.keyHotelFrontKeys = _itemData[83].obtained;
    unlockStatus.keyHotelBackKeys = _itemData[84].obtained;
    unlockStatus.keyTwinkleParkTicket = _itemData[85].obtained;
    unlockStatus.keyEmployeeCard = _itemData[86].obtained;
    unlockStatus.keyIceStone = _itemData[87].obtained;
    unlockStatus.keyWindStone = _itemData[120].obtained;
    unlockStatus.keyDynamite = _itemData[88].obtained;
    unlockStatus.keyJungleCart = _itemData[89].obtained;
    unlockStatus.keyStationFrontKeys = _itemData[121].obtained;
    unlockStatus.keyStationBackKeys = _itemData[122].obtained;
    unlockStatus.keyEgglift = _itemData[123].obtained;
    unlockStatus.keyMonorail = _itemData[124].obtained;
    return unlockStatus;
}

void ItemRepository::ResetItems()
{
    _emblemCount = 0;
    _itemsReceived = 0;
    for (auto& item : _itemData)
    {
        item.second.obtained = false;
    }
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
