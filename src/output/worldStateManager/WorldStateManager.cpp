#include "WorldStateManager.h"

#include <algorithm>
#include "sadx-mod-loader/SADXModLoader/include/UsercallFunctionHandler.h"

WorldStateManager* worldStateManagerPtr;


constexpr int WARP_EGG_CARRIER_INSIDE = 35;

constexpr int WARP_STATION_SQUARE = 17;
constexpr int WARP_MYSTIC_RUINS = 6;
constexpr int WARP_EGG_CARRIER_OUTSIDE = 6;
constexpr int WARP_PAST = 10;

constexpr int SCENE_CHANGE_MYSTIC_RUINS = 33;
constexpr int RED_MOUNTAIN_DOOR_MYSTIC_RUINS = 15;
constexpr int LONG_LADDER_MYSTIC_RUINS = 59;
constexpr int CAVE_WIND_CHANGE_SCENE_MYSTIC_RUINS = 31;
constexpr int EMBLEM_MYSTIC_RUINS = 65;

constexpr int SCENE_CHANGE_STATION_SQUARE = 78;
constexpr int BEACH_GATE_STATION_SQUARE = 67;
constexpr int WALL_THAT_PUSHES_YOU_STATION_SQUARE = 93;
DataPointer(__int16, EggCarrierSunk, 0x3C62394);


// //We pretend that the egg carrier is sunk so that the hedgehog hammer is works
static bool __cdecl HandleHedgehogHammer()
{
    return GetEventFlag(EventFlags_Amy_WarriorFeather);
}

static void __cdecl HandleWarp()
{
    DisableController(0);
    if (levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_StationSquare1 && CurrentCharacter == Characters_Sonic)
        SetNextLevelAndAct_CutsceneMode(LevelIDs_Chaos0, 0);

    else if (levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_StationSquare2 && CurrentCharacter ==
        Characters_Tails)
        SetNextLevelAndAct_CutsceneMode(LevelIDs_EggWalker, 0);

    else if (levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_MysticRuins4 && CurrentCharacter == Characters_Sonic)
        SetNextLevelAndAct_CutsceneMode(LevelIDs_EggViper, 0);

    else if (levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_MysticRuins4 && CurrentCharacter == Characters_Gamma)
        SetNextLevelAndAct_CutsceneMode(LevelIDs_E101, 0);

    else if (levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_MysticRuins1 && (CurrentCharacter == Characters_Sonic
            || CurrentCharacter == Characters_Tails || CurrentCharacter == Characters_Knuckles)
        && EntityData1Ptrs[0]->Position.y < 100)
        SetNextLevelAndAct_CutsceneMode(LevelIDs_Chaos4, 0);

    else if (levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_MysticRuins1
        && (CurrentCharacter == Characters_Sonic || CurrentCharacter == Characters_Tails)
        && EntityData1Ptrs[0]->Position.y > 100 && EntityData1Ptrs[0]->Position.y < 150)
        SetNextLevelAndAct_CutsceneMode(LevelIDs_EggHornet, 0);

    else if (levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_MysticRuins1 && (CurrentCharacter == Characters_Sonic
        || CurrentCharacter == Characters_Tails) && EntityData1Ptrs[0]->Position.y > 150)
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

    else
        SetNextLevelAndAct_CutsceneMode(LevelIDs_ECGarden, 0);
}


//We don't create animals outside levels
//Allow us to spawn enemies in the adventure fields
FunctionHook<void, int, float, float, float> onCreateAnimal(0x4BE610, [](int e_num, float x, float y, float z)-> void
{
    if (CurrentLevel > LevelIDs_HedgehogHammer && CurrentLevel <= LevelIDs_HotShelter)
        onCreateAnimal.Original(e_num, x, y, z);
});

//We delete the police enemy when transitioning between levels
FunctionHook<void, task*> onPoliceEnemyMain(0x4B30E0, [](task* tp) -> void
{
    if (CutsceneMode == 3)
        return FreeTask(tp);
    onPoliceEnemyMain.Original(tp);
});

FunctionHook<void, task*> onCollisionCube(0x4D47E0, [](task* tp) -> void
{
    if (levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_MysticRuins2)
    {
        //We find the cube collision that prevent tails from entering the Master Emerald Shrine and delete it
        if (tp->twp->pos.x < -1070 && tp->twp->pos.x > -1080
            && tp->twp->pos.y < -210 && tp->twp->pos.y > -220
            && tp->twp->pos.z < -1030 && tp->twp->pos.z > -1050)
            FreeTask(tp);
    }
    else if (levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_Casinopolis2)
    {
        //We find the cube collision that prevent sonic from entering the life capsule path in SADX and delete it
        if (tp->twp->pos.x < 2 && tp->twp->pos.x > 0
            && tp->twp->pos.y < -1713 && tp->twp->pos.y > -1716
            && tp->twp->pos.z < 2769 && tp->twp->pos.z > 2765)
            FreeTask(tp);
    }

    else
        onCollisionCube.Original(tp);
});

FunctionHook<void, task*> onCollisionCylinder(0x4D4770, [](task* tp) -> void
{
    if (levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_StationSquare1)
    {
        //We find the cylinder collision that prevent sonic from clipping into the city hall in the DC conversion
        if (tp->twp->pos.x < 324 && tp->twp->pos.x > 320
            && tp->twp->pos.y < -10 && tp->twp->pos.y > -20
            && tp->twp->pos.z < 250 && tp->twp->pos.z > 240)
            FreeTask(tp);
    }
    else if (levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_StationSquare1)
    {
        //We find the cylinder collision that prevent sonic from clipping into the city hall in the DC conversion
        if (tp->twp->pos.x < 218 && tp->twp->pos.x > 215
            && tp->twp->pos.y < -10 && tp->twp->pos.y > -20
            && tp->twp->pos.z < 250 && tp->twp->pos.z > 240)
            FreeTask(tp);
    }

    else
        onCollisionCylinder.Original(tp);
});

static void __cdecl HandleWindyValleyEntrance();
UsercallFuncVoid(onSceneChangeMr_t, (int a1), (a1), 0x539220, rEBX);
static void __cdecl HandleMREntrance(int newScene);

UsercallFunc(bool, onTwinkleParkDoor_t, (char tpChar), (tpChar), 0x63EA90, rEAX, rEAX);
static bool __cdecl HandleTwinkleParkEntrance(char character);


UsercallFunc(int, onEggCarrierEggDoor_t, (int a1), (a1), 0x52B420, rEAX, rESI);
static int __cdecl HandleEggCarrierEggDoor(int a1);


UsercallFunc(int, onEggCarrierOutsideDoor_t, (int a1), (a1), 0x524070, rEAX, rESI);
static int __cdecl HandleEggCarrierOutsideDoor(int a1);


UsercallFuncVoid(_onSceneChangeECInside_t, (int a1, int a2), (a1,a2), 0x52D690, rEAX, rECX);
static void __cdecl HandleSceneChangeEcInside(int a1, int a2);

UsercallFuncVoid(_onSceneChangeECOutside_t, (int a1), (a1), 0x524FE0, rEAX);
static void __cdecl HandleSceneChangeEcOutside(int a1);

UsercallFunc(int, onSkyDeckDoor_t, (EntityData1 * a1), (a1), 0x51DEB0, rEAX, rESI);
static int __cdecl HandleSkyDeckDoor(EntityData1* a1);

UsercallFuncVoid(onLostWorldEntranceCollision_t, (int a1), (a1), 0x532960, rEDI);
static void __cdecl HandleLostWorldEntranceCollision(int a1);

char LeonTimer1 = 10;
char LeonTimer2 = 30;

WorldStateManager::WorldStateManager()
{
    _visitedLevels = VisitedLevels();
    onSceneChangeMr_t.Hook(HandleMREntrance);
    onTwinkleParkDoor_t.Hook(HandleTwinkleParkEntrance);
    onEggCarrierEggDoor_t.Hook(HandleEggCarrierEggDoor);
    onEggCarrierOutsideDoor_t.Hook(HandleEggCarrierOutsideDoor);
    _onSceneChangeECInside_t.Hook(HandleSceneChangeEcInside);
    _onSceneChangeECOutside_t.Hook(HandleSceneChangeEcOutside);
    onSkyDeckDoor_t.Hook(HandleSkyDeckDoor);
    onLostWorldEntranceCollision_t.Hook(HandleLostWorldEntranceCollision);
    WriteCall(reinterpret_cast<void*>(0x5264C5), &HandleWarp);

    WriteCall(reinterpret_cast<void*>(0x528271), &HandleHedgehogHammer);

    WriteCall(reinterpret_cast<void*>(0x537F52), &HandleWindyValleyEntrance);
    WriteCall(reinterpret_cast<void*>(0x537F64), &HandleWindyValleyEntrance);


    worldStateManagerPtr = this;

    //We allow Tails and Big to enter the Master Emerald Shrine
    DataArray(int, islandDoorFlags, 0x111E010, 8);
    islandDoorFlags[Characters_Tails] = FLAG_SONIC_MR_ISLANDDOOR;
    islandDoorFlags[Characters_Big] = FLAG_SONIC_MR_ISLANDDOOR;
    islandDoorFlags[Characters_Amy] = FLAG_SONIC_MR_ISLANDDOOR;

    //We replace the checkpoint for a warp object from the Egg Carrier
    ObjList_SSquare[WARP_STATION_SQUARE] = ObjList_ECarrier3[WARP_EGG_CARRIER_INSIDE];
    ObjList_MRuins[WARP_MYSTIC_RUINS] = ObjList_ECarrier3[WARP_EGG_CARRIER_INSIDE];
    ObjList_MRuins[EMBLEM_MYSTIC_RUINS].Distance = 1000000.0f;
    ObjList_MRuins[EMBLEM_MYSTIC_RUINS].UseDistance = 1;
    ObjList_ECarrier0[WARP_EGG_CARRIER_OUTSIDE] = ObjList_ECarrier3[WARP_EGG_CARRIER_INSIDE];
    ObjList_Past[WARP_PAST] = ObjList_ECarrier3[WARP_EGG_CARRIER_INSIDE];

    WriteData<1>((char*)0x004A6B8C, LeonTimer1); // Leon timer 1
    WriteData<1>((char*)0x004A81C1, LeonTimer2); // Leon timer 2
    WriteData((float**)0x004CD75A, &_nj_screen_.w); // From SADXFE
    WriteData((float**)0x004CD77C, &_nj_screen_.h); // From SADXFE
}


void WorldStateManager::SetEventFlags(std::vector<StoryFlags> storyFlags)
{
    for (StoryFlags storyFlag : storyFlags)
    {
        SetEventFlag(static_cast<EventFlags>(storyFlag));
    }
    WriteSaveFile();
}


void WorldStateManager::UnlockSuperSonic()
{
    SetEventFlag(static_cast<EventFlags>(FLAG_SUPERSONIC_PLAYABLE));
    WriteSaveFile();
}

void WorldStateManager::UpdateOptions(const Options newOptions)
{
    this->options = newOptions;
}

void WorldStateManager::UpdateUnlockStatus(UnlockStatus newUnlockStatus)
{
    this->unlockStatus = newUnlockStatus;
}

void WorldStateManager::UpdateChecks(const std::map<int, LocationData>& checkData)
{
    this->_checkData = checkData;
}

bool WorldStateManager::IsSkyChase1Enabled()
{
    if (!this->options.skyChaseChecks)
        return false;

    if ((this->options.skyChaseChecksHard && this->_checkData[28].checked) ||
        (!this->options.skyChaseChecksHard && this->_checkData[27].checked))
        return false;

    return true;
}

void WorldStateManager::DrawDisableDoorIndicator(const NJS_POINT3 basePoint, const float angle)
{
    NJS_POINT3COL point3Col;
    NJS_POINT3 point[] = {
        {basePoint.x, basePoint.y + CROSS_SIZE_MIN, basePoint.z},
        {basePoint.x + CROSS_SIZE_DIFF, basePoint.y + CROSS_SIZE_MAX, basePoint.z},
        {basePoint.x + CROSS_SIZE_MAX, basePoint.y + CROSS_SIZE_DIFF, basePoint.z},
        {basePoint.x + CROSS_SIZE_MIN, basePoint.y, basePoint.z},
        {basePoint.x + CROSS_SIZE_MAX, basePoint.y - CROSS_SIZE_DIFF, basePoint.z},
        {basePoint.x + CROSS_SIZE_DIFF, basePoint.y - CROSS_SIZE_MAX, basePoint.z},
        {basePoint.x, basePoint.y - CROSS_SIZE_MIN, basePoint.z},
        {basePoint.x - CROSS_SIZE_DIFF, basePoint.y - CROSS_SIZE_MAX, basePoint.z},
        {basePoint.x - CROSS_SIZE_MAX, basePoint.y - CROSS_SIZE_DIFF, basePoint.z},
        {basePoint.x - CROSS_SIZE_MIN, basePoint.y, basePoint.z},
        {basePoint.x - CROSS_SIZE_MAX, basePoint.y + CROSS_SIZE_DIFF, basePoint.z},
        {basePoint.x - CROSS_SIZE_DIFF, basePoint.y + CROSS_SIZE_MAX, basePoint.z},
    };
    // Rotation angle in radians
    const float theta = angle * (3.14 / 180.0f);
    const float cosTheta = cos(theta);
    const float sinTheta = sin(theta);

    // Rotate each point around the Y axis
    for (auto& p : point)
    {
        float x = p.x - basePoint.x;
        float z = p.z - basePoint.z;

        p.x = x * cosTheta + z * sinTheta + basePoint.x;
        p.z = -x * sinTheta + z * cosTheta + basePoint.z;
    }

    point3Col.p = point;
    point3Col.tex = nullptr;
    point3Col.col = this->_wrongDoorColor;
    late_DrawPolygon3D(&point3Col, 12, NJD_TRANSPARENT, LATE_LIG);
}

void WorldStateManager::DrawCorrectDoorIndicator(const NJS_POINT3 basePoint, const float angle)
{
    NJS_POINT3COL point3Col;
    NJS_POINT3 point[] = {
        {basePoint.x, basePoint.y + ARROW_SIZE_MAX, basePoint.z},
        {basePoint.x + ARROW_SIZE_MIN, basePoint.y + ARROW_SIZE_MAX - ARROW_SIZE_MIN, basePoint.z},
        {basePoint.x + ARROW_SIZE_MIN / 3, basePoint.y + ARROW_SIZE_MAX - ARROW_SIZE_MIN, basePoint.z},
        {basePoint.x + ARROW_SIZE_MIN / 3, basePoint.y - ARROW_SIZE_MAX, basePoint.z},
        {basePoint.x - ARROW_SIZE_MIN / 3, basePoint.y - ARROW_SIZE_MAX, basePoint.z},
        {basePoint.x - ARROW_SIZE_MIN / 3, basePoint.y + ARROW_SIZE_MAX - ARROW_SIZE_MIN, basePoint.z},
        {basePoint.x - ARROW_SIZE_MIN, basePoint.y + ARROW_SIZE_MAX - ARROW_SIZE_MIN, basePoint.z},
    };
    // Rotation angle in radians
    const float theta = angle * (3.14 / 180.0f);
    const float cosTheta = cos(theta);
    const float sinTheta = sin(theta);

    // Rotate each point around the Y axis
    for (auto& p : point)
    {
        float x = p.x - basePoint.x;
        float z = p.z - basePoint.z;

        p.x = x * cosTheta + z * sinTheta + basePoint.x;
        p.z = -x * sinTheta + z * cosTheta + basePoint.z;
    }

    const EntityData1* player = EntityData1Ptrs[0];
    const double dz = basePoint.z - player->Position.z;
    const double dy = basePoint.y - player->Position.y;
    const double dx = basePoint.x - player->Position.x;
    const double distance = sqrt(dx * dx + dy * dy + dz * dz);

    float extraPercentage;
    if (distance <= MIN_DRAW_DOOR_ARROW_DISTANCE)
        extraPercentage = 0;
    else if (distance >= MAX_DRAW_DOOR_ARROW_DISTANCE)
        extraPercentage = 1;
    else
        extraPercentage = (distance - MIN_DRAW_DOOR_ARROW_DISTANCE) / (MAX_DRAW_DOOR_ARROW_DISTANCE -
            MIN_DRAW_DOOR_ARROW_DISTANCE);

    uint8_t newAlpha = static_cast<uint8_t>(0xAA - 0xAA * (1 - extraPercentage));
    _arrowColor.argb.a = newAlpha;

    NJS_COLOR arrowColor[7] = {
        _arrowColor,
        _arrowColor,
        _arrowColor,
        _arrowColor,
        _arrowColor,
        _arrowColor,
        _arrowColor,
    };

    point3Col.p = point;
    point3Col.tex = nullptr;
    point3Col.col = arrowColor;
    late_DrawPolygon3D(&point3Col, 7, NJD_TRANSPARENT, LATE_LIG);
}

void WorldStateManager::DrawOtherDoorIndicator(const NJS_POINT3 basePoint, const float angle)
{
    NJS_POINT3COL point3Col;
    NJS_POINT3 point[] = {
        {basePoint.x + ARROW_SIZE_MAX, basePoint.y, basePoint.z},
        {basePoint.x + ARROW_SIZE_MAX - ARROW_SIZE_MIN, basePoint.y + ARROW_SIZE_MIN, basePoint.z},
        {basePoint.x + ARROW_SIZE_MAX - ARROW_SIZE_MIN, basePoint.y + ARROW_SIZE_MIN / 3, basePoint.z},
        {basePoint.x - ARROW_SIZE_MAX, basePoint.y + ARROW_SIZE_MIN / 3, basePoint.z},
        {basePoint.x - ARROW_SIZE_MAX, basePoint.y - ARROW_SIZE_MIN / 3, basePoint.z},
        {basePoint.x + ARROW_SIZE_MAX - ARROW_SIZE_MIN, basePoint.y - ARROW_SIZE_MIN / 3, basePoint.z},
        {basePoint.x + ARROW_SIZE_MAX - ARROW_SIZE_MIN, basePoint.y - ARROW_SIZE_MIN, basePoint.z},
    };
    // Rotation angle in radians
    const float theta = angle * (3.14 / 180.0f);
    const float cosTheta = cos(theta);
    const float sinTheta = sin(theta);

    // Rotate each point around the Y axis
    for (auto& p : point)
    {
        float x = p.x - basePoint.x;
        float z = p.z - basePoint.z;

        p.x = x * cosTheta + z * sinTheta + basePoint.x;
        p.z = -x * sinTheta + z * cosTheta + basePoint.z;
    }
    point3Col.p = point;
    point3Col.tex = nullptr;
    point3Col.col = this->_otherDoorColor;
    late_DrawPolygon3D(&point3Col, 7, NJD_TRANSPARENT, LATE_LIG);
}

void WorldStateManager::ShowLevelEntranceArrows()
{
    if (!this->options.entranceRandomizer)
        return;
    if (!this->_showEntranceIndicators)
        return;
    for (LevelArrow levelArrow : _levelArrows)
    {
        if (CurrentStageAndAct != levelArrow.levelAndAct)
            continue;

        if (!worldStateManagerPtr->levelEntrances.canEnter(levelArrow.entrance, CurrentCharacter))
            DrawDisableDoorIndicator(levelArrow.postion, levelArrow.angle);
        else if (levelArrow.isForCharacter(static_cast<Characters>(CurrentCharacter)))
            DrawCorrectDoorIndicator(levelArrow.postion, levelArrow.angle);
        else
            DrawOtherDoorIndicator(levelArrow.postion, levelArrow.angle);
    }
}

void WorldStateManager::OnFrame()
{
    if (DemoPlaying > 0)
        return;
    if (CurrentLevel == LevelIDs_PerfectChaos)
        return;

    if (IsSkyChase1Enabled() && (CurrentCharacter == Characters_Sonic || CurrentCharacter == Characters_Tails))
        EventFlagArray[33] = 1;

    if (Current_CharObj2 != nullptr && EntityData1Ptrs[0] != nullptr)
        this->ShowLevelEntranceArrows();

    if (this->eggCarrierTransformationCutscene)
    {
        if (levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_EggCarrierOutside4)
            EggCarrierSunk = false;
        else
            EggCarrierSunk = true;
    }

    if (CurrentLevel >= LevelIDs_TwinkleCircuit && CurrentLevel <= LevelIDs_SandHill)
        GameMode = GameModes_Adventure_ActionStg;
    else if (GameMode == GameModes_Adventure_Field || GameMode == GameModes_Adventure_ActionStg)
        GameMode = GameModes_Mission;
}

//Enable all GameGear Games
FunctionHook<int> onHowManyGameGearGames(0x6FDA90, []()-> int
{
    return 12;
});

FunctionHook<bool> onIsGameGearMenuEnabled(0x506460, []()-> bool
{
    return true;
});

//Allow Knuckles to fight Chaos 2
FunctionHook<BOOL> isChaos2DoorOpen(0x638D50, []()-> BOOL
{
    return CurrentCharacter == Characters_Knuckles;
});

FunctionHook<BOOL> isStationDoorOpen(0x63AB70, []()-> BOOL
{
    return worldStateManagerPtr->unlockStatus.keyStationFrontKeys;
});

FunctionHook<BOOL> isHotelDoorOpen(0x630900, []()-> BOOL
{
    return worldStateManagerPtr->unlockStatus.keyHotelFrontKeys;
});

FunctionHook<BOOL> isCasinoHotelDoorOpen(0x630970, []()-> BOOL
{
    return worldStateManagerPtr->unlockStatus.keyHotelBackKeys;
});
FunctionHook<BOOL> isCasinoStationDoorOpen(0x638880, []()-> BOOL
{
    return worldStateManagerPtr->unlockStatus.keyStationBackKeys;
});


//Prevents the recap screen from showing on the last story
FunctionHook<int, int> showRecap(0x643C00, [](int _)-> int
{
    return -1;
});

// Replace Super Sonic "Hmph" with "I'll show you what the Chaos Emeralds can really do."
FunctionHook<void, int> onPlayVoice(0x425710, [](int a1)-> void
{
    if (a1 == 396)
        return onPlayVoice.Original(388);

    return onPlayVoice.Original(a1);
});

//Prevents adding extra 10 seconds for Sonic and Tails
FunctionHook<void, int> onAddSeconds(0x426640, [](int seconds)-> void
{
    if (seconds == 10 && (CurrentCharacter == Characters_Sonic || CurrentCharacter == Characters_Tails))
        return;

    return onAddSeconds.Original(seconds);
});

//We create a custom spawn point after exiting sand hill
FunctionHook<void, EntityData1*> onGetEntranceMRuins(0x530790, [](EntityData1* a1)-> void
{
    onGetEntranceMRuins.Original(a1);
    if (LastLevel == LevelIDs_SandHill)
    {
        a1->Position.x = -1500;
        a1->Position.y = 50;
        a1->Position.z = -70;
        a1->Rotation.x = 0;
        a1->Rotation.y = 4000;
        a1->Rotation.z = 0;
    }
    else if (LastLevel == LevelIDs_Past)
    {
        a1->Position.x = -2.5f;
        a1->Position.y = -240;
        a1->Position.z = 2480;
        a1->Rotation.x = 0;
        a1->Rotation.y = 4000;
        a1->Rotation.z = 0;
    }
});

//We spawn in the middle on the runway for the transformed Egg Carrier
FunctionHook<void, EntityData1*> onGetEntranceEggCarrier(0x52D820, [](EntityData1* a1)-> void
{
    onGetEntranceEggCarrier.Original(a1);
    if (levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_EggCarrierOutside2 && LevelEntrance == 0)
    {
        a1->Position.x = 0;
        a1->Position.y = 650;
        a1->Position.z = -1000;
        a1->Rotation.x = 0;
        a1->Rotation.y = 0x4000;
        a1->Rotation.z = 0;
    }
});

//We spawn in front of the Master Emerald Shrine in the past when time traveling
FunctionHook<void, EntityData1*> onGetEntrancePast(0x542180, [](EntityData1* a1)-> void
{
    onGetEntrancePast.Original(a1);
    if (levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_Past2 && LastLevel == LevelIDs_MysticRuins)
    {
        a1->Position.x = 0;
        a1->Position.y = 10;
        a1->Position.z = 380;
        a1->Rotation.x = 0;
        a1->Rotation.y = 0x4000;
        a1->Rotation.z = 0;
    }
});

//Set starting location when we get a game over 
FunctionHook<void, Sint8> onSetTimeOfDay(0x412C00, [](Sint8 time)-> void
{
    onSetTimeOfDay.Original(time);
    if (GameState == MD_GAME_CONTINUE)
        worldStateManagerPtr->SetStartingArea();
});

//Set starting location when starting the adventure
FunctionHook<void> onAdventureSetLevelAndAct(0x4133E0, []()-> void
{
    onAdventureSetLevelAndAct.Original();
    worldStateManagerPtr->SetStartingArea();
});

void WorldStateManager::SetStartingArea()
{
    if (LastStoryFlag == 1)
        return;
    switch (this->options.GetCharacterStartingArea(static_cast<Characters>(CurrentCharacter)))
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

void WorldStateManager::StartAllMissions()
{
    for (int i = 0; i < 60; i++)
    {
        if (!(MissionFlags[i] & MissionFlags_Complete))
        {
            MissionFlags[i] |= MissionFlags_Found;
            MissionFlags[i] |= MissionFlags_Started;
        }
    }
    WriteSaveFile();
}

void WorldStateManager::MarkBlacklistedMissionsAsCompleted(const std::vector<int>& missionBlacklist)
{
    for (const int mission : missionBlacklist)
    {
        MissionFlags[mission - 1] |= MissionFlags_Found;
        MissionFlags[mission - 1] &= ~MissionFlags_Started;
        MissionFlags[mission - 1] |= MissionFlags_Complete;
    }
    WriteSaveFile();
}


void WorldStateManager::UpdateLevelEntrances(LevelEntrances levelEntrances)
{
    this->levelEntrances = levelEntrances;
    this->_visitedLevels.emeraldCoastEntranceActualLevel = levelEntrances.getLevelInitialsFromEntrance(EmeraldCoast);
    this->_visitedLevels.windyValleyEntranceActualLevel = levelEntrances.getLevelInitialsFromEntrance(WindyValley);
    this->_visitedLevels.casinopolisEntranceActualLevel = levelEntrances.getLevelInitialsFromEntrance(Casinopolis);
    this->_visitedLevels.iceCapEntranceActualLevel = levelEntrances.getLevelInitialsFromEntrance(IceCap);
    this->_visitedLevels.twinkleParkEntranceActualLevel = levelEntrances.getLevelInitialsFromEntrance(TwinklePark);
    this->_visitedLevels.speedHighwayEntranceActualLevel = levelEntrances.getLevelInitialsFromEntrance(SpeedHighway);
    this->_visitedLevels.redMountainEntranceActualLevel = levelEntrances.getLevelInitialsFromEntrance(RedMountain);
    this->_visitedLevels.skyDeckEntranceActualLevel = levelEntrances.getLevelInitialsFromEntrance(SkyDeck);
    this->_visitedLevels.lostWorldEntranceActualLevel = levelEntrances.getLevelInitialsFromEntrance(LostWorld);
    this->_visitedLevels.finalEggEntranceActualLevel = levelEntrances.getLevelInitialsFromEntrance(FinalEgg);
    this->_visitedLevels.hotShelterEntranceActualLevel = levelEntrances.getLevelInitialsFromEntrance(HotShelter);
}

VisitedLevels WorldStateManager::GetVisitedLevels(const int visitedLevel)
{
    const LevelIDs visitedEntrance = levelEntrances.getEntranceLevelIdFromLevel(static_cast<LevelIDs>(visitedLevel));
    switch (visitedEntrance)
    {
    case LevelIDs_EmeraldCoast:
        _visitedLevels.emeraldCoastEntranceVisited = true;
        break;
    case LevelIDs_WindyValley:
        _visitedLevels.windyValleyEntranceVisited = true;
        break;
    case LevelIDs_Casinopolis:
        _visitedLevels.casinopolisEntranceVisited = true;
        break;
    case LevelIDs_IceCap:
        _visitedLevels.iceCapEntranceVisited = true;
        break;
    case LevelIDs_TwinklePark:
        _visitedLevels.twinkleParkEntranceVisited = true;
        break;
    case LevelIDs_SpeedHighway:
        _visitedLevels.speedHighwayEntranceVisited = true;
        break;
    case LevelIDs_RedMountain:
        _visitedLevels.redMountainEntranceVisited = true;
        break;
    case LevelIDs_SkyDeck:
        _visitedLevels.skyDeckEntranceVisited = true;
        break;
    case LevelIDs_LostWorld:
        _visitedLevels.lostWorldEntranceVisited = true;
        break;
    case LevelIDs_FinalEgg:
        _visitedLevels.finalEggEntranceVisited = true;
        break;
    case LevelIDs_HotShelter:
        _visitedLevels.hotShelterEntranceVisited = true;
        break;
    default: break;
    }

    return _visitedLevels;
}

void WorldStateManager::SetEggCarrierTransformationCutscene(const bool eggCarrierTransformation)
{
    this->eggCarrierTransformationCutscene = eggCarrierTransformation;
}

DataArray(int16_t, ChaoStatValues, 0x8895C8, 0x402);

void WorldStateManager::SetChaoStatsMultiplier(const int chaoStatsMultiplier)
{
    if (chaoStatsMultiplier > 1 && chaoStatsMultiplier <= 50)
    {
        for (int i = 0x00; i < 0x402; i++)
        {
            ChaoStatValues[i] = ChaoStatValues[i] * chaoStatsMultiplier;
        }
    }
}

void WorldStateManager::SetShowEntranceIndicators(const bool showEntranceIndicators)
{
    this->_showEntranceIndicators = showEntranceIndicators;
}

typedef struct
{
    int x;
    int y;
    int z;
} NJS_INT_POINT3;

SETEntry CreateSetEntry(const int16_t objectType, const NJS_VECTOR& position, const NJS_INT_POINT3 rotation = {0, 0, 0},
                        const NJS_VECTOR& scale = {1, 1, 1})
{
    SETEntry setEntry;
    setEntry.ObjectType = objectType;
    setEntry.XRotation = rotation.x;
    setEntry.YRotation = rotation.y;
    setEntry.ZRotation = rotation.z;
    setEntry.Position = position;
    setEntry.Properties = scale;
    return setEntry;
}


void AddSetToLevel(const SETEntry& newSetEntry, const LevelAndActIDs levelAndAct, const Characters character)
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

const SETEntry FINAL_EGG_SPRING = CreateSetEntry(1, {-52.21f, -3240.81f, -190.0f});
const SETEntry SEWERS_SPRING = CreateSetEntry(1, {505, -89, 635},
                                              {0, 0, 0}, {0.3f, 0, 51});

const SETEntry RED_MOUNTAIN_SCENE_CHANGE_MR = CreateSetEntry(SCENE_CHANGE_MYSTIC_RUINS, {-2100, -304, 1650},
                                                             {0, 0, 0}, {40, 50, 0});

const SETEntry ICE_CAP_SCENE_CHANGE_MR = CreateSetEntry(SCENE_CHANGE_MYSTIC_RUINS, {-1450, 95, 360},
                                                        {1, 0, 0}, {20, 5, 0});
const SETEntry ICE_CAP_LADDER_MR = CreateSetEntry(LONG_LADDER_MYSTIC_RUINS, {-1450, 40, 360},
                                                  {0, 0XC800, 0}, {0, 0, 0});

const SETEntry CAVE_WIND_CHANGE_SCENE_MR = CreateSetEntry(CAVE_WIND_CHANGE_SCENE_MYSTIC_RUINS, {-727, 168, 744});


const SETEntry RED_MOUNTAIN_DOOR_MR = CreateSetEntry(RED_MOUNTAIN_DOOR_MYSTIC_RUINS, {-1960.7f, -350.19f, 1652.01f},
                                                     {0x1, 0xBEFB, 0xFF6E}, {0.3f, 0, 0});

const SETEntry ICE_CAP_SPRING = CreateSetEntry(1, {-1070, -35, 236},
                                               {0, 0, 0}, {0.3f, -1.25f, 1});

const SETEntry BEACH_GATE_SS = CreateSetEntry(BEACH_GATE_STATION_SQUARE, {-525, -10, 2098},
                                              {0, 0x2000, 0});

const SETEntry CITY_HALL_SCENE_CHANGE_SS = CreateSetEntry(SCENE_CHANGE_STATION_SQUARE, {270, -1, 234},
                                                          {0, 0, 0X402}, {8, 3.2, 0});

//Egg Carrier
const SETEntry EGG_CARRIER_TRANSFORM_AREA_SPRING = CreateSetEntry(1, {-83.42, 0, 0.54});

//Station Square Bosses
const SETEntry WARP_CHAOS0 = CreateSetEntry(WARP_STATION_SQUARE, {270, 0, 450});

const SETEntry WARP_EGG_WALKER = CreateSetEntry(WARP_STATION_SQUARE, {-400, -3, 955});


//Mystic Ruins Bosses
const SETEntry WARP_EGG_HORNET = CreateSetEntry(WARP_MYSTIC_RUINS, {950, 127, 950});

const SETEntry WARP_CHAOS4 = CreateSetEntry(WARP_MYSTIC_RUINS, {80, 72, 180});

const SETEntry WARP_EGG_VIPER = CreateSetEntry(WARP_MYSTIC_RUINS, {0, 0, 0});

const SETEntry WARP_E101 = CreateSetEntry(WARP_MYSTIC_RUINS, {0, 0, 0});

//Egg Carrier Bosses
const SETEntry WARP_CHAOS6 = CreateSetEntry(WARP_EGG_CARRIER_OUTSIDE, {0, 750.5f, -385.69f});

const SETEntry WARP_ZERO = CreateSetEntry(WARP_EGG_CARRIER_OUTSIDE, {0, 750.5f, -385.69f});

const SETEntry WARP_E101_MK2 = CreateSetEntry(WARP_EGG_CARRIER_OUTSIDE, {0, 750.5f, -385.69f});

//Sky Chase
const SETEntry WARP_SKY_CHASE_1 = CreateSetEntry(WARP_MYSTIC_RUINS, {1561, 201, 900}, {0, 0x1C00, 0});
const SETEntry WARP_SKY_CHASE_2_EC1 = CreateSetEntry(WARP_EGG_CARRIER_OUTSIDE, {0, 700, -1100});
const SETEntry WARP_SKY_CHASE_2_EC2 = CreateSetEntry(WARP_EGG_CARRIER_OUTSIDE, {0, 650, -1100});

//Past
const SETEntry WARP_TO_PAST = CreateSetEntry(WARP_MYSTIC_RUINS, {-2.5f, -240, 2397.5f});
const SETEntry WARP_FROM_PAST = CreateSetEntry(WARP_PAST, {0, 7, 247.5f});

FunctionHook<void> onCountSetItemsMaybe(0x0046BD20, []()-> void
{
    onCountSetItemsMaybe.Original();

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

    if (worldStateManagerPtr->eggCarrierTransformationCutscene
        && levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_EggCarrierOutside4)
        LoadPVM("EC_SKY", &EC_SKY_TEXLIST);

    //Freeze trap
    LoadNoNamePVM(&stx_ice0_TEXLIST);

    AddSetToLevel(FINAL_EGG_SPRING, LevelAndActIDs_FinalEgg3, Characters_Sonic);
    AddSetToLevel(SEWERS_SPRING, LevelAndActIDs_StationSquare3, Characters_Sonic);

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

    AddSetToLevel(EGG_CARRIER_TRANSFORM_AREA_SPRING, LevelAndActIDs_EggCarrierOutside5, Characters_Amy);
    AddSetToLevel(EGG_CARRIER_TRANSFORM_AREA_SPRING, LevelAndActIDs_EggCarrierOutside5, Characters_Knuckles);
    AddSetToLevel(EGG_CARRIER_TRANSFORM_AREA_SPRING, LevelAndActIDs_EggCarrierOutside5, Characters_Big);
    AddSetToLevel(EGG_CARRIER_TRANSFORM_AREA_SPRING, LevelAndActIDs_EggCarrierOutside5, Characters_Gamma);

    //Emerald Coast
    AddSetToLevel(BEACH_GATE_SS, LevelAndActIDs_StationSquare5, Characters_Sonic);

    //Speed Highway (City Hall)
    AddSetToLevel(CITY_HALL_SCENE_CHANGE_SS, LevelAndActIDs_StationSquare1, Characters_Big);
    AddSetToLevel(CITY_HALL_SCENE_CHANGE_SS, LevelAndActIDs_StationSquare1, Characters_Sonic);

    if (worldStateManagerPtr->options.bossChecks)
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
    }
    if (worldStateManagerPtr->options.skyChaseChecks)
    {
        //Sky Chase
        if (worldStateManagerPtr->IsSkyChase1Enabled())
        {
            AddSetToLevel(WARP_SKY_CHASE_1, LevelAndActIDs_MysticRuins1, Characters_Sonic);
            AddSetToLevel(WARP_SKY_CHASE_1, LevelAndActIDs_MysticRuins1, Characters_Tails);
        }

        AddSetToLevel(WARP_SKY_CHASE_2_EC1, LevelAndActIDs_EggCarrierOutside1, Characters_Sonic);
        AddSetToLevel(WARP_SKY_CHASE_2_EC2, LevelAndActIDs_EggCarrierOutside2, Characters_Sonic);

        AddSetToLevel(WARP_SKY_CHASE_2_EC1, LevelAndActIDs_EggCarrierOutside1, Characters_Tails);
        AddSetToLevel(WARP_SKY_CHASE_2_EC2, LevelAndActIDs_EggCarrierOutside2, Characters_Tails);
    }

    //Time Travel 
    AddSetToLevel(WARP_TO_PAST, LevelAndActIDs_MysticRuins2, Characters_Tails);
    AddSetToLevel(WARP_FROM_PAST, LevelAndActIDs_Past2, Characters_Tails);
});


// We move the emblem a little higher so Cream can get it.
FunctionHook<void, task*> onEmblemMain(0x4B4940, [](task* tp)-> void
{
    if (levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_StationSquare1 && CurrentCharacter == Characters_Tails)
        if (tp->twp->pos.x > 386 && tp->twp->pos.x < 390
            && tp->twp->pos.y > -6 && tp->twp->pos.y < -5
            && tp->twp->pos.z > 489 && tp->twp->pos.z < 492)
        {
            tp->twp->pos.y = -4;
        }

    onEmblemMain.Original(tp);
});

FunctionHook<void> onMissionSetLoad(0x591A70, []()-> void
{
    if (!worldStateManagerPtr->options.missionModeEnabled)
        return;

    onMissionSetLoad.Original();

    for (int i = 0; i < MissionSetCount; ++i)
    {
        const SETObjData* objData = &MissionSETTable[i];
        if (objData->SETEntry != nullptr)
        {
            const NJS_VECTOR position = objData->SETEntry->Position;
            //We move the mission switch from Big's bed
            if (levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_MysticRuins3 && position.x > 1294 && position.x <
                1298 && position.y > 130 && position.y < 133 && position.z > -729 && position.z < -726)
            {
                objData->SETEntry->Position = {1333, 120, -707};
            }
            //We move the mission card in the sewer, so it doesn't clip with the srping
            if (levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_StationSquare3 && position.x > 506 && position.x <
                507 && position.y > -89 && position.y < -88 && position.z > 635 && position.z < 636)
            {
                objData->SETEntry->Position = {position.x, -70, position.z};
            }

            //We move the mission card 51 in the jungle, so Gamma can get it even if the Snake door is open
            if (levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_MysticRuins3
                && position.x > -515 && position.x < -510
                && position.y > 204 && position.y < 206
                && position.z > -1128 && position.z < -1120)
            {
                objData->SETEntry->Position = {-473.5, 91.5, -1026};
            }
        }
    }
});


//Hook to change the level after beating the boss
FunctionHook<Sint32> onFinishedLevelMaybe(0x414090, []()-> Sint32
{
    const Sint32 response = onFinishedLevelMaybe.Original();
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
    return response;
});

FunctionHook<void, task*> onMysticRuinsKey(0x532400, [](task* tp)-> void
{
    // We prevent the wind stone from spawning if the player doesn't have the item
    if (levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_MysticRuins1
        && (!worldStateManagerPtr->unlockStatus.keyWindStone
            || !worldStateManagerPtr->levelEntrances.canEnter(WindyValley, CurrentCharacter)))
        if (tp->twp->pos.x > 1390 && tp->twp->pos.x < 1395
            && tp->twp->pos.y > 190 && tp->twp->pos.y < 193
            && tp->twp->pos.z > 862 && tp->twp->pos.z < 865)
            return;
    // We don't spawn the golden/silver keys for knuckles if he can enter LostWorld
    if (levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_MysticRuins3 && CurrentCharacter == Characters_Knuckles)
    {
        if (!worldStateManagerPtr->levelEntrances.canEnter(LostWorld, CurrentCharacter))
            return;
    }
    onMysticRuinsKey.Original(tp);
});

FunctionHook<void, task*> onEmployeeCard(0x63C370, [](task* tp)-> void
{
    // We prevent the Employee card from spawning if the player doesn't have the item, or he can't use it
    if (levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_StationSquare4
        && (!worldStateManagerPtr->unlockStatus.keyEmployeeCard
            || !worldStateManagerPtr->levelEntrances.canEnter(SpeedHighway, CurrentCharacter)))
        return;
    onEmployeeCard.Original(tp);
});

// We make Big's hud think we are not in the mission mode
FunctionHook<void> onBigHud_DrawWeightAndLife(0x46FB00, []()-> void
{
    const GameModes bufferGameMode = GameMode;
    if (CurrentLevel >= LevelIDs_StationSquare && CurrentLevel <= LevelIDs_Past)
        GameMode = GameModes_Adventure_Field;
    else
        GameMode = GameModes_Adventure_ActionStg;
    onBigHud_DrawWeightAndLife.Original();
    GameMode = bufferGameMode;
});


// Handles the return position
FunctionHook<void, task*> onSetStartPosReturnToField(0x414500, [](task* tp)-> void
{
    if (CurrentLevel < LevelIDs_EmeraldCoast || CurrentLevel > LevelIDs_HotShelter)
    {
        onSetStartPosReturnToField.Original(tp);
        return;
    }
    const short currentLevelBuffer = CurrentLevel;
    if (CurrentCharacter == Characters_Sonic || CurrentCharacter == Characters_Tails
        || CurrentCharacter == Characters_Knuckles)
        CurrentLevel = LevelIDs_SpeedHighway;
    else
        CurrentLevel = LevelIDs_HotShelter;

    onSetStartPosReturnToField.Original(tp);
    CurrentLevel = currentLevelBuffer;

    const LevelIDs entranceLevel = worldStateManagerPtr->
                                   levelEntrances.getEntranceLevelIdFromLevel(static_cast<LevelIDs>(CurrentLevel));

    switch (entranceLevel)
    {
    case LevelIDs_EmeraldCoast:
        FieldStartPos->Position = {-492.79999, 10, 2053.8};
        FieldStartPos->YRot = 0x0DBA9;
        break;
    case LevelIDs_WindyValley:
        FieldStartPos->Position = {644.90002, 59.099998, -155.0};
        FieldStartPos->YRot = 0x6000;
        break;
    case LevelIDs_TwinklePark:
        FieldStartPos->Position = {785.29999, 50.0, 1771.7};
        FieldStartPos->YRot = 0x7AB7;
        break;
    case LevelIDs_SpeedHighway:
        if (CurrentCharacter == Characters_Knuckles)
        {
            FieldStartPos->Position = {272.0, 4.0, 294.89999};
            FieldStartPos->YRot = 0x3D0C;
        }
        else
        {
            FieldStartPos->Position = {347.79999, 0.0, 1370.3};
            FieldStartPos->YRot = 0x7FB9;
        }
        break;
    case LevelIDs_RedMountain:
        FieldStartPos->Position = {-1945.7, -351.5, 1646.6};
        FieldStartPos->YRot = 0x5F9;
        break;
    case LevelIDs_SkyDeck:
        if (CurrentCharacter == Characters_Knuckles)
        {
            FieldStartPos->Position = {290.0, 17.0, 0.0};
            FieldStartPos->YRot = 0x8000;
        }
        else
        {
            FieldStartPos->Position = {0.0, 655.0, 146.0};
            FieldStartPos->YRot = 0x0C000;
        }
        break;

    case LevelIDs_LostWorld:
        if (CurrentCharacter == Characters_Knuckles)
        {
            FieldStartPos->Position = {-515.90002, 16.6, -1446.0};
            FieldStartPos->YRot = 0xC000;
        }
        else
        {
            FieldStartPos->Position = {-515.0, 92.0, -1054.0};
            FieldStartPos->YRot = 0x4000;
        }
        break;
    case LevelIDs_IceCap:
        FieldStartPos->Position = {-1290.0, 27.5, 315.0};
        FieldStartPos->YRot = 0x0EC68;
        break;
    case LevelIDs_Casinopolis:
        FieldStartPos->Position = {-572.5, -2.5, 939.5};
        FieldStartPos->YRot = 0x1F17;
        break;
    case LevelIDs_FinalEgg:
        if (CurrentCharacter == Characters_Gamma)
        {
            FieldStartPos->Position = {-0.5, 108.8, -138.10001};
            FieldStartPos->YRot = 0x4537;
        }
        else
        {
            FieldStartPos->Position = {133.39999, 108.4, -7.1999998};
            FieldStartPos->YRot = 0x70EF;
        }
        break;
    case LevelIDs_HotShelter:
        FieldStartPos->Position = {0.0, 14.0, 160.0};
        FieldStartPos->YRot = 0xC000;
        break;
    default: ;
    }
});


FunctionHook<void, task*> onSceneChangeMainStationSquare(0x640850, [](task* tp)-> void
{
    const auto& pos = tp->twp->pos;

    // Emerald Coast Entrance
    if (levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_StationSquare5
        && worldStateManagerPtr->levelEntrances.canEnter(EmeraldCoast, CurrentCharacter)
        && pos.x > -590 && pos.x < -580 && pos.y > -25 && pos.y < -15 && pos.z > 2130 && pos.z < 2140)
    {
        tp->twp->ang.z = worldStateManagerPtr->levelEntrances.getLevelAndActIdFromEntrance(
            EmeraldCoast, CurrentCharacter);
    }
    //  Casinopolis
    if (levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_StationSquare2
        && worldStateManagerPtr->levelEntrances.canEnter(Casinopolis, CurrentCharacter)
        && pos.x > -646 && pos.x < -642 && pos.y > -8 && pos.y < 4 && pos.z > 878 && pos.z < 882)
    {
        tp->twp->ang.z = worldStateManagerPtr->levelEntrances.getLevelAndActIdFromEntrance(
            Casinopolis, CurrentCharacter);
    }

    // TwinklePark
    if (levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_StationSquare6
        && worldStateManagerPtr->levelEntrances.canEnter(TwinklePark, CurrentCharacter)
        && pos.x > 850 && pos.x < 860 && pos.y > 40 && pos.y < 50 && pos.z > 1760 && pos.z < 1780)
    {
        tp->twp->ang.z = worldStateManagerPtr->levelEntrances.getLevelAndActIdFromEntrance(
            TwinklePark, CurrentCharacter);
    }

    // SpeedHighway (City Hall)
    if (levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_StationSquare1
        && worldStateManagerPtr->levelEntrances.canEnter(SpeedHighway, CurrentCharacter)
        && pos.x > 269 && pos.x < 272 && pos.y > -4 && pos.y < 0 && pos.z > 232 && pos.z < 236)
    {
        tp->twp->ang.z = worldStateManagerPtr->levelEntrances.getLevelAndActIdFromEntrance(
            SpeedHighway, CurrentCharacter);
    }

    onSceneChangeMainStationSquare.Original(tp);
});

// SpeedHighway (Mains Area)
FunctionHook<void, Uint8, Uint8> onSetNextLevelAndActCutsceneMode(0x4145D0, [](Uint8 level, Uint8 act)-> void
{
    if (levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_StationSquare4)
    {
        const EntityData1* player = EntityData1Ptrs[0];
        if (player->Position.x > 400 && player->Position.x < 550
            && player->Position.y > -10 && player->Position.y < 50
            && player->Position.z > 1300 && player->Position.z < 1450)
        {
            const LevelAndActIDs levelAndAct = worldStateManagerPtr->levelEntrances.getLevelAndActIdFromEntrance(
                SpeedHighway, CurrentCharacter);
            onSetNextLevelAndActCutsceneMode.Original(GET_LEVEL(levelAndAct), GET_ACT(levelAndAct));
            return;
        }
    }
    onSetNextLevelAndActCutsceneMode.Original(level, act);
});

// WindyValley
static void __cdecl HandleWindyValleyEntrance()
{
    if (worldStateManagerPtr->levelEntrances.canEnter(WindyValley, CurrentCharacter))
    {
        const LevelAndActIDs levelAndAct = worldStateManagerPtr->levelEntrances.getLevelAndActIdFromEntrance(
            WindyValley, CurrentCharacter);
        SetNextLevelAndAct_CutsceneMode(GET_LEVEL(levelAndAct), GET_ACT(levelAndAct));
    }
}

// MysticRuins
static void __cdecl HandleMREntrance(const int newScene)
{
    // Jungle Final Egg tower
    if (levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_MysticRuins3 && newScene == 5)
    {
        SetNextLevelAndAct_CutsceneMode(LevelIDs_MysticRuins, 3);
    }
    else if (levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_MysticRuins4 && newScene == 4)
    {
        SetNextLevelAndAct_CutsceneMode(LevelIDs_MysticRuins, 2);
        SetLevelEntrance(4);
    }
    // Final Egg
    else if (levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_MysticRuins4
        && worldStateManagerPtr->levelEntrances.canEnter(FinalEgg, CurrentCharacter) && (newScene == 2 || newScene ==
            3))
    {
        const LevelAndActIDs levelAndAct = worldStateManagerPtr->levelEntrances.getLevelAndActIdFromEntrance(
            FinalEgg, CurrentCharacter);
        SetNextLevelAndAct_CutsceneMode(GET_LEVEL(levelAndAct), GET_ACT(levelAndAct));
    }
    // Lost World
    else if (levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_MysticRuins3
        && worldStateManagerPtr->levelEntrances.canEnter(LostWorld, CurrentCharacter) && (newScene == 6 || newScene ==
            7))
    {
        const LevelAndActIDs levelAndAct = worldStateManagerPtr->levelEntrances.getLevelAndActIdFromEntrance(
            LostWorld, CurrentCharacter);
        SetNextLevelAndAct_CutsceneMode(GET_LEVEL(levelAndAct), GET_ACT(levelAndAct));
    }
    // Ice Cap
    else if (levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_MysticRuins2
        && worldStateManagerPtr->levelEntrances.canEnter(IceCap, CurrentCharacter) && newScene == 1)
    {
        const LevelAndActIDs levelAndAct = worldStateManagerPtr->levelEntrances.getLevelAndActIdFromEntrance(
            IceCap, CurrentCharacter);
        SetNextLevelAndAct_CutsceneMode(GET_LEVEL(levelAndAct), GET_ACT(levelAndAct));
    }
    // Red Mountain
    else if (levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_MysticRuins2
        && worldStateManagerPtr->levelEntrances.canEnter(RedMountain, CurrentCharacter) && newScene == 0)
    {
        const LevelAndActIDs levelAndAct = worldStateManagerPtr->levelEntrances.getLevelAndActIdFromEntrance(
            RedMountain, CurrentCharacter);
        SetNextLevelAndAct_CutsceneMode(GET_LEVEL(levelAndAct), GET_ACT(levelAndAct));
    }
    else
    {
        onSceneChangeMr_t.Original(newScene);
    }
}


// HotShelter
void HandleSceneChangeEcInside(int a1, int a2)
{
    if (levelact(CurrentLevel, CurrentAct) != LevelAndActIDs_EggCarrierInside2)
        return _onSceneChangeECInside_t.Original(a1, a2);

    const int doorId = *(_DWORD*)(a1 + 20);
    if (doorId != 512)
        return _onSceneChangeECInside_t.Original(a1, a2);

    const LevelAndActIDs levelAndAct = worldStateManagerPtr->levelEntrances.getLevelAndActIdFromEntrance(
        HotShelter, CurrentCharacter);
    camerahax_adventurefields();
    SetNextLevelAndAct_CutsceneMode(GET_LEVEL(levelAndAct), GET_ACT(levelAndAct));
}


// SkyDeck
void HandleSceneChangeEcOutside(int a1)
{
    if (levelact(CurrentLevel, CurrentAct) != LevelAndActIDs_EggCarrierOutside6 && levelact(CurrentLevel, CurrentAct) !=
        LevelAndActIDs_EggCarrierOutside2)
        return _onSceneChangeECOutside_t.Original(a1);
    const int doorId = *(_DWORD*)(a1 + 20);
    if (doorId != 256)
        return _onSceneChangeECOutside_t.Original(a1);
    const LevelAndActIDs levelAndAct = worldStateManagerPtr->levelEntrances.getLevelAndActIdFromEntrance(
        SkyDeck, CurrentCharacter);
    camerahax_adventurefields();
    SetNextLevelAndAct_CutsceneMode(GET_LEVEL(levelAndAct), GET_ACT(levelAndAct));
}

// Handles the Emerald Coast entrance
FunctionHook<BOOL> isEmeraldCoastOpen(0x639A30, []()-> BOOL
{
    if (CurrentCharacter == Characters_Gamma)
        return false;
    return worldStateManagerPtr->levelEntrances.canEnter(EmeraldCoast, CurrentCharacter);
});

FunctionHook<void, task*> loadEmeraldCoastGateTargets(0x63A0C0, [](task* tp)-> void
{
    if (levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_StationSquare5
        && !worldStateManagerPtr->levelEntrances.canEnter(EmeraldCoast, CurrentCharacter))
        FreeTask(tp);
    else
        loadEmeraldCoastGateTargets.Original(tp);
});

// Handles the Windy Valley entrance
// Makes Sonic, Tails and Gamma use the winds stone
FunctionHook<BOOL> isWindyValleyOpen(0x536E40, []()-> BOOL
{
    if (CurrentCharacter == Characters_Sonic)
        return EventFlagArray[FLAG_SONIC_MR_WINDYSTONE] && worldStateManagerPtr->levelEntrances.canEnter(
            WindyValley, CurrentCharacter);

    if (CurrentCharacter == Characters_Tails)
        return EventFlagArray[FLAG_MILES_MR_WINDYSTONE] && worldStateManagerPtr->levelEntrances.canEnter(
            WindyValley, CurrentCharacter);

    if (CurrentCharacter == Characters_Gamma)
        return EventFlagArray[FLAG_E102_MR_WINDYSTONE] && worldStateManagerPtr->levelEntrances.canEnter(
            WindyValley, CurrentCharacter);
    return worldStateManagerPtr->levelEntrances.canEnter(WindyValley, CurrentCharacter) && worldStateManagerPtr->
        unlockStatus.keyWindStone;
});

// Handles the Casinopolis entrance
FunctionHook<BOOL> isCasinoOpen(0x6383E0, []()-> BOOL
{
    if (CurrentCharacter == Characters_Sonic || CurrentCharacter == Characters_Tails)
        return isCasinoOpen.Original() && worldStateManagerPtr->levelEntrances.canEnter(Casinopolis, CurrentCharacter);

    //We open the casino door for knuckles despite any story flags
    if (CurrentCharacter == Characters_Knuckles)
        return GetEventFlag(static_cast<EventFlags>(FLAG_KNUCKLES_SS_ENTRANCE_CASINO)) && worldStateManagerPtr->
            levelEntrances.canEnter(Casinopolis, CurrentCharacter);

    return worldStateManagerPtr->levelEntrances.canEnter(Casinopolis, CurrentCharacter);
});


// Handles the Twinkle Park entrance
static bool __cdecl HandleTwinkleParkEntrance(const char character)
{
    return worldStateManagerPtr->levelEntrances.canEnter(TwinklePark, CurrentCharacter);
}

// Speed Highway
FunctionHook<BOOL> isSpeedHighwayShutterOpen(0x63A2A0, []()-> BOOL
{
    if (CurrentCharacter == Characters_Sonic)
        return isSpeedHighwayShutterOpen.Original();
    return worldStateManagerPtr->levelEntrances.canEnter(SpeedHighway, CurrentCharacter)
        && worldStateManagerPtr->unlockStatus.keyEmployeeCard;
});

FunctionHook<void, task*> loadSpeedHighwayShutter(0x63A530, [](task* tp)-> void
{
    if ((CurrentCharacter == Characters_Gamma || CurrentCharacter == Characters_Amy || CurrentCharacter ==
            Characters_Big)
        && worldStateManagerPtr->levelEntrances.canEnter(SpeedHighway, CurrentCharacter)
        && worldStateManagerPtr->unlockStatus.keyEmployeeCard)
        FreeTask(tp);
    else
        loadSpeedHighwayShutter.Original(tp);
});

FunctionHook<void, task*> loadSpeedHighwayShutter2(0x63A500, [](task* tp)-> void
{
    if ((CurrentCharacter == Characters_Gamma || CurrentCharacter == Characters_Amy || CurrentCharacter ==
            Characters_Big)
        && worldStateManagerPtr->levelEntrances.canEnter(SpeedHighway, CurrentCharacter)
        && worldStateManagerPtr->unlockStatus.keyEmployeeCard)
        FreeTask(tp);
    else
        loadSpeedHighwayShutter2.Original(tp);
});

FunctionHook<void, ObjectMaster*> onOHighEle(0x6393F0, [](ObjectMaster* tp)-> void
{
    OEleboxIn(tp);
});


FunctionHook<BOOL> isCityHallDoorOpen(0x636BF0, []()-> BOOL
{
    return worldStateManagerPtr->levelEntrances.canEnter(SpeedHighway, CurrentCharacter) && isCityHallDoorOpen.
        Original();
});

//We don't create Knuckles barricade if he doesn't have access to the level
FunctionHook<void, task*> loadBarricade(0x637580, [](task* tp)-> void
{
    if (CurrentCharacter == Characters_Knuckles && levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_StationSquare1)
        if (!worldStateManagerPtr->levelEntrances.canEnter(SpeedHighway, CurrentCharacter))
            return FreeTask(tp);

    loadBarricade.Original(tp);
});


FunctionHook<BOOL, EntityData1*> isFinalEggGammaDoorOpen(0x53ED30, [](EntityData1* entity)-> BOOL
{
    if (levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_MysticRuins3)
        return true;

    if (levelact(CurrentLevel, CurrentAct) != LevelAndActIDs_MysticRuins4)
        return isFinalEggGammaDoorOpen.Original(entity);

    if (entity->Position.y < 100)
        return isFinalEggGammaDoorOpen.Original(entity);

    if (entity->Position.z < -150)
    {
        if (CurrentCharacter != Characters_Gamma)
            return false;
        return worldStateManagerPtr->levelEntrances.canEnter(FinalEgg, CurrentCharacter);
    }
    return true;
});


FunctionHook<void, task*> onLoadSceneChangeMr(0x5394F0, [](task* tp)-> void
{
    // Final Egg
    if ((CurrentCharacter != Characters_Gamma)
        && levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_MysticRuins4 && tp->twp->ang.x == 3)
    {
        if (!worldStateManagerPtr->levelEntrances.canEnter(FinalEgg, CurrentCharacter))
        {
            return FreeTask(tp);
        }
    }

    //Ice Cap
    if (levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_MysticRuins2 && tp->twp->ang.x == 1)
    {
        if (!worldStateManagerPtr->levelEntrances.canEnter(IceCap, CurrentCharacter))
        {
            return FreeTask(tp);
        }
    }

    onLoadSceneChangeMr.Original(tp);
});

FunctionHook<void, task*> onHiddenGate(0x53C3E0, [](task* tp)-> void
{
    const int bufferCharacter = CurrentCharacter;
    CurrentCharacter = Characters_Sonic;
    onHiddenGate.Original(tp);
    CurrentCharacter = bufferCharacter;
});

FunctionHook<BOOL> isFinalEggTowerActive(0x538550, []()-> BOOL
{
    return true;
});
FunctionHook<BOOL> isFinalEggDoorActive(0x53EDF0, []()-> BOOL
{
    return true;
});


//Makes knuckles able to enter the lost world using the keys
FunctionHook<BOOL> isLostWorldBackEntranceOpen(0x53B6C0, []()-> BOOL
{
    if (CurrentCharacter == Characters_Knuckles)
        return EventFlagArray[FLAG_KNUCKLES_MR_REDCUBE] && EventFlagArray[
                FLAG_KNUCKLES_MR_BLUECUBE]
            && worldStateManagerPtr->levelEntrances.canEnter(LostWorld, CurrentCharacter);

    return false;
});

//Allows everyone to enter Lost World
FunctionHook<BOOL> isLostWorldFrontEntranceOpen(0x532E60, []()-> BOOL
{
    if (CurrentCharacter == Characters_Knuckles)
        return false;
    return worldStateManagerPtr->levelEntrances.canEnter(LostWorld, CurrentCharacter);
});


void HandleLostWorldEntranceCollision(const int a1)
{
    const int bufferCharacter = CurrentCharacter;
    CurrentCharacter = Characters_Sonic;
    onLostWorldEntranceCollision_t.Original(a1);
    CurrentCharacter = bufferCharacter;
}


FunctionHook<BOOL> isAngelIslandOpen(0x534570, []()-> BOOL
{
    return worldStateManagerPtr->unlockStatus.keyDynamite;
});

//Prevents the monkey from blocking the entrance to Red Mountain for knuckles
FunctionPointer(int, isMonkeyDead, (int a1), 0x53F920);
FunctionHook<BOOL, int> isMonkeyDoorOpen(0x53E5D0, [](int a1)-> BOOL
{
    if (levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_MysticRuins1)
        return true;

    if (CurrentCharacter == Characters_Sonic || CurrentCharacter == Characters_Gamma
        || CurrentCharacter == Characters_Knuckles)
        return isMonkeyDead(1) && worldStateManagerPtr->levelEntrances.canEnter(RedMountain, CurrentCharacter);

    //For everyone else, we return true if we are in the main mystic ruins area
    return worldStateManagerPtr->levelEntrances.canEnter(RedMountain, CurrentCharacter);
});


// We only load the monkey if it's needed for opening the door
FunctionHook<void, task*> onLoadMonkeyCage(0x540730, [](task* tp)-> void
{
    if (levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_MysticRuins2)
    {
        if (CurrentCharacter == Characters_Tails || CurrentCharacter == Characters_Big
            || CurrentCharacter == Characters_Amy)
            return FreeTask(tp);
        if (!worldStateManagerPtr->levelEntrances.canEnter(RedMountain, CurrentCharacter))
            return FreeTask(tp);
    }
    onLoadMonkeyCage.Original(tp);
});

// Removed the ladder on Ice Cap
FunctionHook<void, task*> onLoadLongLadderMr(0x536CB0, [](task* tp)-> void
{
    if (levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_MysticRuins2)
    {
        if (!worldStateManagerPtr->levelEntrances.canEnter(IceCap, CurrentCharacter))
        {
            return FreeTask(tp);
        }
    }
    onLoadLongLadderMr.Original(tp);
});


FunctionHook<BOOL, int> preventKeyStoneFromSpawning(0x53C630, [](int a1)-> BOOL
{
    if (levelact(CurrentLevel, CurrentAct) == LevelAndActIDs_MysticRuins2
        && ((CurrentCharacter == Characters_Amy || CurrentCharacter == Characters_Knuckles
            || CurrentCharacter == Characters_Gamma) && worldStateManagerPtr->levelEntrances.canEnter(
            IceCap, CurrentCharacter)))
    {
        return worldStateManagerPtr->unlockStatus.keyIceStone;
    }

    return preventKeyStoneFromSpawning.Original(a1);
});

// HotShelter
static int __cdecl HandleEggCarrierEggDoor(const int a1)
{
    // Middle door
    if (levelact(CurrentLevel, CurrentAct) != LevelAndActIDs_EggCarrierInside2)
        return onEggCarrierEggDoor_t.Original(a1);

    if (*reinterpret_cast<BYTE*>(a1 + 1) != 6)
        return onEggCarrierEggDoor_t.Original(a1);

    if (!worldStateManagerPtr->levelEntrances.canEnter(HotShelter, CurrentCharacter))
        return false;

    const EntityData1* player = EntityData1Ptrs[0];
    const double dz = player->Position.z - *(float*)(a1 + 40);
    const double dy = player->Position.y - *(float*)(a1 + 36);
    const double dx = player->Position.x - *(float*)(a1 + 32);
    const double distance = dx * dx + dy * dy + dz * dz;
    if (squareroot(distance) > 50.0)
        return false;

    if (CurrentCharacter == Characters_Amy || CurrentCharacter == Characters_Big)
        return IsSwitchPressed(1);
    return true;
}

static int __cdecl HandleEggCarrierOutsideDoor(const int a1)
{
    if (levelact(CurrentLevel, CurrentAct) != LevelAndActIDs_EggCarrierOutside1)
        return onEggCarrierOutsideDoor_t.Original(a1);

    const int doorId = *reinterpret_cast<BYTE*>(a1 + 1);
    if (doorId != 1)
        return onEggCarrierOutsideDoor_t.Original(a1);

    const EntityData1* player = EntityData1Ptrs[0];
    const double dz = player->Position.z - *(float*)(a1 + 40);
    const double dy = player->Position.y - *(float*)(a1 + 36);
    const double dx = player->Position.x - *(float*)(a1 + 32);
    const double distance = dx * dx + dy * dy + dz * dz;
    if (squareroot(distance) > 50.0)
        return false;
    return true;
}

FunctionHook<void, task*> onLoadPoolWater(0x51DC30, [](task* tp)-> void
{
    if (CurrentCharacter != Characters_Knuckles)
        return onLoadPoolWater.Original(tp);

    if (!worldStateManagerPtr->levelEntrances.canEnter(SkyDeck, CurrentCharacter))
        return onLoadPoolWater.Original(tp);

    FreeTask(tp);
});

FunctionHook<void, task*> onLoadPoolDoor(0x51E320, [](task* tp)-> void
{
    if (CurrentCharacter != Characters_Knuckles)
        return onLoadPoolDoor.Original(tp);

    if (!worldStateManagerPtr->levelEntrances.canEnter(SkyDeck, CurrentCharacter))
        return onLoadPoolDoor.Original(tp);
    FreeTask(tp);
});

int HandleSkyDeckDoor(EntityData1* a1)
{
    if (!worldStateManagerPtr->levelEntrances.canEnter(SkyDeck, CurrentCharacter))
        return false;

    if (CurrentCharacter != Characters_Knuckles
        && levelact(CurrentLevel, CurrentAct) != LevelAndActIDs_EggCarrierOutside2)
        return false;

    if (CurrentCharacter == Characters_Knuckles
        && levelact(CurrentLevel, CurrentAct) != LevelAndActIDs_EggCarrierOutside6)
        return false;

    const EntityData1* player = EntityData1Ptrs[0];
    const double dz = player->Position.z - a1->Position.z;
    const double dy = player->Position.y - a1->Position.y;
    const double dx = player->Position.x - a1->Position.x;
    const double distance = squareroot(dx * dx + dy * dy + dz * dz);

    return distance <= 50.0;
}
