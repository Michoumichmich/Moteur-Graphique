#ifndef GRAPHIC_ENGINE_OUTPUTPICTUREMANAGER_H
#define GRAPHIC_ENGINE_OUTPUTPICTUREMANAGER_H

#include <string>
#include "Color.h"
#include <config.h>
#include <list>
#include "ColorMapper.h"

class OutputPictureManager {
private:
    unsigned int width;
    unsigned int height;
    ColorMapper * mapper = nullptr;
    /**
     * allColors[height ie y][width ie x]
     */
    Color **allColors;

public :
  std::string outFile;

  explicit OutputPictureManager(std::string = "output.ppm", unsigned int width = DEFAULT_WIDTH, unsigned int height = DEFAULT_HEIGHT);

  void writePixel(Color, unsigned int x, unsigned int y);

  void writePixel(double, unsigned int x, unsigned int y);

  void setColorMapper(ColorMapper * color_mapper);

  void savePicture();

  ~OutputPictureManager();
};

#endif //GRAPHIC_ENGINE_OUTPUTPICTUREMANAGER_H
