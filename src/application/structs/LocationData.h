#pragma once
#include <string>
#include <unordered_map>
#include "../../pch.h"

enum LocationType
{
    LocationUpgrade,
    LocationCharacter,
    LocationLevel,
    LocationUnknown
};

struct LocationData
{
    LocationData() : address(0x00),
                     type(LocationUnknown),
                     checked(false),
                     displayName(std::string("Unknown")),
                     originalItemId(-1)
    {
    }

    LocationData(const int eventFlag, LocationType type, std::string displayName, int originalItemId) :
        address(eventFlag),
        type(type),
        checked(false),
        displayName(displayName),
        originalItemId(originalItemId)
    {
    }


    int address;
    LocationType type;
    bool checked;
    std::string displayName;
    int originalItemId;
};
