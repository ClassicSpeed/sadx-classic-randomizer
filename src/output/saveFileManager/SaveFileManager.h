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

private:
    SaveFileManager()
    {
    }

    inline static SaveFileManager* _instance = nullptr;
    void OnSaveFileCreated();
};
