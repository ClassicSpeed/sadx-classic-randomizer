#include "DoorIndicatorManager.h"


DoorIndicatorManager::DoorIndicatorManager()
{
}

void DoorIndicatorManager::DrawDisable(const NJS_POINT3 basePoint, const float angle)
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

void DoorIndicatorManager::DrawCorrect(const NJS_POINT3 basePoint, const float angle)
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

void DoorIndicatorManager::DrawOtherDoor(const NJS_POINT3 basePoint, const float angle)
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
