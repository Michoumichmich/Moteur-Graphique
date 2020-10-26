#include "Color.h"
#include <cmath>

Color::Color()
{
  red = 0;
  blue = 0;
  green = 0;
  colormode = colorMode::RGB;
}

Color::Color(double r, double g, double b) : red(r), green(g), blue(b), colormode(colorMode::RGB)
{
}

Color::Color(int r, int g, int b, int d) : red((double) r / d), green((double) g / d), blue((double) b / d), colormode(colorMode::RGB)
{
}

struct rgbPixel Color::getPixelValues(unsigned int bitDepth) const
{
  unsigned int factor = (unsigned) pow(2, bitDepth) - 1;
  return rgbPixel{(unsigned int) (red * factor), (unsigned int) (green * factor), (unsigned int) (blue * factor)};
}

Color::Color(double d) : Color(d, d, d)
{
}


