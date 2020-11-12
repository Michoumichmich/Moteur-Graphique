#ifndef GRAPHIC_ENGINE_RAYCASTER_H
#define GRAPHIC_ENGINE_RAYCASTER_H

#include <list>
#include "RT_Ray.h"

/**
 * @class RT_RayCaster
 * Creates the first set of rays given the camera used and the output picture resolution.
 */
class RT_RayCaster {
public:
    static std::list<RT_Ray>
    generateFirstRays(struct RT_RayConfig config, Camera *cam);
};

#endif //GRAPHIC_ENGINE_RAYCASTER_H
