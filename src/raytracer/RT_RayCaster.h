#ifndef GRAPHIC_ENGINE_RAYCASTER_H
#define GRAPHIC_ENGINE_RAYCASTER_H

#include <list>
#include "RT_Ray.h"

/**
 * Creates the first set of rays given the camera used and the output picture resolution.
 */

class RT_RayCaster {
public:
    static std::list<RT_Ray> generateFirstRays(Camera *cam, OutputPictureManager *pic,double height,double width);
};

#endif //GRAPHIC_ENGINE_RAYCASTER_H
