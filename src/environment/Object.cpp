#include <memory>
#include "Object.h"

std::shared_ptr<std::list<Tessel>> Object::getTessels(int resolution)
{
    if (needComputeTessels) {
        tessels->clear();
        Tesselate(resolution);

        for (Tessel& aTessel : *tessels) {
            aTessel = CoordinatesHandler::fromLocalToGlobal(aTessel, transformations);
            aTessel.properties = properties;
        }
        needComputeTessels = false;
    }
    return tessels;
}

Object* Object::setTransformation(struct transformations transfo)
{
    transformations = transfo;
    needComputeTessels = true;
    return this;
}

Object* Object::setCenter(Point3D center)
{
    transformations.pt = center;
    return this;
}

Object* Object::setColor(Color color)
{
    properties.color = color;
    return this;
}

Object* Object::setLightIntensity(double intensity)
{
    properties.lightIntensity = intensity;
    return this;
}

Object* Object::setDiffusivity(double diffusivity)
{
    properties.diffusivity = diffusivity;
    return this;
}

Object* Object::setReflexivity(double reflexivity)
{
    properties.reflexivity = reflexivity;
    return this;
}

Object* Object::setRefractiveIndex(double index)
{
    properties.refractiveIndex = index;
    return this;
}

Object* Object::setTransparency(double transparency)
{
    properties.transparency = transparency;
    return this;
}

std::ostream& operator<<(std::ostream& out, Object& object) {
    return object.print(out);
}

Object::~Object() = default;
