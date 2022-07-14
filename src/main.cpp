#include "rtweekend.h"

#include "Camera.h"
#include "color.h"
#include "HittableList.h"
#include "Material.h"
#include "Sphere.h"

#include <iostream>

HittableList RandomScene()
{
    HittableList world;
    auto groundMaterial = make_shared<Lambertian>(Color(0.5, 0.5, 0.5));
    world.Add(make_shared<Sphere>(Point3(0, -1000, 0), 1000, groundMaterial));

    for (int32_t a = -11; a < 11; ++a)
    {
        for (int32_t b = -11; b < 11; ++b)
        {
            double chosenMaterial = RandomDouble();
            Point3 center(a + 0.9*RandomDouble(), 0.2, b + 0.9*RandomDouble());

            if ((center - Point3(4, 0.2, 0)).Length() > 0.9)
            {
                shared_ptr<Material> sphereMaterial;

                if (chosenMaterial < 0.8) // Diffuse
                {
                    Color albedo = Color::Random() * Color::Random();
                    sphereMaterial = make_shared<Lambertian>(albedo);
                }
                else if (chosenMaterial < 0.95)
                {
                    Color albedo = Color::Random(0.5, 1);
                    double fuzz = RandomDouble(0, 0.5);
                    sphereMaterial = make_shared<Metal>(albedo, fuzz);
                }
                else
                {
                    sphereMaterial = make_shared<Dielectric>(1.5);
                }
                world.Add(make_shared<Sphere>(center, 0.2, sphereMaterial));
            }
        }
    }

    auto material1 = make_shared<Dielectric>(1.5);
    world.Add(make_shared<Sphere>(Point3(0,1,0), 1.0, material1));

    auto material2 = make_shared<Lambertian>(Color(0.4, 0.2, 0.1));
    world.Add(make_shared<Sphere>(Point3(-4,1,0), 1.0, material2));

    auto material3 = make_shared<Metal>(Color(0.7, 0.6, 0.5), 0.0);
    world.Add(make_shared<Sphere>(Point3(4,1,0), 1.0, material3));

    return world;
}

Color RayColor(const Ray& r, HittableList& world, uint32_t depth)
{
    if (depth <= 0)
    {
        return Color(0.0, 0.0, 0.0);
    }
    HitRecord rec;
    if (world.Hit(r, 0.001, infinity, rec))
    {
        Ray scatteredRay;
        Color attenuation;
        if (rec.MaterialPtr->Scatter(r, rec, attenuation, scatteredRay))
        {
            return attenuation * RayColor(scatteredRay, world, depth-1);
        }
        return Color(0.0, 0.0, 0.0);
        /* Point3 target = rec.P + rec.Normal + RandomUnitVector(); // Lambertian */
        /* Point3 target = rec.P + RandomInHemisphere(rec.Normal); */
        /* return 0.5 * RayColor(Ray(rec.P, target - rec.P), world, depth-1); */
    }
    Vector3 unitDirection = UnitVector(r.Direction);
    double t = 0.5 * (unitDirection.y() + 1.0);
    return (1.0-t) * Color(1.0, 1.0, 1.0) + t*Color(0.5, 0.7, 1.0);
}

int main()
{
    // Image
    const double ASPECT_RATIO = 16.0 / 9.0;
    const uint32_t IMAGE_WIDTH = 2560;
    const uint32_t IMAGE_HEIGHT = static_cast<int>(IMAGE_WIDTH / ASPECT_RATIO);
    const uint32_t SAMPLES_PER_PIXEL = 500;
    const uint32_t MAX_DEPTH = 50;

    // World
    HittableList world = RandomScene();

    // Camera
    Point3 lookFrom(13, 2, 3);
    Point3 lookAt(0,0,0);
    Vector3 viewUp(0,1,0);
    double distanceToFocus = 10.0;
    double aperture = 0.1;
    Camera camera(lookFrom, lookAt, viewUp, 20, ASPECT_RATIO, aperture, distanceToFocus);

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
