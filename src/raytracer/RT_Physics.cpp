#include "RT_Physics.h"

Vector RT_Physics::computePhongIllumination(Vector p, Vector n, Vector incomingRay, Vector ambientIntensity, std::list<Light> lights, ApparenceProperties properties) {
    /**
     * Ambient component
     */
    Vector intensity = ambientIntensity * properties.materialIntensity;

    /**
     * Diffuse and specular components
     */
    incomingRay = incomingRay.normalize();
    std::list<Light>::iterator it;
    for (it = lights.begin(); it != lights.end(); it++) {
        Vector lightDirection = (it->position - p).normalize();
        RT_RayConfig config{};
        config.isShadowRay = true;
        //TODO Cast shadow rays to check if point is in shadow
        intensity+= properties.materialDiffuseIntensity * it->intensity * n.dot(lightDirection); /**< Diffuse term */
        double specular = n.dot((lightDirection + incomingRay).normalize());
        intensity+= properties.materialSpecularIntensity * it->intensity * specular; /**< Specular term, computed with Blinn's formula */
    }

    return intensity;
}