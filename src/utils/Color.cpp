#include "Color.h"
#include <cmath>

Color::Color()
{
  red = 0;
  blue = 0;
  green = 0;
  colormode = colorMode::RGB;
}

Color::Color(double r, double g, double b) : colormode(colorMode::RGB), red(r), green(g), blue(b)
{
}

Color::Color(int r, int g, int b, int d) : colormode(colorMode::RGB), red((double) r / d), green((double) g / d), blue((double) b / d)
{
}

struct rgbPixel Color::getPixelValues(unsigned int bitDepth) const {
    unsigned int factor = (unsigned) pow(2, bitDepth) - 1;
    return rgbPixel{(unsigned int) (red * factor), (unsigned int) (green * factor), (unsigned int) (blue * factor)};
}

Color::Color(double d) : Color(d, d, d) {
}

Color Color::invert() {
    return Color(256 - red, 256 - green, 256 - blue);
}


