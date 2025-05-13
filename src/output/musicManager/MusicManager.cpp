#include "MusicManager.h"
#include <fstream>
#include "json/json.h"

MusicManager::MusicManager()
{
    // TODO: Fix
    this->ProcessSongFile(
        "C:/Program Files (x86)/Steam/steamapps/common/Sonic Adventure DX/mods/SADX_Archipelago/songs.json");
}

int MusicManager::GetRandomSongId(int id)
{
    return _songMap.GetRandomSongId(id);
}

const SongData* MusicManager::FindSongById(MusicIDs songId)
{
    return _songMap.FindById(songId);
}


void MusicManager::ProcessSongFile(const std::string& filePath)
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

    // Iterate through the JSON object and add songs to _songMap
    for (const auto& codename : root.getMemberNames())
    {
        const Json::Value& songData = root[codename];
        int id = songData["id"].asInt();
        std::string fullName = songData["fullName"].asString();
        std::vector<std::string> possibleCodenames;

        for (const auto& possibleCodename : songData["curated"])
        {
            possibleCodenames.push_back(possibleCodename.asString());
        }
        _songMap.AddSong(id, codename, fullName, possibleCodenames);
    }
}
