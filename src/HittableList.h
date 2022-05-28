#pragma once

#include "Hittable.h"

#include <memory>
#include <vector>

using std::shared_ptr;
using std::make_shared;

struct HittableList : public Hittable
{
    HittableList() {}
    HittableList(shared_ptr<Hittable> object) { Add(object); }

    void Clear() { Objects.clear(); }
    void Add(shared_ptr<Hittable> object) { Objects.push_back(object); }

    virtual bool Hit(
            const Ray& r,
            double tMin,
            double tMax,
            HitRecord& rec) const override;

    std::vector<shared_ptr<Hittable>> Objects;
};

bool HittableList::Hit(const Ray& r, double tMin, double tMax, HitRecord& rec) const
{
    HitRecord tempRec;
    bool hitAnything = false;
    double closest = tMax;
    for (const auto& object : Objects)
    {
        if (object->Hit(r, tMin, closest, tempRec))
        {
            hitAnything = true;
            closest = tempRec.T;
            rec = tempRec;
        }
    }
    return hitAnything;
}

