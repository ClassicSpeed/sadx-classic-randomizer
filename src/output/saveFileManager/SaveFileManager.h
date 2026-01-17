#pragma once

#include "../../pch.h"

class SaveFileManager : public IOnFrame
{
public:
    static SaveFileManager& Init()
    {
        if (_instance == nullptr)
            _instance = new SaveFileManager();
        return *_instance;
    }

    void OnFrame() override;

    void OnSaveFileLoaded();
    void StartAllMissions();
    void SetMissionCompleted(int mission);

    void SetEventFlags(std::vector<StoryFlags> storyFlags);
    void UnlockSuperSonic();
    void MarkBlacklistedMissionsAsCompleted(const std::vector<int>& missionBlacklist);

private:
    SaveFileManager();


    inline static FunctionHook<int> _howManyGameGearGamesHook{0x6FDA90};
    static int OnHowManyGameGearGames();

    inline static FunctionHook<bool> _isGameGearMenuEnabledHook{0x506460};
    static bool OnIsGameGearMenuEnabled();

    inline static FunctionHook<int, int> _showRecapHook{0x643C00};
    static int OnShowRecap(int _);


    inline static SaveFileManager* _instance = nullptr;
    void OnSaveFileCreated();
};
