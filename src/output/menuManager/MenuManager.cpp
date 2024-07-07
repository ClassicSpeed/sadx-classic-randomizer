#include "MenuManager.h"

#include "../../pch.h"




void MenuManager::UnlockCharacterSelection(int eventAddress)
{
    if (GameMode == GameModes_Menu)
        SetEventFlag(static_cast<EventFlags>(eventAddress));
}

void MenuManager::LockCharacterSelection(int eventAddress)
{
    if (GameMode == GameModes_Menu)
        ClearEventFlag(static_cast<EventFlags>(eventAddress));
}
