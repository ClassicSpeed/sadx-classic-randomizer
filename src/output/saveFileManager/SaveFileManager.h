#pragma once

#include "../../pch.h"

class SaveFileManager
{
public:
    static SaveFileManager& Init()
    {
        if (_instance == nullptr)
            _instance = new SaveFileManager();
        return *_instance;
    }

    void OnSaveFileLoaded();
    void OnFrame();
    void StartAllMissions();
    void SetMissionCompleted(int mission);

private:
    SaveFileManager(){}
    inline static SaveFileManager* _instance = nullptr;
    void OnSaveFileCreated();

};
