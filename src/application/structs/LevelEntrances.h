#pragma once
#include "../../pch.h"
#include <map>
#include "../../application/structs/Options.h"

// Define a struct to hold the key
struct CharacterLevelKey
{
    int character;
    Levels level;

    // Implement the operator< for std::map
    bool operator<(const CharacterLevelKey& other) const
    {
        if (character != other.character)
            return character < other.character;
        return level < other.level;
    }
};



class LevelEntrances
{
public:
    LevelEntrances();
    LevelEntrances(const std::initializer_list<std::pair<Levels, Levels>> pairs);
    void addRelationship(const Levels levelEntrance, const Levels actualLevel);
    Levels getLevelFromEntrance(const Levels entrance) const;
    LevelAndActIDs getLevelAndActIdFromEntrance(const Levels entrance, const int characters) const;
    Levels getEntranceFromLevel(const Levels level) const;
    LevelIDs getEntranceLevelIdFromLevel(const LevelIDs currentLevel) const;
    bool canEnter(const Levels levelEntrance, const short currentCharacter);
    static LevelIDs ConvertLevelsToLevelIDs(const Levels level);
    static Levels ConvertLevelIDsToLevel(const LevelIDs levelIdS);
    static int transformToHex(const LevelIDs levelId);

private:
    std::map<Levels, Levels> _entranceToLevel;
    std::map<Levels, Levels> _levelToEntrance;
};
