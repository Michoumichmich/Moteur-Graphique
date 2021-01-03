#include "Pyramid.h"

#include <cmath>

Pyramid::Pyramid(double edge) : edge(edge) {

}

void Pyramid::Tesselate(int resolution) {
    double center_dist = (edge / 2) * tan(PI / 6);
    Point3D pt1(center_dist, -edge / 2, -center_dist);
    Point3D pt2(center_dist, edge / 2, -center_dist);
    Point3D pt3(-(edge * sqrt(5) / 2 - center_dist), 0, -center_dist);
    Point3D pt4(0, 0, edge * sqrt(5) / 2 - center_dist);
    tessels->emplace_back(pt1, pt2, pt3);
    tessels->emplace_back(pt1, pt2, pt4);
    tessels->emplace_back(pt2, pt3, pt4);
    tessels->emplace_back(pt1, pt3, pt4);
}

void Pyramid::serialize(std::stringstream &stream) {

}

void Pyramid::deserialize(std::istream &stream) {

}

std::ostream &Pyramid::print(std::ostream &str) {
    return str << "Pyramid(" << transformations.pt << ", " << edge << ")";
}