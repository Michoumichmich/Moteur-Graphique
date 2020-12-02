#include "RT_Physics.h"
#include "environment.h"

Vector
RT_Physics::computePhongIllumination(Vector p, Vector n, Vector incomingRay, Environment env, RT_RayEnvIntersector inter, ApparenceProperties properties) {
    /**
     * Ambient component
     */
    Vector intensity = env.ambientIntensity * properties.materialIntensity;

    /**
     * Diffuse and specular components
     */
    incomingRay = incomingRay.normalize();
    std::list<Light *>::iterator it;
    for (it = env.allLights.begin(); it != env.allLights.end(); it++) {
        Vector lightDirection = ((*it)->position - p).normalize();
        if (!inter.RT_RayFindIntersection(p, lightDirection).intersectsSometing) {
            intensity += properties.materialDiffuseIntensity * (*it)->intensity * n.dot(lightDirection); /**< Diffuse term */
            double specular = n.dot((lightDirection + incomingRay).normalize());
            intensity += properties.materialSpecularIntensity * (*it)->intensity * specular; /**< Specular term, computed with Blinn's formula */
        }
    }

    return intensity;
}