#ifndef GRAPHICSENGINE_SPHERE_H
#define GRAPHICSENGINE_SPHERE_H

#include "../Object.h"

class Sphere : public Object {
private:
    double radius;
public:
    explicit Sphere(double radius);

    void Tesselate(int resolution) override;

    void deserialize(std::istream &stream) override;

    std::string serialize(std::ostream &stream) override;
};

#endif //GRAPHICSENGINE_SPHERE_H
