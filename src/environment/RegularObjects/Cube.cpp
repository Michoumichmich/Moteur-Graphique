#include "Cube.h"
#include <sstream>

Cube::Cube(double size)
        : size(size) {

}

void Cube::Tesselate(int resolution) {
    tessels->emplace_back(Point3D(size / 2, -size / 2, size / 2), Point3D(-size / 2, -size / 2, size / 2), Point3D(-size / 2, -size / 2, -size / 2));
    tessels->emplace_back(Point3D(size / 2, -size / 2, size / 2), Point3D(size / 2, -size / 2, -size / 2), Point3D(-size / 2, -size / 2, -size / 2));
    tessels->emplace_back(Point3D(size / 2, size / 2, size / 2), Point3D(-size / 2, size / 2, size / 2), Point3D(-size / 2, size / 2, -size / 2));
    tessels->emplace_back(Point3D(size / 2, size / 2, size / 2), Point3D(size / 2, size / 2, -size / 2), Point3D(-size / 2, size / 2, -size / 2));
    tessels->emplace_back(Point3D(size / 2, -size / 2, size / 2), Point3D(size / 2, size / 2, size / 2), Point3D(size / 2, -size / 2, -size / 2));
    tessels->emplace_back(Point3D(size / 2, size / 2, -size / 2), Point3D(size / 2, size / 2, size / 2), Point3D(size / 2, -size / 2, -size / 2));
    tessels->emplace_back(Point3D(-size / 2, -size / 2, size / 2), Point3D(-size / 2, size / 2, size / 2), Point3D(-size / 2, -size / 2, -size / 2));
    tessels->emplace_back(Point3D(-size / 2, size / 2, -size / 2), Point3D(-size / 2, size / 2, size / 2), Point3D(-size / 2, -size / 2, -size / 2));
    tessels->emplace_back(Point3D(size / 2, -size / 2, size / 2), Point3D(-size / 2, -size / 2, size / 2), Point3D(size / 2, size / 2, size / 2));
    tessels->emplace_back(Point3D(-size / 2, size / 2, size / 2), Point3D(-size / 2, -size / 2, size / 2), Point3D(size / 2, size / 2, size / 2));
    tessels->emplace_back(Point3D(size / 2, -size / 2, -size / 2), Point3D(-size / 2, -size / 2, -size / 2), Point3D(size / 2, size / 2, -size / 2));
    tessels->emplace_back(Point3D(-size / 2, size / 2, -size / 2), Point3D(-size / 2, -size / 2, -size / 2), Point3D(size / 2, size / 2, -size / 2));
}

void Cube::serialize(std::stringstream &stream) {
    stream << Serializable::export_entry("Cube", {{"size", std::to_string(size)}});
}

void Cube::deserialize(std::istream &stream) {
}

std::ostream &Cube::print(std::ostream &str) {
    return str << "Cube(" << transformations.pt << ", " << size << ")";
}
