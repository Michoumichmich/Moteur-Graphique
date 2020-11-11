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
  double refractiveIndex{};
  double transparency{};
  double diffusivity{};
  bool emitsLight{};
  double lightBrightness{};

  /**
   * Phong illumination parameters as Vector for RGB components
   */
   Vector materialIntensity{};
   Vector materialDiffuseIntensity{};
   Vector materialSpecularIntensity{};

};

#endif //GRAPHIC_ENGINE_APPARENCEPROPERTIES_H
