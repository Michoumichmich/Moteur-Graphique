#include "Point3D.h"
#include <cmath>


Point3D::Point3D() : x(0), y(0), z(0) {
}

Point3D::Point3D(double x, double y, double z) : x(x), y(y), z(z) {
}

double Point3D::distance(Point3D &a, Point3D &b) {
    return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2) + pow(a.z - b.z, 2));
}
