#include "RT_OutputManager.h"

#include <vector>
#include <utils.h>

RT_OutputManager::RT_OutputManager(RT_RayConfig config, unsigned int width, unsigned int height)
        :config(config), height(height), width(width)
{
    allRaysOutput = std::vector(height, std::vector<RT_RayOutput>(width));
}

/**
 * x corresponds to the width and y to the height
 * @param ray
 * @param x
 * @param y
 */
void RT_OutputManager::RT_SaveRay(struct RT_RayOutput ray, unsigned int x, unsigned int y)
{
    this->allRaysOutput[y][x] = ray;
    static int counter = 0;
    counter++;

    if ((ray.ortho_distance<distance_min || distance_min<0) && ray.ortho_distance>0) {
        distance_min = ray.ortho_distance;
    }

    if ((ray.ortho_distance>distance_max || distance_max<0) && ray.ortho_distance>0) {
        distance_max = ray.ortho_distance;
    }

    if (counter%200==0) {
        printf("\rProgress: %3.2f %%", 100.*counter/(width*height));
        fflush(stdout);
    }
}

void RT_OutputManager::export_picture(std::string name)
{
    printf("\rRendering of %s done!\n", name.c_str());

    OutputPictureManager pic = OutputPictureManager(std::move(name), width, height, config.env->currCam()->down_sampling);
    if (config.rtMode==RT_RayRenderMode::RT_DEPTHMAP) {
        //pic.setColorMapper(new ColorMapper(LINEAR, config.env->backgroundColor, distance_min, distance_max));
        pic.setColorMapper(new ColorMapper(LINEAR, config.env->backgroundColor, 0.02, 0.04));
    }
    for (unsigned int x = 0; x<width; x++) {
        for (unsigned y = 0; y<height; y++) {
            struct RT_RayOutput rayOutput = allRaysOutput[y][x];
            if (rayOutput.distance>=0) { // If the ray hits an object
                if (config.rtMode == RT_RayRenderMode::RT_BITMAP) {
                    pic.writePixel(rayOutput.resultColor, x, y);
                } else if (config.rtMode == RT_RayRenderMode::RT_DEPTHMAP) {
                    pic.writePixel(rayOutput.resultColor, rayOutput.ortho_distance, x, y);
                } else if (config.rtMode == RT_RayRenderMode::RT_STANDARD) {
                    pic.writePixel(rayOutput.resultColor, x, y);
                }
            }
            else {
                if (config.env->show_background_color) {
                    pic.writePixel(config.env->backgroundColor, x, y);
                } else {
                    pic.writePixel(Color(0.0), x, y);
                }
            }
        }
    }
    pic.savePicture();
}

void RT_OutputManager::apply_global_operations()
{
    //Haze effect;
    double haze_int = config.env->haze_intensity;
    for (unsigned int x = 0; x<width; x++) {
        for (unsigned y = 0; y<height; y++) {
            struct RT_RayOutput rayOutput = allRaysOutput[y][x];
            if (rayOutput.distance>=0) {
                double dist_coef = (1 - haze_int) + (haze_int) * (distance_max - rayOutput.ortho_distance) / (distance_max - distance_min);
                if (config.rtMode==RT_RayRenderMode::RT_STANDARD) {
                    rayOutput.resultColor = rayOutput.resultColor*dist_coef+config.env->backgroundColor*(1-dist_coef);
                }
            }
            allRaysOutput[y][x] = rayOutput;
        }
    }
}



