#include "FakeArchipelagoManager.h"
#include "SADXModLoader.h"

void FakeArchipelagoManager::OnPlayingFrame() const
{

    if (PressedButtons.empty())
        return;
    
    for (const auto& button : PressedButtons)

        if (button & WhistleButtons && Current_CharObj2 != nullptr)
        {
            //TODO: remove hardcode
            _randomizer.OnItemReceived(1);
        }
}
