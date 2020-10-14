#include "Tessel.h"

Tessel::Tessel() {

}

Tessel::Tessel(Point3D p1, Point3D p2, Point3D p3, ApparenceProperties prop) {
    summmits[0] = p1;
    summmits[1] = p2;
    summmits[2] = p3;
}