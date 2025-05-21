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

enum SongSource
{
    SADXSource,
    SA2BSource,
    CustomSource
};

struct SongData
{
    int id;
    std::string codename;
    std::string name;
    SongType type;
    SongSource source;
    std::vector<std::string> possibleSADXCodenames;
    std::vector<std::string> possibleSA2BCodenames;
    std::vector<std::string> possibleCustomCodenames;
    std::string sa2Replacement;

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
public:
    void AddSong(int id, const std::string& codename, const std::string& name, SongType type, SongSource source,
                 const std::vector<std::string>& possibleSADXCodenames,
                 const std::vector<std::string>& possibleSA2BCodenames,
                 const std::vector<std::string>& possibleCustomCodenames,
                 const std::string& sa2Replacement)
    {
        SongData songData = {
            id, codename, name, type, source, possibleSADXCodenames, possibleSA2BCodenames, possibleCustomCodenames,
            sa2Replacement
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

    std::vector<int> GetSa2Song(const int id) const
    {
        const auto songData = FindById(id);
        if (songData == nullptr)
            return {id};

        const auto sa2SongData = FindByCodename(songData->sa2Replacement);
        if (sa2SongData == nullptr)
            return {id};
        
        return {sa2SongData->id};
    }

    std::vector<int> GetCuratedSongs(const int id, const Options options) const
    {
        std::vector<int> allPossibleIds = {};

        const auto songData = FindById(id);

        if (options.MusicSourceIncludeSadx())
        {
            for (const auto& possibleCodename : songData->possibleSADXCodenames)
            {
                const auto possibleSongData = FindByCodename(possibleCodename);
                if (possibleSongData != nullptr)
                    allPossibleIds.push_back(possibleSongData->id);
            }
        }
        else if (options.MusicSourceIncludeSa2B())
        {
            for (const auto& possibleCodename : songData->possibleSA2BCodenames)
            {
                const auto possibleSongData = FindByCodename(possibleCodename);
                if (possibleSongData != nullptr)
                    allPossibleIds.push_back(possibleSongData->id);
            }
        }
        else if (options.MusicSourceIncludeCustom())
        {
            for (const auto& possibleCodename : songData->possibleCustomCodenames)
            {
                const auto possibleSongData = FindByCodename(possibleCodename);
                if (possibleSongData != nullptr)
                    allPossibleIds.push_back(possibleSongData->id);
            }
        }
        return allPossibleIds;
    }

    std::vector<int> GetSongsByType(const SongType songType)
    {
        return _songsByType[songType];
    }

    std::vector<int> GetAllSongs(const bool isJingle)
    {
        if (isJingle)
            return _allJingles;

        return _allSongs;
    }

    void UpdateSongLists(const Options& options)
    {
        for (const auto& song : _idMap)
        {
            if (song.second.source == SADXSource && !options.MusicSourceIncludeSadx())
                continue;
            if (song.second.source == SA2BSource && !options.MusicSourceIncludeSa2B())
                continue;
            if (song.second.source == CustomSource && !options.MusicSourceIncludeCustom())
                continue;

            _songsByType[song.second.type].push_back(song.first);
            if (song.second.type == Jingle)
                _allJingles.push_back(song.first);
            else
                _allSongs.push_back(song.first);
        }
    }

private:
    std::map<int, SongData> _idMap;
    std::unordered_map<std::string, int> _codenameMap;

    std::unordered_map<SongType, std::vector<int>> _songsByType;
    std::vector<int> _allSongs;
    std::vector<int> _allJingles;
};

class MusicManager
{
public:
    MusicManager();
    const SongData* FindSongById(int songId);
    void ProcessSongsFile(const HelperFunctions& helperFunctions);
    void ParseSongCategory(const HelperFunctions& helperFunctions, Json::Value categoryRoot, std::string categoryPath,
                           SongSource songSource);
    SongType GetSongTypeFromString(const std::string& typeStr);
    void UpdateOptions(Options newOptions);
    void RandomizeMusic();
    std::vector<int> GetPossibleSongIds(int id);
    int GetSingularitySong();
    int GetSongForId(int songId);

private:
    Options _options;
    SongMap _songMap;
    std::unordered_map<int, std::vector<int>> _songRandomizationMap;
};
