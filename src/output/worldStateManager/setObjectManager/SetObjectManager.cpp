#include "SetObjectManager.h"

DataArray(int, IslandDoorFlags, 0x111E010, 8);
UsercallFunc(int, twinkleCircuitDoorHook, (char tpChar), (tpChar), 0x63F810, rEAX, rESI);
UsercallFuncVoid(finalEggDoorCheckAHook, (int a1), (a1), 0x53C130, rEAX);
UsercallFunc(int16_t, finalEggDoorCheckBHook, (int a1), (a1), 0x53BC70, rAX, rEAX);
UsercallFuncVoid(lostWorldEntranceCollisionHook, (int a1), (a1), 0x532960, rEDI);

SetObjectManager::SetObjectManager(Options& options, Settings& settings) : _options(options), _settings(settings)
{
    _countSetItemsMaybeHook.Hook(OnCountSetItemsMaybe);
    _collisionCubeHook.Hook(OnCollisionCube);
    _collisionCylinderHook.Hook(OnCollisionCylinder);
    _setTimeOfDayHook.Hook(OnSetTimeOfDay);
    _adventureSetLevelAndActHook.Hook(OnAdventureSetLevelAndAct);
    _prepareLevelHook.Hook(OnPrepareLevel);
    _emblemMainHook.Hook(OnEmblemMain);
    _missionSetLoadHook.Hook(OnMissionSetLoad);
    _finishedLevelMaybeHook.Hook(OnFinishedLevelMaybe);
    _bigHudDrawWeightAndLifeHook.Hook(OnBigHudDrawWeightAndLife);
    _isFinalEggTowerActiveHook.Hook(OnIsFinalEggTowerActive);
    _isFinalEggDoorActiveHook.Hook(OnIsFinalEggDoorActive);
    lostWorldEntranceCollisionHook.Hook(OnLostWorldEntranceCollision);

    twinkleCircuitDoorHook.Hook(OnTwinkleCircuitDoor);
    finalEggDoorCheckAHook.Hook(OnFinalEggDoorCheckA);
    finalEggDoorCheckBHook.Hook(OnFinalEggDoorCheckB);

    WriteCall(reinterpret_cast<void*>(0x528271), &HandleHedgehogHammer);
    WriteCall(reinterpret_cast<void*>(0x5264C5), &HandleWarp);

    //We allow Tails and Big to enter the Master Emerald Shrine
    IslandDoorFlags[Characters_Tails] = FLAG_SONIC_MR_ISLANDDOOR;
    IslandDoorFlags[Characters_Big] = FLAG_SONIC_MR_ISLANDDOOR;
    IslandDoorFlags[Characters_Amy] = FLAG_SONIC_MR_ISLANDDOOR;

    //We replace the checkpoint for a warp object from the Egg Carrier
    ObjList_SSquare[WARP_STATION_SQUARE] = ObjList_ECarrier3[WARP_EGG_CARRIER_INSIDE];
    ObjList_MRuins[WARP_MYSTIC_RUINS] = ObjList_ECarrier3[WARP_EGG_CARRIER_INSIDE];
    ObjList_MRuins[EMBLEM_MYSTIC_RUINS].Distance = 1000000.0f;
    ObjList_MRuins[EMBLEM_MYSTIC_RUINS].UseDistance = 1;
    ObjList_ECarrier0[WARP_EGG_CARRIER_OUTSIDE] = ObjList_ECarrier3[WARP_EGG_CARRIER_INSIDE];
    ObjList_Past[WARP_PAST] = ObjList_ECarrier3[WARP_EGG_CARRIER_INSIDE];


    WriteData<1>((char*)0x004A6B8C, LEON_TIMER1); // Leon timer 1
    WriteData<1>((char*)0x004A81C1, LEON_TIMER2); // Leon timer 2
    WriteData((float**)0x004CD75A, &_nj_screen_.w); // From SADXFE
    WriteData((float**)0x004CD77C, &_nj_screen_.h); // From SADXFE
}


void SetObjectManager::OnFrame()
{
    if (this->_settings.eggCarrierTransformationCutscene)
    {
        if (levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_EggCarrierOutside4)
            _eggCarrierSunk = false;
        else
            _eggCarrierSunk = true;
    }

    if (CurrentLevel >= LevelIDs_TwinkleCircuit && CurrentLevel <= LevelIDs_SandHill)
        GameMode = GameModes_Adventure_ActionStg;
    else if (GameMode == GameModes_Adventure_Field || GameMode == GameModes_Adventure_ActionStg)
        GameMode = GameModes_Mission;
}

void SetObjectManager::AddSetToLevel(const SETEntry& newSetEntry, const LevelAndActIDs levelAndAct,
                                     const Characters character)
{
    if (CurrentCharacter == character && levelact(CurrentLevel, CurrentAct) == levelAndAct)
    {
        SETObjData* setObjData = &SETTable[SETTable_Count];
        setObjData->Flags |= 0x8000u;

        setObjData->SETEntry = new SETEntry(newSetEntry);

        setObjData->LoadCount = 0;
        SETTable_Count += 1;
    }
}

void SetObjectManager::OnCountSetItemsMaybe()
{
    _countSetItemsMaybeHook.Original();

    if (DemoPlaying > 0)
        return;

    for (int i = 0; i < SETTable_Count; ++i)
    {
        const SETObjData* objData = &SETTable[i];
        if (objData->SETEntry != nullptr)
        {
            //We delete the wall that prevent tails from entering the Emerald Coast
            if (levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_StationSquare5
                && objData->SETEntry->ObjectType == WALL_THAT_PUSHES_YOU_STATION_SQUARE)
            {
                objData->SETEntry->Properties = {0, 0, 0};
            }
        }
    }

    //Warp point
    LoadPVM("EC_ALIFE", ADV01C_TEXLISTS[3]);

    //Buyon enemy
    LoadPVM("E_BUYON", &E_BUYON_TEXLIST);

    //Cop
    LoadPVM("NISEPAT", &NISEPAT_TEXLIST);

    //Sky Chase Tarjet
    LoadNoNamePVM(&TARGET_TEXLIST);

    if (_instance->_settings.eggCarrierTransformationCutscene
        && levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_EggCarrierOutside4)
        LoadPVM("EC_SKY", &EC_SKY_TEXLIST);

    //Freeze trap
    LoadNoNamePVM(&stx_ice0_TEXLIST);

    AddSetToLevel(FINAL_EGG_SPRING, LevelAndActIDs_FinalEgg3, Characters_Sonic);
    AddSetToLevel(SEWERS_SPRING, LevelAndActIDs_StationSquare3, Characters_Sonic);
    AddSetToLevel(CITY_HALL_SEWERS_SCENE_CHANGE_SS, LevelAndActIDs_StationSquare1, Characters_Knuckles);
    AddSetToLevel(CITY_HALL_SEWERS_SCENE_CHANGE_SS, LevelAndActIDs_StationSquare1, Characters_Amy);
    AddSetToLevel(CITY_HALL_SEWERS_SCENE_CHANGE_SS, LevelAndActIDs_StationSquare1, Characters_Gamma);

    AddSetToLevel(SEWERS_SPRING, LevelAndActIDs_StationSquare3, Characters_Tails);
    AddSetToLevel(SEWERS_SPRING, LevelAndActIDs_StationSquare3, Characters_Knuckles);
    AddSetToLevel(SEWERS_SPRING, LevelAndActIDs_StationSquare3, Characters_Amy);
    AddSetToLevel(SEWERS_SPRING, LevelAndActIDs_StationSquare3, Characters_Gamma);
    AddSetToLevel(SEWERS_SPRING_BIG, LevelAndActIDs_StationSquare3, Characters_Big);
    AddSetToLevel(EXTRA_SEWERS_SPRING, LevelAndActIDs_StationSquare3, Characters_Amy);
    AddSetToLevel(EXTRA_SEWERS_SPRING, LevelAndActIDs_StationSquare3, Characters_Big);

    AddSetToLevel(SS_MAIN_BARRICADE_SS, LevelAndActIDs_StationSquare4, Characters_Knuckles);
    AddSetToLevel(SS_MAIN_BARRICADE_SS, LevelAndActIDs_StationSquare4, Characters_Amy);
    AddSetToLevel(SS_MAIN_BARRICADE_SS, LevelAndActIDs_StationSquare4, Characters_Gamma);
    AddSetToLevel(SS_MAIN_BARRICADE_SS, LevelAndActIDs_StationSquare4, Characters_Big);

    AddSetToLevel(CITY_HALL_BARRICADE_SS, LevelAndActIDs_StationSquare1, Characters_Sonic);
    AddSetToLevel(CITY_HALL_BARRICADE_SS, LevelAndActIDs_StationSquare1, Characters_Tails);
    AddSetToLevel(CITY_HALL_BARRICADE_SS, LevelAndActIDs_StationSquare1, Characters_Knuckles);
    AddSetToLevel(CITY_HALL_BARRICADE_SS, LevelAndActIDs_StationSquare1, Characters_Amy);
    AddSetToLevel(CITY_HALL_BARRICADE_SS, LevelAndActIDs_StationSquare1, Characters_Gamma);
    AddSetToLevel(CITY_HALL_BARRICADE_SS, LevelAndActIDs_StationSquare1, Characters_Big);

    AddSetToLevel(CITY_HALL_BARRICADE_WALL_SS, LevelAndActIDs_StationSquare1, Characters_Sonic);
    AddSetToLevel(CITY_HALL_BARRICADE_WALL_SS, LevelAndActIDs_StationSquare1, Characters_Tails);
    AddSetToLevel(CITY_HALL_BARRICADE_WALL_SS, LevelAndActIDs_StationSquare1, Characters_Knuckles);
    AddSetToLevel(CITY_HALL_BARRICADE_WALL_SS, LevelAndActIDs_StationSquare1, Characters_Amy);
    AddSetToLevel(CITY_HALL_BARRICADE_WALL_SS, LevelAndActIDs_StationSquare1, Characters_Gamma);
    AddSetToLevel(CITY_HALL_BARRICADE_WALL_SS, LevelAndActIDs_StationSquare1, Characters_Big);

    AddSetToLevel(EXTRA_WALL_FROM_ANGEL_ISLAND_MR, LevelAndActIDs_MysticRuins2, Characters_Sonic);
    AddSetToLevel(EXTRA_WALL_FROM_ANGEL_ISLAND_MR, LevelAndActIDs_MysticRuins2, Characters_Tails);
    AddSetToLevel(EXTRA_WALL_FROM_ANGEL_ISLAND_MR, LevelAndActIDs_MysticRuins2, Characters_Knuckles);
    AddSetToLevel(EXTRA_WALL_FROM_ANGEL_ISLAND_MR, LevelAndActIDs_MysticRuins2, Characters_Amy);
    AddSetToLevel(EXTRA_WALL_FROM_ANGEL_ISLAND_MR, LevelAndActIDs_MysticRuins2, Characters_Gamma);
    AddSetToLevel(EXTRA_WALL_FROM_ANGEL_ISLAND_MR, LevelAndActIDs_MysticRuins2, Characters_Big);

    AddSetToLevel(EGG_CAP_EC, LevelAndActIDs_EggCarrierOutside5, Characters_Sonic);
    AddSetToLevel(EGG_CAP_EC, LevelAndActIDs_EggCarrierOutside5, Characters_Tails);
    AddSetToLevel(EGG_CAP_EC, LevelAndActIDs_EggCarrierOutside5, Characters_Knuckles);
    AddSetToLevel(EGG_CAP_EC, LevelAndActIDs_EggCarrierOutside5, Characters_Amy);
    AddSetToLevel(EGG_CAP_EC, LevelAndActIDs_EggCarrierOutside5, Characters_Gamma);
    AddSetToLevel(EGG_CAP_EC, LevelAndActIDs_EggCarrierOutside5, Characters_Big);

    AddSetToLevel(SCENE_CHANGE_CAPTAIN_ROOM_EC, LevelAndActIDs_EggCarrierOutside4, Characters_Sonic);
    AddSetToLevel(SCENE_CHANGE_CAPTAIN_ROOM_EC, LevelAndActIDs_EggCarrierOutside4, Characters_Tails);
    AddSetToLevel(SCENE_CHANGE_CAPTAIN_ROOM_EC, LevelAndActIDs_EggCarrierOutside4, Characters_Knuckles);
    AddSetToLevel(SCENE_CHANGE_CAPTAIN_ROOM_EC, LevelAndActIDs_EggCarrierOutside4, Characters_Amy);
    AddSetToLevel(SCENE_CHANGE_CAPTAIN_ROOM_EC, LevelAndActIDs_EggCarrierOutside4, Characters_Gamma);
    AddSetToLevel(SCENE_CHANGE_CAPTAIN_ROOM_EC, LevelAndActIDs_EggCarrierOutside4, Characters_Big);

    AddSetToLevel(FINAL_EGG_TO_EC_MR, LevelAndActIDs_MysticRuins4, Characters_Sonic);
    AddSetToLevel(FINAL_EGG_TO_EC_MR, LevelAndActIDs_MysticRuins4, Characters_Tails);
    AddSetToLevel(FINAL_EGG_TO_EC_MR, LevelAndActIDs_MysticRuins4, Characters_Knuckles);
    AddSetToLevel(FINAL_EGG_TO_EC_MR, LevelAndActIDs_MysticRuins4, Characters_Amy);
    AddSetToLevel(FINAL_EGG_TO_EC_MR, LevelAndActIDs_MysticRuins4, Characters_Gamma);
    AddSetToLevel(FINAL_EGG_TO_EC_MR, LevelAndActIDs_MysticRuins4, Characters_Big);

    AddSetToLevel(SCENE_CHANGE_LEFT_DOOR_EC, LevelAndActIDs_EggCarrierInside2, Characters_Sonic);
    AddSetToLevel(SCENE_CHANGE_LEFT_DOOR_EC, LevelAndActIDs_EggCarrierInside2, Characters_Tails);
    AddSetToLevel(SCENE_CHANGE_LEFT_DOOR_EC, LevelAndActIDs_EggCarrierInside2, Characters_Knuckles);
    AddSetToLevel(SCENE_CHANGE_LEFT_DOOR_EC, LevelAndActIDs_EggCarrierInside2, Characters_Amy);
    AddSetToLevel(SCENE_CHANGE_LEFT_DOOR_EC, LevelAndActIDs_EggCarrierInside2, Characters_Gamma);
    AddSetToLevel(SCENE_CHANGE_LEFT_DOOR_EC, LevelAndActIDs_EggCarrierInside2, Characters_Big);


    AddSetToLevel(RED_MOUNTAIN_SCENE_CHANGE_MR, LevelAndActIDs_MysticRuins2, Characters_Tails);
    AddSetToLevel(RED_MOUNTAIN_DOOR_MR, LevelAndActIDs_MysticRuins2, Characters_Tails);
    AddSetToLevel(RED_MOUNTAIN_SCENE_CHANGE_MR, LevelAndActIDs_MysticRuins2, Characters_Big);
    AddSetToLevel(RED_MOUNTAIN_DOOR_MR, LevelAndActIDs_MysticRuins2, Characters_Big);

    AddSetToLevel(ICE_CAP_LADDER_MR, LevelAndActIDs_MysticRuins2, Characters_Knuckles);
    AddSetToLevel(ICE_CAP_SCENE_CHANGE_MR, LevelAndActIDs_MysticRuins2, Characters_Knuckles);
    AddSetToLevel(ICE_CAP_LADDER_MR, LevelAndActIDs_MysticRuins2, Characters_Gamma);
    AddSetToLevel(ICE_CAP_SCENE_CHANGE_MR, LevelAndActIDs_MysticRuins2, Characters_Gamma);

    AddSetToLevel(CAVE_WIND_CHANGE_SCENE_MR, LevelAndActIDs_MysticRuins1, Characters_Amy);

    AddSetToLevel(ICE_CAP_SPRING, LevelAndActIDs_MysticRuins2, Characters_Amy);

    AddSetToLevel(EGG_CARRIER_TRANSFORM_AREA_SPRING, LevelAndActIDs_EggCarrierOutside5, Characters_Sonic);
    AddSetToLevel(EGG_CARRIER_TRANSFORM_AREA_SPRING, LevelAndActIDs_EggCarrierOutside5, Characters_Tails);
    AddSetToLevel(EGG_CARRIER_TRANSFORM_AREA_SPRING, LevelAndActIDs_EggCarrierOutside5, Characters_Knuckles);
    AddSetToLevel(EGG_CARRIER_TRANSFORM_AREA_SPRING, LevelAndActIDs_EggCarrierOutside5, Characters_Amy);
    AddSetToLevel(EGG_CARRIER_TRANSFORM_AREA_SPRING, LevelAndActIDs_EggCarrierOutside5, Characters_Big);
    AddSetToLevel(EGG_CARRIER_TRANSFORM_AREA_SPRING, LevelAndActIDs_EggCarrierOutside5, Characters_Gamma);

    //Emerald Coast
    AddSetToLevel(BEACH_GATE_SS, LevelAndActIDs_StationSquare5, Characters_Sonic);

    //Speed Highway (City Hall)
    AddSetToLevel(CITY_HALL_SCENE_CHANGE_SS, LevelAndActIDs_StationSquare1, Characters_Big);
    AddSetToLevel(CITY_HALL_SCENE_CHANGE_SS, LevelAndActIDs_StationSquare1, Characters_Sonic);

    //Station Square Bosses
    AddSetToLevel(WARP_CHAOS0, LevelAndActIDs_StationSquare1, Characters_Sonic);
    AddSetToLevel(WARP_EGG_WALKER, LevelAndActIDs_StationSquare2, Characters_Tails);

    //Mystic Ruins Bosses
    AddSetToLevel(WARP_EGG_HORNET, LevelAndActIDs_MysticRuins1, Characters_Sonic);
    AddSetToLevel(WARP_EGG_HORNET, LevelAndActIDs_MysticRuins1, Characters_Tails);

    AddSetToLevel(WARP_CHAOS4, LevelAndActIDs_MysticRuins1, Characters_Sonic);
    AddSetToLevel(WARP_CHAOS4, LevelAndActIDs_MysticRuins1, Characters_Tails);
    AddSetToLevel(WARP_CHAOS4, LevelAndActIDs_MysticRuins1, Characters_Knuckles);

    AddSetToLevel(WARP_EGG_VIPER, LevelAndActIDs_MysticRuins4, Characters_Sonic);
    AddSetToLevel(WARP_E101, LevelAndActIDs_MysticRuins4, Characters_Gamma);

    //Egg Carrier Bosses
    AddSetToLevel(WARP_CHAOS6, LevelAndActIDs_EggCarrierOutside1, Characters_Sonic);
    AddSetToLevel(WARP_CHAOS6, LevelAndActIDs_EggCarrierOutside2, Characters_Sonic);

    AddSetToLevel(WARP_CHAOS6, LevelAndActIDs_EggCarrierOutside1, Characters_Knuckles);
    AddSetToLevel(WARP_CHAOS6, LevelAndActIDs_EggCarrierOutside2, Characters_Knuckles);

    AddSetToLevel(WARP_CHAOS6, LevelAndActIDs_EggCarrierOutside1, Characters_Big);
    AddSetToLevel(WARP_CHAOS6, LevelAndActIDs_EggCarrierOutside2, Characters_Big);

    AddSetToLevel(WARP_ZERO, LevelAndActIDs_EggCarrierOutside1, Characters_Amy);
    AddSetToLevel(WARP_ZERO, LevelAndActIDs_EggCarrierOutside2, Characters_Amy);

    AddSetToLevel(WARP_E101_MK2, LevelAndActIDs_EggCarrierOutside1, Characters_Gamma);
    AddSetToLevel(WARP_E101_MK2, LevelAndActIDs_EggCarrierOutside2, Characters_Gamma);


    //Station Square Bosses
    AddSetToLevel(WARP_CHAOS0, LevelAndActIDs_StationSquare1, Characters_Tails);
    AddSetToLevel(WARP_CHAOS0, LevelAndActIDs_StationSquare1, Characters_Knuckles);
    AddSetToLevel(WARP_CHAOS0, LevelAndActIDs_StationSquare1, Characters_Amy);
    AddSetToLevel(WARP_CHAOS0, LevelAndActIDs_StationSquare1, Characters_Gamma);
    AddSetToLevel(WARP_CHAOS0, LevelAndActIDs_StationSquare1, Characters_Big);

    AddSetToLevel(WARP_EGG_WALKER, LevelAndActIDs_StationSquare2, Characters_Sonic);
    AddSetToLevel(WARP_EGG_WALKER, LevelAndActIDs_StationSquare2, Characters_Knuckles);
    AddSetToLevel(WARP_EGG_WALKER, LevelAndActIDs_StationSquare2, Characters_Amy);
    AddSetToLevel(WARP_EGG_WALKER, LevelAndActIDs_StationSquare2, Characters_Gamma);
    AddSetToLevel(WARP_EGG_WALKER, LevelAndActIDs_StationSquare2, Characters_Big);

    //Mystic Ruins Bosses
    AddSetToLevel(WARP_EGG_HORNET, LevelAndActIDs_MysticRuins1, Characters_Knuckles);
    AddSetToLevel(WARP_EGG_HORNET, LevelAndActIDs_MysticRuins1, Characters_Amy);
    AddSetToLevel(WARP_EGG_HORNET, LevelAndActIDs_MysticRuins1, Characters_Gamma);
    AddSetToLevel(WARP_EGG_HORNET, LevelAndActIDs_MysticRuins1, Characters_Big);

    AddSetToLevel(WARP_CHAOS4, LevelAndActIDs_MysticRuins1, Characters_Amy);
    AddSetToLevel(WARP_CHAOS4, LevelAndActIDs_MysticRuins1, Characters_Gamma);
    AddSetToLevel(WARP_CHAOS4, LevelAndActIDs_MysticRuins1, Characters_Big);

    AddSetToLevel(WARP_EGG_VIPER, LevelAndActIDs_MysticRuins4, Characters_Tails);
    AddSetToLevel(WARP_EGG_VIPER, LevelAndActIDs_MysticRuins4, Characters_Knuckles);
    AddSetToLevel(WARP_EGG_VIPER, LevelAndActIDs_MysticRuins4, Characters_Amy);
    AddSetToLevel(WARP_EGG_VIPER, LevelAndActIDs_MysticRuins4, Characters_Big);

    //Egg Carrier Bosses
    AddSetToLevel(WARP_CHAOS6, LevelAndActIDs_EggCarrierOutside1, Characters_Tails);
    AddSetToLevel(WARP_CHAOS6, LevelAndActIDs_EggCarrierOutside2, Characters_Tails);


    AddSetToLevel(WARP_SKY_CHASE_1_WITHOUT_RUNWAY, LevelAndActIDs_MysticRuins1, Characters_Sonic);
    AddSetToLevel(WARP_SKY_CHASE_1_WITHOUT_RUNWAY, LevelAndActIDs_MysticRuins1, Characters_Tails);
    AddSetToLevel(WARP_SKY_CHASE_1_WITHOUT_RUNWAY, LevelAndActIDs_MysticRuins1, Characters_Knuckles);
    AddSetToLevel(WARP_SKY_CHASE_1_WITHOUT_RUNWAY, LevelAndActIDs_MysticRuins1, Characters_Amy);
    AddSetToLevel(WARP_SKY_CHASE_1_WITHOUT_RUNWAY, LevelAndActIDs_MysticRuins1, Characters_Gamma);
    AddSetToLevel(WARP_SKY_CHASE_1_WITHOUT_RUNWAY, LevelAndActIDs_MysticRuins1, Characters_Big);

    AddSetToLevel(WARP_SKY_CHASE_2_EC1, LevelAndActIDs_EggCarrierOutside1, Characters_Sonic);
    AddSetToLevel(WARP_SKY_CHASE_2_EC1, LevelAndActIDs_EggCarrierOutside1, Characters_Tails);
    AddSetToLevel(WARP_SKY_CHASE_2_EC1, LevelAndActIDs_EggCarrierOutside1, Characters_Knuckles);
    AddSetToLevel(WARP_SKY_CHASE_2_EC1, LevelAndActIDs_EggCarrierOutside1, Characters_Amy);
    AddSetToLevel(WARP_SKY_CHASE_2_EC1, LevelAndActIDs_EggCarrierOutside1, Characters_Gamma);
    AddSetToLevel(WARP_SKY_CHASE_2_EC1, LevelAndActIDs_EggCarrierOutside1, Characters_Big);

    AddSetToLevel(WARP_SKY_CHASE_2_EC2, LevelAndActIDs_EggCarrierOutside2, Characters_Sonic);
    AddSetToLevel(WARP_SKY_CHASE_2_EC2, LevelAndActIDs_EggCarrierOutside2, Characters_Tails);
    AddSetToLevel(WARP_SKY_CHASE_2_EC2, LevelAndActIDs_EggCarrierOutside2, Characters_Knuckles);
    AddSetToLevel(WARP_SKY_CHASE_2_EC2, LevelAndActIDs_EggCarrierOutside2, Characters_Amy);
    AddSetToLevel(WARP_SKY_CHASE_2_EC2, LevelAndActIDs_EggCarrierOutside2, Characters_Gamma);
    AddSetToLevel(WARP_SKY_CHASE_2_EC2, LevelAndActIDs_EggCarrierOutside2, Characters_Big);

    AddSetToLevel(WIND_STONE_MR, LevelAndActIDs_MysticRuins1, Characters_Knuckles);
    AddSetToLevel(WIND_STONE_MR, LevelAndActIDs_MysticRuins1, Characters_Amy);
    AddSetToLevel(WIND_STONE_MR, LevelAndActIDs_MysticRuins1, Characters_Big);

    //Time Travel 
    AddSetToLevel(WARP_TO_PAST, LevelAndActIDs_MysticRuins2, Characters_Sonic);
    AddSetToLevel(WARP_TO_PAST, LevelAndActIDs_MysticRuins2, Characters_Tails);
    AddSetToLevel(WARP_TO_PAST, LevelAndActIDs_MysticRuins2, Characters_Knuckles);
    AddSetToLevel(WARP_TO_PAST, LevelAndActIDs_MysticRuins2, Characters_Amy);
    AddSetToLevel(WARP_TO_PAST, LevelAndActIDs_MysticRuins2, Characters_Gamma);
    AddSetToLevel(WARP_TO_PAST, LevelAndActIDs_MysticRuins2, Characters_Big);

    AddSetToLevel(WARP_FROM_PAST, LevelAndActIDs_Past2, Characters_Sonic);
    AddSetToLevel(WARP_FROM_PAST, LevelAndActIDs_Past2, Characters_Tails);
    AddSetToLevel(WARP_FROM_PAST, LevelAndActIDs_Past2, Characters_Knuckles);
    AddSetToLevel(WARP_FROM_PAST, LevelAndActIDs_Past2, Characters_Amy);
    AddSetToLevel(WARP_FROM_PAST, LevelAndActIDs_Past2, Characters_Gamma);
    AddSetToLevel(WARP_FROM_PAST, LevelAndActIDs_Past2, Characters_Big);

    AddSetToLevel(WARP_TO_PAST_2, LevelAndActIDs_MysticRuins3, Characters_Sonic);
    AddSetToLevel(WARP_TO_PAST_2, LevelAndActIDs_MysticRuins3, Characters_Tails);
    AddSetToLevel(WARP_TO_PAST_2, LevelAndActIDs_MysticRuins3, Characters_Knuckles);
    AddSetToLevel(WARP_TO_PAST_2, LevelAndActIDs_MysticRuins3, Characters_Amy);
    AddSetToLevel(WARP_TO_PAST_2, LevelAndActIDs_MysticRuins3, Characters_Gamma);
    AddSetToLevel(WARP_TO_PAST_2, LevelAndActIDs_MysticRuins3, Characters_Big);

    AddSetToLevel(WARP_FROM_PAST_2, LevelAndActIDs_Past1, Characters_Sonic);
    AddSetToLevel(WARP_FROM_PAST_2, LevelAndActIDs_Past1, Characters_Tails);
    AddSetToLevel(WARP_FROM_PAST_2, LevelAndActIDs_Past1, Characters_Knuckles);
    AddSetToLevel(WARP_FROM_PAST_2, LevelAndActIDs_Past1, Characters_Amy);
    AddSetToLevel(WARP_FROM_PAST_2, LevelAndActIDs_Past1, Characters_Gamma);
    AddSetToLevel(WARP_FROM_PAST_2, LevelAndActIDs_Past1, Characters_Big);
}


void SetObjectManager::OnCollisionCube(task* tp)
{
    if (levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_MysticRuins2)
    {
        //We find the cube collision that prevent tails from entering the Master Emerald Shrine and delete it
        if (IsNearPosition(tp->twp->pos, -1075, -215, -1040))
            FreeTask(tp);
    }
    else if (levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_Casinopolis2)
    {
        //We find the cube collision that prevent sonic from entering the life capsule path in SADX and delete it
        if (IsNearPosition(tp->twp->pos, 1, -1715, 2767))
            FreeTask(tp);
    }
    else
        _collisionCubeHook.Original(tp);
}


void SetObjectManager::OnCollisionCylinder(task* tp)
{
    if (levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_StationSquare1)
    {
        //We find the cylinder collision that prevent sonic from clipping into the city hall in the DC conversion
        if (IsNearPosition(tp->twp->pos, 322, -15, 245))
            FreeTask(tp);
            //We find the second cylinder collision
        else if (IsNearPosition(tp->twp->pos, 216, -15, 245))
            FreeTask(tp);
    }
    else
        _collisionCylinderHook.Original(tp);
}

// //We pretend that the egg carrier is sunk so that the hedgehog hammer works
bool SetObjectManager::HandleHedgehogHammer()
{
    return GetEventFlag(EventFlags_Amy_WarriorFeather);
}


void SetObjectManager::HandleWarp()
{
    DisableController(0);
    if (levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_StationSquare1)
        SetNextLevelAndAct_CutsceneMode(LevelIDs_Chaos0, 0);

    else if (levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_StationSquare2)
        SetNextLevelAndAct_CutsceneMode(LevelIDs_EggWalker, 0);

    else if (levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_MysticRuins4 && (CurrentCharacter == Characters_Sonic
        || CurrentCharacter == Characters_Gamma))
        SetNextLevelAndAct_CutsceneMode(LevelIDs_EggViper, 0);

    else if (levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_MysticRuins1 && EntityData1Ptrs[0]->Position.y < 100)
        SetNextLevelAndAct_CutsceneMode(LevelIDs_Chaos4, 0);

    else if (levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_MysticRuins1 && EntityData1Ptrs[0]->Position.y > 100
        && EntityData1Ptrs[0]->Position.y < 150)
        SetNextLevelAndAct_CutsceneMode(LevelIDs_EggHornet, 0);

    else if (levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_MysticRuins1 && EntityData1Ptrs[0]->Position.y > 150)
        SetNextLevelAndAct_CutsceneMode(LevelIDs_SkyChase1, 0);

    else if (CurrentLevel == LevelIDs_EggCarrierOutside && EntityData1Ptrs[0]->Position.z > -500
        && (CurrentCharacter != Characters_Tails))
        SetNextLevelAndAct_CutsceneMode(LevelIDs_Chaos6, 0);

    else if (CurrentLevel == LevelIDs_EggCarrierOutside && EntityData1Ptrs[0]->Position.z < -500
        && (CurrentCharacter == Characters_Sonic || CurrentCharacter == Characters_Tails))
        SetNextLevelAndAct_CutsceneMode(LevelIDs_SkyChase2, 0);

    else if (levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_MysticRuins2)
        SetNextLevelAndAct_CutsceneMode(LevelIDs_Past, 1);

    else if (levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_Past2)
        SetNextLevelAndAct_CutsceneMode(LevelIDs_MysticRuins, 1);

    else if (levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_MysticRuins3)
        SetNextLevelAndAct_CutsceneMode(LevelIDs_Past, 0);

    else if (levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_Past1)
        SetNextLevelAndAct_CutsceneMode(LevelIDs_MysticRuins, 2);

    else if (levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_ECGarden)
        SetNextLevelAndAct_CutsceneMode(LevelIDs_EggCarrierInside, 5);

    else
        SetNextLevelAndAct_CutsceneMode(LevelIDs_ECGarden, 0);
}


// Set starting location when we get a game over
void SetObjectManager::OnSetTimeOfDay(Sint8 time)
{
    _setTimeOfDayHook.Original(time);
    if (GameState == MD_GAME_CONTINUE)
        _instance->SetStartingArea();
}

// Set starting location when starting the adventure
void SetObjectManager::OnAdventureSetLevelAndAct()
{
    _adventureSetLevelAndActHook.Original();
    _instance->SetStartingArea();
}

void SetObjectManager::SetStartingArea()
{
    if (LastStoryFlag == 1)
        return;
    switch (this->_options.GetCharacterStartingArea(static_cast<Characters>(CurrentCharacter)))
    {
    case CityHall:
        SetLevelAndAct(LevelIDs_StationSquare, 0);
        break;
    case Station:
        SetLevelAndAct(LevelIDs_StationSquare, 1);
        SetEntranceNumber(0);
        break;
    case Casino:
        SetLevelAndAct(LevelIDs_StationSquare, 1);
        SetEntranceNumber(1);
        break;
    case Sewers:
        SetLevelAndAct(LevelIDs_StationSquare, 2);
        break;
    case SSMain:
        SetLevelAndAct(LevelIDs_StationSquare, 3);
        break;
    case TPTunnel:
        SetLevelAndAct(LevelIDs_StationSquare, 3);
        SetEntranceNumber(4);
        break;
    case Hotel:
        SetLevelAndAct(LevelIDs_StationSquare, 4);
        SetEntranceNumber(1);
        break;
    case HotelPool:
        SetLevelAndAct(LevelIDs_StationSquare, 4);
        break;
    case TPLobby:
        SetLevelAndAct(LevelIDs_StationSquare, 5);
        break;
    case MRMain:
        SetLevelAndAct(LevelIDs_MysticRuins, 0);
        break;
    case AngelIsland:
        SetLevelAndAct(LevelIDs_MysticRuins, 1);
        SetEntranceNumber(1);
        break;
    case IceCave:
        SetLevelAndAct(LevelIDs_MysticRuins, 1);
        SetEntranceNumber(2);
        break;
    case PastMain:
        SetLevelAndAct(LevelIDs_Past, 0);
        break;
    case PastAltar:
        SetLevelAndAct(LevelIDs_Past, 1);
        break;
    case Jungle:
        SetLevelAndAct(LevelIDs_MysticRuins, 2);
        break;
    case FinalEggTower:
        SetLevelAndAct(LevelIDs_MysticRuins, 3);
        break;
    case ECOutside:
        SetLevelAndAct(LevelIDs_EggCarrierOutside, 0);
        break;
    case CaptainRoom:
        SetLevelAndAct(LevelIDs_EggCarrierOutside, 3);
        break;
    case ECPool:
        SetLevelAndAct(LevelIDs_EggCarrierOutside, 5);
        break;
    case Arsenal:
        SetLevelAndAct(LevelIDs_EggCarrierInside, 0);
        break;
    case ECInside:
        SetLevelAndAct(LevelIDs_EggCarrierInside, 1);
        break;
    case HedgehogHammer:
        SetLevelAndAct(LevelIDs_EggCarrierInside, 2);
        break;
    case PrisonHall:
        SetLevelAndAct(LevelIDs_EggCarrierInside, 3);
        break;
    case WaterTank:
        SetLevelAndAct(LevelIDs_EggCarrierInside, 4);
        break;
    case WarpHall:
        SetLevelAndAct(LevelIDs_EggCarrierInside, 5);
        break;
    case SSChaoGarden:
        SetLevelAndAct(LevelIDs_SSGarden, 0);
        break;
    case MRChaoGarden:
        SetLevelAndAct(LevelIDs_MRGarden, 0);
        break;
    case ECChaoGarden:
        SetLevelAndAct(LevelIDs_ECGarden, 0);
        break;
    default:
        SetLevelAndAct(LevelIDs_StationSquare, 3);
        break;
    }
}

//We make the game load Sonic's set files for Angel Island when playing as Tails or Big
Sint32 SetObjectManager::OnPrepareLevel()
{
    Sint32 result;
    if ((CurrentCharacter == Characters_Tails || CurrentCharacter == Characters_Big) &&
        levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_MysticRuins2)
    {
        const char* originalCharId = CharIDStrings[CurrentCharacter];
        CharIDStrings[CurrentCharacter] = "S";
        result = _prepareLevelHook.Original();
        CharIDStrings[CurrentCharacter] = originalCharId;
    }
    else
    {
        result = _prepareLevelHook.Original();
    }
    return result;
}


// We move the emblem a little higher so Cream can get it.
//Move a little lower since it clips with the ground
void SetObjectManager::OnEmblemMain(task* tp)
{
    if (levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_StationSquare1 && CurrentCharacter == Characters_Tails)
        if (IsNearPosition(tp->twp->pos, 388, -5.5, 490.5))
        {
            tp->twp->pos.y = -4.7f;
        }

    _emblemMainHook.Original(tp);
}

void SetObjectManager::OnMissionSetLoad()
{
    if (!_instance->_options.missionModeEnabled)
        return;

    _missionSetLoadHook.Original();

    for (int i = 0; i < MissionSetCount; ++i)
    {
        const SETObjData* objData = &MissionSETTable[i];
        if (objData->SETEntry != nullptr)
        {
            const NJS_VECTOR position = objData->SETEntry->Position;
            //We move the mission switch from Big's bed
            if (levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_MysticRuins3 &&
                IsNearPosition(position, 1296, 131.5, -727.5))
            {
                objData->SETEntry->Position = {1333, 120, -707};
            }
            //We move the mission card in the sewer, so it doesn't clip with the spring
            if (levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_StationSquare3 &&
                IsNearPosition(position, 506.5, -88.5, 635.5))
            {
                objData->SETEntry->Position = {position.x, -70, position.z};
            }

            //We move the mission card 51 in the jungle, so Gamma can get it even if the Snake door is open
            if (levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_MysticRuins3 &&
                IsNearPosition(position, -512.5, 205, -1124))
            {
                objData->SETEntry->Position = {-515.9674, 70.18237, -989.24146};
            }
        }
    }
}

//Hook to change the level after beating the boss
Sint32 SetObjectManager::OnFinishedLevelMaybe()
{
    const Sint32 response = _finishedLevelMaybeHook.Original();
    if (GameState != MD_GAME_END)
        return response;

    if (CurrentLevel == LevelIDs_Chaos0)
    {
        SetNextLevelAndAct(LevelIDs_StationSquare, 0);
    }
    else if (CurrentLevel == LevelIDs_Chaos2)
    {
        SetNextLevelAndAct(LevelIDs_StationSquare, 4);
    }
    else if (CurrentLevel == LevelIDs_Chaos4)
    {
        SetNextLevelAndAct(LevelIDs_MysticRuins, 0);
    }
    else if (CurrentLevel == LevelIDs_Chaos6 || CurrentLevel == LevelIDs_Zero
        || CurrentLevel == LevelIDs_E101R || CurrentLevel == LevelIDs_SkyChase2)
    {
        SetNextLevelAndAct(LevelIDs_EggCarrierOutside, LastAct);
    }
    else if (CurrentLevel == LevelIDs_EggHornet || CurrentLevel == LevelIDs_SkyChase1)
    {
        SetNextLevelAndAct(LevelIDs_MysticRuins, 0);
    }
    else if (CurrentLevel == LevelIDs_EggWalker)
    {
        SetNextLevelAndAct(LevelIDs_StationSquare, 1);
    }
    else if (CurrentLevel == LevelIDs_EggViper || CurrentLevel == LevelIDs_E101)
    {
        SetNextLevelAndAct(LevelIDs_MysticRuins, 3);
    }
    else if (CurrentLevel == LevelIDs_TwinkleCircuit)
    {
        SetNextLevelAndAct(LevelIDs_StationSquare, 5);
    }
    return response;
}

// We make Big's hud think we are not in the mission mode
void SetObjectManager::OnBigHudDrawWeightAndLife()
{
    const GameModes bufferGameMode = GameMode;
    if (CurrentLevel >= LevelIDs_StationSquare && CurrentLevel <= LevelIDs_Past)
        GameMode = GameModes_Adventure_Field;
    else
        GameMode = GameModes_Adventure_ActionStg;
    _bigHudDrawWeightAndLifeHook.Original();
    GameMode = bufferGameMode;
}


// Handles the Twinkle Circuit door
int SetObjectManager::OnTwinkleCircuitDoor(const char character)
{
    return _instance->_options.twinkleCircuitChecks;
}

void SetObjectManager::OnFinalEggDoorCheckA(const int a1)
{
    const int bufferCharacter = CurrentCharacter;
    CurrentCharacter = Characters_Sonic;
    finalEggDoorCheckAHook.Original(a1);
    CurrentCharacter = bufferCharacter;
}

short SetObjectManager::OnFinalEggDoorCheckB(const int a1)
{
    const int bufferCharacter = CurrentCharacter;
    CurrentCharacter = Characters_Sonic;
    const int result = finalEggDoorCheckBHook.Original(a1);
    CurrentCharacter = bufferCharacter;
    return result;
}

BOOL SetObjectManager::OnIsFinalEggTowerActive()
{
    return true;
}

BOOL SetObjectManager::OnIsFinalEggDoorActive()
{
    return true;
}

void SetObjectManager::OnLostWorldEntranceCollision(const int a1)
{
    const int bufferCharacter = CurrentCharacter;
    CurrentCharacter = Characters_Sonic;
    lostWorldEntranceCollisionHook.Original(a1);
    CurrentCharacter = bufferCharacter;
}
