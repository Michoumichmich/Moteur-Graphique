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

Vector Vector::operator*(const double &f) const {
    return {x * f, y * f, z * f};
}

Vector Vector::operator*(const Vector &v) const {
    return {x * v.x, y * v.y, z * v.z};
}

double Vector::dot(const Vector &v) const {
    { return x * v.x + y * v.y + z * v.z; }
}

Vector &Vector::operator+=(const Vector &v) {
    x += v.x, y += v.y, z += v.z;
    return *this;
}

Vector Vector::operator-(const Vector &v) const {
    return {x - v.x, y - v.y, z - v.z};
}

Vector Vector::operator+(const Vector &v) const {
    return {x + v.x, y + v.y, z + v.z};
}

Vector &Vector::operator*=(const Vector &v) {
    x *= v.x, y *= v.y, z *= v.z;
    return *this;
}

Vector Vector::operator-() const {
    return {-x, -y, -z};
}

double Vector::norm2() const {
    return x * x + y * y + z * z;
}

double Vector::norm() const {
    return sqrt(norm2());
}

Vector::Vector(Point3D p) : Vector(p.getX(), p.getY(), p.getZ()) {
}

Vector Vector::crossProduct(Vector u, Vector v) {
    double A = (u.y) * (v.z) - (u.z) * (v.y);
    double B = (u.z) * (v.x) - (u.x) * (v.z);
    double C = (u.x) * (v.y) - (u.y) * (v.x);
    return Vector(A, B, C);
}

Vector Vector::normalize() const {
    return *this * (1 / (*this).norm());
}
