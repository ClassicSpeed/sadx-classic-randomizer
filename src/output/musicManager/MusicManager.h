#pragma once
#include "../../pch.h"
#include <map>
#include <random>
#include <string>
#include <unordered_map>
#include <vector>
#include "../../application/structs/Options.h"


enum SongType
{
    Level,
    Fight,
    Theme,
    Jingle,
    Menu,
    AdventureField,
    Event
};

struct SongData
{
    int id;
    std::string codename;
    std::string name;
    SongType type;
    std::vector<std::string> possibleSADXCodenames;
    std::vector<std::string> possibleSA2BCodenames;
    std::vector<std::string> possibleCustomCodenames;
    std::string sa2Replacement;
    std::vector<int> possibleIds;

    std::vector<std::string> getAllCodenames() const
    {
        std::vector<std::string> allCodenames;
        allCodenames.insert(allCodenames.end(), possibleSADXCodenames.begin(), possibleSADXCodenames.end());
        allCodenames.insert(allCodenames.end(), possibleSA2BCodenames.begin(), possibleSA2BCodenames.end());
        allCodenames.insert(allCodenames.end(), possibleCustomCodenames.begin(), possibleCustomCodenames.end());
        return allCodenames;
    }
};

class SongMap
{
    mutable std::mt19937 gen{std::random_device{}()}; // Declare the generator as a class member

public:
    void AddSong(int id, const std::string& codename, const std::string& name, SongType type,
                 const std::vector<std::string>& possibleSADXCodenames,
                 const std::vector<std::string>& possibleSA2BCodenames,
                 const std::vector<std::string>& possibleCustomCodenames,
                 const std::string& sa2Replacement)
    {
        SongData songData = {
            id, codename, name, type, possibleSADXCodenames, possibleSA2BCodenames, possibleCustomCodenames,
            sa2Replacement, {}
        };
        _idMap[id] = songData;
        _codenameMap[codename] = id;
    }

    const SongData* FindById(int id) const
    {
        auto it = _idMap.find(id);
        if (it != _idMap.end())
        {
            return &it->second;
        }
        return nullptr;
    }

    const SongData* FindByCodename(const std::string& codename) const
    {
        auto it = _codenameMap.find(codename);
        if (it != _codenameMap.end())
        {
            auto song = &(_idMap.at(it->second));
            return song;
        }
        return nullptr;
    }

    int GetRandomSongId(const int id) const
    {
        auto it = _idMap.find(id);
        if (it == _idMap.end())
        {
            return 255; // Return an empty string if the ID is not found
        }
        const SongData& songData = it->second;
        // Combine the base codename with the filtered possible codenames
        std::vector<int> allPossibleIds;
        for (const auto& possibleId : songData.possibleIds)
        {
            allPossibleIds.push_back(possibleId);
        }

        // Generate a random index
        std::uniform_int_distribution<> dist(0, allPossibleIds.size() - 1);
        const int finalId = allPossibleIds[dist(gen)];
        const auto song = FindById(finalId);
        // Return a random codename
        return song->id;
    }

    void UpdatedIds()
    {
        for (auto& it : _idMap)
        {
            int id = it.first;
            const SongData& songData = it.second;
            for (const auto& codename : songData.getAllCodenames())
            {
                auto it2 = _codenameMap.find(codename);
                if (it2 != _codenameMap.end())
                {
                    _idMap[id].possibleIds.push_back(it2->second);
                }
            }
        }
    }

private:
    std::map<int, SongData> _idMap;
    std::unordered_map<std::string, int> _codenameMap;
};

class MusicManager
{
public:
    MusicManager();
    int GetRandomSongId(int id);
    const SongData* FindSongById(MusicIDs songId);
    void ProcessSongsFile(const HelperFunctions& helperFunctions);
    void ParseSongCategory(const HelperFunctions& helperFunctions, Json::Value categoryRoot, std::string categoryPath,
                           bool showWarningForMissingFiles);
    SongType GetSongTypeFromString(const std::string& typeStr);
    void UpdateOptions(Options newOptions);
    Options options;

private:
    SongMap _songMap;
};
