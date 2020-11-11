#include "RT_OutputManager.h"

RT_OutputManager::RT_OutputManager(RT_RayConfig config, unsigned int width, unsigned int height) : config(config), height(height), width(width) {
    allRaysOutput = static_cast<struct RT_RayOutput **>( calloc(sizeof(struct RT_RayOutput *), height));
    if (allRaysOutput != nullptr) {
        for (unsigned i = 0; i < height; i++) {
            allRaysOutput[i] = (struct RT_RayOutput *) calloc(sizeof(struct RT_RayOutput), width);
            if (allRaysOutput[i] != nullptr) {
                for (unsigned j = 0; j < width; j++) {
                    allRaysOutput[i][j] = RT_RayOutput();
                }
            }
        }
    }
}

/**
 * x corresponds to the width and y to the height
 * @param ray
 * @param x
 * @param y
 */
void RT_OutputManager::RT_SaveRay(struct RT_RayOutput ray, unsigned int x, unsigned int y) {
    this->allRaysOutput[y][x] = ray;
}

void RT_OutputManager::export_picture(OutputPictureManager *pic) {
    for (unsigned int x = 0; x < width; x++) {
        for (unsigned y = 0; y < height; y++) {
            struct RT_RayOutput rayOutput = allRaysOutput[y][x];
            if (config.rtMode == RT_RayRenderingMode::RT_BITMAP && rayOutput.distance >= 0) {
                pic->writePixel(rayOutput.resultColor, x, y);
            } else if (config.rtMode == RT_RayRenderingMode::RT_DEPTHMAP && rayOutput.distance >= 0) {
                //pic->RT_SaveRay(rayOutput, x, y);
                pic->writePixel(rayOutput.resultColor, rayOutput.ortho_distance, x, y);
            } else if (config.rtMode == RT_RayRenderingMode::RT_STANDARD && rayOutput.distance >= 0) {
                //pic->RT_SaveRay(rayOutput, x, y);
                pic->writePixel(rayOutput.resultColor, x, y);
            } else {
                //pic->RT_SaveRay(rayOutput, x, y);
                pic->writePixel(Color(0), x, y);
            }
        }
    }
    pic->savePicture();
}

void RT_OutputManager::apply_global_transformations() {

}



