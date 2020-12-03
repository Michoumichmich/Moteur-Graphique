#ifndef GRAPHIC_ENGINE_COLOR_H
#define GRAPHIC_ENGINE_COLOR_H

#include <ostream>
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

    Color operator+(const Color& c1) const;

    explicit Color();

    Color(int, int, int, int = 256);

    [[nodiscard]] Color invert() const;

    Color(double, double, double);

    explicit Color(double);

    double getIntensity() const;

    inline Color operator*(const Color& b) const
    {
        return Color(red*b.red, green*b.green, blue*b.blue);
    };

    inline Color operator*(const double& b) const
    {
        return Color(b*red, b*green, b*blue);
    }

    /**
     * Converts a color to a RGB pixel composed of three ints between 0 and 2**bitDepth-1
     * @param bitDepth
     * @return
     */
    [[nodiscard]] struct rgbPixel getPixelValues(unsigned int bitDepth) const;

    friend std::ostream& operator<<(std::ostream& stream, const Color& color);

};

#endif //GRAPHIC_ENGINE_COLOR_H
