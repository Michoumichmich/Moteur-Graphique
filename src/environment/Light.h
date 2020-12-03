#ifndef _GRAPHIC_ENGINE_LIGHT_H
#define _GRAPHIC_ENGINE_LIGHT_H

#include "utils.h"

class Light {
public:
    Light(Vector p, double intensity);

    Vector position;
    double intensity;

    friend std::ostream& operator<<(std::ostream&, const Light&);
};

#endif //G_RAPHIC_ENGINE_LIGHT_H
