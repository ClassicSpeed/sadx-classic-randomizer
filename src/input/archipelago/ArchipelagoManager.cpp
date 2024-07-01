#include "ArchipelagoManager.h"
#include "Archipelago.h"


void ArchipelagoManager::OnFrame() const
{
    //Check savefile

    //Check mod version

    //Connect?
    if (!_connected)
    {
        this->Connect();
    }
}


void SADX_ResetItems()
{
    //apm->ResetItems();
    PrintDebug("Reset items\n");
}

void SADX_RecvItem(int64_t item_id, bool notify)
{
    // apm->ReceiveItem(item_id, notify);
    PrintDebug("Recived item %d\n", item_id);
}

void SADX_CheckLocation(int64_t loc_id)
{
    // apm->CheckLocation(loc_id);
    PrintDebug("Checked location %d\n", loc_id);
}

void ArchipelagoManager::Connect() const
{
    AP_Init("localhost", "Sonic Adventure DX", "Classic", "");
    AP_SetItemClearCallback(&SADX_ResetItems);
    AP_SetItemRecvCallback(&SADX_RecvItem);
    AP_SetLocationCheckedCallback(&SADX_CheckLocation);
    AP_Start();
}
