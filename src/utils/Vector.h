#ifndef GRAPHIC_ENGINE_VECTOR_H
#define GRAPHIC_ENGINE_VECTOR_H

#include "Point3D.h"
#include <math.h>

class Vector : public Point3D {
    public:
        double x,y,z;
        Vector();
        Vector(Point3D x,Point3D y);
        Vector(double x,double y,double z);
        Vector operator * (const double &f) const { return Vector(x * f, y * f, z * f); } 
        Vector operator * (const Vector &v) const { return Vector(x * v.x, y * v.y, z * v.z); } 
        double dot(const Vector &v) const { return x * v.x + y * v.y + z * v.z; } 
        Vector operator - (const Vector &v) const { return Vector(x - v.x, y - v.y, z - v.z); } 
        Vector operator + (const Vector &v) const { return Vector(x + v.x, y + v.y, z + v.z); } 
        Vector& operator += (const Vector &v) { x += v.x, y += v.y, z += v.z; return *this; } 
        Vector& operator *= (const Vector &v) { x *= v.x, y *= v.y, z *= v.z; return *this; } 
        Vector operator - () const { return Vector(-x, -y, -z); } 
        double length2() const { return x * x + y * y + z * z; } 
        double length() const { return sqrt(length2()); } 
};


#endif //GRAPHIC_ENGINE_VECTOR_H
