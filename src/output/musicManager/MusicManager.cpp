#include "MusicManager.h"
#include <fstream>
#include "json/json.h"

MusicManager::MusicManager()
{
}

int MusicManager::GetRandomSongId(int id)
{
    return _songMap.GetRandomSongId(id);
}

const SongData* MusicManager::FindSongById(MusicIDs songId)
{
    return _songMap.FindById(songId);
}

void MusicManager::ProcessSongsFile(const HelperFunctions& helperFunctions)
{
    // TODO: Fix
    this->ProcessSongFile(
        "C:/development/workspaces/sadx-classic-randomizer/assets/SADX_Archipelago/songs.json", helperFunctions);
}


void MusicManager::ProcessSongFile(const std::string& filePath, const HelperFunctions& helperFunctions)
{
    // Open the JSON file
    std::ifstream file(filePath, std::ifstream::binary);
    if (!file.is_open())
    {
        throw std::runtime_error("Failed to open file: " + filePath);
    }

    // Parse the JSON file
    Json::Value root;
    Json::CharReaderBuilder builder;
    std::string errs;
    if (!Json::parseFromStream(builder, file, &root, &errs))
    {
        throw std::runtime_error("Failed to parse JSON: " + errs);
    }

    //SADX
    Json::Value sadxRoot = root["sadx"];

    for (const auto& codename : sadxRoot.getMemberNames())
    {
        const Json::Value& songData = sadxRoot[codename];
        std::string name = songData["name"].asString();
        int id = songData["id"].asInt();
        std::vector<std::string> possibleCodenames;
        //TODO: Separate by options
        for (const auto& possibleCodename : songData["curatedSADX"])
        {
            possibleCodenames.push_back(possibleCodename.asString());
        }
        for (const auto& possibleCodename : songData["curatedSA2B"])
        {
            possibleCodenames.push_back(possibleCodename.asString());
        }
        for (const auto& possibleCodename : songData["curatedCustom"])
        {
            possibleCodenames.push_back(possibleCodename.asString());
        }

        std::string sa2Replacement = songData["SA2Breplacement"].asString();
        _songMap.AddSong(id, codename, name, possibleCodenames, sa2Replacement);
    }
    //SA2B
    Json::Value sa2Root = root["sa2b"];
    for (const auto& codename : sa2Root.getMemberNames())
    {
        const Json::Value& songData = sa2Root[codename];
        std::string name = songData["name"].asString();

        std::string fullPath = "ADX/" + codename;
        auto allocatedName = new char[fullPath.size() + 1];
        std::strcpy(allocatedName, fullPath.c_str());
        MusicInfo musicInfo = {allocatedName, 1};

        int id = helperFunctions.RegisterMusicFile(musicInfo);
        _songMap.AddSong(id, codename, name, std::vector<std::string>(), "");
    }
    //Custom
    Json::Value customRoot = root["custom"];
    for (const auto& codename : customRoot.getMemberNames())
    {
        const Json::Value& songData = customRoot[codename];
        std::string name = songData["name"].asString();

        std::string fullPath = "custom/" + codename;
        auto allocatedName = new char[fullPath.size() + 1];
        std::strcpy(allocatedName, fullPath.c_str());
        MusicInfo musicInfo = {allocatedName, 1};

        int id = helperFunctions.RegisterMusicFile(musicInfo);
        _songMap.AddSong(id, codename, name, std::vector<std::string>(), "");
    }

    _songMap.UpdatedIds();
}
