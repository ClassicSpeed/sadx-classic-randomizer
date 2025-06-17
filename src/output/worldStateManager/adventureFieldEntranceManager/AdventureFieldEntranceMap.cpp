#include "AdventureFieldEntranceMap.h"

//TODO: enable controls after entering the EC

//TODO: Improve performance by using a map or unordered_map for faster lookups
AdventureFieldEntranceMap::AdventureFieldEntranceMap()
{
    _entranceList = {


        //City Hall
        {CityHallToSsMain, LevelAndActIDs_StationSquare1, 1, SsMainToCityHall, 50.0f, {550.79f, 14.5, 856.22f}},


        //Station
        {StationToSsMain, LevelAndActIDs_StationSquare2, 0, SsMainToStation, 0.0f, {0, 0, 0}},

        // Sewers

        // SSMain
        {SsMainToCityHall, LevelAndActIDs_StationSquare4, 1, CityHallToSsMain, 110.8F, {443, 15, 1077}},
        {SsMainToStation, LevelAndActIDs_StationSquare4, 0, StationToSsMain, 18.81f, {28, 41, 1388}},
        {SsMainToHotel, LevelAndActIDs_StationSquare4, 3, HotelToSsMain, 90, {-168, 15, 1685}},
        {SsMainToTwinkleParkLobby, LevelAndActIDs_StationSquare4, 4, TwinkleParkLobbyToSsMain, 90, {580, 65, 1772}},
        {SsMainToEcOutside, LevelAndActIDs_StationSquare4, 6, EcOutsideToSsMain, 90, {580, 65, 1772}},

        // Hotel
        {HotelToSsMain, LevelAndActIDs_StationSquare5, 1, SsMainToHotel, 90, {-168, 15, 1685}},


        // Twinkle Park Lobby
        {TwinkleParkLobbyToSsMain, LevelAndActIDs_StationSquare6, 0, SsMainToTwinkleParkLobby, 90, {580, 65, 1772}},


        // Egg Carrier Outside (Untransformed)
        {EcOutsideToSsMain, LevelAndActIDs_EggCarrierOutside1, 0, SsMainToEcOutside, 0.0f, {0, 0, 0}},
    };
}

const std::vector<AdventureFieldEntrance>& AdventureFieldEntranceMap::GetEntrances() const
{
    return _entranceList;
}

AdventureFieldEntrance* AdventureFieldEntranceMap::GetNewConnection(
    const LevelAndActIDs sourceLocation, const LevelAndActIDs destinationLocation)

{
    const EntranceId sourceEntranceId = FindEntranceByLocation(sourceLocation, destinationLocation);
    if (sourceEntranceId == static_cast<EntranceId>(-1))
        return nullptr;
    PrintDebug("------AdventureFieldEntranceMap: Found entrance %d for source location %d, %d\n",
               sourceEntranceId, GET_LEVEL(sourceLocation), GET_ACT(sourceLocation));

    const EntranceId destinationEntranceId = GetReplacementConnection(sourceEntranceId);

    PrintDebug("------AdventureFieldEntranceMap: Found replacement connection %d for entrance %d\n",
               destinationEntranceId, sourceEntranceId);


    AdventureFieldEntrance* newEntrance = FindEntranceById(destinationEntranceId);
    PrintDebug("------AdventureFieldEntranceMap: Found entrance by ID %d, %d\n",
               GET_LEVEL(newEntrance->levelAndActId), GET_ACT(newEntrance->levelAndActId));
    return newEntrance;
}


EntranceId AdventureFieldEntranceMap::FindEntranceByLocation(
    const LevelAndActIDs sourceLocation, const LevelAndActIDs destinationLocation)
{
    for (auto& entrance : _entranceList)
    {
        if (entrance.levelAndActId == sourceLocation)
        {
            for (const auto& destEntrance : _entranceList)
            {
                if (destEntrance.levelAndActId == destinationLocation &&
                    destEntrance.connectsTo == entrance.entranceId)
                {
                    return entrance.entranceId;
                }
            }
        }
    }

    return static_cast<EntranceId>(-1); // Return invalid ID if not found
}

EntranceId AdventureFieldEntranceMap::GetReplacementConnection(const EntranceId entranceId)
{
    for (const auto& [entranceA, entranceB] : _entranceNewConnections)
    {
        if (entranceA == entranceId)
            return entranceB;
        if (entranceB == entranceId)
            return entranceA;
    }
    return entranceId;
}


AdventureFieldEntrance* AdventureFieldEntranceMap::FindEntranceById(const EntranceId entranceId)
{
    for (auto& entrance : _entranceList)
    {
        if (entrance.entranceId == entranceId)
            return &entrance;
    }

    return nullptr;
}
