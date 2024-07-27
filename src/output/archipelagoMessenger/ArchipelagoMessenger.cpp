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

void ArchipelagoMessenger::SendDeath()
{
    AP_DeathLinkSend();
}

void ArchipelagoMessenger::UpdateTags(Options options)
{
    std::vector<std::string> tags;
    if (options.deathLinkActive)
        tags.emplace_back("DeathLink");
    if (options.ringLinkActive)
        tags.emplace_back("RingLink");

    AP_SetTags(tags);
}

void ArchipelagoMessenger::SendRingUpdate(int ringDifference)
{
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
    std::vector<std::string> tags = {std::string("RingLink")};
    b.tags = &tags;
    AP_SendBounce(b);
}
