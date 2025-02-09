#pragma once

class SaveFileManager
{
public:
    void OnSaveFileLoaded();
    void OnFrame();
    void StartAllMissions();
    void SetMissionCompleted(int mission);

private:    
    void OnSaveFileCreated();
};
