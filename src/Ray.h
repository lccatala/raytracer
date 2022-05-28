#pragma once

#include "Vector3.h"

struct Ray
{
    Ray() {}
    Ray(const Point3& origin, const Vector3& direction)
        : Origin(origin), Direction(direction)
    {}

    Point3 At(double t) const
    {
        return Origin + t*Direction;
    }

    Point3 Origin;
    Vector3 Direction;
};
