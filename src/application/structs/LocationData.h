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
    LocationLifeCapsule,
    LocationBossFight,
    LocationMission,
    LocationUnknown
};

struct LifeBoxLocationData
{
    float x;
    float y;
    float z;
    LevelAndActIDs level;
    Characters character;
    int locationId;
};

struct LocationData
{
    LocationData() : eventFlag(static_cast<StoryFlags>(0x00)),
                     character(0),
                     level(0),
                     mission(0),
                     emblemId(0),
                     missionNumber(0),
                     type(LocationUnknown),
                     checked(false),
                     displayName(std::string("Unknown")),
                     originalItemId(-1)
    {
    }

    LocationData(const StoryFlags eventFlag, const int character, const int level, const int mission,
                 const int emblemId, const int missionNumber, const LocationType type, const bool checked,
                 const std::string& displayName,
                 const int originalItemId)
        : eventFlag(eventFlag),
          character(character),
          level(level),
          mission(mission),
          emblemId(emblemId),
          missionNumber(missionNumber),
          type(type),
          checked(checked),
          displayName(displayName),
          originalItemId(originalItemId)
    {
    }

    static LocationData UpgradeLocation(StoryFlags eventFlag, const std::string& displayName, const int originalItemId)
    {
        return LocationData(eventFlag, -1, -1, -1, -1, -1, LocationUpgrade, false, displayName, originalItemId);
    }

    static LocationData LevelLocation(const int character, const int level, const int mission)
    {
        return LocationData(static_cast<StoryFlags>(0x0), character, level, mission, -1, -1, LocationLevel, false,
                            std::to_string(character) + std::to_string(level) + std::to_string(mission), -1);
    }

    static LocationData SubLevelLocation(const int level, const int mission)
    {
        return LocationData(static_cast<StoryFlags>(0x0), -1, level, mission, -1, -1, LocationSubLevel, false,
                            std::to_string(level) + std::to_string(mission), -1);
    }

    static LocationData FieldEmblemLocation(const int emblemId, const std::string& displayName)
    {
        return LocationData(static_cast<StoryFlags>(0x0), -1, -1, -1, emblemId, -1, LocationFieldEmblem, false,
                            displayName,
                            -1);
    }

    static LocationData LifeCapsuleLocation(const LifeBoxLocationData& lifeCapsule)
    {
        return LocationData(static_cast<StoryFlags>(0x0), lifeCapsule.character, lifeCapsule.level, -1, -1, -1,
                            LocationLifeCapsule, false,
                            "Life Capsule " + std::to_string(lifeCapsule.character) + " - " + std::to_string(
                                lifeCapsule.level), -1);
    }

    static LocationData BossFightLocation(const int character, const int level)
    {
        return LocationData(static_cast<StoryFlags>(0x0), character, level, -1, -1, -1, LocationBossFight, false,
                            std::to_string(character) + std::to_string(level), -1);
    }

    static LocationData MissionLocation(const int character, const int missionNumber)
    {
        return LocationData(static_cast<StoryFlags>(0x0), character, -1, -1, -1, missionNumber, LocationMission, false,
                            "Mission " + std::to_string(missionNumber), -1);
    }

    StoryFlags eventFlag;

    int character;
    int level;
    int mission;

    int emblemId;
    int missionNumber;

    LocationType type;
    bool checked;
    std::string displayName;
    int originalItemId;
};
