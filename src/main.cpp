#include <iostream>

#include "color.h"
#include "Vector3.h"
#include "Ray.h"

bool HitSphere(const Point3& center, double radius, const Ray& r)
{
    Vector3 oc = r.Origin - center;
    double a = Dot(r.Direction, r.Direction);
    double b = 2.0 * Dot(oc, r.Direction);
    double c = Dot(oc, oc) - radius*radius;
    double discriminant = b*b - 4*a*c;
    return (discriminant > 0);
}

// Linearly blend white and blue depending on Y coordinate
// after scaling Y to be between -1 and 1
Color RayColor(const Ray& r)
{
    if (HitSphere(Point3(0,0,-1), 0.5, r))
    {
        return Color(1,0,0);
    }
    Vector3 unitDirection = UnitVector(r.Direction);
    auto t = 0.5 * (unitDirection.y() + 1.0);
    return (1.0-t) * Color(1.0, 1.0, 1.0) + t*Color(0.5, 0.7, 1.0);
}

int main()
{
    // Image
    const double ASPECT_RATIO = 16.0 / 9.0;
    const int IMAGE_WIDTH = 400;
    const int IMAGE_HEIGHT = static_cast<int>(IMAGE_WIDTH / ASPECT_RATIO);

    // Camera
    const double VIEWPORT_HEIGHT = 2.0;
    const double VIEWPORT_WIDTH = ASPECT_RATIO * VIEWPORT_HEIGHT;
    const double FOCAL_LENGTH = 1.0;

    Point3 origin = Point3(0, 0, 0);
    Vector3 horizontal = Vector3(VIEWPORT_WIDTH, 0, 0);
    Vector3 vertical = Vector3(0, VIEWPORT_HEIGHT, 0);
    Point3 lowerLeftCorner = origin - horizontal/2 - vertical/2 - Vector3(0, 0, FOCAL_LENGTH);

    std::cout << "P3\n" << IMAGE_WIDTH << ' ' << IMAGE_HEIGHT << "\n255\n";

    for (int j = IMAGE_HEIGHT-1; j >= 0; --j)
    {
        std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
        for (int i = 0; i < IMAGE_WIDTH; ++i)
        {
            double u = double(i) / (IMAGE_WIDTH-1);
            double v = double(j) / (IMAGE_HEIGHT-1);
            Ray r(origin, lowerLeftCorner + u*horizontal + v*vertical - origin);
            Color pixelColor = RayColor(r);
            WriteColor(std::cout, pixelColor);
        }
    }

    std::cerr << "\nDone\n";

}
