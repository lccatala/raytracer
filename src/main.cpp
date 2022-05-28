#include "rtweekend.h"
#include "Camera.h"

#include "color.h"
#include "HittableList.h"
#include "Sphere.h"

#include <iostream>

Color RayColor(const Ray& r, HittableList& world, uint32_t depth)
{
    if (depth <= 0)
    {
        return Color(0.0, 0.0, 0.0);
    }
    HitRecord rec;
    if (world.Hit(r, 0.001, infinity, rec))
    {
        Point3 target = rec.P + rec.Normal + RandomUnitVector(); // Lambertian
        /* Point3 target = rec.P + RandomInHemisphere(rec.Normal); */
        return 0.5 * RayColor(Ray(rec.P, target - rec.P), world, depth-1);
    }
    Vector3 unitDirection = UnitVector(r.Direction);
    double t = 0.5 * (unitDirection.y() + 1.0);
    return (1.0-t) * Color(1.0, 1.0, 1.0) + t*Color(0.5, 0.7, 1.0);
}

int main()
{
    // Image
    const double ASPECT_RATIO = 16.0 / 9.0;
    const uint32_t IMAGE_WIDTH = 400;
    const uint32_t IMAGE_HEIGHT = static_cast<int>(IMAGE_WIDTH / ASPECT_RATIO);
    const uint32_t SAMPLES_PER_PIXEL = 100;
    const uint32_t MAX_DEPTH = 50;

    // World
    HittableList world;
    world.Add(make_shared<Sphere>(Point3(0,0,-1), 0.5));
    world.Add(make_shared<Sphere>(Point3(0, -100.5, -1), 100));

    // Camera
    Camera camera;

    // Render
    std::cout << "P3\n" << IMAGE_WIDTH << ' ' << IMAGE_HEIGHT << "\n255\n";

    for (int j = IMAGE_HEIGHT-1; j >= 0; --j)
    {
        std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
        for (int i = 0; i < IMAGE_WIDTH; ++i)
        {
            Color pixelColor(0.0, 0.0, 0.0);
            for (uint32_t s = 0; s < SAMPLES_PER_PIXEL; ++s)
            {
                double u = (i + RandomDouble()) / (IMAGE_WIDTH-1);
                double v = (j + RandomDouble()) / (IMAGE_HEIGHT-1);
                Ray r = camera.GetRay(u, v);
                pixelColor += RayColor(r, world, MAX_DEPTH);
            }
            WriteColor(std::cout, pixelColor, SAMPLES_PER_PIXEL);
        }
    }

    std::cerr << "\nDone\n";

}
