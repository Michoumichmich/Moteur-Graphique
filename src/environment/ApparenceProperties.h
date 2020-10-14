#ifndef GRAPHIC_ENGINE_APPARENCEPROPERTIES_H
#define GRAPHIC_ENGINE_APPARENCEPROPERTIES_H

#include <utils.h>

class ApparenceProperties {
 public:
  /**
   * Either object's or light's color
   */
  Color color;
  double refractiveIndex;
  double transparency;
  double diffusivity;
  bool emitsLight;
  double lightBrightness;
};

#endif //GRAPHIC_ENGINE_APPARENCEPROPERTIES_H
