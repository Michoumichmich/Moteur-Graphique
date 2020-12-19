#include "RT_RayCaster.h"
#include <time.h>

std::vector<std::list<RT_Ray>> RT_RayCaster::generateFirstRays(RT_RayConfig config, const std::shared_ptr<Camera> &cam, unsigned int pool_count) {
    std::vector<std::list<RT_Ray>> Rays(pool_count);

    if (cam->getMode() == ORTHOGRAPHIC) {
        /**
         * The direction in which we look is constant
         */
        Vector direction = cam->getCamViewCenter();
        for (int x = 0; x < cam->pxWidthCount(); x++) {
            for (int y = 0; y < cam->pxHeightCount(); y++) {
                Vector shift = Vector(cam->getTarget(), cam->translatePixelCoordinates(x, y));
                Point3D originFromInfinite = cam->getOrigin() + shift;
#ifdef DEBUG
                //std::cout << "[RT_RayCaster] dir: " << direction << " origin from inf: " << originFromInfinite << std::endl;
#endif
                Rays[rand() % pool_count].emplace_back(direction, originFromInfinite, config, x, y);
            }
        }
    } else if (cam->getMode() == PERSPECTIVE) {
        for (int x = 0; x < cam->pxWidthCount(); x++) {
            for (int y = 0; y < cam->pxHeightCount(); y++) {
                Vector direction = Vector(cam->getOrigin(), cam->translatePixelCoordinates(x, y));
#ifdef DEBUG
                //std::cout << "[RT_RayCaster] dir: " << direction << " origin: " << cam->origin << std::endl;
#endif
                Rays[rand() % pool_count].emplace_back(direction, cam->getOrigin(), config, x, y);
            }
        }
    }
    return Rays;
}
