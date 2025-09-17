#include "Link.h"


void Link::ProcessDeath(const std::string& deathCause)
{
    const double timePassed = (std::clock() - _deathLinkCooldownTimer) / static_cast<double>(CLOCKS_PER_SEC);
    if (_deathLinkCooldownTimer < 0 || timePassed > _deathLinkCooldown)
    {
        if (!CheckDeathLinkChance(_options.receiveDeathLinkChance))
        {
            _displayManager.QueueItemMessage("You survived a Death Link!");
            return;
        }

        //Processing a death won't restart the cooldown timer
        _pendingDeathCause = deathCause;
        _deathPending = true;
    }
}

//Move to Own Manager
void Link::OnFrame()
{
    if (_syncTimer == 0)
        this->OnSync();
    else
        _syncTimer--;

    if (Current_CharObj2 == nullptr || EntityData1Ptrs[0] == nullptr)
        return;
    if (!_options.deathLinkActive)
        return;
    if (!_deathPending)
        return;
    if (GameMode != GameModes_Mission)
        return;
    if (GameState != MD_GAME_MAIN)
        return;
    if (!IsControllerEnabled(0))
        return;
    if (CurrentChaoStage == SADXChaoStage_Race || CurrentChaoStage == SADXChaoStage_RaceEntry
        || CurrentChaoStage == SADXChaoStage_ChaoTransporter || CurrentChaoStage == SADXChaoStage_BlackMarket)
        return;


    const double timePassed = (std::clock() - _deathLinkCooldownTimer) / static_cast<double>(CLOCKS_PER_SEC);

    if (_deathLinkCooldownTimer < 0 || timePassed > _deathLinkCooldown)
    {
        _deathLinkCooldownTimer = std::clock();
        _characterManager.KillPlayer();
        _displayManager.QueueItemMessage(_pendingDeathCause);
        _pendingDeathCause.clear();
        _deathPending = false;
    }
}


void Link::OnDeath()
{
    if (!_options.deathLinkActive)
        return;
    if (DemoPlaying > 0)
        return;

    const double timePassed = (std::clock() - _deathLinkCooldownTimer) / static_cast<double>(CLOCKS_PER_SEC);

    if (_deathLinkCooldownTimer < 0 || timePassed > _deathLinkCooldown)
    {
        _deathLinkCooldownTimer = std::clock();

        if (!CheckDeathLinkChance(_options.sendDeathLinkChance))
        {
            _displayManager.QueueItemMessage("Death Link not sent!");
            return;
        }
        _archipelagoMessenger.SendDeath(_settings.playerName);
        _displayManager.QueueItemMessage("Death Sent");
    }
}


void Link::OnSync()
{
    _syncTimer = SYNC_RATE;
    if (!_options.ringLinkActive)
        return;
    const RingDifference ringDifference = _characterManager.GetRingDifference();

    _archipelagoMessenger.SendRingUpdate(ringDifference.ringDifference);
    _archipelagoMessenger.SendHardRingUpdate(ringDifference.hardRingDifference);
}


void Link::ProcessRings(const Sint16 amount)
{
    _characterManager.ProcessRings(amount);
}

void Link::ProcessTrapLink(std::string itemName, std::string message)
{
    FillerType filler = _itemRepository.GetFillerFromName(itemName);

    if (!_options.IsTrapEnabled(filler))
        return;

    const double timePassed = (std::clock() - _trapLinkCooldownTimer) / static_cast<double>(CLOCKS_PER_SEC);
    if (_trapLinkCooldownTimer >= 0 && timePassed <= _trapLinkCooldown)
        return;

    _trapLinkCooldownTimer = std::clock();
    _displayManager.QueueItemMessage(message);
    _characterManager.GiveFillerItem(filler, true);
}
