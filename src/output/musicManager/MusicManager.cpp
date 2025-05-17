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
    // Open the JSON file
    std::string filePath = "./mods/SADX_Archipelago/songs.json";
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

    Json::Value settingsRoot = root["settings"];

    for (const auto& codename : sadxRoot.getMemberNames())
    {
        const Json::Value& songData = sadxRoot[codename];
        std::string name = songData["name"].asString();
        int id = songData["id"].asInt();
        std::string type = songData["type"].asString();

        SongType songType = GetSongTypeFromString(type);

        std::vector<std::string> possibleSADXCodenames;
        std::vector<std::string> possibleSA2BCodenames;
        std::vector<std::string> possibleCustomCodenames;
        for (const auto& possibleCodename : songData["curatedSADX"])
            possibleSADXCodenames.push_back(possibleCodename.asString());

        if (settingsRoot["includeVanillaInCurated"].asBool() || possibleSADXCodenames.empty())
            possibleSADXCodenames.push_back(codename);

        for (const auto& possibleCodename : songData["curatedSA2B"])
            possibleSA2BCodenames.push_back(possibleCodename.asString());

        for (const auto& possibleCodename : songData["curatedCustom"])
            possibleCustomCodenames.push_back(possibleCodename.asString());


        std::string sa2Replacement = songData["SA2Breplacement"].asString();
        _songMap.AddSong(id, codename, name, songType, possibleSADXCodenames, possibleSA2BCodenames,
                         possibleCustomCodenames,
                         sa2Replacement);
    }

    bool showWarningForMissingFiles = settingsRoot["showWarningForMissingFiles"].asBool();
    
    //SA2B
    ParseSongCategory(helperFunctions, root["sa2b"], settingsRoot["sa2bADXpath"].asString(), showWarningForMissingFiles);

    //Custom    
    ParseSongCategory(helperFunctions, root["custom"], settingsRoot["customADXpath"].asString(), showWarningForMissingFiles);

    _songMap.UpdatedIds();
}


void MusicManager::ParseSongCategory(const HelperFunctions& helperFunctions, Json::Value categoryRoot,
                                     std::string categoryPath, bool showWarningForMissingFiles)
{
    for (const auto& codename : categoryRoot.getMemberNames())
    {
        const Json::Value& songData = categoryRoot[codename];
        std::string name = songData["name"].asString();
        std::string type = songData["type"].asString();

        SongType songType = GetSongTypeFromString(type);

        std::string fullPath = categoryPath + codename;

        const std::ifstream fin("./SoundData/bgm/wma/" + fullPath + ".adx");
        if (!fin)
        {
            if(showWarningForMissingFiles)
            {
                std::string errorMessage = "Warning: Missing song file!\n\nFile name: " + fullPath +
                                            ".adx\n\nPlease check the file name and try again.";
                MessageBox(WindowHandle, std::wstring(errorMessage.begin(), errorMessage.end()).c_str(),
                           L"SADX Archipelago Warning: Missing music file", MB_OK | MB_ICONERROR);
            }
        }
        else
        {
            auto allocatedName = new char[fullPath.size() + 1];
            std::strcpy(allocatedName, fullPath.c_str());
            int loop = 1;
            if (songType == SongType::Jingle || songType == SongType::Event)
                loop = 0;

            MusicInfo musicInfo = {allocatedName, loop};

            int id = helperFunctions.RegisterMusicFile(musicInfo);
            _songMap.AddSong(id, codename, name, songType, std::vector<std::string>(),
                             std::vector<std::string>(), std::vector<std::string>(), "");
        }
    }
}

SongType MusicManager::GetSongTypeFromString(const std::string& typeStr)
{
    static const std::unordered_map<std::string, SongType> stringToEnum = {
        {"level", SongType::Level},
        {"fight", SongType::Fight},
        {"theme", SongType::Theme},
        {"jingle", SongType::Jingle},
        {"menu", SongType::Menu},
        {"adventurefield", SongType::AdventureField},
        {"event", SongType::Event}
    };

    auto it = stringToEnum.find(typeStr);
    if (it != stringToEnum.end())
    {
        return it->second;
    }

    return SongType::Level;
}
