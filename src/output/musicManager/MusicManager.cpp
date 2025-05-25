#include "MusicManager.h"
#include <fstream>
#include "json/json.h"


MusicManager::MusicManager()
{
}

const SongData* MusicManager::FindSongById(const int songId)
{
    return _songMap.FindById(songId);
}

void MusicManager::ProcessSongsFile(const HelperFunctions& helperFunctions, const std::string& songsPath)
{
    // Open the JSON file
    std::string filePath = songsPath + "songs.json";
    std::ifstream file(filePath, std::ifstream::binary);
    if (!file.is_open())
    {
        std::string errorMessage = "Error: Couldn't open song mapping file!\n\nFile location: /Sonic Adventure DX/"
            + filePath + "\n\nPlease check the file location/mod settings and try again.";
        MessageBox(WindowHandle, std::wstring(errorMessage.begin(), errorMessage.end()).c_str(),
                   L"SADX Archipelago Error: Missing songs mapping file", MB_OK | MB_ICONERROR);

        exit(0);
    }

    // Parse the JSON file
    Json::Value root;
    Json::CharReaderBuilder builder;
    std::string errs;
    if (!Json::parseFromStream(builder, file, &root, &errs))
    {
        std::string errorMessage = "Error: Couldn't parse the song mapping file!\n\nFile location: /Sonic Adventure DX/"
            + filePath + "\n\nPlease use a JSON validator with the songs.json file  and try again.";
        MessageBox(WindowHandle, std::wstring(errorMessage.begin(), errorMessage.end()).c_str(),
                   L"SADX Archipelago Error: Malformed songs mapping file", MB_OK | MB_ICONERROR);

        exit(0);
    }


    //SADX
    Json::Value sadxRoot = root["sadx"];
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

        for (const auto& possibleCodename : songData["curatedSA2B"])
            possibleSA2BCodenames.push_back(possibleCodename.asString());

        for (const auto& possibleCodename : songData["curatedCustom"])
            possibleCustomCodenames.push_back(possibleCodename.asString());


        std::string sa2Replacement = songData["SA2Breplacement"].asString();
        _songMap.AddSong(id, codename, name, songType, SADXSource, possibleSADXCodenames, possibleSA2BCodenames,
                         possibleCustomCodenames,
                         sa2Replacement);
    }

    //SA2B
    ParseSongCategory(helperFunctions, root["sa2b"], _options.sa2BAdxPath, SA2BSource);

    //Custom    
    ParseSongCategory(helperFunctions, root["custom"], _options.customAdxPath, CustomSource);
}


void MusicManager::ParseSongCategory(const HelperFunctions& helperFunctions, Json::Value categoryRoot,
                                     std::string categoryPath, SongSource songSource)
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
            if (_options.showWarningForMissingFiles)
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
            int loop = songType == Jingle ? 0 : 1;

            MusicInfo musicInfo = {allocatedName, loop};

            int id = helperFunctions.RegisterMusicFile(musicInfo);
            _songMap.AddSong(id, codename, name, songType, songSource, std::vector<std::string>(),
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

void MusicManager::UpdateOptions(const Options newOptions)
{
    this->_options = newOptions;
}

void MusicManager::RandomizeMusic()
{
    // We don't randomize until every option is set
    if (_options.musicSource == MusicSourceNone
        || _options.musicShuffle == MusicShuffleNone
        || _options.musicShuffleConsistency == MusicShuffleConsistencyNone
        || _options.musicShuffleSeed == -1)
        return;

    _songMap.UpdateSongLists(_options);
    if (_options.musicShuffle == MusicShuffleSingularity)
    {
        const int singularitySong = this->GetSingularitySong();
        for (size_t id = 0; id < MusicList.size(); ++id)
        {
            _songRandomizationMap[id] = {singularitySong};
        }
    }
    else
    {
        std::mt19937 gen;
        if (_options.musicShuffleConsistency == MusicShuffleConsistencyStatic)
            gen = std::mt19937(_options.musicShuffleSeed);
        else
            gen = std::mt19937(std::random_device{}());
        for (size_t id = 0; id < MusicList.size(); ++id)
        {
            const std::vector<int> possibleIds = this->GetPossibleSongIds(static_cast<int>(id), gen);
            if (!possibleIds.empty())
                _songRandomizationMap[id] = possibleIds;
        }
    }
}


std::vector<int> MusicManager::GetPossibleSongIds(int const id, std::mt19937& gen)
{
    // Get all the possible songs for the given id
    std::vector<int> allPossibleIds = {};
    const auto songInfo = FindSongById(id);

    if (_options.musicShuffle == MusicShuffleDisabled || songInfo == nullptr)
    {
        if (_options.musicSource == MusicSourceSa2B || _options.musicSource == MusicSourceSa2BCustom)
            return _songMap.GetSa2Song(id);
        return {id};
    }

    if (_options.musicShuffle == MusicShuffleCurated)
        allPossibleIds = _songMap.GetCuratedSongs(id, _options);
    else if (_options.musicShuffle == MusicShuffleByType)
        allPossibleIds = _songMap.GetSongsByType(songInfo->type);
    else if (_options.musicShuffle == MusicShuffleFull)
        allPossibleIds = _songMap.GetAllSongs(songInfo->type == Jingle);

    if (allPossibleIds.empty() || _options.includeVanillaSongs)
    {
        // If no songs are found, return the original id
        allPossibleIds.push_back(id);
    }

    if (_options.musicShuffleConsistency == MusicShuffleConsistencyStatic
        || _options.musicShuffleConsistency == MusicShuffleConsistencyOnRestart)
    {
        std::uniform_int_distribution<> dis(0, allPossibleIds.size() - 1);
        return {allPossibleIds[dis(gen)]};
    }
    //MusicShuffleConsistencyPerPlay
    return allPossibleIds;
}

int MusicManager::GetSingularitySong()
{
    const auto allSongs = _songMap.GetAllSongs(false);

    if (_options.musicShuffleConsistency == MusicShuffleConsistencyStatic)
    {
        std::mt19937 gen(_options.musicShuffleSeed);
        std::uniform_int_distribution<> dis(0, allSongs.size() - 1);

        return allSongs[dis(gen)];
    }
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, allSongs.size() - 1);

    return allSongs[dis(gen)];
}

int MusicManager::GetSongForId(int const songId)
{
    if (_songRandomizationMap[songId].empty())
        return songId;
    if (_songRandomizationMap[songId].size() == 1)
        return _songRandomizationMap[songId][0];

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, _songRandomizationMap[songId].size() - 1);

    return _songRandomizationMap[songId][dis(gen)];
}

int MusicManager::GetSongNewForId(int const songId, int const currentSongId)
{
    if (_songRandomizationMap[songId].empty())
        return songId;

    std::vector<int> filteredSongs;
    for (int song : _songRandomizationMap[songId])
    {
        if (song != currentSongId)
            filteredSongs.push_back(song);
    }

    if (filteredSongs.empty())
        return currentSongId;

    if (filteredSongs.size() == 1)
        return filteredSongs[0];

    // Randomly select a song from the filtered list
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, filteredSongs.size() - 1);

    return filteredSongs[dis(gen)];
}
