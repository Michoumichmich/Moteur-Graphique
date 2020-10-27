#include "Object.h"


std::list<Tessel *> Object::getTessels()
{

  if (this->needComputeTessels)
    {
      this->tessels = {};
      this->Tesselate();
      std::list<Tessel *>::iterator aTessel;
      for (aTessel = tessels.begin(); aTessel != tessels.end(); aTessel++)
        {
          **aTessel = CoordinatesHandler::fromLocalToGlobal(**aTessel, this->tranfo);
        }
      this->needComputeTessels = false;
    }
  return this->tessels;
}

void Object::setTransformation(struct transformations transfo)
{
  this->tranfo = transfo;
  this->needComputeTessels = true;
}
