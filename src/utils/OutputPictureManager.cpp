#include "OutputPictureManager.h"

#include <utility>

OutputPictureManager::OutputPictureManager(std::string name, enum colorMode color, unsigned int width, unsigned int height) :
        outFile(std::move(name)), color_mode(color), width(width), height(height) {
    allColors = (Color **) calloc(sizeof(Color *), height);
    for (int i = 0; i < height; i++) {
        allColors[i] = (Color *) calloc(sizeof(Color), width);
        for (int j = 0; j < width; j++) {
            allColors[i][j] = Color(0.0);
        }
    }
}

void OutputPictureManager::writePixel(Color c, unsigned int x, unsigned int y) {
    this->allColors[y][x] = c;
}

OutputPictureManager::~OutputPictureManager() {
    for (int i = 0; i < height; i++) {
        free(allColors[i]);
    }
    free(allColors);
}

void OutputPictureManager::savePicture() {
    FILE *f;
    unsigned char *img = NULL;
    unsigned int filesize = 54 + 3 * width * height;  //w is your image width, h is image height, both int
    img = (unsigned char *) malloc(3 * width * height);
    unsigned int x, y;
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            x = i;
            y = (height - 1) - j;
            struct rgbPixel rgb = allColors[y][x].getPixelValues(8);
            img[(x + y * width) * 3 + 2] = (unsigned char) (rgb.red);
            img[(x + y * width) * 3 + 1] = (unsigned char) (rgb.green);
            img[(x + y * width) * 3 + 0] = (unsigned char) (rgb.blue);
        }
    }

    unsigned char bmpfileheader[14] = {'B', 'M', 0, 0, 0, 0, 0, 0, 0, 0, 54, 0, 0, 0};
    unsigned char bmpinfoheader[40] = {40, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 24, 0};
    unsigned char bmppad[3] = {0, 0, 0};

    bmpfileheader[2] = (unsigned char) (filesize);
    bmpfileheader[3] = (unsigned char) (filesize >> 8u);
    bmpfileheader[4] = (unsigned char) (filesize >> 16u);
    bmpfileheader[5] = (unsigned char) (filesize >> 24u);

    bmpinfoheader[4] = (unsigned char) (width);
    bmpinfoheader[5] = (unsigned char) (width >> 8u);
    bmpinfoheader[6] = (unsigned char) (width >> 16u);
    bmpinfoheader[7] = (unsigned char) (width >> 24u);
    bmpinfoheader[8] = (unsigned char) (height);
    bmpinfoheader[9] = (unsigned char) (height >> 8u);
    bmpinfoheader[10] = (unsigned char) (height >> 16u);
    bmpinfoheader[11] = (unsigned char) (height >> 24u);

    f = fopen("img.bmp", "wb");
    fwrite(bmpfileheader, 1, 14, f);
    fwrite(bmpinfoheader, 1, 40, f);
    for (int i = 0; i < height; i++) {
        fwrite(img + (width * (height - i - 1) * 3), 3, width, f);
        fwrite(bmppad, 1, (4 - (width * 3) % 4) % 4, f);
    }

    free(img);
    fclose(f);

}