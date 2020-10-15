#include "RT_RayCaster.h"

std::list<RT_Ray> RT_RayCaster::generateFirstRays(Camera *cam, OutputPictureManager *pic, unsigned int pixel_height_count, unsigned int pixel_width_count) {
    std::list<RT_Ray> Rays;

    if (cam->mode == ORTHOGRAPHIC) {
        for (int i = 0; i < pixel_width_count; i += 1 / pixel_height_count) {
            for (int j = 0; j < pixel_width_count; j += 1 / pixel_width_count) {
                Rays.push_back(RT_Ray(Vector(cam->origin, cam->target), cam->origin, 1 /*default counter ?*/, true));
            }
        }
    } else if (cam->mode == PERSPECTIVE) {
        double pixel_width = cam->viewportWidth / pixel_width_count;
        double pixel_height = cam->viewportHeight / pixel_height_count;
        //TODO
    }

    return Rays;
}
