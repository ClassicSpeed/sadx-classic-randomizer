#include "IDoorLogicStrategy.h"


class DefaultDoorLogicStrategy : public IDoorLogicStrategy
{
public:
    DefaultDoorLogicStrategy(Options& options, GameStatus& gameStatus)
        : _options(options),
          _gameStatus(gameStatus)
    {
    }

    bool IsDoorOpen(const EntranceId entranceId) override
    {
        switch (entranceId)
        {
        case CityHallToSsMain:
            return _gameStatus.unlock.keyPolicePass;
        case CityHallToSewers:
            return true;
        case CityHallToSpeedHighway:
            return CurrentCharacter == Characters_Knuckles;
        case CityHallToChaos0:
            return CurrentCharacter == Characters_Sonic;
        case StationToSsMain:
            return _gameStatus.unlock.keyStationKey;
        case StationToMrMain:
            return _gameStatus.unlock.keyTrain;
        case StationToCasinopolis: // TODO: Check
            return CurrentCharacter == Characters_Sonic || CurrentCharacter == Characters_Tails
                || CurrentCharacter == Characters_Knuckles;
        case StationToHotel:
            return _gameStatus.unlock.keyCasinoKey;
        case StationToEggWalker:
            return CurrentCharacter == Characters_Tails;
        case SewersToCityHall:
            return true;
        case SewersToSsMain:
            return CurrentCharacter == Characters_Big;
        case SsMainToHotel:
            return _gameStatus.unlock.keyHotelKey;
        case SsMainToStation:
            return _gameStatus.unlock.keyStationKey;
        case SsMainToCityHall:
            return _gameStatus.unlock.keyPolicePass;
        case SsMainToTwinkleParkLobby:
            return true;
        case SsMainToEcOutside:
            return _gameStatus.unlock.keyBoat;
        case SsMainToBridge:
            return _gameStatus.unlock.keyBoat;
        case SsMainToSewers:
            return CurrentCharacter == Characters_Big;
        case SsMainToSpeedHighway:
            return (CurrentCharacter == Characters_Sonic || CurrentCharacter == Characters_Tails)
                && _gameStatus.unlock.keyEmployeeCard;
        case HotelToSsMain:
            return _gameStatus.unlock.keyHotelKey;
        case HotelToStation:
            return _gameStatus.unlock.keyCasinoKey;
        case HotelToEmeraldCoast:
            return CurrentCharacter == Characters_Sonic || CurrentCharacter == Characters_Gamma
                || CurrentCharacter == Characters_Big;
        case HotelToSsChaoGarden:
            return true;
        case HotelToChaos2:
            return CurrentCharacter == Characters_Knuckles;
        case TwinkleParkLobbyToSsMain:
            return true;
        case TwinkleParkLobbyToTwinklePark:
            return CurrentCharacter == Characters_Sonic || CurrentCharacter == Characters_Amy
                || CurrentCharacter == Characters_Big;
        case TwinkleParkLobbyToTwinkleCircuit:
            return true;
        case MrMainToSsMain:
            return _gameStatus.unlock.keyTrain;
        case MrMainToEcOutside:
            return _gameStatus.unlock.keyRaft;
        case MrMainToBridge:
            return _gameStatus.unlock.keyRaft;
        case MrMainToAngelIsland:
            return _gameStatus.unlock.keyDynamite;
        case MrMainToWindyValley: // TODO: Check
            return _gameStatus.unlock.keyWindStone;
        case MrMainToJungle:
            return _gameStatus.unlock.keyJungleCart;
        case MrMainToChaos4:
            return CurrentCharacter == Characters_Sonic || CurrentCharacter == Characters_Tails
                || CurrentCharacter == Characters_Knuckles;
        case MrMainToEggHornet:
            return CurrentCharacter == Characters_Sonic || CurrentCharacter == Characters_Tails;
        case MrMainToMrChaoGarden:
            return true;
        case MrMainToSkyChase1:
            return CurrentCharacter == Characters_Sonic || CurrentCharacter == Characters_Tails;
        case AngelIslandToMrMain:
            return _gameStatus.unlock.keyDynamite;
        case AngelIslandToIceCap: // TODO: Check
            return _gameStatus.unlock.keyIceStone;
        case AngelIslandToRedMountain:
            return CurrentCharacter == Characters_Sonic || CurrentCharacter == Characters_Gamma
                || CurrentCharacter == Characters_Knuckles;
        case AngelIslandToPastAltar:
            return _gameStatus.unlock.keyTimeMachine;
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
            return CurrentCharacter == Characters_Sonic;
        case JungleToLostWorldAlternative: // TODO: Check
            return CurrentCharacter == Characters_Knuckles;
        case JungleToFinalEggTower:
            return true;
        case JungleToSandHill:
            return CurrentCharacter == Characters_Sonic || CurrentCharacter == Characters_Tails;
        case JungleToPastMain:
            return _gameStatus.unlock.keyTimeMachine;
        case FinalEggTowerToJungle:
            return true;
        case FinalEggTowerToFinalEgg:
            return CurrentCharacter == Characters_Sonic || CurrentCharacter == Characters_Amy;
        case FinalEggTowerToFinalEggAlternative:
            return CurrentCharacter == Characters_Gamma;
        case FinalEggTowerToBetaEggViper:
            return CurrentCharacter == Characters_Sonic || CurrentCharacter == Characters_Gamma;
        case FinalEggTowerToEcInside:
            return _options.connectFinalEggToEggCarrier;
        case EcOutsideToSsMain:
            return _gameStatus.unlock.keyBoat;
        case EcOutsideToMrMain:
            return _gameStatus.unlock.keyRaft;
        case EcOutsideToSkyChase2:
            return CurrentCharacter == Characters_Sonic || CurrentCharacter == Characters_Tails;
        case EcOutsideToChaos6ZeroBeta:
            return CurrentCharacter == Characters_Sonic
                || CurrentCharacter == Characters_Knuckles
                || CurrentCharacter == Characters_Amy
                || CurrentCharacter == Characters_Gamma
                || CurrentCharacter == Characters_Big;
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
            return CurrentCharacter == Characters_Sonic || CurrentCharacter == Characters_Tails;
        case BridgeToSkyChase2:
            return CurrentCharacter == Characters_Sonic || CurrentCharacter == Characters_Tails;
        case BridgeToChaos6ZeroBeta:
            return CurrentCharacter == Characters_Sonic
                || CurrentCharacter == Characters_Knuckles
                || CurrentCharacter == Characters_Amy
                || CurrentCharacter == Characters_Gamma
                || CurrentCharacter == Characters_Big;
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
            break;
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
            return CurrentCharacter == Characters_Knuckles;
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
            return CurrentCharacter == Characters_Amy || CurrentCharacter == Characters_Gamma
                || CurrentCharacter == Characters_Big;
        case EcInsideToHedgehogHammer:
            return CurrentCharacter == Characters_Amy || CurrentCharacter == Characters_Gamma
                || CurrentCharacter == Characters_Big;
        case EcInsideToFinalEggTower:
            return _options.connectFinalEggToEggCarrier;
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
        case CasinopolisToStation:
        case EggWalkerToStation:
        case SpeedHighwayToSsMain:
        case EmeraldCoastToHotel:
        case Chaos2ToHotel:
        case TwinkleParkToTwinkleParkLobby:
        case TwinkleCircuitToTwinkleParkLobby:
        case WindyValleyToMrMain:
        case Chaos4ToMrMain:
        case EggHornetToMrMain:
        case SkyChase1ToMrMain:
        case IceCapToAngelIsland:
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
        return false;
    }

    bool ShowDisableDoorIndicator(EntranceId entranceId) override
    {
        return !IsDoorOpen(entranceId);
    }

private:
    Options& _options;
    GameStatus& _gameStatus;
};


//TODO: Implement normal gameplay with key items
//TODO: Implement normal gameplay with emblems
//TODO: Implement random gameplay with emblems
