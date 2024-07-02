#include "ArchipelagoManager.h"
#include "Archipelago.h"

constexpr int64_t BASE_ID = 5438000;
Randomizer* randomizerPtr = nullptr;

ArchipelagoManager::ArchipelagoManager(Randomizer& randomizer)
    : _randomizer(randomizer)
{
    randomizerPtr = &this->_randomizer;
}

void ArchipelagoManager::OnFrame()
{
    //TODO: Check savefile

    //TODO: Check mod version

    //TODO: Check connection lost

    if (!_connected)
    {
        this->Connect();
    }
}


void SADX_RecvItem(const int64_t itemId, bool notify)
{
    randomizerPtr->OnItemReceived(itemId - BASE_ID);
    
}

void SADX_ResetItems()
{
    //TODO: Do something?
    PrintDebug("Reset items\n");
}

void SADX_CheckLocation(int64_t loc_id)
{
    //TODO: Do something?
    PrintDebug("Checked location %d\n", loc_id);
}

void ArchipelagoManager::Connect()
{
    //TODO: Get settings from configuration
    AP_Init("archipelago.gg:49288", "Sonic Adventure DX", "Classic", "");
    AP_SetItemClearCallback(&SADX_ResetItems);
    AP_SetItemRecvCallback(&SADX_RecvItem);
    AP_SetLocationCheckedCallback(&SADX_CheckLocation);
    AP_Start();
    _connected = true;
}
