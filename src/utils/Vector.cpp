#include "Vector.h"

Vector::Vector(double x, double y, double z) : Point3D(x, y, z)
{
  this->x = x;
  this->y = y;
  this->z = z;
}

Vector::Vector(Point3D x, Point3D y)
{
  this->x = x.getX() - y.getX();
  this->y = x.getY() - y.getY();
  this->z = x.getZ() - y.getZ();
}

Vector::Vector() : Vector(0, 0, 0)
{
}
Vector Vector::operator*(const double &f) const
{
  return {x * f, y * f, z * f};
}
Vector Vector::operator*(const Vector &v) const
{
  return {x * v.x, y * v.y, z * v.z};
}
double Vector::dot(const Vector &v) const
{
  { return x * v.x + y * v.y + z * v.z; }
}
Vector &Vector::operator+=(const Vector &v)
{
  x += v.x, y += v.y, z += v.z;
  return *this;
}
Vector Vector::operator-(const Vector &v) const
{
  return {x - v.x, y - v.y, z - v.z};
}
Vector Vector::operator+(const Vector &v) const
{
  return {x + v.x, y + v.y, z + v.z};
}
Vector &Vector::operator*=(const Vector &v)
{
  x *= v.x, y *= v.y, z *= v.z;
  return *this;
}
Vector Vector::operator-() const
{
  return {-x, -y, -z};
}
double Vector::length2() const
{
  return x * x + y * y + z * z;
}
double Vector::length() const
{
  return sqrt(length2());
}
