#include "Tessel.h"

Tessel::Tessel()
{
//TODO
}

Tessel::Tessel(Point3D a, Point3D b, Point3D c, ApparenceProperties prop)
{
  //TODO
}

Tessel::Tessel(Tessel const &tessel)
{
  this->properties = tessel.properties;
  this->summmits[0] = tessel.summmits[0];
  this->summmits[1] = tessel.summmits[1];
  this->summmits[2] = tessel.summmits[2];
}
