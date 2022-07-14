#pragma once

#include "rtweekend.h"

struct HitRecord;

struct Material
{
    virtual bool Scatter(
            const Ray& rIn,
            const HitRecord& rec,
            Color& attenuation,
            Ray& scatteredRay) const = 0;
};

struct Lambertian : public Material
{
    Lambertian(const Color& albedo)
        : Albedo(albedo) {}

    virtual bool Scatter(
            const Ray& rIn,
            const HitRecord& rec,
            Color& attenuation,
            Ray& scatteredRay) const override
    {
        Vector3 scatterDirection = rec.Normal + RandomUnitVector();

        if (scatterDirection.NearZero())
        {
            scatterDirection = rec.Normal;
        }

        scatteredRay = Ray(rec.P, scatterDirection);
        attenuation = Albedo;
        return true;
    }

    Color Albedo;
};

struct Metal : public Material
{
    Metal(const Color& albedo, double fuzz)
        : Albedo(albedo) , Fuzz(fuzz) {}

    virtual bool Scatter(
            const Ray& rIn,
            const HitRecord& rec,
            Color& attenuation,
            Ray& scatteredRay) const override
    {
        Vector3 reflected = Reflect(UnitVector(rIn.Direction), rec.Normal);
        scatteredRay = Ray(rec.P, reflected + Fuzz * RandomInUnitSphere());
        attenuation = Albedo;
        return (Dot(scatteredRay.Direction, rec.Normal) > 0.0);
    }

    double Fuzz;
    Color Albedo;
};

struct Dielectric : public Material
{
    Dielectric(double refractionIndex)
        : RefractionIndex(refractionIndex) {}

    virtual bool Scatter(
            const Ray& rIn,
            const HitRecord& rec,
            Color& attenuation,
            Ray& scatteredRay) const override
    {
        attenuation = Color(1.0, 1.0, 1.0);
        double refractionRatio = rec.FrontFace ? (1.0 / RefractionIndex) : RefractionIndex;
        Vector3 unitDirection = UnitVector(rIn.Direction);
        double cosTheta = fmin(Dot(-unitDirection, rec.Normal), 1.0);
        double sinTheta = sqrt(1.0 - cosTheta*cosTheta);
        bool canRefract = refractionRatio * sinTheta <= 1.0;
        Vector3 direction;
        if (canRefract && Reflectance(cosTheta, refractionRatio) <= RandomDouble())
        {
            direction = Refract(unitDirection, rec.Normal, refractionRatio);
        }
        else
        {
            direction = Reflect(unitDirection, rec.Normal);
        }
        scatteredRay = Ray(rec.P, direction);
        return true;
    }

    static double Reflectance(double cosine, double refIdx)
    {
        // Schlick's approximation for reflectance
        double r0 = (1.0-refIdx) / (1+refIdx);
        r0 = r0*r0;
        return r0 + (1.0-r0) * pow((1.0-cosine), 5);
    }

    double RefractionIndex;
};
