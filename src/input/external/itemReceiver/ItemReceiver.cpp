#include "ItemReceiver.h"
#include "SADXModLoader.h"

void ItemReceiver::OnPlayingFrame() const
{

    if (PressedButtons.empty())
        return;
    
    for (const auto& button : PressedButtons)

        if (button & WhistleButtons && Current_CharObj2 != nullptr)
        {
            //TODO: remove hardcode
            _randomizer.OnItemReceived(Upgrades_RhythmBadge, "Tails' Rhythm Badge");
        }
}
