#ifndef GRAPHIC_ENGINE_COLOR_H
#define GRAPHIC_ENGINE_COLOR_H

enum class colorMode {
    RGB,
    BLACK_AND_WHITE,
    GREY_SCALE,
    ALPHA_MASK
};

struct rgbPixel {
    unsigned int red;
    unsigned int green;
    unsigned int blue;
};

class Color {
private:
    colorMode colormode;
    double greyScale{};
    unsigned char bit{};
public:
    double red;
    double green;
    double blue;

    explicit Color();

    Color(int, int, int, int);

    Color(double, double, double);

    explicit Color(double);

    /**
     * Converts a color to a RGB pixel composed of three ints between 0 and 2**bitDepth-1
     * @param bitDepth
     * @return
     */
    struct rgbPixel getPixelValues(unsigned int bitDepth) const;

};

#endif //GRAPHIC_ENGINE_COLOR_H
