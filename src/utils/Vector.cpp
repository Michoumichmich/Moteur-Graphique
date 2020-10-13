#include "Vector.h"

Vector::Vector(double x, double y, double z) : Point3D(x, y, z) {
    this->x = x;
    this->y = y;
    this->z = z;
}

Vector::Vector(Point3D x, Point3D y) {
    this->x = x.getX() - y.getX();
    this->y = x.getY() - y.getY();
    this->z = x.getZ() - y.getZ();
}

Vector::Vector() : Vector(0, 0, 0) {

}
