#ifndef GRAPHICSENGINE_RT_OUTPUTMANAGER_H
#define GRAPHICSENGINE_RT_OUTPUTMANAGER_H

#include <utils.h>
#include "RT_Commons.h"


class RT_OutputManager {


private:
    struct RT_RayOutput **allRaysOutput;
    RT_RayConfig config;
    unsigned int height;
    unsigned int width;
public:
    explicit RT_OutputManager(RT_RayConfig config, unsigned int width = DEFAULT_WIDTH, unsigned int height = DEFAULT_HEIGHT);

    ~RT_OutputManager();

    void RT_SaveRay(struct RT_RayOutput, unsigned int x, unsigned int y);

    void apply_global_transformations();

    void export_picture(OutputPictureManager *pManager);
};


#endif //GRAPHICSENGINE_RT_OUTPUTMANAGER_H
