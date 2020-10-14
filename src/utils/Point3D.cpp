#include "Point3D.h"
#include <cmath>

double Point3D::getX() const
{
  return x;
}

double Point3D::getY() const
{
  return y;
}

Point3D Point3D::setX(double x)
{
  this->x = x;
  return *this;
}

Point3D Point3D::setY(double y)
{
  this->y = y;
  return *this;
}

double Point3D::getZ() const
{
  return z;
}

Point3D Point3D::setZ(double z)
{
  this->z = z;
  return *this;
}

Point3D::Point3D() : Point3D(0, 0, 0)
{
}

Point3D::Point3D(double x, double y, double z)
{
  this->setX(x).setY(y).setZ(z);
}
double Point3D::distance(Point3D a, Point3D b)
{
  return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2) + pow(a.z - b.z, 2));
}
