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
    LocationBossFight,
    LocationMission,
    LocationChaoEgg,
    LocationChaoRace,
    LocationEnemy,
    LocationCapsule,
    LocationUnknown
};


enum CapsuleType
{
    SpeedUpCapsule, InvincibilityCapsule, FiveRingsCapsule, TenRingsCapsule, RandomRingsCapsule, ShieldCapsule,
    ExtraLifeCapsule, EnemyBombCapsule, MagneticShieldCapsule
};

enum EnemyType
{
    BoaBoa,
    Buyon,
    CopSpeeder,
    ElectroSpinner,
    EggKeeper,
    Gola,
    IceBall,
    KartKiki,
    Kiki,
    Leon,
    Rhinotank,
    Spinner,
    Sweep,
    SpikySpinner
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

struct EnemyLocationData
{
    float x;
    float y;
    float z;
    LevelAndActIDs level;
    Characters character;
    EnemyType enemyType;
    int locationId;
};

struct CapsuleLocationData
{
    float x;
    float y;
    float z;
    LevelAndActIDs level;
    Characters character;
    CapsuleType capsuleType;
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
                 const std::string& displayName, const int originalItemId, const int capsuleType, const int enemyType)
        : eventFlag(eventFlag),
          character(character),
          level(level),
          mission(mission),
          emblemId(emblemId),
          missionNumber(missionNumber),
          type(type),
          checked(checked),
          displayName(displayName),
          originalItemId(originalItemId),
          capsuleType(capsuleType),
          enemyType(enemyType)
    {
    }

    static LocationData UpgradeLocation(StoryFlags eventFlag, const std::string& displayName, const int originalItemId)
    {
        return LocationData(eventFlag, -1, -1, -1, -1, -1, LocationUpgrade, false, displayName, originalItemId, -1, -1);
    }

    static LocationData LevelLocation(const int character, const int level, const int mission)
    {
        return LocationData(static_cast<StoryFlags>(0x0), character, level, mission, -1, -1, LocationLevel, false,
                            std::to_string(character) + std::to_string(level) + std::to_string(mission), -1, -1, -1);
    }

    static LocationData SubLevelLocation(const int level, const int mission)
    {
        return LocationData(static_cast<StoryFlags>(0x0), -1, level, mission, -1, -1, LocationSubLevel, false,
                            std::to_string(level) + std::to_string(mission), -1, -1, -1);
    }

    static LocationData FieldEmblemLocation(const int emblemId, const std::string& displayName)
    {
        return LocationData(static_cast<StoryFlags>(0x0), -1, -1, -1, emblemId, -1, LocationFieldEmblem, false,
                            displayName, -1, -1, -1);
    }


    static LocationData BossFightLocation(const int character, const int level)
    {
        return LocationData(static_cast<StoryFlags>(0x0), character, level, -1, -1, -1, LocationBossFight, false,
                            std::to_string(character) + std::to_string(level), -1, -1, -1);
    }

    static LocationData MissionLocation(const int character, const int missionNumber)
    {
        return LocationData(static_cast<StoryFlags>(0x0), character, -1, -1, -1, missionNumber, LocationMission, false,
                            "Mission " + std::to_string(missionNumber), -1, -1, -1);
    }


    static LocationData ChaoEggLocation(const StoryFlags eventFlag, const std::string& displayName)
    {
        return LocationData(eventFlag, -1, -1, -1, -1, -1, LocationChaoEgg, false,
                            displayName, -1, -1, -1);
    }

    static LocationData ChaoRaceLocation(const int emblemId, const std::string& displayName)
    {
        return LocationData(static_cast<StoryFlags>(0x0), -1, -1, -1, emblemId, -1, LocationChaoRace, false,
                            displayName, -1, -1, -1);
    }


    static LocationData EnemyLocation(const EnemyLocationData& enemy)
    {
        return LocationData(static_cast<StoryFlags>(0x0), enemy.character, enemy.level, -1, -1, -1, LocationEnemy,
                            false,
                            "Enemy " + std::to_string(enemy.character) + " - " + std::to_string(enemy.level), -1, -1,
                            enemy.enemyType);
    }

    static LocationData CapsuleLocation(const CapsuleLocationData& capsule)
    {
        return LocationData(static_cast<StoryFlags>(0x0), capsule.character, capsule.level, -1, -1, -1, LocationCapsule,
                            false,
                            "Enemy " + std::to_string(capsule.character) + " - " + std::to_string(capsule.level), -1,
                            capsule.capsuleType, -1);
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
    int capsuleType;
    int enemyType;
};
