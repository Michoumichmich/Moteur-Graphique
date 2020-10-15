//
// Created by michel on 11/10/2020.
//

#include <functional>
#include "Sphere.h"

void Sphere::Tesselate() {
    int n_lat = 20;
    int n_long = 20;

    Point3D globe[n_lat+1][n_long+1];

    auto map = [](double value, double start1, double stop1, double start2, double stop2) {
        return start2 + (stop2 - start2) * ((value - start1) / (stop1 - start1));
    };
    for (int i = 0; i < n_lat; ++i) {
        double theta = map(i, 0, n_lat, 0, PI);
        for (int j = 0; j < n_long; ++j) {
            double phi = map(j, 0, n_long, 0, 2 * PI);
            double x = sin(theta) * cos(phi) * radius;
            double y = sin(theta) * sin(phi) * radius;
            double z = cos(theta) * radius;
            globe[i][j] = Point3D(x, y, z);
        }
    }

    for (int i = 0; i < n_lat; ++i) {
        for (int j = 0; j < n_long; ++j) {
            this->tessels.push_back(new Tessel(globe[i][j], globe[i + 1][j], globe[i][j + 1], this->properties));
            this->tessels.push_back(new Tessel(globe[i + 1][j + 1], globe[i + 1][j], globe[i][j + 1], this->properties));
        }
    }
}

Sphere::Sphere(double radius) : radius(radius) {
}
