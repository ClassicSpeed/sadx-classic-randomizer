#pragma once
#include "../../../pch.h"


enum EntranceId
{
    // City Hall
    CityHallToSsMain = 0,
    CityHallToSewers,
    CityHallToSewersToyShop, //TODO: Doesn't exist, I have to add it to the game
    CityHallToSpeedHighwayAlternative,
    CityHallToChaos0,

    // Station + Casino
    StationToSsMain,
    StationToMrMain,
    StationToCasinopolis,
    StationToHotel,
    StationToEggWalker,

    // Sewers
    SewersToCityHall,
    SewersToCityHallToyShop,
    SewersToSsMain,

    // SSMain
    SsMainToHotel,
    SsMainToStation,
    SsMainToCityHall,
    SsMainToTwinkleParkLobby,
    SsMainToEcOutside,
    //SsMainToBridge, When transformed
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
    // MrMainToEcBridge, When transformed
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

    // Jungle
    JungleToMrMain,
    JungleToLostWorld,
    JungleToLostWorldAlternative,
    JungleToFinalEggTower,
    JungleToSandHill,

    // Final Egg Tower
    FinalEggTowerToJungle,
    FinalEggTowerToFinalEgg,
    FinalEggTowerToFinalEggAlternative,
    FinalEggTowerToBeta, //TODO: It's the same as FinalEggTowerToEggViper, merge it later
    FinalEggTowerToEggViper,
    //FinalEggTowerToEcInside??

    // Past Altar
    PastAltarToAngelIsland,
    PastAltarToPastMain,

    // Past Main
    PastMainToPastAltar,


    // Egg Carrier Outside (Untransformed)
    EcOutsideToSsMain,
    EcOutsideToMrMain,
    EcOutsideToSkyChase2,
    EcOutsideToChaos6,
    EcOutsideToZero,
    EcOutsideToBetaMk2,
    EcOutsideToPool,
    EcOutsideToEcInsideMonorail,
    EcOutsideToEcInsideEggLift,
    EcOutsideToCaptainRoom,

    // Bridge (Transformed) //TODO: Check how to handle this
    BridgeToSsMain,
    BridgeToMrMain,
    BridgeToSkyDeck,
    BridgeToSkyChase2,
    BridgeToChaos6,
    BridgeToZero,
    BridgeToBetaMk2,
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
    PoolToSkyDeckAlternative,

    // Arsenal
    ArsenalToEcInside,

    // Egg Carrier Inside
    EcInsideToEcOutsideEggLift,
    EcInsideToEcOutsideMonorail,
    EcInsideToEcBridgeEggLift, //TODO: Check how to handle this
    EcInsideToEcDeckMonorail,
    EcInsideToHotShelter,
    EcInsideToHedgehogHammer,
    // EcInsideToFinalEggTower??,
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


    /*
        Chaos0
        SpeedHighwayAlternative
        Casinopolis
        EggWalker
        SpeedHighway
        EmeraldCoast
        Chaos2
        TwinklePark
        TwinkleCircuit
        WindyValley
        Chaos4
        EggHornet
        SkyChase1
        IceCap
        RedMountain
        LostWorld
        LostWorldAlternative
        FinalEggTower
        SandHill
        FinalEgg
        FinalEggAlternative
        Beta
        EggViper
        SkyChase2
        Chaos6
        Zero
        BetaMk2
        SkyDeck
    HotShelter
     */
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
        // SSMain connections
        {SsMainToCityHall, CityHallToSsMain},
        {SsMainToStation, StationToSsMain},
        {SsMainToHotel, HotelToSsMain},
        {SsMainToTwinkleParkLobby, TwinkleParkLobbyToSsMain},
        {SsMainToEcOutside, EcOutsideToSsMain},

        // City Hall connections
        {CityHallToSsMain, SsMainToCityHall},

        // Station connections
        {StationToSsMain, SsMainToStation},

        // Hotel connections
        {HotelToSsMain, SsMainToHotel},

        // Twinkle Park Lobby connections
        {TwinkleParkLobbyToSsMain, SsMainToTwinkleParkLobby},

        // Egg Carrier Outside connections
        {EcOutsideToSsMain, SsMainToEcOutside},
    };
};
