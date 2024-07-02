#include "CharacterSelectionManager.h"
#include "SADXModLoader.h"

void CharacterSelectionManager::Unlock(int eventAddress)
{
    SetEventFlag(static_cast<EventFlags>(eventAddress));
}

void CharacterSelectionManager::Lock(int eventAddress)
{
    ClearEventFlag(static_cast<EventFlags>(eventAddress));
}
