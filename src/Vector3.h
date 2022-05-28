#pragma once

#include <cmath>
#include <iostream>

using std::sqrt;

struct Vector3
{
    Vector3()
        : e{0, 0, 0} {}
    Vector3(double e0, double e1, double e2) : e{e0, e1, e2} {}

    double x() const { return e[0]; }
    double y() const { return e[1]; }
    double z() const { return e[2]; }

    Vector3 operator-() const { return Vector3(-e[0], -e[1], -e[2]); }
    double operator[](int i) const { return e[i]; }
    double& operator[](int i) { return e[i]; }

    Vector3& operator+=(const Vector3& v)
    {
        e[0] += v.e[0];
        e[1] += v.e[1];
        e[2] += v.e[2];
        return *this;
    }


    Vector3& operator*=(const double t)
    {
        e[0] *= t;
        e[1] *= t;
        e[2] *= t;
        return *this;
    }

    Vector3& operator/=(const double t)
    {
        return *this *= 1/t;
    }

    double Length() const
    {
        return sqrt(LengthSquared());
    }

    double LengthSquared() const
    {
        return e[0]*e[0] + e[1]*e[1] + e[2]*e[2];
    }

    inline static Vector3 Random()
    {
        return Vector3(RandomDouble(), RandomDouble(), RandomDouble());
    }

    inline static Vector3 Random(double min, double max)
    {
        return Vector3(
                RandomDouble(min, max),
                RandomDouble(min, max),
                RandomDouble(min, max));
    }

    double e[3];
};

using Point3 = Vector3;
using Color = Vector3;

inline std::ostream& operator<<(std::ostream& out, const Vector3& v)
{
    return out << v.e[0] << ' ' << v.e[1] << ' ' << v.e[2];
}

inline Vector3 operator+(const Vector3& u, const Vector3& v)
{
    return Vector3(u.e[0] + v.e[0], u.e[1] + v.e[1], u.e[2] + v.e[2]);
}

inline Vector3 operator-(const Vector3& u, const Vector3& v)
{
    return Vector3(u.e[0] - v.e[0], u.e[1] - v.e[1], u.e[2] - v.e[2]);
}

inline Vector3 operator*(const Vector3& u, const Vector3& v)
{
    return Vector3(u.e[0] * v.e[0], u.e[1] * v.e[1], u.e[2] * v.e[2]);
}

inline Vector3 operator*(double t, const Vector3& v)
{
    return Vector3(t * v.e[0], t * v.e[1], t * v.e[2]);
}

inline Vector3 operator*(const Vector3 &v, double t)
{
    return t * v;
}

inline Vector3 operator/(Vector3 v, double t)
{
    return (1/t) * v;
}

inline double Dot(const Vector3& u, const Vector3& v)
{
    return u.e[0] * v.e[0]
         + u.e[1] * v.e[1]
         + u.e[2] * v.e[2];
}

inline Vector3 UnitVector(Vector3 v)
{
    return v / v.Length();
}

Vector3 RandomInUnitSphere()
{
    while (true)
    {
        Vector3 p = Vector3::Random(-1, 1);
        if (p.LengthSquared() < 1.0)
        {
            return p;
        }
    }
}

Vector3 RandomUnitVector()
{
    return UnitVector(RandomInUnitSphere());
}

Vector3 RandomInHemisphere(const Vector3& normal)
{
    Vector3 inUnitSphere = RandomInUnitSphere();
    if (Dot(inUnitSphere, normal) > 0.0) // In the same hemisphere as the normal
    {
        return inUnitSphere;
    }
    else
    {
        return -inUnitSphere;
    }
}
