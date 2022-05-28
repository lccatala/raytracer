#pragma once

#include "Vector3.h"

#include <iostream>

void WriteColor(std::ostream& out, Color pixelColor, uint32_t samplesPerPixel)
{
    double r = pixelColor.x();
    double g = pixelColor.y();
    double b = pixelColor.z();

    // Divide color by the number of samples and gamma correct for gamma=2.0
    // TODO: why not /= instead of *= 1/n?
    double scale = 1.0 / samplesPerPixel;
    r = sqrt(scale * r);
    g = sqrt(scale * g);
    b = sqrt(scale * b);

    // Write the translated [0,255] value of each color component
    out << static_cast<int>(256 * Clamp(r, 0.0, 0.999)) << ' '
        << static_cast<int>(256 * Clamp(g, 0.0, 0.999)) << ' '
        << static_cast<int>(256 * Clamp(b, 0.0, 0.999)) << '\n';
}
