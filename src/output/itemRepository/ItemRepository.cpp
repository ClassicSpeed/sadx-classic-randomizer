#include "ItemRepository.h"


ItemRepository::ItemRepository()
{
    _itemData = {
        // {1, ItemData(EventFlags_SonicUnlockedAdventure, ItemCharacter, "Story unlock (Sonic)")},
        {2, ItemData(EventFlags_TailsUnlockedAdventure, ItemCharacter, "Story unlock (Tails)")},
        {3, ItemData(EventFlags_KnucklesUnlockedAdventure, ItemCharacter, "Story unlock (Knuckles)")},
        {4, ItemData(EventFlags_AmyUnlockedAdventure, ItemCharacter, "Story unlock (Amy)")},
        {5, ItemData(EventFlags_GammaUnlockedAdventure, ItemCharacter, "Story unlock (Gamma)")},
        {6, ItemData(EventFlags_BigUnlockedAdventure, ItemCharacter, "Story unlock (Big)")},


        {10, ItemData(Upgrades_LightShoes, ItemUpgrade, "Light shoes (Sonic)")},
        {11, ItemData(Upgrades_CrystalRing, ItemUpgrade, "Crystal ring (Sonic)")},
        {12, ItemData(Upgrades_AncientLight, ItemUpgrade, "Ancient light (Sonic)")},

        {20, ItemData(Upgrades_JetAnklet, ItemUpgrade, "Jet Ankle (Tails)")},
        {21, ItemData(Upgrades_RhythmBadge, ItemUpgrade, "Rhythm Badge (Tails)")},

        {30, ItemData(Upgrades_ShovelClaw, ItemUpgrade, "Shovel claw (Knuckles)")},
        {31, ItemData(Upgrades_FightingGloves, ItemUpgrade, "Fighting gloves (Knuckles)")},

        {40, ItemData(Upgrades_LongHammer, ItemUpgrade, "Long Hammer (Amy)")},
        {41, ItemData(Upgrades_WarriorFeather, ItemUpgrade, "Warrior feather (Amy)")},

        {50, ItemData(Upgrades_LaserBlaster, ItemUpgrade, "Laser Blaster (Gamma)")},
        {51, ItemData(Upgrades_JetBooster, ItemUpgrade, "Jet booster (Gamma)")},

        {60, ItemData(Upgrades_LifeRing, ItemUpgrade, "Life belt (Big)")},
        {61, ItemData(Upgrades_PowerRod, ItemUpgrade, "Power rod (Big)")},

        {90, ItemData(0, ItemEmblem, "Emblem)")},
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
    
    unlockStatus.sonicUnlocked = true;
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
    unlockStatus.gammaLaserBlasterUnlocked = _itemData[50].obtained;
    unlockStatus.gammaJetBoosterUnlocked = _itemData[51].obtained;

    unlockStatus.bigUnlocked = _itemData[6].obtained;
    unlockStatus.bigLifeRingUnlocked = _itemData[60].obtained;
    unlockStatus.bigPowerRodUnlocked = _itemData[61].obtained;
    return unlockStatus;
}
