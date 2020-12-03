#include "Light.h"

Light::Light(Vector p, double intensity)
        :position(p), intensity(intensity) { };

std::ostream& operator<<(std::ostream& out, const Light& light)
{
    out << "Light(" << light.position << ", " << light.intensity << ")";
    return out;
}