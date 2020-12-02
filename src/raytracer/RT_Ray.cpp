#include <raytracer.h>
#include <utils.h>
#include <cmath>

RT_Ray::RT_Ray(Vector dir, Point3D orig, struct RT_RayConfig config) : dir(dir), origin(orig), ray_conf(config) {
}

RT_Ray::RT_Ray(Vector dir, Point3D orig, struct RT_RayConfig config, unsigned int x, unsigned int y) : dir(dir), origin(orig), ray_conf(config), x(x), y(y) {
}

/**
 * Takes a primary ray ie from the camera, computes it given its configuration and writes it using the
 * picture manager to a file.
 * @param intersector
 * @param pic
 */
void RT_Ray::RT_ComputePrimaryRay(RT_RayEnvIntersector *intersector, RT_OutputManager *pic) {
    struct RT_RayOutput rayOutput = RT_ComputeRay(intersector);
    pic->RT_SaveRay(rayOutput, x, y);
}

/**
 * Recursively (if needed) computes a ray.
 * @param intersector
 * @return the ray's color, distance to the first object and intensity.
 */
struct RT_RayOutput RT_Ray::RT_ComputeRay(RT_RayEnvIntersector *intersector) {
    struct RT_IntersectorResult res = intersector->RT_RayFindIntersection(origin, dir);

    /* No reflexions or whatever, we return directly the result */
    if (ray_conf.rtMode == RT_RayRenderMode::RT_BITMAP || ray_conf.rtMode == RT_RayRenderMode::RT_DEPTHMAP) {
        /* Distance TO THE PLANE where is the intersection point, for the DOF etc, depth mapping, etc */
        double ortho_dist = std::sqrt(ray_conf.cam_view_center.dot(res.intersectionPoint - origin));
        if (res.intersectsSometing) {
            return RT_RayOutput{res.tessel.properties.color, res.intersectionPoint, res.distance, ortho_dist, 1};
        } else {
            return RT_RayOutput{ray_conf.env->backgroundColor, res.intersectionPoint, res.distance, ortho_dist, 1};
        }
    }


    if (ray_conf.rtMode == RT_RayRenderMode::RT_STANDARD) {
        if (!res.intersectsSometing || res.type == RT_RayIntersectionType::INF) {
            return RT_RayOutput{ray_conf.env->backgroundColor, res.intersectionPoint, -1, 1};
        }

        /* On a touché une texture, on affiche la couleur du pixel */
        if (res.type == RT_RayIntersectionType::MAPPED_TEXTURE) {
            return RT_RayOutput{res.texture.getPixelAtCoordinates(res.intersectionPoint), res.intersectionPoint, (origin - res.intersectionPoint).length(), 1};
            //TODO Add general case for hitting any material, and treat the cases separately depending on if the surface is opaque, reflective, or transparent reflective.
        }

        if (res.type == RT_RayIntersectionType::TESSEL) {
            if (!res.tessel.properties.sendRay()) {
                Vector color = RT_Physics::computePhongIllumination(res.intersectionPoint, res.tessel.getNormalVector(), (origin - res.intersectionPoint).normalize(), environment, *intersector, res.tessel.properties);
                return RT_RayOutput{Color(color.x, color.y, color.z), res.intersectionPoint, (origin - res.intersectionPoint).length(), 1};
            }
            //TODO else send other rays
            std::list<RT_Ray> rays = RT_PrepareRays(res);
        }
        return RT_RayOutput();
    }

    //BUG
    return RT_RayOutput();
}

Color RT_Ray::RT_ComputePreparedRays(std::list<RT_Ray> rays, RT_RayEnvIntersector *intersector) {
    struct RT_RayOutput tmp;
    for (auto &ray: rays) {
        tmp = ray.RT_ComputeRay(intersector);
    }
    //TODO
}

std::list<RT_Ray> RT_Ray::RT_PrepareRays(RT_IntersectorResult result) {
    return std::list<RT_Ray>();
    //TODO
}
