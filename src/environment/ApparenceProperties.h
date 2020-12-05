#ifndef GRAPHIC_ENGINE_APPARENCEPROPERTIES_H
#define GRAPHIC_ENGINE_APPARENCEPROPERTIES_H

#include <utils.h>

class ApparenceProperties {
public:
    /**
     * Either object's or light's color
     * Default is white so we can use it for the depth map directly
     */
    Color color = Color(1);
    double refractiveIndex = 2;
    double transparency = 0;
    double reflexivity = 0;
    double diffusivity = 0;
    double lightIntensity = 0; /**< Objects can also emit light */

    [[nodiscard]] inline bool sendRay() const
    {
        return transparency==0 && reflexivity==0 && diffusivity==0;
    };

    /**
     * Phong illumination parameters
     */
    Vector materialIntensity{};
    Vector materialDiffuseIntensity{};
    Vector materialSpecularIntensity{};
};

#endif //GRAPHIC_ENGINE_APPARENCEPROPERTIES_H
