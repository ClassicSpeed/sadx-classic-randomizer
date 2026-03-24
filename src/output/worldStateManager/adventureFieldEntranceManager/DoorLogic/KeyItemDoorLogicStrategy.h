#include "IDoorLogicStrategy.h"


class KeyItemDoorLogicStrategy : public IDoorLogicStrategy
{
public:
    KeyItemDoorLogicStrategy(Options& options, GameStatus& gameStatus,
                             AdventureFieldEntranceMap& adventureFieldEntranceMap)
        : _options(options),
          _gameStatus(gameStatus), _adventureFieldEntranceMap(adventureFieldEntranceMap)
    {
    }

    DoorState GetDoorState(const EntranceId entranceId) override
    {
        if (entranceId == InvalidEntranceId)
            return DoorBlocked;
        const auto oppositeEntrance = _adventureFieldEntranceMap.GetReplacementConnection(entranceId);

        //Check if door leads to level for the player
        auto entrance = _adventureFieldEntranceMap.FindEntranceById(oppositeEntrance);
        //Static entrance
        if (entrance == nullptr)
            return DoorBlocked;
        // Is level for character
        if (_adventureFieldEntranceMap.CalculateCorrectAct(entrance->levelAndActId) == LevelAndActIDs_HedgehogHammer)
            return DoorBlocked;

        // We prevent characters from using wrong entrances
        if (_options.entranceRandomizer == 0)
        {
            if (entranceId == SsMainToSpeedHighway)
                if (CurrentCharacter == Characters_Knuckles)
                    return DoorBlocked;
            if (entranceId == CityHallToSpeedHighway)
                if (CurrentCharacter != Characters_Knuckles)
                    return DoorBlocked;
            if (entranceId == JungleToLostWorld)
                if (CurrentCharacter == Characters_Knuckles)
                    return DoorBlocked;
            if (entranceId == JungleToLostWorldAlternative)
                if (CurrentCharacter != Characters_Knuckles)
                    return DoorBlocked;
            if (entranceId == FinalEggTowerToFinalEgg)
                if (CurrentCharacter == Characters_Gamma)
                    return DoorBlocked;
            if (entranceId == FinalEggTowerToFinalEggAlternative)
                if (CurrentCharacter != Characters_Gamma)
                    return DoorBlocked;
            if (entranceId == BridgeToSkyDeck)
                if (CurrentCharacter == Characters_Knuckles)
                    return DoorBlocked;
            if (entranceId == PoolToSkyDeck)
                if (CurrentCharacter != Characters_Knuckles)
                    return DoorBlocked;
        }


        switch (entranceId)
        {
        case CityHallToSsMain:
            return _gameStatus.unlock.keyPolicePass ? DoorUnlocked : DoorLocked;
        case CityHallToSewers:
            return DoorOpen;
        case CityHallToSpeedHighway:
            return DoorOpen;
        case CityHallToChaos0:
            return DoorOpen;
        case StationToSsMain:
            return _gameStatus.unlock.keyStationKey ? DoorUnlocked : DoorLocked;
        case StationToMrMain:
            return _gameStatus.unlock.keyTrain ? DoorUnlocked : DoorLocked;
        case StationToCasino:
            return _gameStatus.unlock.keyShutterKey ? DoorUnlocked : DoorLocked;
        case CasinoToStation:
            return _gameStatus.unlock.keyShutterKey ? DoorUnlocked : DoorLocked;
        case CasinoToCasinopolis:
            return DoorOpen;
        case CasinoToHotel:
            return _gameStatus.unlock.keyCasinoKey ? DoorUnlocked : DoorLocked;
        case CasinoToEggWalker:
            return DoorOpen;
        case SewersToCityHall:
            return DoorOpen;
        case SewersToTwinkleParkTunnel:
            return DoorOpen;
        case SsMainToHotel:
            return _gameStatus.unlock.keyHotelKey ? DoorUnlocked : DoorLocked;
        case SsMainToStation:
            return _gameStatus.unlock.keyStationKey ? DoorUnlocked : DoorLocked;
        case SsMainToCityHall:
            return _gameStatus.unlock.keyPolicePass ? DoorUnlocked : DoorLocked;
        case SsMainToTwinkleParkTunnel:
            return _gameStatus.unlock.keyTwinkleParkTicket ? DoorUnlocked : DoorLocked;
        case SsMainToBridge:
            return _gameStatus.unlock.keyBoat ? DoorUnlocked : DoorLocked;
        case SsMainToSpeedHighway:
            return _gameStatus.unlock.keyEmployeeCard ? DoorUnlocked : DoorLocked;
        case HotelToSsMain:
            return _gameStatus.unlock.keyHotelKey ? DoorUnlocked : DoorLocked;
        case HotelToCasino:
            return _gameStatus.unlock.keyCasinoKey ? DoorUnlocked : DoorLocked;
        case HotelToSsChaoGarden:
            return DoorOpen;
        case HotelToChaos2:
            return DoorOpen;
        case HotelToHotelPool:
            return _gameStatus.unlock.keyPoolKey ? DoorUnlocked : DoorLocked;
        case HotelPoolToHotel:
            return _gameStatus.unlock.keyPoolKey ? DoorUnlocked : DoorLocked;
        case HotelPoolToEmeraldCoast:
            return DoorOpen;
        case TwinkleParkTunnelToSsMain:
            return _gameStatus.unlock.keyTwinkleParkTicket ? DoorUnlocked : DoorLocked;
        case TwinkleParkTunnelToTwinkleParkLobby:
            return DoorOpen;
        case TwinkleParkTunnelToSewers:
            return DoorOpen;
        case TwinkleParkLobbyToTwinkleParkTunnel:
            return DoorOpen;
        case TwinkleParkLobbyToTwinklePark:
            return DoorOpen;
        case TwinkleParkLobbyToTwinkleCircuit:
            return DoorOpen;
        case MrMainToStation:
            return _gameStatus.unlock.keyTrain ? DoorUnlocked : DoorLocked;
        case MrMainToBridge:
            return _gameStatus.unlock.keyRaft ? DoorUnlocked : DoorLocked;
        case MrMainToAngelIsland:
            return _gameStatus.unlock.keyDynamite ? DoorUnlocked : DoorLocked;
        case MrMainToWindyValley:
            return _gameStatus.unlock.keyWindStone ? DoorUnlocked : DoorLocked;
        case MrMainToJungle:
            return _gameStatus.unlock.keyJungleCart ? DoorUnlocked : DoorLocked;
        case MrMainToChaos4:
            return DoorOpen;
        case MrMainToEggHornet:
            return DoorOpen;
        case MrMainToMrChaoGarden:
            return DoorOpen;
        case MrMainToSkyChase1:
            return DoorOpen;
        case AngelIslandToMrMain:
            return _gameStatus.unlock.keyDynamite ? DoorUnlocked : DoorLocked;
        case AngelIslandToIceCave:
            return _gameStatus.unlock.keyIceStone ? DoorUnlocked : DoorLocked;
        case AngelIslandToRedMountain:
            return DoorOpen;
        case AngelIslandToPastAltar:
            return _gameStatus.unlock.keyTimeMachine ? DoorUnlocked : DoorLocked;
        case IceCaveToAngelIsland:
            return _gameStatus.unlock.keyIceStone ? DoorUnlocked : DoorLocked;
        case IceCaveToIceCap:
            return DoorOpen;
        case PastAltarToAngelIsland:
            return _gameStatus.unlock.keyTimeMachine ? DoorUnlocked : DoorLocked;
        case PastAltarToPastMain:
            return DoorOpen;
        case PastMainToPastAltar:
            return DoorOpen;
        case PastMainToJungle:
            return _gameStatus.unlock.keyTimeMachine ? DoorUnlocked : DoorLocked;
        case JungleToMrMain:
            return _gameStatus.unlock.keyJungleCart ? DoorUnlocked : DoorLocked;
        case JungleToLostWorld:
            return DoorOpen;
        case JungleToLostWorldAlternative:
            return DoorOpen;
        case JungleToFinalEggTower:
            return DoorOpen;
        case JungleToSandHill:
            return DoorOpen;
        case JungleToPastMain:
            return _gameStatus.unlock.keyTimeMachine ? DoorUnlocked : DoorLocked;
        case FinalEggTowerToJungle:
            return DoorOpen;
        case FinalEggTowerToFinalEgg:
            return DoorOpen;
        case FinalEggTowerToFinalEggAlternative:
            return DoorOpen;
        case FinalEggTowerToBetaEggViper:
            return DoorOpen;
        case FinalEggTowerToEcInside:
            return DoorOpen;
        case BridgeToSsMain:
            return _gameStatus.unlock.keyBoat ? DoorUnlocked : DoorLocked;
        case BridgeToMrMain:
            return _gameStatus.unlock.keyRaft ? DoorUnlocked : DoorLocked;
        case BridgeToSkyDeck:
            return DoorOpen;
        case BridgeToSkyChase2:
            return DoorOpen;
        case BridgeToChaos6ZeroBeta:
            return DoorOpen;
        case BridgeToEcInsideMonorail:
            return _gameStatus.unlock.keyMonorail ? DoorUnlocked : DoorLocked;
        case DeckToPool:
            return DoorOpen;
        case DeckToCaptainRoom:
            return DoorOpen;
        case DeckToPrivateRoom:
            return DoorOpen;
        case DeckToPrivateRoomAlternative:
            return DoorOpen;
        case DeckToEcInsideEggLift:
            return _gameStatus.unlock.keyEgglift ? DoorUnlocked : DoorLocked;
        case CaptainRoomToDeck:
            return DoorOpen;
        case CaptainRoomToPrivateRoom:
            return DoorOpen;
        case PrivateRoomToCaptainRoom:
            return DoorOpen;
        case PrivateRoomToDeck:
            return DoorOpen;
        case PrivateRoomToDeckAlternative:
            return DoorOpen;
        case PoolToDeck:
            return DoorOpen;
        case PoolToSkyDeck:
            return DoorOpen;
        case ArsenalToEcInside:
            return DoorOpen;
        case EcInsideToDeckEggLift:
            return _gameStatus.unlock.keyEgglift ? DoorUnlocked : DoorLocked;
        case EcInsideToBridgeMonorail:
            return _gameStatus.unlock.keyMonorail ? DoorUnlocked : DoorLocked;
        case EcInsideToHotShelter:
            return DoorOpen;
        case EcInsideToHedgehogHammer:
            return DoorOpen;
        case EcInsideToFinalEggTower:
            return DoorOpen;
        case EcInsideToWarpHall:
            return DoorOpen;
        case EcInsideToArsenal:
            return DoorOpen;
        case EcInsideToWaterTank:
            return DoorOpen;
        case HedgehogHammerToEcInside:
            return DoorOpen;
        case HedgehogHammerToPrisonHall:
            return DoorOpen;
        case PrisonHallToHedgehogHammer:
            return DoorOpen;
        case WaterTankToEcInside:
            return DoorOpen;
        case WarpHallToEcInside:
            return DoorOpen;
        case WarpHallToEcChaoGarden:
            return DoorOpen;
        case SsChaoGardenToHotel:
            return DoorOpen;
        case MrChaoGardenToMrMain:
            return DoorOpen;
        case EcChaoGardenToWarpHall:
            return DoorOpen;
        case SpeedHighwayToCityHall:
        case Chaos0ToCityHall:
        case CasinopolisToCasino:
        case EggWalkerToCasino:
        case SpeedHighwayToSsMain:
        case EmeraldCoastToHotelPool:
        case Chaos2ToHotel:
        case TwinkleParkToTwinkleParkLobby:
        case TwinkleCircuitToTwinkleParkLobby:
        case WindyValleyToMrMain:
        case Chaos4ToMrMain:
        case EggHornetToMrMain:
        case SkyChase1ToMrMain:
        case IceCapToIceCave:
        case RedMountainToAngelIsland:
        case LostWorldToJungle:
        case LostWorldToJungleAlternative:
        case SandHillToJungle:
        case FinalEggToFinalEggTower:
        case FinalEggToFinalEggTowerAlternative:
        case BetaEggViperToFinalEggTower:
        case SkyChase2ToBridge:
        case Chaos6ZeroBetaToBridge:
        case SkyDeckToBridge:
        case SkyDeckToPool:
        case HotShelterToEcInside:
            return DoorOpen;
        case InvalidEntranceId:
            return DoorLocked;
        default:
            return DoorOpen;
        }
    }

private:
    Options& _options;
    GameStatus& _gameStatus;
    AdventureFieldEntranceMap& _adventureFieldEntranceMap;
};
