#pragma once
#include <string>
#include "SADXModLoader.h"

struct CheckData
{
    CheckData() : eventFlag(static_cast<EventFlags>(0x00)),
                  checked(false),
                  displayName(std::string("Unknown")),
                  originalItemId(-1)
    {
    }

    CheckData(const EventFlags eventFlag, std::string displayName, int originalItemId) :
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