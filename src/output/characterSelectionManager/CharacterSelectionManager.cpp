#include "CharacterSelectionManager.h"
#include "SADXModLoader.h"

void CharacterSelectionManager::Unlock(int eventAddress)
{
    if (GameMode == GameModes_Menu)
        SetEventFlag(static_cast<EventFlags>(eventAddress));
}

void CharacterSelectionManager::Lock(int eventAddress)
{
    if (GameMode == GameModes_Menu)
        ClearEventFlag(static_cast<EventFlags>(eventAddress));
}
