#pragma once
#include "../../pch.h"
#include "../../configuration/options/Options.h"
#include "../../output/displayManager/DisplayManager.h"
#include "../../output/characterManager/CharacterManager.h"
#include "../../output/archipelagoMessenger/ArchipelagoMessenger.h"
#include "../../output/itemRepository/ItemRepository.h"
#include <random>
constexpr int SYNC_RATE = 10;

inline bool CheckDeathLinkChance(const int chance)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 100);

    return dis(gen) <= chance;
}

class Link : public IOnFrame
{
public:
    static Link& Init(Options& options, Settings& settings, DisplayManager& displayManager,
                      CharacterManager& characterManager, ItemRepository& itemRepository,
                      ArchipelagoMessenger& archipelagoMessenger)
    {
        if (_instance == nullptr)
            _instance = new Link(options, settings, displayManager, characterManager, itemRepository,
                                 archipelagoMessenger);
        return *_instance;
    }

    void ProcessDeath(const std::string& deathCause);
    void OnFrame() override;
    void OnSync();
    void OnDeath();
    void ProcessRings(Sint16 amount);
    void ProcessTrapLink(std::string itemName, std::string message);

private:
    Link(Options& options, Settings& settings, DisplayManager& displayManager,
         CharacterManager& characterManager, ItemRepository& itemRepository,
         ArchipelagoMessenger& archipelagoMessenger)
        : _options(options), _settings(settings), _displayManager(displayManager),
          _characterManager(characterManager), _itemRepository(itemRepository),
          _archipelagoMessenger(archipelagoMessenger), _deathPending(false)
    {
    }

    inline static Link* _instance = nullptr;
    Options& _options;
    Settings& _settings;
    DisplayManager& _displayManager;
    CharacterManager& _characterManager;
    ItemRepository& _itemRepository;
    ArchipelagoMessenger& _archipelagoMessenger;


    float _deathLinkCooldown = 5.0f;
    std::clock_t _deathLinkCooldownTimer = -1;

    float _trapLinkCooldown = 5.0f;
    std::clock_t _trapLinkCooldownTimer = -1;

    std::string _pendingDeathCause;
    bool _deathPending;


    int _syncTimer = 0;
};
