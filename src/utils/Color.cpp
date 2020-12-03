#include "Color.h"
#include <cmath>

Color::Color()
{
    red = 0;
    blue = 0;
    green = 0;
    colormode = colorMode::RGB;
}

Color::Color(double r, double g, double b)
        :colormode(colorMode::RGB), red(r), green(g), blue(b)
{
}

Color::Color(int r, int g, int b, int d)
        :colormode(colorMode::RGB), red((double) r/d), green((double) g/d), blue((double) b/d)
{
}

struct rgbPixel Color::getPixelValues(unsigned int bitDepth) const
{
    int factor = (int) pow(2, bitDepth)-1;
    int r = (int) (red*factor);
    r = r>factor ? factor : r;
    r = r<0 ? 0 : r;

    int g = (int) (green*factor);
    g = g>factor ? factor : g;
    g = g<0 ? 0 : g;

    int b = (int) (blue*factor);
    b = b>factor ? factor : b;
    b = b<0 ? 0 : b;

    return rgbPixel{(unsigned int) (r), (unsigned int) (g), (unsigned int) (b)};
}

Color::Color(double d)
        :Color(d, d, d)
{
}

Color Color::invert() const
{
    return Color(256-red, 256-green, 256-blue);
}

Color Color::operator+(const Color& c1) const
{
    return Color(this->red+c1.red, this->green+c1.green, this->blue+c1.blue);
}
double Color::getIntensity() const
{
    return sqrt(red*red + green*green + blue * blue)/sqrt(3);
    //return (red+green+blue)/3;
}


