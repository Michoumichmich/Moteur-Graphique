#ifndef GRAPHICSENGINE_PLANE_H
#define GRAPHICSENGINE_PLANE_H


#include "../Object.h"

class Plane : public Object {
private:
    double x_size, y_size;
public:
    explicit Plane(double x, double y);

    void Tesselate(int resolution) override;

    void serialize(std::stringstream &stream) override;

    void deserialize(std::istream &stream) override;

    std::ostream &print(std::ostream &str) override;
};


#endif //GRAPHICSENGINE_PLANE_H
