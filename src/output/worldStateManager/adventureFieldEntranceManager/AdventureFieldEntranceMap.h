#pragma once
#include "../../../pch.h"
#include "../../../configuration/options/Options.h"


struct AdventureFieldEntrance
{
    EntranceId entranceId;
    LevelAndActIDs levelAndActId;
    int entranceNumber;
    EntranceId connectsTo;
    float indicatorAngle;
    NJS_POINT3 indicatorPosition;
};


//For each entrance:
//- Test you can go in and leave into a specific entrance
//- Test you can go into a specific entrance and go out from this one
//- Test you can close the entrance


class AdventureFieldEntranceMap
{
public:
    static AdventureFieldEntranceMap& Init(Options& options)
    {
        if (_instance == nullptr)
            _instance = new AdventureFieldEntranceMap(options);
        return *_instance;
    }

    AdventureFieldEntrance* GetNewConnection(LevelAndActIDs sourceLocation, LevelAndActIDs destinationLocation,
                                             bool isEggCarrierTransformed);
    AdventureFieldEntrance* GetCurrentEntrance(LevelAndActIDs sourceLocation, LevelAndActIDs destinationLocation);
    const std::vector<AdventureFieldEntrance>& GetEntrances() const;
    const std::vector<AdventureFieldEntrance>& GetStaticEntrances() const;
    EntranceId GetReplacementConnection(EntranceId fromEntranceId, bool isEggCarrierTransformed);
    AdventureFieldEntrance* FindEntranceById(EntranceId entranceId);
    LevelAndActIDs CalculateCorrectAct(LevelAndActIDs levelAndActId);
    void UpdateRandomEntrances();

private:
    explicit AdventureFieldEntranceMap(Options& options);
    inline static AdventureFieldEntranceMap* _instance = nullptr;
    Options& _options;

    EntranceId FindEntranceByLocation(LevelAndActIDs sourceLocation, LevelAndActIDs destinationLocation);

    std::vector<AdventureFieldEntrance> _entranceList = {};
    std::vector<AdventureFieldEntrance> _staticEntranceList = {};

    std::map<EntranceId, EntranceId> _entranceOriginalConnections = {
        {CityHallToSsMain, SsMainToCityHall},
        {CityHallToSewers, SewersToCityHall},
        {CityHallToSpeedHighway, SpeedHighwayToCityHall},
        {CityHallToChaos0, Chaos0ToCityHall},
        {StationToSsMain, SsMainToStation},
        {StationToMrMain, MrMainToStation},
        {CasinoToCasinopolis, CasinopolisToCasino},
        {CasinoToHotel, HotelToCasino},
        {CasinoToEggWalker, EggWalkerToCasino},

        {SewersToTwinkleParkTunnel, TwinkleParkTunnelToSewers},
        {SsMainToHotel, HotelToSsMain},

        {TwinkleParkTunnelToTwinkleParkLobby, TwinkleParkLobbyToTwinkleParkTunnel},

        {SsMainToEcOutside, EcOutsideToSsMain},
        {SsMainToSpeedHighway, SpeedHighwayToSsMain},
        {HotelPoolToEmeraldCoast, EmeraldCoastToHotelPool},

        {HotelToSsChaoGarden, SsChaoGardenToHotel},
        {HotelToChaos2, Chaos2ToHotel},
        {TwinkleParkLobbyToTwinklePark, TwinkleParkToTwinkleParkLobby},
        {TwinkleParkLobbyToTwinkleCircuit, TwinkleCircuitToTwinkleParkLobby},
        {MrMainToEcOutside, EcOutsideToMrMain},
        {MrMainToAngelIsland, AngelIslandToMrMain},
        {MrMainToWindyValley, WindyValleyToMrMain,},
        {MrMainToJungle, JungleToMrMain},
        {MrMainToChaos4, Chaos4ToMrMain},
        {MrMainToEggHornet, EggHornetToMrMain},
        {MrMainToMrChaoGarden, MrChaoGardenToMrMain},
        {MrMainToSkyChase1, SkyChase1ToMrMain},
        {IceCaveToIceCap, IceCapToIceCave},
        {AngelIslandToRedMountain, RedMountainToAngelIsland},
        {AngelIslandToPastAltar, PastAltarToAngelIsland},
        {PastAltarToPastMain, PastMainToPastAltar},
        {PastMainToJungle, JungleToPastMain},
        {JungleToLostWorld, LostWorldToJungle},
        {JungleToLostWorldAlternative, LostWorldToJungleAlternative},
        {JungleToFinalEggTower, FinalEggTowerToJungle},
        {JungleToSandHill, SandHillToJungle},
        {FinalEggTowerToFinalEgg, FinalEggToFinalEggTower},
        {FinalEggTowerToFinalEggAlternative, FinalEggToFinalEggTowerAlternative},
        {FinalEggTowerToBetaEggViper, BetaEggViperToFinalEggTower},
        {FinalEggTowerToEcInside, EcInsideToFinalEggTower},
        {EcOutsideToSkyChase2, SkyChase2ToEcOutside},
        {EcOutsideToChaos6ZeroBeta, Chaos6ZeroBetaToEcOutside},
        {EcOutsideToEcInsideMonorail, EcInsideToEcOutsideMonorail},
        {EcOutsideToEcInsideEggLift, EcInsideToEcOutsideEggLift},
        {EcOutsideToCaptainRoom, CaptainRoomToEcOutside},
        {EcOutsideToPool, PoolToEcOutside},
        {BridgeToSsMain, SsMainToBridge},
        {BridgeToMrMain, MrMainToBridge},
        {BridgeToSkyDeck, SkyDeckToBridge},
        {BridgeToSkyChase2, SkyChase2ToBridge},
        {BridgeToChaos6ZeroBeta, Chaos6ZeroBetaToBridge},
        {BridgeToEcInsideMonorail, EcInsideToBridgeMonorail},
        {CaptainRoomToPrivateRoom, PrivateRoomToCaptainRoom},
        {PrivateRoomToDeck, DeckToPrivateRoom},
        {PrivateRoomToDeckAlternative, DeckToPrivateRoomAlternative},
        {DeckToPool, PoolToDeck},
        {DeckToCaptainRoom, CaptainRoomToDeck},
        {DeckToEcInsideEggLift, EcInsideToDeckEggLift},
        {PoolToSkyDeck, SkyDeckToPool},
        {EcInsideToHotShelter, HotShelterToEcInside},
        {EcInsideToHedgehogHammer, HedgehogHammerToEcInside},
        {HedgehogHammerToPrisonHall, PrisonHallToHedgehogHammer},
        {EcInsideToWarpHall, WarpHallToEcInside},
        {WarpHallToEcChaoGarden, EcChaoGardenToWarpHall},
        {EcInsideToArsenal, ArsenalToEcInside},
        {EcInsideToWaterTank, WaterTankToEcInside},


        {HotelToHotelPool, HotelPoolToHotel},
        {SsMainToTwinkleParkTunnel, TwinkleParkTunnelToSsMain},
        {StationToCasino, CasinoToStation},
        {AngelIslandToIceCave, IceCaveToAngelIsland},
    };
};
