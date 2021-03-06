#include <raytracer.h>
#include <utils.h>

#define free_ptr_list(list) while(!list.empty()) delete list.front(), list.pop_front()

RT_Ray::RT_Ray(Vector dir, Point3D orig, struct RT_RayConfig config)
        : dir(dir), origin(orig), ray_conf(config) {
}

RT_Ray::RT_Ray(Vector dir, Point3D orig, struct RT_RayConfig config, unsigned int x, unsigned int y)
        : dir(dir), origin(orig), ray_conf(config), x(x), y(y) {
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
    auto inter = intersector->RT_RayFindIntersection(origin, dir);
    struct RT_IntersectorResult res;

    if (inter) {
        res = inter.value();
    }

    /* No reflexions or whatever, we return directly the result */
    if (ray_conf.rtMode == RT_RayRenderMode::RT_BITMAP || ray_conf.rtMode == RT_RayRenderMode::RT_DEPTHMAP ||
        ray_conf.rtMode == RT_RayRenderMode::RT_DEPTHMAP_BW) {
        /* Distance TO THE PLANE where is the intersection point, for the DOF etc, depth mapping, etc */
        if (inter) {
            return RT_RayOutput{res.tessel.properties.color, res.intersectionPoint, res.distance, res.ortho_dist, 1};
        } else {
            return RT_RayOutput{ray_conf.env->backgroundColor, res.intersectionPoint, res.distance, res.ortho_dist, 1};
        }
    } else if (ray_conf.rtMode == RT_RayRenderMode::RT_STANDARD) {
        if (!inter || res.type == RT_RayIntersectionType::INF) {
            return RT_RayOutput{ray_conf.env->backgroundColor, res.intersectionPoint, -1, 1};
        }

        /* On a touché une texture, on affiche la couleur du pixel */
        if (res.type == RT_RayIntersectionType::MAPPED_TEXTURE) {
            return RT_RayOutput{res.texture.getPixelAtCoordinates(res.intersectionPoint), res.intersectionPoint, (origin - res.intersectionPoint).length(), 1};
            //TODO Add general case for hitting any material, and treat the cases separately depending on if the surface is opaque, reflective, or transparent reflective.
        }

        if (res.type == RT_RayIntersectionType::TESSEL) {
            Color result_color = res.tessel.properties.color;
            if (!res.tessel.properties.sendRay()) {
                Vector color = RT_Physics::computePhongIllumination(res.intersectionPoint, res.tessel.getNormalVector(),
                                                                    (origin - res.intersectionPoint).normalize(), (ray_conf.env), *intersector,
                                                                    res.tessel.properties);
                //TODO ?     return RT_RayOutput{Color(color.x, color.y, color.z), res.intersectionPoint, (origin - res.intersectionPoint).length(), 1};
            }

            if (this->ray_conf.bouncesLeft > 0) {
                auto rays = RT_PrepareRays(res);
                Color child_rays_color = RT_ComputePreparedRays(rays, intersector);
                result_color = result_color * (1 - res.tessel.properties.reflexivity) + child_rays_color * res.tessel.properties.reflexivity;

                result_color = res.tessel.properties.color * res.tessel.properties.lightIntensity + result_color * (1 - res.tessel.properties.lightIntensity);

            }


            //if (result_color.green>1 || result_color.blue>1 || result_color.red>1) {std::cout << result_color;}

            //TODO stuff with the color, take in account phong illumin ? etc
            return RT_RayOutput{result_color, res.intersectionPoint, res.distance, res.ortho_dist, 1};
        }
        return RT_RayOutput{ray_conf.env->backgroundColor, Vector(), -1, -1, 1};
    }
    //No intersection found.
    return RT_RayOutput{ray_conf.env->backgroundColor, Vector(), -1, -1, 1};
}

Color RT_Ray::RT_ComputePreparedRays(const std::list<std::shared_ptr<RT_Ray>> &rays, RT_RayEnvIntersector *intersector) {
    struct RT_RayOutput tmp;
    Color color(0);
    for (const auto &ray: rays) {
        tmp = ray->RT_ComputeRay(intersector);
        color = color + tmp.resultColor * ray->ray_conf.intensity * tmp.intensity;
    }
    return color;
}

std::list<std::shared_ptr<RT_Ray>> RT_Ray::RT_PrepareRays(RT_IntersectorResult result) {
    std::list<std::shared_ptr<RT_Ray>> rays;
    ApparenceProperties tessel_prop = result.tessel.properties;
    /*  if (this->ray_conf.transparency) {
          this->ray_conf.intensity *= (1-tessel_prop.transparency);
          RT_RayConfig new_config = this->ray_conf;
          new_config.bouncesLeft--;
          new_config.intensity *= tessel_prop.transparency;
          RT_Ray transparent_ray = RT_Ray(this->dir, result.intersectionPoint, new_config);
          rays.push_back(transparent_ray);
      }*/

    if (this->ray_conf.reflexions) {
        RT_RayConfig new_config = this->ray_conf;
        new_config.bouncesLeft--;
        //    new_config.intensity *= tessel_prop.reflexivity;
        //   this->ray_conf.intensity *= (1 - tessel_prop.reflexivity);
        //  std::cout << "intensity" << this->ray_conf.intensity << " child intenisty" << new_config.intensity<< std::endl;
        auto reflected = std::make_shared<RT_Ray>(result.tessel.getReflexionVector(this->dir), result.intersectionPoint, new_config);
        rays.push_back(reflected);
    }
    return rays;
    //TODO
}
