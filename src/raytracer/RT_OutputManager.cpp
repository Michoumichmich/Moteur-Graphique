#include "RT_OutputManager.h"

#include <utility>

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


    if (ray.ortho_distance < distance_min || distance_min < 0) {
        distance_min = ray.ortho_distance;
    }

    if (ray.ortho_distance > distance_max || distance_max < 0) {
        distance_max = ray.ortho_distance;
    }


}

void RT_OutputManager::export_picture(std::string name) {
    OutputPictureManager *pic = new OutputPictureManager(std::move(name), width, height);
    if (config.rtMode == RT_RayRenderingMode::RT_DEPTHMAP) {
        pic->setColorMapper(new ColorMapper(LINEAR, distance_min, distance_max));
    }
    for (unsigned int x = 0; x < width; x++) {
        for (unsigned y = 0; y < height; y++) {
            struct RT_RayOutput rayOutput = allRaysOutput[y][x];
            if (rayOutput.distance >= 0) {
                if (config.rtMode == RT_RayRenderingMode::RT_BITMAP) {
                    pic->writePixel(rayOutput.resultColor, x, y);
                } else if (config.rtMode == RT_RayRenderingMode::RT_DEPTHMAP) {
                    //pic->RT_SaveRay(rayOutput, x, y);
                    pic->writePixel(rayOutput.resultColor, rayOutput.ortho_distance, x, y);
                } else if (config.rtMode == RT_RayRenderingMode::RT_STANDARD) {
                    //pic->RT_SaveRay(rayOutput, x, y);
                    pic->writePixel(rayOutput.resultColor, x, y);
                }
            } else {
                //pic->RT_SaveRay(rayOutput, x, y);
                pic->writePixel(Color(0.0), x, y);
            }
        }
    }
    pic->savePicture();
    delete pic;
}

void RT_OutputManager::apply_global_operations() {

}

RT_OutputManager::~RT_OutputManager() {
    for (unsigned int y = 0; y < height; y++)
        free(allRaysOutput[y]);
    free(allRaysOutput);
}




