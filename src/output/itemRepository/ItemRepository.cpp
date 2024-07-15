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


        {10, ItemData::UpgradeItem(Upgrades_LightShoes, "Light shoes (Sonic)")},
        {11, ItemData::UpgradeItem(Upgrades_CrystalRing, "Crystal ring (Sonic)")},
        {12, ItemData::UpgradeItem(Upgrades_AncientLight, "Ancient light (Sonic)")},

        {20, ItemData::UpgradeItem(Upgrades_JetAnklet, "Jet Ankle (Tails)")},
        {21, ItemData::UpgradeItem(Upgrades_RhythmBadge, "Rhythm Badge (Tails)")},

        {30, ItemData::UpgradeItem(Upgrades_ShovelClaw, "Shovel claw (Knuckles)")},
        {31, ItemData::UpgradeItem(Upgrades_FightingGloves, "Fighting gloves (Knuckles)")},

        {40, ItemData::UpgradeItem(Upgrades_WarriorFeather, "Warrior feather (Amy)")},
        {41, ItemData::UpgradeItem(Upgrades_LongHammer, "Long Hammer (Amy)")},

        {50, ItemData::UpgradeItem(Upgrades_JetBooster, "Jet booster (Gamma)")},
        {51, ItemData::UpgradeItem(Upgrades_LaserBlaster, "Laser Blaster (Gamma)")},

        {60, ItemData::UpgradeItem(Upgrades_LifeRing, "Life belt (Big)")},
        {61, ItemData::UpgradeItem(Upgrades_PowerRod, "Power rod (Big)")},
        //TODO: Add lures
        // {62, ItemData::UpgradeItem(static_cast<Upgrades>(0), "Lure 1 (Big)")},
        // {63, ItemData::UpgradeItem(static_cast<Upgrades>(0), "Lure 2 (Big)")},
        // {64, ItemData::UpgradeItem(static_cast<Upgrades>(0), "Lure 3 (Big)")},
        // {65, ItemData::UpgradeItem(static_cast<Upgrades>(0), "Lure 4 (Big)")},
\
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
        {
            83, ItemData::KeyItem({
                                      FLAG_SONIC_SS_HOTEL_FRONT, FLAG_MILES_SS_HOTEL_FRONT,
                                      FLAG_KNUCKLES_SS_HOTEL_FRONT, FLAG_AMY_SS_HOTEL_FRONT,
                                      FLAG_E102_SS_HOTEL_FRONT, FLAG_BIG_SS_HOTEL_FRONT, FLAG_BIG_SS_HOTEL_POOL
                                  }, "Hotel Keys")
        },
        {
            84, ItemData::KeyItem({
                                      FLAG_SONIC_SS_STATION_BACK, FLAG_MILES_SS_STATION_BACK,
                                      FLAG_KNUCKLES_SS_STATION_BACK, FLAG_AMY_SS_STATION_BACK
                                  }, "Casino District Keys")
        },
        {
            85, ItemData::KeyItem({
                                      FLAG_SONIC_SS_TPARK_ELEVATOR, FLAG_SONIC_SS_ENTRANCE_CIRCUIT,
                                      FLAG_MILES_SS_CARTPASSPORT,
                                      FLAG_KNUCKLES_SS_CARTPASSPORT,
                                      FLAG_AMY_SS_TPARK_ELEVATOR, FLAG_AMY_SS_ENTRANCE_CIRCUIT,
                                      FLAG_E102_SS_CARTPASSPORT,
                                      /*FLAG_BIG_SS_TPARK_ELEVATOR,*/ FLAG_BIG_SS_ENTRANCE_CIRCUIT,
                                  }, "Twinkle Park Ticket")
        },
        {86, ItemData::KeyItem({FLAG_SONIC_SS_CARD, FLAG_MILES_SS_ENTRANCE_HIGHWAY}, "Employee Card")},
        {87, ItemData::KeyItem({FLAG_SONIC_SS_ICESTONE, FLAG_MILES_SS_ICESTONE, FLAG_BIG_SS_ICESTONE}, "Ice Stone")},
        {
            88, ItemData::KeyItem({
                                      FLAG_SONIC_MR_WESTROCK, FLAG_MILES_MR_WESTROCK, FLAG_KNUCKLES_MR_WESTROCK,
                                      FLAG_E102_MR_WESTROCK, FLAG_BIG_MR_WESTROCK,
                                      FLAG_SONIC_MR_ISLANDDOOR, FLAG_KNUCKLES_MR_ISLANDDOOR,
                                      FLAG_AMY_MR_ISLANDDOOR, FLAG_E102_MR_ISLANDDOOR
                                  }, "Dynamite")
        },
        {
            89, ItemData::KeyItem({
                                      FLAG_SONIC_MR_TRUCK, FLAG_MILES_MR_TRUCK, FLAG_KNUCKLES_MR_TRUCK,
                                      FLAG_AMY_MR_TRUCK, FLAG_E102_MR_TRUCK, FLAG_BIG_MR_TRUCK
                                  }, "Jungle Kart")
        },

        {90, ItemData::EmblemItem("Emblem")},
    };
}


ItemData ItemRepository::SetObtained(const int64_t itemId)
{
    _itemData[itemId].obtained = true;
    return _itemData[itemId];
}

ItemData ItemRepository::GetItem(const int itemId)
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


int ItemRepository::GetEmblemGoal() const
{
    return _emblemGoal;
}

void ItemRepository::SetEmblemGoal(int emblemGoal)
{
    _emblemGoal = emblemGoal;
}


UnlockStatus ItemRepository::GetUnlockStatus()
{
    auto unlockStatus = UnlockStatus();

    unlockStatus.currentEmblems = _emblemCount;
    unlockStatus.emblemGoal = _emblemGoal;

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
    unlockStatus.amyLongHammerUnlocked = _itemData[40].obtained;
    unlockStatus.amyWarriorFeatherUnlocked = _itemData[41].obtained;

    unlockStatus.gammaUnlocked = _itemData[5].obtained;
    unlockStatus.gammaJetBoosterUnlocked = _itemData[50].obtained;
    unlockStatus.gammaLaserBlasterUnlocked = _itemData[51].obtained;

    unlockStatus.bigUnlocked = _itemData[6].obtained;
    unlockStatus.bigLifeRingUnlocked = _itemData[60].obtained;
    unlockStatus.bigPowerRodUnlocked = _itemData[61].obtained;


    unlockStatus.keyTrain = _itemData[80].obtained;
    unlockStatus.keyBoat = _itemData[81].obtained;
    unlockStatus.keyRaft = _itemData[82].obtained;
    unlockStatus.keyHotelKeys = _itemData[83].obtained;
    unlockStatus.keyCasinoKeys = _itemData[84].obtained;
    unlockStatus.keyTwinkleParkTicket = _itemData[85].obtained;
    unlockStatus.keyEmployeeCard = _itemData[86].obtained;
    unlockStatus.keyIceStone = _itemData[87].obtained;
    unlockStatus.keyDynamite = _itemData[88].obtained;
    unlockStatus.jungleKart = _itemData[89].obtained;
    return unlockStatus;
}
