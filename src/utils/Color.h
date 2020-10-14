#ifndef GRAPHIC_ENGINE_COLOR_H
#define GRAPHIC_ENGINE_COLOR_H

enum colorMode {
    RGB,
    BLACK_AND_WHITE,
    GREY_SCALE,
    ALPHA_MASK
};

enum colors {
    BLACK
};

struct rgbPixel {
    unsigned int red;
    unsigned int green;
    unsigned int blue;
};

class Color {
private:
    double red;
    double green;
    enum colorMode colormode;
    double blue;
    double greyScale{};
    unsigned char bit{};
public:
    explicit Color();

    Color(unsigned int, unsigned int, unsigned int);

    struct rgbPixel getPixelValues(unsigned int bitDepth);
};

#endif //GRAPHIC_ENGINE_COLOR_H
