#pragma once
#include "../../pch.h"
#include <map>
#include <random>
#include <string>
#include <unordered_map>
#include <vector>

struct SongData
{
    int id;
    std::string codename;
    std::string fullName;
    std::vector<std::string> possibleCodenames;
};


class SongMap
{
    mutable std::mt19937 gen{std::random_device{}()}; // Declare the generator as a class member

public:
    void AddSong(int id, const std::string& codename, const std::string& fullName,
                 const std::vector<std::string>& possibleCodenames)
    {
        SongData songData = {id, codename, fullName, possibleCodenames};
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
        std::vector<std::string> allCodenames;
        for (const auto& codename : songData.possibleCodenames)
        {
            if (!codename.empty())
            {
                allCodenames.push_back(codename);
            }
        }
        allCodenames.push_back(songData.codename);

        // Generate a random index
        std::uniform_int_distribution<> dist(0, allCodenames.size() - 1);

        const auto song = FindByCodename(allCodenames[dist(gen)]);
        // Return a random codename
        return song->id;
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

private:    
    void ProcessSongFile();
    SongMap _songMap;
};
