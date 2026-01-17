#pragma once

#include "../../pch.h"
#include "../../application/randomizer/Randomizer.h"


class CharacterLoadingDetector : public IOnFrame
{
public:
    static CharacterLoadingDetector& Init(Randomizer& randomizer, Settings& settings)
    {
        if (_instance == nullptr)
            _instance = new CharacterLoadingDetector(randomizer, settings);
        return *_instance;
    }

    void OnFrame() override;

    void OnCharacterSelectScreenLoaded() const;
    void OnCharacterLoaded();

private:
    explicit CharacterLoadingDetector(Randomizer& randomizer, Settings& settings);
    inline static CharacterLoadingDetector* _instance = nullptr;
    Randomizer& _randomizer;
    Settings& _settings;


    inline static FunctionHook<void> _loadCharacterHook{0x4157C0};
    static void OnLoadCharacter();

    inline static FunctionHook<void> _loadCharacterSelectScreenHook{0x512BC0};
    static void OnLoadCharacterSelectScreen();


    int _loadCharacterNextFrame = 0;
};
