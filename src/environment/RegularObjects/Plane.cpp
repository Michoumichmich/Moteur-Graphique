//
// Created by michel on 17/12/2020.
//

#include "Plane.h"

Plane::Plane(double x, double y)
        : x_size(x), y_size(y) {}

void Plane::Tesselate(int resolution) {
    tessels->emplace_back(Point3D(x_size / 2, -y_size / 2, 0), Point3D(-x_size / 2, -y_size / 2, 0), Point3D(x_size / 2, y_size / 2, 0));
    tessels->emplace_back(Point3D(-x_size / 2, y_size / 2, 0), Point3D(-x_size / 2, -y_size / 2, 0), Point3D(x_size / 2, y_size / 2, 0));
}

void Plane::serialize(std::stringstream &stream) {}

void Plane::deserialize(std::istream &stream) {}

std::ostream &Plane::print(std::ostream &str) {
    return str << "Plane(" << transformations.pt << ", x:" << x_size << " y:" << y_size << ")";
}
