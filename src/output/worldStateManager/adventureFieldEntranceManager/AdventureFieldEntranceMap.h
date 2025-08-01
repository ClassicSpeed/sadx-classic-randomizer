#pragma once
#include "../../../pch.h"


enum EntranceId
{
    // City Hall
    CityHallToSsMain = 0,
    CityHallToSewers,
    CityHallToSpeedHighway,
    CityHallToChaos0,

    // Station + Casino
    StationToSsMain,
    StationToMrMain,
    StationToCasinopolis,
    StationToHotel,
    StationToEggWalker,

    // Sewers
    SewersToCityHall,
    SewersToSsMain,

    // SSMain
    SsMainToHotel,
    SsMainToStation,
    SsMainToCityHall,
    SsMainToTwinkleParkLobby,
    SsMainToEcOutside,
    SsMainToBridge,
    SsMainToSewers,
    SsMainToSpeedHighway,

    // Hotel
    HotelToSsMain,
    HotelToStation,
    HotelToEmeraldCoast,
    HotelToSsChaoGarden,
    HotelToChaos2,

    // Twinkle Park Lobby
    TwinkleParkLobbyToSsMain,
    TwinkleParkLobbyToTwinklePark,
    TwinkleParkLobbyToTwinkleCircuit,

    // MRMain
    MrMainToSsMain,
    MrMainToEcOutside,
    MrMainToBridge,
    MrMainToAngelIsland,
    MrMainToWindyValley,
    MrMainToJungle,
    MrMainToChaos4,
    MrMainToEggHornet,
    MrMainToMrChaoGarden,
    MrMainToSkyChase1,

    // Angel Island
    AngelIslandToMrMain,
    AngelIslandToIceCap,
    AngelIslandToRedMountain,
    AngelIslandToPastAltar,

    // Past Altar
    PastAltarToAngelIsland,
    PastAltarToPastMain,

    // Past Main
    PastMainToPastAltar,

    // Jungle
    JungleToMrMain,
    JungleToLostWorld,
    JungleToLostWorldKnuckles,
    JungleToFinalEggTower,
    JungleToSandHill,

    // Final Egg Tower
    FinalEggTowerToJungle,
    FinalEggTowerToFinalEgg,
    FinalEggTowerToFinalEggGamma,
    FinalEggTowerToBetaEggViper,
    FinalEggTowerToEcInside,


    // Egg Carrier Outside (Untransformed)
    EcOutsideToSsMain,
    EcOutsideToMrMain,
    EcOutsideToSkyChase2,
    EcOutsideToChaos6ZeroBeta,
    EcOutsideToEcInsideMonorail,
    EcOutsideToEcInsideEggLift,
    EcOutsideToCaptainRoom,
    EcOutsideToPool,

    // Bridge (Transformed) //TODO: Check how to handle this
    BridgeToSsMain,
    BridgeToMrMain,
    BridgeToSkyDeck,
    BridgeToSkyChase2,
    BridgeToChaos6ZeroBeta,
    BridgeToEcInsideMonorail,

    // Deck (Transformed)  //TODO: Check how to handle this
    DeckToPool,
    DeckToCaptainRoom, //TODO: Probably needs a spring
    DeckToPrivateRoom,
    DeckToPrivateRoomAlternative, //Higher entrance TODO: Probably needs a spring
    DeckToEcInsideEggLift,

    // Captain Room
    CaptainRoomToEcOutside,
    CaptainRoomToDeck,
    CaptainRoomToPrivateRoom, //TODO: Needs to open the floor

    // Private Room
    PrivateRoomToCaptainRoom,
    PrivateRoomToDeck, //TODO: What happens when transformed?
    PrivateRoomToDeckAlternative, //Higher entrance

    // Pool
    PoolToEcOutside,
    PoolToDeck,
    PoolToSkyDeck,

    // Arsenal
    ArsenalToEcInside,

    // Egg Carrier Inside
    EcInsideToEcOutsideEggLift,
    EcInsideToEcOutsideMonorail,
    EcInsideToEcDeckEggLift,
    EcInsideToEcBridgeMonorail,
    EcInsideToHotShelter,
    EcInsideToHedgehogHammer,
    EcInsideToFinalEggTower,
    EcInsideToWarpHall,
    EcInsideToArsenal,
    EcInsideToWaterTank,

    // Hedgehog Hammer
    HedgehogHammerToEcInside,
    HedgehogHammerToPrisonHall,

    // Prison Hall
    PrisonHallToHedgehogHammer,

    // Water Tank
    WaterTankToEcInside,

    // Warp Hall
    WarpHallToEcInside,
    WarpHallToEcChaoGarden,

    // SS Chao Garden
    SsChaoGardenToHotel,
    SsChaoGardenToEcChaoGarden,
    SsChaoGardenToMrChaoGarden,

    // Mr Chao Garden
    MrChaoGardenToMrMain,
    MrChaoGardenToSsChaoGarden,
    MrChaoGardenToEcChaoGarden,

    // Ec Chao Garden
    EcChaoGardenToWarpHall,
    EcChaoGardenToSsChaoGarden,
    EcChaoGardenToMrChaoGarden,


    // Levels
    SpeedHighwayToCityHall,
    Chaos0ToCityHall,
    CasinopolisToStation,
    EggWalkerToStation,
    SpeedHighwayToSsMain,
    EmeraldCoastToHotel,
    Chaos2ToHotel,
    TwinkleParkToTwinkleParkLobby,
    TwinkleCircuitToTwinkleParkLobby,
    WindyValleyToMrMain,
    Chaos4ToMrMain,
    EggHornetToMrMain,
    SkyChase1ToMrMain,
    IceCapToAngelIsland,
    RedMountainToAngelIsland,
    LostWorldToJungle,
    LostWorldToJungleKnuckles,
    SandHillToJungle,
    FinalEggToFinalEggTower,
    FinalEggGammaToFinalEggTower,
    BetaEggViperToFinalEggTower,
    SkyChase2ToEcOutside,
    SkyChase2ToBridge,
    Chaos6ZeroBetaToEcOutside,
    Chaos6ZeroBetaToBridge,
    SkyDeckToBridge,
    SkyDeckTPool,
    HotShelterToEcInside,

    InvalidEntranceId
};

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
    static AdventureFieldEntranceMap& Init()
    {
        if (_instance == nullptr)
            _instance = new AdventureFieldEntranceMap();
        return *_instance;
    }

    AdventureFieldEntrance* GetNewConnection(LevelAndActIDs sourceLocation, LevelAndActIDs destinationLocation);
    const std::vector<AdventureFieldEntrance>& GetEntrances() const;

private:
    explicit AdventureFieldEntranceMap();
    inline static AdventureFieldEntranceMap* _instance = nullptr;

    EntranceId FindEntranceByLocation(LevelAndActIDs sourceLocation, LevelAndActIDs destinationLocation);
    EntranceId GetReplacementConnection(EntranceId entranceId);
    AdventureFieldEntrance* FindEntranceById(EntranceId entranceId);

    std::vector<AdventureFieldEntrance> _entranceList = {};

    std::map<EntranceId, EntranceId> _entranceNewConnections = {
        {CityHallToSsMain, SsMainToCityHall},

        {CityHallToSewers, SewersToCityHall},
        {CityHallToSpeedHighway, SpeedHighwayToCityHall},
        {CityHallToChaos0, Chaos0ToCityHall},
        {StationToSsMain, SsMainToStation},
        {StationToMrMain, MrMainToSsMain},
        {StationToCasinopolis, CasinopolisToStation},
        {StationToHotel, HotelToStation},
        {StationToEggWalker, EggWalkerToStation},

        {SewersToSsMain, SsMainToSewers},
        {SsMainToHotel, HotelToSsMain},

        {SsMainToTwinkleParkLobby, TwinkleParkLobbyToSsMain},

        {SsMainToEcOutside, EcOutsideToSsMain},
        {SsMainToSpeedHighway, SpeedHighwayToSsMain},
        {HotelToEmeraldCoast, EmeraldCoastToHotel},
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
        {AngelIslandToIceCap, IceCapToAngelIsland},
        {AngelIslandToRedMountain, RedMountainToAngelIsland},
        {AngelIslandToPastAltar, PastAltarToAngelIsland},
        {PastAltarToPastMain, PastMainToPastAltar},
        {JungleToLostWorld, LostWorldToJungle},
        {JungleToFinalEggTower, FinalEggTowerToJungle},
        {JungleToSandHill, SandHillToJungle},
        {FinalEggTowerToFinalEgg, FinalEggToFinalEggTower},
        {FinalEggTowerToFinalEggGamma, FinalEggGammaToFinalEggTower},
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
        {BridgeToEcInsideMonorail, EcInsideToEcBridgeMonorail},
        {CaptainRoomToPrivateRoom, PrivateRoomToCaptainRoom},
        {PrivateRoomToDeck, DeckToPrivateRoom},
        {PrivateRoomToDeckAlternative, DeckToPrivateRoomAlternative},
        {DeckToPool, PoolToDeck},
        {DeckToCaptainRoom, CaptainRoomToDeck},
        {DeckToEcInsideEggLift, EcInsideToEcDeckEggLift},
        {PoolToSkyDeck, SkyDeckTPool},
        {EcInsideToHotShelter, HotShelterToEcInside},
        {EcInsideToHedgehogHammer, HedgehogHammerToEcInside},
        {HedgehogHammerToPrisonHall, PrisonHallToHedgehogHammer},
        {EcInsideToWarpHall, WarpHallToEcInside},
        {WarpHallToEcChaoGarden, EcChaoGardenToWarpHall},
        {EcInsideToArsenal, ArsenalToEcInside},
        {EcInsideToWaterTank, WaterTankToEcInside},
        {SsChaoGardenToEcChaoGarden, EcChaoGardenToSsChaoGarden},
        {SsChaoGardenToMrChaoGarden, MrChaoGardenToSsChaoGarden},
        {MrChaoGardenToEcChaoGarden, EcChaoGardenToMrChaoGarden},
    };
};
