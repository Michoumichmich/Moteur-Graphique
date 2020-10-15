#ifndef GRAPHIC_ENGINE_COLOR_H
#define GRAPHIC_ENGINE_COLOR_H

enum colorMode {
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
    double red;
    double green;
    enum colorMode colormode;
    double blue;
    double greyScale{};
    unsigned char bit{};
public:
    explicit Color();

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
