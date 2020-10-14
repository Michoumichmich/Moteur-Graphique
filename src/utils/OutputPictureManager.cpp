#include "OutputPictureManager.h"

#include <utility>

OutputPictureManager::OutputPictureManager(std::string name, enum colorMode color) : outFile(std::move(name)), color_mode(color) {}

void OutputPictureManager::writePixel(Color, unsigned int x, unsigned int y) {
    //TODO
};
