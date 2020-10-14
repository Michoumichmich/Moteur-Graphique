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

class Color {
public:
    unsigned int red;
    unsigned int green;
    unsigned int blue;
    unsigned char bit;
    unsigned int bitDepth;

    Color(enum colors color = BLACK);

};

#endif //GRAPHIC_ENGINE_COLOR_H
