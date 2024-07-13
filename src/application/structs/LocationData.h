#pragma once
#include <string>
#include <unordered_map>
#include "../../pch.h"

enum LocationType
{
    LocationUpgrade,
    LocationLevel,
    LocationSubLevel,
    LocationFieldEmblem,
    LocationUnknown
};

struct LocationData
{
    LocationData() : eventFlag(static_cast<StoryFlags>(0x00)), character(0), level(0), mission(0), emblemId(0),
                     type(LocationUnknown),
                     checked(false),
                     displayName(std::string("Unknown")),
                     originalItemId(-1)
    {
    }

    LocationData(const StoryFlags eventFlag, const int character, const int level, const int mission,
                 const int emblemId, const LocationType type, const bool checked, const std::string& displayName,
                 const int originalItemId)
        : eventFlag(eventFlag),
          character(character),
          level(level),
          mission(mission),
          emblemId(emblemId),
          type(type),
          checked(checked),
          displayName(displayName),
          originalItemId(originalItemId)
    {
    }

    static LocationData UpgradeLocation(StoryFlags eventFlag, const std::string& displayName, const int originalItemId)
    {
        return LocationData(eventFlag, -1, -1, -1, -1, LocationUpgrade, false, displayName, originalItemId);
    }

    static LocationData LevelLocation(const int character, const int level, const int mission)
    {
        return LocationData(static_cast<StoryFlags>(0x0), character, level, mission, -1, LocationLevel, false,
                            std::to_string(character) + std::to_string(level) + std::to_string(mission), -1);
    }

    static LocationData SubLevelLocation(const int level, const int mission)
    {
        return LocationData(static_cast<StoryFlags>(0x0), -1, level, mission, -1, LocationSubLevel, false,
                            std::to_string(level) + std::to_string(mission), -1);
    }

    static LocationData FieldEmblemLocation(const int emblemId, const std::string& displayName)
    {
        return LocationData(static_cast<StoryFlags>(0x0), -1, -1, -1, emblemId, LocationFieldEmblem, false, displayName,
                            -1);
    }


    StoryFlags eventFlag;

    int character;
    int level;
    int mission;

    int emblemId;

    LocationType type;
    bool checked;
    std::string displayName;
    int originalItemId;
};
