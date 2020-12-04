#ifndef GRAPHIC_ENGINE_OUTPUTPICTUREMANAGER_H
#define GRAPHIC_ENGINE_OUTPUTPICTUREMANAGER_H

#include <string>
#include "Color.h"
#include <config.h>
#include <list>
#include <vector>
#include "ColorMapper.h"

class OutputPictureManager {
private:
    std::string outFile;
    unsigned int width;
    unsigned int height;
    ColorMapper* mapper = nullptr;
    /**
     * allColors[height ie y][width ie x]
     */
    std::vector<std::vector<Color>> allColors;
public :
    OutputPictureManager(std::string name, unsigned int width, unsigned int height);

    void writePixel(Color c, unsigned int x, unsigned int y);

    void writePixel(double d, unsigned int x, unsigned int y);

    void setColorMapper(ColorMapper* color_mapper);

    void savePicture();

    ~OutputPictureManager();

    void setOutFile(const std::string& basicString);

    void writePixel(Color color, double d, unsigned int x, unsigned int y);
};

#endif //GRAPHIC_ENGINE_OUTPUTPICTUREMANAGER_H
