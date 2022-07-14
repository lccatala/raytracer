#pragma once

#include "Hittable.h"
#include "Vector3.h"

struct Sphere : Hittable
{
    Sphere() {}
    Sphere(Point3 center, double radius, shared_ptr<Material> materialPtr)
        : Center(center), Radius(radius), MaterialPtr(materialPtr) {};

    virtual bool Hit(const Ray& r,
                     double tMin,
                     double tMax,
                     HitRecord& rec) const override;

    Point3 Center;
    double Radius;
    shared_ptr<Material> MaterialPtr;
};

bool Sphere::Hit(const Ray& r, double tMin, double tMax, HitRecord& rec) const
{
    Vector3 oc = r.Origin - Center;
    double a = r.Direction.LengthSquared();
    double halfB = Dot(oc, r.Direction);
    double c = oc.LengthSquared() - Radius*Radius;

    double discriminant = halfB*halfB - a*c;
    if (discriminant < 0.0)
    {
        return false;
    }
    double sqrtD = sqrt(discriminant);

    // Find the nearest root that lies in the acceptable range
    double root = (-halfB - sqrtD) / a;
    if (root < tMin || root > tMax)
    {
        root = (-halfB + sqrtD) / a;
        if (root < tMin || root > tMax)
        {
            return false;
        }
    }

    rec.T = root;
    rec.P = r.At(rec.T);
    Vector3 outwardNormal = (rec.P - Center) / Radius;
    rec.SetFaceNormal(r, outwardNormal);
    rec.MaterialPtr = MaterialPtr;

    return true;
}
