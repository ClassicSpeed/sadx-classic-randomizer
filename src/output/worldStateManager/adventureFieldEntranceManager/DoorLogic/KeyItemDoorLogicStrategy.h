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

    bool IsDoorOpen(const EntranceId entranceId) override
    {
        if (entranceId == InvalidEntranceId)
            return false;
        const auto oppositeEntrance = _adventureFieldEntranceMap.GetReplacementConnection(entranceId, false);

        //Check if door leads to level for the player
        auto entrance = _adventureFieldEntranceMap.FindEntranceById(oppositeEntrance);
        if (_adventureFieldEntranceMap.CalculateCorrectAct(entrance->levelAndActId) == LevelAndActIDs_HedgehogHammer)
            return false;


        switch (entranceId)
        {
        case CityHallToSsMain:
            return _gameStatus.unlock.keyPolicePass;
        case CityHallToSewers:
            return true;
        case CityHallToSpeedHighway:
            return true;
        case CityHallToChaos0:
            return true;
        case StationToSsMain:
            return _gameStatus.unlock.keyStationKey;
        case StationToMrMain:
            return _gameStatus.unlock.keyTrain;
        case StationToCasino:
            return _gameStatus.unlock.keyShutterKey;
        case CasinoToStation:
            return _gameStatus.unlock.keyShutterKey;
        case CasinoToCasinopolis:
            return true;
        case CasinoToHotel:
            return _gameStatus.unlock.keyCasinoKey;
        case CasinoToEggWalker:
            return true;
        case SewersToCityHall:
            return true;
        case SewersToTwinkleParkTunnel:
            return true;
        case SsMainToHotel:
            return _gameStatus.unlock.keyHotelKey;
        case SsMainToStation:
            return _gameStatus.unlock.keyStationKey;
        case SsMainToCityHall:
            return _gameStatus.unlock.keyPolicePass;
        case SsMainToTwinkleParkTunnel:
            return _gameStatus.unlock.keyTwinkleParkTicket;
        case SsMainToEcOutside:
            return _gameStatus.unlock.keyBoat;
        case SsMainToBridge:
            return _gameStatus.unlock.keyBoat;
        case SsMainToSpeedHighway:
            return _gameStatus.unlock.keyEmployeeCard;
        case HotelToSsMain:
            return _gameStatus.unlock.keyHotelKey;
        case HotelToCasino:
            return _gameStatus.unlock.keyCasinoKey;
        case HotelToSsChaoGarden:
            return true;
        case HotelToChaos2:
            return true;
        case HotelToHotelPool:
            return _gameStatus.unlock.keyPoolKey;
        case HotelPoolToHotel:
            return _gameStatus.unlock.keyPoolKey;
        case HotelPoolToEmeraldCoast:
            return true;
        case TwinkleParkTunnelToSsMain:
            return _gameStatus.unlock.keyTwinkleParkTicket;
        case TwinkleParkTunnelToTwinkleParkLobby:
            return true;
        case TwinkleParkTunnelToSewers:
            return true;
        case TwinkleParkLobbyToTwinkleParkTunnel:
            return true;
        case TwinkleParkLobbyToTwinklePark:
            return true;
        case TwinkleParkLobbyToTwinkleCircuit:
            return true;
        case MrMainToStation:
            return _gameStatus.unlock.keyTrain;
        case MrMainToEcOutside:
            return _gameStatus.unlock.keyRaft;
        case MrMainToBridge:
            return _gameStatus.unlock.keyRaft;
        case MrMainToAngelIsland:
            return _gameStatus.unlock.keyDynamite;
        case MrMainToWindyValley:
            return _gameStatus.unlock.keyWindStone;
        case MrMainToJungle:
            return _gameStatus.unlock.keyJungleCart;
        case MrMainToChaos4:
            return true;
        case MrMainToEggHornet:
            return true;
        case MrMainToMrChaoGarden:
            return true;
        case MrMainToSkyChase1:
            return true;
        case AngelIslandToMrMain:
            return _gameStatus.unlock.keyDynamite;
        case AngelIslandToIceCave:
            return _gameStatus.unlock.keyIceStone;
        case AngelIslandToRedMountain:
            return true;
        case AngelIslandToPastAltar:
            return _gameStatus.unlock.keyTimeMachine;
        case IceCaveToAngelIsland:
            return _gameStatus.unlock.keyIceStone;
        case IceCaveToIceCap:
            return true;
        case PastAltarToAngelIsland:
            return _gameStatus.unlock.keyTimeMachine;
        case PastAltarToPastMain:
            return true;
        case PastMainToPastAltar:
            return true;
        case PastMainToJungle:
            return _gameStatus.unlock.keyTimeMachine;
        case JungleToMrMain:
            return _gameStatus.unlock.keyJungleCart;
        case JungleToLostWorld:
            return true;
        case JungleToLostWorldAlternative:
            return true;
        case JungleToFinalEggTower:
            return true;
        case JungleToSandHill:
            return true;
        case JungleToPastMain:
            return _gameStatus.unlock.keyTimeMachine;
        case FinalEggTowerToJungle:
            return true;
        case FinalEggTowerToFinalEgg:
            return true;
        case FinalEggTowerToFinalEggAlternative:
            return true;
        case FinalEggTowerToBetaEggViper:
            return true;
        case FinalEggTowerToEcInside:
            return true;
        case EcOutsideToSsMain:
            return _gameStatus.unlock.keyBoat;
        case EcOutsideToMrMain:
            return _gameStatus.unlock.keyRaft;
        case EcOutsideToSkyChase2:
            return true;
        case EcOutsideToChaos6ZeroBeta:
            return true;
        case EcOutsideToEcInsideMonorail:
            return _gameStatus.unlock.keyMonorail;
        case EcOutsideToEcInsideEggLift:
            return _gameStatus.unlock.keyEgglift;
        case EcOutsideToCaptainRoom:
            return true;
        case EcOutsideToPool:
            return true;
        case BridgeToSsMain:
            return _gameStatus.unlock.keyBoat;
        case BridgeToMrMain:
            return _gameStatus.unlock.keyRaft;
        case BridgeToSkyDeck:
            return true;
        case BridgeToSkyChase2:
            return true;
        case BridgeToChaos6ZeroBeta:
            return true;
        case BridgeToEcInsideMonorail:
            return _gameStatus.unlock.keyMonorail;
        case DeckToPool:
            return true;
        case DeckToCaptainRoom:
            return true;
        case DeckToPrivateRoom:
            return true;
        case DeckToPrivateRoomAlternative:
            return true;
        case DeckToEcInsideEggLift:
            return _gameStatus.unlock.keyEgglift;
        case CaptainRoomToEcOutside:
            return true;
        case CaptainRoomToDeck:
            return true;
        case CaptainRoomToPrivateRoom:
            return true;
        case PrivateRoomToCaptainRoom:
            return true;
        case PrivateRoomToDeck:
            return true;
        case PrivateRoomToDeckAlternative:
            return true;
        case PoolToEcOutside:
            return true;
        case PoolToDeck:
            return true;
        case PoolToSkyDeck:
            return true;
        case ArsenalToEcInside:
            return true;
        case EcInsideToEcOutsideEggLift:
            return _gameStatus.unlock.keyEgglift;
        case EcInsideToEcOutsideMonorail:
            return _gameStatus.unlock.keyMonorail;
        case EcInsideToDeckEggLift:
            return _gameStatus.unlock.keyEgglift;
        case EcInsideToBridgeMonorail:
            return _gameStatus.unlock.keyMonorail;
        case EcInsideToHotShelter:
            return true;
        case EcInsideToHedgehogHammer:
            return true;
        case EcInsideToFinalEggTower:
            return true;
        case EcInsideToWarpHall:
            return true;
        case EcInsideToArsenal:
            return true;
        case EcInsideToWaterTank:
            return true;
        case HedgehogHammerToEcInside:
            return true;
        case HedgehogHammerToPrisonHall:
            return true;
        case PrisonHallToHedgehogHammer:
            return true;
        case WaterTankToEcInside:
            return true;
        case WarpHallToEcInside:
            return true;
        case WarpHallToEcChaoGarden:
            return true;
        case SsChaoGardenToHotel:
            return true;
        case MrChaoGardenToMrMain:
            return true;
        case EcChaoGardenToWarpHall:
            return true;
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
        case SkyChase2ToEcOutside:
        case SkyChase2ToBridge:
        case Chaos6ZeroBetaToEcOutside:
        case Chaos6ZeroBetaToBridge:
        case SkyDeckToBridge:
        case SkyDeckToPool:
        case HotShelterToEcInside:
            return true;
        case InvalidEntranceId:
            return false;
        }
        return true;
    }

    bool ShowDisableDoorIndicator(EntranceId entranceId) override
    {
        if (entranceId == InvalidEntranceId)
            return true;
        return !IsDoorOpen(entranceId);
    }

private:
    Options& _options;
    GameStatus& _gameStatus;
    AdventureFieldEntranceMap& _adventureFieldEntranceMap;
};
