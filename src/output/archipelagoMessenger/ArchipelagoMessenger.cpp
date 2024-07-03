#include "ArchipelagoMessenger.h"
#include "../../pch.h"
constexpr int64_t BASE_ID = 5438000;

void ArchipelagoMessenger::CheckLocation(const int locationId)
{
    AP_SendItem(BASE_ID + locationId);
}

void ArchipelagoMessenger::GameCompleted()
{
    AP_StoryComplete();
}
