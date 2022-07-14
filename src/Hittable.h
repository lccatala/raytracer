#pragma once

#include "rtweekend.h"

class Material;

struct HitRecord
{
    Point3 P;
    Vector3 Normal;
    double T;
    bool FrontFace;
    shared_ptr<Material> MaterialPtr;

    inline void SetFaceNormal(const Ray& r, const Vector3& outwardNormal)
    {
        FrontFace = Dot(r.Direction, outwardNormal) < 0.0;
        Normal = FrontFace ? outwardNormal : -outwardNormal;
    }
};

struct Hittable
{
    virtual bool Hit(const Ray& r, double tMin, double tMax, HitRecord& rec) const = 0;
};
