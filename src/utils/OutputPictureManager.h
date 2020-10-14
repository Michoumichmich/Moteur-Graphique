#ifndef GRAPHIC_ENGINE_OUTPUTPICTUREMANAGER_H
#define GRAPHIC_ENGINE_OUTPUTPICTUREMANAGER_H

#include <string>
#include "Color.h"
#include <config.h>
#include <list>

class OutputPictureManager {
private:
    enum colorMode color_mode;
    unsigned int width;
    unsigned int height;
    /**
     * allColors[height ie y][width ie x]
     */
    Color **allColors;

public :
    explicit OutputPictureManager(std::string = "output.ppm", enum colorMode = RGB, unsigned int width = DEFAULT_WIDTH, unsigned int height = DEFAULT_HEIGHT);

    void writePixel(Color, unsigned int x, unsigned int y);

    std::string outFile;

    void savePicture();

    ~OutputPictureManager();
};

#endif //GRAPHIC_ENGINE_OUTPUTPICTUREMANAGER_H
