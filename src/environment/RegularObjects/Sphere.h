
#ifndef GRAPHICSENGINE_SPHERE_H
#define GRAPHICSENGINE_SPHERE_H

#include "../Object.h"

class Sphere : public Object {
private:
    double radius;
public:
    explicit Sphere(double radius);

    void Tesselate(int resolution) override;

    void deserialize(std::istream& stream) override;

    void serialize(std::stringstream& stream) override;

    std::ostream& print(std::ostream& str) override;
};

#endif //GRAPHICSENGINE_SPHERE_H
