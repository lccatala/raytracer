#pragma once

#include "Vector3.h"

struct Ray
{
    Ray() {}
    Ray(const Point3& origin, const Vector3& direction)
        : Origin(origin), Direction(direction)
    {}

    Point3 Origin;
    Vector3 Direction;
};
