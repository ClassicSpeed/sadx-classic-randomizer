#include "ArchipelagoMessenger.h"

#include <chrono>


ArchipelagoMessenger::ArchipelagoMessenger(const int instanceId, const int64_t baseId)
{
    _instanceId = instanceId;
    _baseId = baseId;
}

void ArchipelagoMessenger::CheckLocation(const int locationId)
{
    AP_SendItem(_baseId + locationId);
}

void ArchipelagoMessenger::GameCompleted()
{
    AP_StoryComplete();
}

void ArchipelagoMessenger::UpdateTags(Options options)
{
    std::vector<std::string> tags;
    if (options.deathLinkActive)
        tags.emplace_back("DeathLink");
    if (options.ringLinkActive)
        tags.emplace_back("RingLink");
    if (options.hardRingLinkActive)
        tags.emplace_back("HardRingLink");

    AP_SetTags(tags);
}


void ArchipelagoMessenger::SendDeath(std::string playerName)
{
    const std::string characterName = CHARACTERS_MAP.at(CurrentCharacter);
    Json::FastWriter writer;
    std::chrono::time_point<std::chrono::system_clock> timestamp = std::chrono::system_clock::now();
    AP_Bounce b;
    Json::Value v;
    v["time"] = std::chrono::duration_cast<std::chrono::seconds>(timestamp.time_since_epoch()).count();
    v["source"] = playerName;
    v["cause"] = characterName + " died. (" + playerName + ")";
    b.data = writer.write(v);
    b.games = nullptr;
    b.slots = nullptr;
    std::vector<std::string> tags = {std::string("DeathLink")};
    b.tags = &tags;
    AP_SendBounce(b);
}


void ArchipelagoMessenger::SendRingUpdate(const int ringDifference) {
    SendRingPacket(ringDifference, "RingLink");
}

void ArchipelagoMessenger::SendHardRingUpdate(const int ringDifference) {
    SendRingPacket(ringDifference, "HardRingLink");
}

void ArchipelagoMessenger::SendRingPacket(const int ringDifference, const std::string& tagName) {
    if(ringDifference == 0)
        return;
    Json::FastWriter writer;
    std::chrono::time_point<std::chrono::system_clock> timestamp = std::chrono::system_clock::now();
    AP_Bounce b;
    Json::Value v;
    v["time"] = std::chrono::duration_cast<std::chrono::seconds>(timestamp.time_since_epoch()).count();
    v["source"] = this->_instanceId;
    v["amount"] = ringDifference;
    b.data = writer.write(v);
    b.slots = nullptr;
    b.games = nullptr;
    std::vector<std::string> tags = { tagName };
    b.tags = &tags;
    AP_SendBounce(b);
}