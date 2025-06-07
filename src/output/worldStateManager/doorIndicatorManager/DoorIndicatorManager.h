#pragma once
#include "../../../pch.h"
constexpr double MIN_DRAW_DOOR_ARROW_DISTANCE = 50.0;
constexpr double MAX_DRAW_DOOR_ARROW_DISTANCE = 100.0;

constexpr float CROSS_SIZE_MIN = 4.0;
constexpr float CROSS_SIZE_MAX = 12.0;
constexpr float CROSS_SIZE_DIFF = CROSS_SIZE_MAX - CROSS_SIZE_MIN;

constexpr float ARROW_SIZE_MAX = 10.0;
constexpr float ARROW_SIZE_MIN = 10.0;

class DoorIndicatorManager
{
public:
    static DoorIndicatorManager& Init()
    {
        if (_instance == nullptr)
            _instance = new DoorIndicatorManager();
        return *_instance;
    }

    void DrawDisable(NJS_POINT3 basePoint, float angle);
    void DrawCorrect(NJS_POINT3 basePoint, float angle);
    void DrawOtherDoor(NJS_POINT3 basePoint, float angle);

private:
    explicit DoorIndicatorManager();
    inline static DoorIndicatorManager* _instance = nullptr;
    NJS_COLOR _wrongDoorColor[12] = {
        {0xAAFF0000},
        {0xAAFF0000},
        {0xAAFF0000},
        {0xAAFF0000},
        {0xAAFF0000},
        {0xAAFF0000},
        {0xAAFF0000},
        {0xAAFF0000},
        {0xAAFF0000},
        {0xAAFF0000},
        {0xAAFF0000},
        {0xAAFF0000},
    };
    NJS_COLOR _arrowColor = {0xAA00FF00};

    NJS_COLOR _otherDoorColor[7] = {
        {0xAAFF4D00},
        {0xAAFF4D00},
        {0xAAFF4D00},
        {0xAAFF4D00},
        {0xAAFF4D00},
        {0xAAFF4D00},
        {0xAAFF4D00},
    };
};
