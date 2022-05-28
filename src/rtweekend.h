#pragma once

#include <cmath>
#include <limits>
#include <memory>
#include <cstdlib>
#include <random>

// Usings
using std::make_shared;
using std::shared_ptr;
using std::sqrt;

// Constants
const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

// Utility functions
inline double ToRadians(double degrees)
{
    return degrees * pi / 180.0;
}


// Random numbers

inline double RandomDouble()
{
    static std::uniform_real_distribution<double> distribution(0.0, 1.0);
    static std::mt19937 generator;
    return distribution(generator);
}

inline double RandomDouble(double min, double max)
{
    return min + (max - min) * RandomDouble();
}

inline double Clamp(double x, double min, double max)
{
    if (x < min) return min;
    if (x > max) return max;
    return x;
}

// Common headers
#include "Ray.h"
#include "Vector3.h"
