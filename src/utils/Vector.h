#ifndef GRAPHIC_ENGINE_VECTOR_H
#define GRAPHIC_ENGINE_VECTOR_H

#include "Point3D.h"
#include <cmath>

class Vector : public Point3D {
 public:
  double x{}, y{}, z{};
  Vector();
  Vector(Point3D x, Point3D y);
  Vector(double x, double y, double z);
  Vector operator*(const double &f) const;

  Vector operator*(const Vector &v) const;

  double dot(const Vector &v) const;

  Vector operator-(const Vector &v) const;

  Vector operator+(const Vector &v) const;

  Vector &operator+=(const Vector &v);

  Vector &operator*=(const Vector &v);

  Vector operator-() const;

  double length2() const;

  double length() const;
};

#endif //GRAPHIC_ENGINE_VECTOR_H
