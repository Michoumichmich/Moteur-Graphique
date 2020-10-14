#ifndef GRAPHIC_ENGINE_OUTPUTPICTUREMANAGER_H
#define GRAPHIC_ENGINE_OUTPUTPICTUREMANAGER_H

#include <string>
#include "Color.h"

class OutputPictureManager {
 private:
  enum colorMode color_mode;
 public :
  explicit OutputPictureManager(std::string = "output.ppm", enum colorMode = RGB);
  void writePixel(Color, unsigned int x, unsigned int y);
  std::string outFile;
};

#endif //GRAPHIC_ENGINE_OUTPUTPICTUREMANAGER_H
