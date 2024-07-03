#include "MenuManager.h"

#include "FunctionHook.h"
#include "SADXModLoader.h"


MenuManager::MenuManager()
{
    FunctionHook<BOOL> blockTrialMenu(0x506780, []() -> BOOL { return false; });
    FunctionHook<BOOL> blockMissionMenu(0x506410, []() -> BOOL { return false; });
}

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
