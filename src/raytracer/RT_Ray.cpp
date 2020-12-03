#include <raytracer.h>
#include <utils.h>

#define free_ptr_list(list) while(!list.empty()) delete list.front(), list.pop_front()

RT_Ray::RT_Ray(Vector dir, Point3D orig, struct RT_RayConfig config)
        :dir(dir), origin(orig), ray_conf(config)
{
}

RT_Ray::RT_Ray(Vector dir, Point3D orig, struct RT_RayConfig config, unsigned int x, unsigned int y)
        :dir(dir), origin(orig), ray_conf(config), x(x), y(y)
{
}

/**
 * Takes a primary ray ie from the camera, computes it given its configuration and writes it using the
 * picture manager to a file.
 * @param intersector
 * @param pic
 */
void RT_Ray::RT_ComputePrimaryRay(RT_RayEnvIntersector* intersector, RT_OutputManager* pic)
{
    struct RT_RayOutput rayOutput = RT_ComputeRay(intersector);
    pic->RT_SaveRay(rayOutput, x, y);
}

/**
 * Recursively (if needed) computes a ray.
 * @param intersector
 * @return the ray's color, distance to the first object and intensity.
 */
struct RT_RayOutput RT_Ray::RT_ComputeRay(RT_RayEnvIntersector* intersector)
{
    struct RT_IntersectorResult res = intersector->RT_RayFindIntersection(origin, dir);

    /* No reflexions or whatever, we return directly the result */
    if (ray_conf.rtMode==RT_RayRenderMode::RT_BITMAP || ray_conf.rtMode==RT_RayRenderMode::RT_DEPTHMAP) {
        /* Distance TO THE PLANE where is the intersection point, for the DOF etc, depth mapping, etc */
        if (res.intersectsSometing) {
            return RT_RayOutput{res.tessel.properties.color, res.intersectionPoint, res.distance, res.ortho_dist, 1};
        }
        else {
            return RT_RayOutput{ray_conf.env->backgroundColor, res.intersectionPoint, res.distance, res.ortho_dist, 1};
        }
    }

    if (ray_conf.rtMode==RT_RayRenderMode::RT_STANDARD) {
        if (!res.intersectsSometing || res.type==RT_RayIntersectionType::INF) {
            return RT_RayOutput{ray_conf.env->backgroundColor, res.intersectionPoint, -1, 1};
        }

        /* On a touché une texture, on affiche la couleur du pixel */
        if (res.type==RT_RayIntersectionType::MAPPED_TEXTURE) {
            return RT_RayOutput{res.texture.getPixelAtCoordinates(res.intersectionPoint), res.intersectionPoint, (origin-res.intersectionPoint).length(), 1};
            //TODO Add general case for hitting any material, and treat the cases separately depending on if the surface is opaque, reflective, or transparent reflective.
        }

        if (res.type==RT_RayIntersectionType::TESSEL) {
            Color result_color = res.tessel.properties.color;
            if (!res.tessel.properties.sendRay()) {
                Vector color = RT_Physics::computePhongIllumination(res.intersectionPoint, res.tessel.getNormalVector(), (origin-res.intersectionPoint).normalize(), &environment, *intersector,
                        res.tessel.properties);
                //TODO ?     return RT_RayOutput{Color(color.x, color.y, color.z), res.intersectionPoint, (origin - res.intersectionPoint).length(), 1};
            }
            Color child_rays_color;
            if (this->ray_conf.bouncesLeft>0) {
                auto rays = RT_PrepareRays(res);
                child_rays_color = RT_ComputePreparedRays(rays, intersector);
            }

            //result_color = result_color*res.tessel.properties.lightIntensity*this->ray_conf.intensity ;
            result_color = result_color+child_rays_color*(1-this->ray_conf.intensity);
            // result_color.blue  += std::max(result_color.blue, child_rays_color.blue);
            // result_color.red  += std::max(result_color.red, child_rays_color.red);
            // result_color.green += std::max(result_color.green, child_rays_color.green);

            //  result_color = result_color * child_rays_color.getIntensity() + ;

            //TODO stuff with the color, take in account phong illumin ? etc
            return RT_RayOutput{result_color, res.intersectionPoint, res.distance, res.ortho_dist, 1};
        }
        return RT_RayOutput();
    }
    //No intersection found.
    return RT_RayOutput();
}

Color RT_Ray::RT_ComputePreparedRays(const std::list<std::shared_ptr<RT_Ray>>& rays, RT_RayEnvIntersector* intersector)
{
    struct RT_RayOutput tmp;
    Color color(0);
    for (const auto& ray: rays) {
        tmp = ray->RT_ComputeRay(intersector);
        color = color+tmp.resultColor*ray->ray_conf.intensity;
    }
    return color;
}

std::list<std::shared_ptr<RT_Ray>> RT_Ray::RT_PrepareRays(RT_IntersectorResult result)
{
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
        new_config.intensity *= tessel_prop.reflexivity;
        this->ray_conf.intensity *= (1-tessel_prop.reflexivity);
        //  std::cout << "intensity" << this->ray_conf.intensity << " child intenisty" << new_config.intensity<< std::endl;
        auto reflected = std::make_shared<RT_Ray>(result.tessel.getReflexionVector(this->dir), result.intersectionPoint, new_config);
        rays.push_back(reflected);
    }
    return rays;
    //TODO
}
