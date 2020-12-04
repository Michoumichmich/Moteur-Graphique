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

    if ((ray.ortho_distance<distance_min || distance_min<0) && ray.ortho_distance>0) {
        distance_min = ray.ortho_distance;
    }

    if ((ray.ortho_distance>distance_max || distance_max<0) && ray.ortho_distance>0) {
        distance_max = ray.ortho_distance;
    }

}

void RT_OutputManager::export_picture(std::string name)
{
    OutputPictureManager pic = OutputPictureManager(std::move(name), width, height);
    if (config.rtMode==RT_RayRenderMode::RT_DEPTHMAP) {
        //pic.setColorMapper(new ColorMapper(LINEAR, config.env->backgroundColor, distance_min, distance_max));
        pic.setColorMapper(new ColorMapper(TOPO_LINES,config.env->backgroundColor, 0.02, 0.03));
    }
    for (unsigned int x = 0; x<width; x++) {
        for (unsigned y = 0; y<height; y++) {
            struct RT_RayOutput rayOutput = allRaysOutput[y][x];
            if (rayOutput.distance>=0) {
                if (config.rtMode==RT_RayRenderMode::RT_BITMAP) {
                    pic.writePixel(rayOutput.resultColor, x, y);
                }
                else if (config.rtMode==RT_RayRenderMode::RT_DEPTHMAP) {
                    //pic->RT_SaveRay(rayOutput, x, y);
                    pic.writePixel(rayOutput.resultColor, rayOutput.ortho_distance, x, y);
                }
                else if (config.rtMode==RT_RayRenderMode::RT_STANDARD) {
                    //pic->RT_SaveRay(rayOutput, x, y);
                    pic.writePixel(rayOutput.resultColor, x, y);
                }
            }
            else {
                //pic->RT_SaveRay(rayOutput, x, y);
                pic.writePixel(Color(0.0), x, y);
            }
        }
    }
    pic.savePicture();
}

void RT_OutputManager::apply_global_operations()
{
    //Haze effect;
    for (unsigned int x = 0; x<width; x++) {
        for (unsigned y = 0; y<height; y++) {
            struct RT_RayOutput rayOutput = allRaysOutput[y][x];
            if (rayOutput.distance>=0) {
                double corrector = 0.85;
                double dist_coef = corrector+(1-corrector)*(distance_max-rayOutput.ortho_distance)/(distance_max-distance_min);

                if (config.rtMode==RT_RayRenderMode::RT_STANDARD) {
                    rayOutput.resultColor = rayOutput.resultColor*dist_coef+config.env->backgroundColor*(1-dist_coef);
                }
            }
            allRaysOutput[y][x] = rayOutput;
        }
    }
}



