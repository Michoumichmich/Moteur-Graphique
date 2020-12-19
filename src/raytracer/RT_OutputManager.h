#ifndef GRAPHICSENGINE_RT_OUTPUTMANAGER_H
#define GRAPHICSENGINE_RT_OUTPUTMANAGER_H

#include <utils.h>
#include <vector>
#include "RT_Commons.h"

class RT_OutputManager {

private:
    std::vector<std::vector<RT_RayOutput>> allRaysOutput;
    RT_RayConfig config;
    unsigned int height;
    unsigned int width;
    double distance_min = -1;
    double distance_max = -1;
    int counter = 0;
public:
    explicit RT_OutputManager(RT_RayConfig config, unsigned int width, unsigned int height);

    void RT_SaveRay(struct RT_RayOutput, unsigned int x, unsigned int y);

    void apply_global_operations();

    void export_picture(std::string out_name);
};

#endif //GRAPHICSENGINE_RT_OUTPUTMANAGER_H
