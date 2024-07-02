#include "ItemRepository.h"
#include "SADXModLoader.h"


ItemRepository::ItemRepository()
{
    _itemData = {
        {1, ItemData(EventFlags_SonicUnlockedAdventure, ItemCharacter, "Story unlock (Sonic)")},
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
