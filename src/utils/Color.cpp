#include "Color.h"

Color::Color() {
    red = 0;
    blue = 0;
    green = 0;
    colormode = RGB;
}

Color::Color(unsigned int r, unsigned int g, unsigned int b) : red(r), green(g), blue(b), colormode(RGB) {

}

struct rgbPixel Color::getPixelValues(unsigned int bitDepth) {
    unsigned int factor = 2u ^bitDepth;
    return rgbPixel{(unsigned int) (red * factor), (unsigned int) (green * factor), (unsigned int) (blue * factor)};
}

