#include <iostream>
#include "color.h"
#include "Vector3.h"

int main()
{
    const int IMAGE_WIDTH = 256;
    const int IMAGE_HEIGHT = 256;

    std::cout << "P3\n" << IMAGE_WIDTH << ' ' << IMAGE_HEIGHT << "\n255\n";

    for (int j = IMAGE_HEIGHT-1; j >= 0; --j)
    {
        std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
        for (int i = 0; i < IMAGE_WIDTH; ++i)
        {
            Color pixelColor(double(i) / (IMAGE_WIDTH-1), double(j) / (IMAGE_HEIGHT-1), 0.25);
            WriteColor(std::cout, pixelColor);
        }
    }

    std::cerr << "\nDone\n";

}
