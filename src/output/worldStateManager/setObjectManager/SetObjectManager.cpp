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
    _isChaos2DoorOpenHook.Hook(OnIsChaos2DoorOpen);
    _getEntranceMRuinsHook.Hook(OnGetEntranceMRuins);
    _getEntranceEggCarrierHook.Hook(OnGetEntranceEggCarrier);
    _getEntrancePastHook.Hook(OnGetEntrancePast);
    _setTimeOfDayHook.Hook(OnSetTimeOfDay);
    _adventureSetLevelAndActHook.Hook(OnAdventureSetLevelAndAct);
    _prepareLevelHook.Hook(OnPrepareLevel);
    _emblemMainHook.Hook(OnEmblemMain);
    _missionSetLoadHook.Hook(OnMissionSetLoad);
    _finishedLevelMaybeHook.Hook(OnFinishedLevelMaybe);
    _bigHudDrawWeightAndLifeHook.Hook(OnBigHudDrawWeightAndLife);
    _setNextLevelAndActCutsceneModeHook.Hook(OnSetNextLevelAndActCutsceneMode);
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
    if (_options.skyChaseChecks && (CurrentCharacter == Characters_Sonic || (CurrentCharacter == Characters_Tails && !
        _options.missionModeEnabled)) && !_options.emblemGating)
        EventFlagArray[33] = 1;


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
    if (_instance->_options.emblemGating)
    {
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
    }

    AddSetToLevel(COLLISION_CUBE_MR, LevelAndActIDs_MysticRuins1, Characters_Sonic);
    AddSetToLevel(COLLISION_CUBE_MR, LevelAndActIDs_MysticRuins1, Characters_Tails);
    AddSetToLevel(COLLISION_CUBE_MR, LevelAndActIDs_MysticRuins1, Characters_Knuckles);
    AddSetToLevel(COLLISION_CUBE_MR, LevelAndActIDs_MysticRuins1, Characters_Amy);
    AddSetToLevel(COLLISION_CUBE_MR, LevelAndActIDs_MysticRuins1, Characters_Big);
    AddSetToLevel(COLLISION_CUBE_MR, LevelAndActIDs_MysticRuins1, Characters_Gamma);

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

    if (_instance->_options.bossChecks)
    {
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


        if (_instance->_options.emblemGating)
        {
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
        }
    }
    if (_instance->_options.skyChaseChecks)
    {
        if (_instance->_options.emblemGating)
        {
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
        }
        else
        {
            AddSetToLevel(WARP_SKY_CHASE_1_WITH_RUNWAY, LevelAndActIDs_MysticRuins1, Characters_Sonic);
            if (_instance->_options.missionModeEnabled)
                AddSetToLevel(WARP_SKY_CHASE_1_WITHOUT_RUNWAY, LevelAndActIDs_MysticRuins1, Characters_Tails);
            else
                AddSetToLevel(WARP_SKY_CHASE_1_WITH_RUNWAY, LevelAndActIDs_MysticRuins1, Characters_Tails);

            AddSetToLevel(WARP_SKY_CHASE_2_EC1, LevelAndActIDs_EggCarrierOutside1, Characters_Sonic);
            AddSetToLevel(WARP_SKY_CHASE_2_EC2, LevelAndActIDs_EggCarrierOutside2, Characters_Sonic);

            AddSetToLevel(WARP_SKY_CHASE_2_EC1, LevelAndActIDs_EggCarrierOutside1, Characters_Tails);
            AddSetToLevel(WARP_SKY_CHASE_2_EC2, LevelAndActIDs_EggCarrierOutside2, Characters_Tails);
        }
    }

    if (_instance->_options.emblemGating)
    {
        AddSetToLevel(WIND_STONE_MR, LevelAndActIDs_MysticRuins1, Characters_Knuckles);
        AddSetToLevel(WIND_STONE_MR, LevelAndActIDs_MysticRuins1, Characters_Amy);
        AddSetToLevel(WIND_STONE_MR, LevelAndActIDs_MysticRuins1, Characters_Big);
    }
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

    else if (levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_MysticRuins4 && CurrentCharacter == Characters_Sonic)
        SetNextLevelAndAct_CutsceneMode(LevelIDs_EggViper, 0);

    else if (levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_MysticRuins4 && CurrentCharacter == Characters_Gamma)
        SetNextLevelAndAct_CutsceneMode(LevelIDs_E101, 0);

    else if (levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_MysticRuins1 && EntityData1Ptrs[0]->Position.y < 100)
        SetNextLevelAndAct_CutsceneMode(LevelIDs_Chaos4, 0);

    else if (levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_MysticRuins1 && EntityData1Ptrs[0]->Position.y > 100
        && EntityData1Ptrs[0]->Position.y < 150)
        SetNextLevelAndAct_CutsceneMode(LevelIDs_EggHornet, 0);

    else if (levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_MysticRuins1 && EntityData1Ptrs[0]->Position.y > 150)
        SetNextLevelAndAct_CutsceneMode(LevelIDs_SkyChase1, 0);

    else if (CurrentLevel == LevelIDs_EggCarrierOutside && CurrentCharacter == Characters_Gamma)
        SetNextLevelAndAct_CutsceneMode(LevelIDs_E101R, 0);

    else if (CurrentLevel == LevelIDs_EggCarrierOutside && CurrentCharacter == Characters_Amy)
        SetNextLevelAndAct_CutsceneMode(LevelIDs_Zero, 0);

    else if (CurrentLevel == LevelIDs_EggCarrierOutside && EntityData1Ptrs[0]->Position.z > -500
        && (CurrentCharacter == Characters_Sonic || CurrentCharacter == Characters_Big))

        SetNextLevelAndAct_CutsceneMode(LevelIDs_Chaos6, 0);

    else if (CurrentLevel == LevelIDs_EggCarrierOutside && (CurrentCharacter == Characters_Knuckles))
        SetNextLevelAndAct_CutsceneMode(LevelIDs_Chaos6, 1);

    else if (CurrentLevel == LevelIDs_EggCarrierOutside && EntityData1Ptrs[0]->Position.z < -500
        && (CurrentCharacter == Characters_Sonic || CurrentCharacter == Characters_Tails))
        SetNextLevelAndAct_CutsceneMode(LevelIDs_SkyChase2, 0);

    else if (levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_MysticRuins2)
        SetNextLevelAndAct_CutsceneMode(LevelIDs_Past, 1);

    else if (levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_Past2)
        SetNextLevelAndAct_CutsceneMode(LevelIDs_MysticRuins, 1);

    else if (levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_MysticRuins3)
    {
        SetNextLevelAndAct_CutsceneMode(LevelIDs_Past, 0);
    }


    else if (levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_Past1)
    {
        SetNextLevelAndAct_CutsceneMode(LevelIDs_MysticRuins, 2);
    }


    else if (levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_ECGarden)
    {
        PrintDebug("----------Debug: Warp from EC Garden to EC Inside Cutscene\n");
        SetNextLevelAndAct_CutsceneMode(LevelIDs_EggCarrierInside, 5);
    }
    else
    {
        PrintDebug("-----------Debug: Warp to EC Garden\n");
        SetNextLevelAndAct_CutsceneMode(LevelIDs_ECGarden, 0);
    }
}

// Allow Knuckles to fight Chaos 2
BOOL SetObjectManager::OnIsChaos2DoorOpen()
{
    if (_instance->_options.emblemGating)
        return _isChaos2DoorOpenHook.Original();
    return CurrentCharacter == Characters_Knuckles;
}

//TODO: Register it?
//TODO: Create a spawn point for Sky Deck/Egg Hornet
// We create a custom spawn point after exiting sand hill
void SetObjectManager::OnGetEntranceMRuins(taskwk* twp)
{
    _getEntranceMRuinsHook.Original(twp);

    if (CurrentStageAndAct == LevelAndActIDs_MysticRuins3)
    {
        if (GetLevelEntranceID() == 3)
        {
            twp->pos = {-1500, 50, -70};
            twp->ang = {0, 0x4000, 0};
        }
        else if (GetLevelEntranceID() == 5)
        {
            twp->pos = {-667, 90.5f, -1150};
            twp->ang = {0, 0x4000, 0};
        }
    }
}

// We spawn in the middle on the runway for the transformed Egg Carrier
void SetObjectManager::OnGetEntranceEggCarrier(EntityData1* a1)
{
    _getEntranceEggCarrierHook.Original(a1);
    if (levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_EggCarrierOutside2 && LevelEntrance == 0)
    {
        a1->Position.x = 0;
        a1->Position.y = 650;
        a1->Position.z = -1000;
        a1->Rotation.x = 0;
        a1->Rotation.y = 0x4000;
        a1->Rotation.z = 0;
    }
}

//TODO: check if this is needed
// We spawn in front of the Master Emerald Shrine in the past when time traveling
void SetObjectManager::OnGetEntrancePast(taskwk* twp)
{
    _getEntrancePastHook.Original(twp);

    if (CurrentStageAndAct == LevelAndActIDs_Past2 || levelact(NextLevel, NextAct) == LevelAndActIDs_Past2)
    {
        if (GetLevelEntranceID() == 1)
        {
            twp->pos = {0, 10, 300};
            twp->ang = {0, 0x4000, 0};
            return;
        }
    }
    if (CurrentStageAndAct == LevelAndActIDs_Past1 || levelact(NextLevel, NextAct) == LevelAndActIDs_Past1)
    {
        if (GetLevelEntranceID() == 2)
        {
            twp->pos = {-151.5f, 300, 30};
            twp->ang = {0, 0x4000, 0};
            return;
        }
    }
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
    case StationSquareMain:
        SetLevelAndAct(LevelIDs_StationSquare, 3);
        break;
    case Station:
        SetLevelAndAct(LevelIDs_StationSquare, 1);
        SetEntranceNumber(0);
        break;
    case HotelArea:
        SetLevelAndAct(LevelIDs_StationSquare, 4);
        break;
    case CasinoArea:
        SetLevelAndAct(LevelIDs_StationSquare, 1);
        SetEntranceNumber(2);
        break;
    case TwinkleParkArea:
        SetLevelAndAct(LevelIDs_StationSquare, 5);
        break;
    case MysticRuinsMain:
        SetLevelAndAct(LevelIDs_MysticRuins, 0);
        break;
    case Jungle:
        SetLevelAndAct(LevelIDs_MysticRuins, 2);
        break;
    case EggCarrierOutside:
        SetLevelAndAct(LevelIDs_EggCarrierOutside, 0);
        break;
    case EggCarrierInside:
        ClearEventFlag(static_cast<EventFlags>(FLAG_SONIC_EC_TRANSFORM));
        ClearEventFlag(static_cast<EventFlags>(FLAG_MILES_EC_TRANSFORM));
        ClearEventFlag(static_cast<EventFlags>(FLAG_KNUCKLES_EC_TRANSFORM));
        ClearEventFlag(static_cast<EventFlags>(FLAG_AMY_EC_TRANSFORM));
        ClearEventFlag(static_cast<EventFlags>(FLAG_E102_EC_TRANSFORM));
        ClearEventFlag(static_cast<EventFlags>(FLAG_BIG_EC_TRANSFORM));
        SetLevelAndAct(LevelIDs_EggCarrierInside, 1);
        break;
    case AngelIsland:
        SetLevelAndAct(LevelIDs_MysticRuins, 1);
        SetEntranceNumber(1);
        break;
    case EggCarrierFrontDeck:
    case NoStatingArea:
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
            tp->twp->pos.y = -4;
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

//TODO: Later, check if we can make the quit option in a boss return us to the field
//Hook to change the level after beating the boss
Sint32 SetObjectManager::OnFinishedLevelMaybe()
{
    const Sint32 response = _finishedLevelMaybeHook.Original();
    if (GameState != MD_GAME_END)
        return response;

    if (CurrentLevel == LevelIDs_Chaos0)
    {
        SetNextLevelAndAct(LevelIDs_StationSquare, 0);
        SetEntranceNumber(0);
    }
    else if (CurrentLevel == LevelIDs_Chaos2)
    {
        SetNextLevelAndAct(LevelIDs_StationSquare, 4);
        SetEntranceNumber(5);
    }
    else if (CurrentLevel == LevelIDs_Chaos4)
    {
        SetNextLevelAndAct(LevelIDs_MysticRuins, 0);
        SetEntranceNumber(5);
    }
    else if (CurrentLevel == LevelIDs_Chaos6 || CurrentLevel == LevelIDs_Zero
        || CurrentLevel == LevelIDs_E101R || CurrentLevel == LevelIDs_SkyChase2)
    {
        SetEntranceNumber(0);
        SetNextLevelAndAct(LevelIDs_EggCarrierOutside, LastAct);
    }
    else if (CurrentLevel == LevelIDs_EggHornet || CurrentLevel == LevelIDs_SkyChase1)
    {
        SetNextLevelAndAct(LevelIDs_MysticRuins, 0);
        SetEntranceNumber(0);
    }
    else if (CurrentLevel == LevelIDs_EggWalker)
    {
        SetNextLevelAndAct(LevelIDs_StationSquare, 1);
        SetEntranceNumber(1);
    }
    else if (CurrentLevel == LevelIDs_EggViper || CurrentLevel == LevelIDs_E101)
    {
        SetNextLevelAndAct(LevelIDs_MysticRuins, 3);
        SetEntranceNumber(3);
    }
    else if (CurrentLevel == LevelIDs_TwinkleCircuit)
    {
        SetNextLevelAndAct(LevelIDs_StationSquare, 5);
        SetEntranceNumber(2);
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

void SetObjectManager::OnSetNextLevelAndActCutsceneMode(Uint8 level, Uint8 act)
{
    if (level == LevelIDs_TwinkleCircuit)
    {
        if (!_instance->_options.multipleTwinkleCircuitChecks)
        {
            _setNextLevelAndActCutsceneModeHook.Original(level, 0);
        }
        else
        {
            switch (CurrentCharacter)
            {
            case Characters_Sonic:
                // Samba GP Track
                _setNextLevelAndActCutsceneModeHook.Original(level, 2);
                break;
            case Characters_Tails:
                //Similar to original but with more stuff
                _setNextLevelAndActCutsceneModeHook.Original(level, 1);
                break;
            case Characters_Knuckles:
                //Harder Track with many sharp curves
                _setNextLevelAndActCutsceneModeHook.Original(level, 5);
                break;
            case Characters_Amy:
                //Original Track
                _setNextLevelAndActCutsceneModeHook.Original(level, 0);
                break;
            case Characters_Gamma:
                //Easier, round Track
                _setNextLevelAndActCutsceneModeHook.Original(level, 4);
                break;
            case Characters_Big:
                //Track with large walls
                _setNextLevelAndActCutsceneModeHook.Original(level, 3);
                break;
            default:
                _setNextLevelAndActCutsceneModeHook.Original(level, 0);
                break;
            }
        }
        return;
    }
    _setNextLevelAndActCutsceneModeHook.Original(level, act);
}

// Handles the Twinkle Circuit door
int SetObjectManager::OnTwinkleCircuitDoor(const char character)
{
    return _instance->_options.twinkleCircuitCheck;
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
