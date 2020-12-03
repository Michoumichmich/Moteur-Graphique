//
// Created by lilian on 15/10/2020.
//

#include "Cube.h"
#include <sstream>

Cube::Cube(double size) : size(size) {

}

void Cube::Tesselate(int resolution) {
    tessels.push_back(new Tessel(Point3D(size / 2, -size / 2, size / 2), Point3D(-size / 2, -size / 2, size / 2), Point3D(-size / 2, -size / 2, -size / 2)));
    tessels.push_back(new Tessel(Point3D(size / 2, -size / 2, size / 2), Point3D(size / 2, -size / 2, -size / 2), Point3D(-size / 2, -size / 2, -size / 2)));
    tessels.push_back(new Tessel(Point3D(size / 2, size / 2, size / 2), Point3D(-size / 2, size / 2, size / 2), Point3D(-size / 2, size / 2, -size / 2)));
    tessels.push_back(new Tessel(Point3D(size / 2, size / 2, size / 2), Point3D(size / 2, size / 2, -size / 2), Point3D(-size / 2, size / 2, -size / 2)));
    tessels.push_back(new Tessel(Point3D(size / 2, -size / 2, size / 2), Point3D(size / 2, size / 2, size / 2), Point3D(size / 2, -size / 2, -size / 2)));
    tessels.push_back(new Tessel(Point3D(size / 2, size / 2, -size / 2), Point3D(size / 2, size / 2, size / 2), Point3D(size / 2, -size / 2, -size / 2)));
    tessels.push_back(new Tessel(Point3D(-size / 2, -size / 2, size / 2), Point3D(-size / 2, size / 2, size / 2), Point3D(-size / 2, -size / 2, -size / 2)));
    tessels.push_back(new Tessel(Point3D(-size / 2, size / 2, -size / 2), Point3D(-size / 2, size / 2, size / 2), Point3D(-size / 2, -size / 2, -size / 2)));
    tessels.push_back(new Tessel(Point3D(size / 2, -size / 2, size / 2), Point3D(-size / 2, -size / 2, size / 2), Point3D(size / 2, size / 2, size / 2)));
    tessels.push_back(new Tessel(Point3D(-size / 2, size / 2, size / 2), Point3D(-size / 2, -size / 2, size / 2), Point3D(size / 2, size / 2, size / 2)));
    tessels.push_back(new Tessel(Point3D(size / 2, -size / 2, -size / 2), Point3D(-size / 2, -size / 2, -size / 2), Point3D(size / 2, size / 2, -size / 2)));
    tessels.push_back(new Tessel(Point3D(-size / 2, size / 2, -size / 2), Point3D(-size / 2, -size / 2, -size / 2), Point3D(size / 2, size / 2, -size / 2)));
}

void Cube::serialize(std::stringstream &stream) {
    stream << Serializable::export_entry("Cube", {{"size", std::to_string(size)}});
}

void Cube::deserialize(std::istream &stream) {

}

std::ostream& operator<< (std::ostream &out, const Cube &cube) {
    out << "Cube(" << cube.transformations.pt << ", " << cube.size << ")";
    return out;
}