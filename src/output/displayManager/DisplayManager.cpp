#include "DisplayManager.h"
#include "SADXModLoader.h"


void DisplayManager::FoundItem(std::string displayName)
{
    PrintDebug("  << Found the check: %s\n", displayName.c_str());
}

void DisplayManager::ReceiveItem(std::string displayName)
{
    PrintDebug("  >> Received the item: %s\n", displayName.c_str());
}
