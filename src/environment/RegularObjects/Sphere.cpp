#include "Sphere.h"
#include <cmath>
#include <sstream>
#include <vector>

void Sphere::Tesselate(int resolution) {
    int n = resolution;
    std::vector<std::vector<Point3D>> globe(n + 1, std::vector<Point3D>(n + 1));

    auto map = [](double value, double start1, double stop1, double start2, double stop2) {
        return start2 + (stop2 - start2) * ((value - start1) / (stop1 - start1));
    };

    for (int i = 0; i <= n; ++i) {
        double theta = map(i, 0, n, 0, PI);
        for (int j = 0; j <= n; ++j) {
            double phi = map(j, 0, n, 0, 2 * PI);
            double x = radius * sin(theta) * cos(phi);
            double y = radius * sin(theta) * sin(phi);
            double z = radius * cos(theta);
            globe[i][j] = Point3D(x, y, z);
        }
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            this->tessels->push_back(Tessel(globe[i][j], globe[i + 1][j], globe[i][j + 1], this->properties));
            this->tessels->push_back(Tessel(globe[i + 1][j + 1], globe[i + 1][j], globe[i][j + 1], this->properties));
        }
    }
}

Sphere::Sphere(double radius)
        : radius(radius) {
}

void Sphere::serialize(std::stringstream &stream) {
    stream << Serializable::export_entry("Sphere", {{"radius", std::to_string(radius)}});
}

void Sphere::deserialize(std::istream &stream) {
}

std::ostream &Sphere::print(std::ostream &str) {
    return str << "Sphere(" << transformations.pt << ", " << radius << ")";
}
