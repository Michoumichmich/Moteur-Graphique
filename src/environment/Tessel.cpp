#include "Tessel.h"

Tessel::Tessel() {
//TODO
}

Tessel::Tessel(Point3D p1, Point3D p2, Point3D p3) {
    summmits[0] = p1;
    summmits[1] = p2;
    summmits[2] = p3;
}

Tessel::Tessel(Point3D p1, Point3D p2, Point3D p3, ApparenceProperties prop) : Tessel(p1, p2, p3) {
    this->properties = prop;
}

Vector Tessel::getNormalVector() {
    Vector tmp = Vector(summmits[0], summmits[1]);
    return tmp.cross(Vector(summmits[1], summmits[2])).normalize();
}

Vector Tessel::getReflexionVector(Vector direction) {
    Vector n = getNormalVector();
    return direction - 2 * (direction.dot(n)) * n;
}
