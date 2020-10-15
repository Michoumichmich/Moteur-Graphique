#include "RT_RayCaster.h"

std::list<RT_Ray> RT_RayCaster::generateFirstRays(Camera *cam, unsigned int pixel_height_count, unsigned int pixel_width_count) {
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
        Vector view = Vector(cam->target, cam->origin);
        Vector up_unit = (cam->viewUp - view.normalize() * (view.normalize().dot(cam->viewUp))).normalize();
        // double dot = view.normalize().dot(cam->viewUp);
        Vector right_unit = Vector::crossProduct(up_unit, view).normalize();
        Point3D bottomLeft = Vector(cam->target) - up_unit * (cam->viewportHeight / 2.0) - right_unit * (cam->viewportWidth / 2.0);

        for (unsigned x = 0; x < pixel_width_count; x++) {
            for (unsigned y = 0; y < pixel_height_count; y++) {
                Vector target = Vector(bottomLeft) + up_unit * (y / pixel_height) + right_unit * (x / pixel_width);
                Rays.emplace_back(target, cam->origin, 1, true, x, y);
            }
        }
    }

    return Rays;
}
