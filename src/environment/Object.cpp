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
    needComputeTessels = true;
    transformations.pt = center;
    return this;
}

Object* Object::setColor(Color color)
{
    needComputeTessels = true;
    properties.color = color;
    return this;
}

Object* Object::setLightIntensity(double intensity)
{
    needComputeTessels = true;
    properties.lightIntensity = intensity;
    return this;
}

Object* Object::setDiffusivity(double diffusivity)
{
    needComputeTessels = true;
    properties.diffusivity = diffusivity;
    return this;
}

Object* Object::setReflexivity(double reflexivity)
{
    needComputeTessels = true;
    properties.reflexivity = reflexivity;
    return this;
}

Object* Object::setRefractiveIndex(double index)
{
    needComputeTessels = true;
    properties.refractiveIndex = index;
    return this;
}

Object* Object::setTransparency(double transparency)
{
    needComputeTessels = true;
    properties.transparency = transparency;
    return this;
}

std::ostream& operator<<(std::ostream& out, Object& object) {
    return object.print(out);
}

Object::~Object() = default;
