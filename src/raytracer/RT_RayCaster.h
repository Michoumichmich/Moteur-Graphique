#ifndef GRAPHIC_ENGINE_RAYCASTER_H
#define GRAPHIC_ENGINE_RAYCASTER_H

#include <list>
#include "RT_Ray.h"
#include<memory>

/**
 * @class RT_RayCaster
 * Creates the first set of rays given the camera used and the output picture resolution.
 */
class RT_RayCaster {
public:
    static std::vector<std::list<RT_Ray>> generateFirstRays(struct RT_RayConfig config, const std::shared_ptr<Camera> &cam, unsigned int pool_count = 32);
};

#endif //GRAPHIC_ENGINE_RAYCASTER_H
