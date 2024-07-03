#pragma once
#include <string>
#include "../../pch.h"

struct LocationData
{
    LocationData() : eventFlag(static_cast<EventFlags>(0x00)),
                     checked(false),
                     displayName(std::string("Unknown")),
                     originalItemId(-1)
    {
    }

    LocationData(const EventFlags eventFlag, std::string displayName, int originalItemId) :
        eventFlag(eventFlag),
        checked(false),
        displayName(displayName),
        originalItemId(originalItemId)
    {
    }

    EventFlags eventFlag;
    bool checked;
    std::string displayName;
    int originalItemId;
};
