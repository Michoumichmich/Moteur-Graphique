//
// Created by michel on 11/10/2020.
//

#include <functional>
#include "Sphere.h"

void Sphere::Tesselate() {
    int n_lat = 20;
    int n_long = 20;

    Point3D globe[n_lat+1][n_long+1];

    std::function<float(float, float, float, float, float)> map = [](float value, float start1, float stop1, float start2, float stop2) {
        return start2 + (stop2 - start2) * ((value - start1) / (stop1 - start1));
    };

    for (int i = 0; i < n_lat; ++i) {
        float theta = map(i, 0, n_lat, 0, PI);
        for (int j = 0; j < n_long; ++j) {
            float phi = map(j, 0, n_long, 0, 2 * PI);
            float x = sin(theta) * cos(phi);
            float y = sin(theta) * sin(phi);;
            float z = cos(theta);
            globe[i][j] = Point3D(x, y, z);
        }
    }
    for (int i = 0; i < n_lat; ++i) {
        for (int j = 0; j < n_long; ++j) {
            this->tessels.push_back(new Tessel(globe[i][j], globe[i+1][j], globe[i][j+1]));
            this->tessels.push_back(new Tessel(globe[i+1][j+1], globe[i+1][j], globe[i][j+1]));
        }
    }
}