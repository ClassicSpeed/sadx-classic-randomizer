#include "ArchipelagoMessenger.h"

#include <chrono>


ArchipelagoMessenger::ArchipelagoMessenger(Options& options, GameStatus& gameStatus) : _options(options),
    _gameStatus(gameStatus)
{
}

void ArchipelagoMessenger::CheckLocation(const int locationId)
{
    AP_SendItem(_options.baseId + locationId);
}

void ArchipelagoMessenger::GameCompleted()
{
    AP_StoryComplete();
}

void ArchipelagoMessenger::UpdateTags()
{
    std::vector<std::string> tags;
    if (_options.deathLinkActive)
        tags.emplace_back("DeathLink");
    if (_options.ringLinkActive)
        tags.emplace_back("RingLink");
    if (_options.hardRingLinkActive)
        tags.emplace_back("HardRingLink");
    if (_options.trapLinkActive)
        tags.emplace_back("TrapLink");

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


void ArchipelagoMessenger::SendRingUpdate(const int ringDifference)
{
    SendRingPacket(ringDifference, "RingLink");
}

void ArchipelagoMessenger::SendHardRingUpdate(const int ringDifference)
{
    SendRingPacket(ringDifference, "HardRingLink");
}

void ArchipelagoMessenger::SendRingPacket(const int ringDifference, const std::string& tagName)
{
    if (ringDifference == 0)
        return;
    Json::FastWriter writer;
    std::chrono::time_point<std::chrono::system_clock> timestamp = std::chrono::system_clock::now();
    AP_Bounce b;
    Json::Value v;
    v["time"] = std::chrono::duration_cast<std::chrono::seconds>(timestamp.time_since_epoch()).count();
    v["source"] = _options.instanceId;
    v["amount"] = ringDifference;
    b.data = writer.write(v);
    b.slots = nullptr;
    b.games = nullptr;
    std::vector<std::string> tags = {tagName};
    b.tags = &tags;
    AP_SendBounce(b);
}


void ArchipelagoMessenger::SendTrapLink(std::string trapName, std::string playerName)
{
    Json::FastWriter writer;
    std::chrono::time_point<std::chrono::system_clock> timestamp = std::chrono::system_clock::now();
    AP_Bounce b;
    Json::Value v;
    v["time"] = std::chrono::duration_cast<std::chrono::seconds>(timestamp.time_since_epoch()).count();
    v["source"] = playerName;
    v["trap_name"] = trapName;
    b.data = writer.write(v);
    b.games = nullptr;
    b.slots = nullptr;
    std::vector<std::string> tags = {std::string("TrapLink")};
    b.tags = &tags;
    AP_SendBounce(b);
}

void ArchipelagoMessenger::SetMapStatus()
{
    PrintDebug(" --- Setting map status to the server 1...\n");

    AP_SetServerDataRequest* map_status = new AP_SetServerDataRequest();
    AP_DataStorageOperation operation = *new AP_DataStorageOperation();
    int filler_value = 42;
    operation.operation = "replace";
    operation.value = &filler_value;
    map_status->key = AP_GetPrivateServerDataPrefix() + "MapStatus";
    map_status->type = AP_DataType::Int;
    map_status->want_reply = true;
    map_status->operations.push_back(operation);

    // AP_SetServerDataRequest map_status;
    // map_status.key = AP_GetPrivateServerDataPrefix() + "MapStatus";
    // map_status.type = AP_DataType::Int;
    // int def_val = 43;
    // map_status.operations = {{ "default", &def_val }};
    // map_status.default_value = &def_val;
    // map_status.want_reply = true;
    PrintDebug(" --- Setting map status to the server 2...\n");
    AP_SetServerData(map_status);
    PrintDebug(" --- Setting map status to the server 3...\n");
}
