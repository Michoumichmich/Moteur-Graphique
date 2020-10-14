#include "Tessel.h"


Tessel::Tessel() {
//TODO
}

Tessel::Tessel(Point3D p1, Point3D p2, Point3D p3, ApparenceProperties prop) {
    summmits[0] = p1;
    summmits[1] = p2;
    summmits[2] = p3;
}

Tessel::Tessel(Tessel const &tessel) {
  this->properties = tessel.properties;
  this->summmits[0] = tessel.summmits[0];
  this->summmits[1] = tessel.summmits[1];
  this->summmits[2] = tessel.summmits[2];
}

