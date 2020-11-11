#include "Object.h"

std::list<Tessel *> Object::getTessels(int resolution)
{

  if (this->needComputeTessels)
    {
      this->tessels.clear();
      this->Tesselate(resolution);
      std::list<Tessel *>::iterator aTessel;
      for (aTessel = tessels.begin(); aTessel != tessels.end(); aTessel++)
        {
          **aTessel = CoordinatesHandler::fromLocalToGlobal(**aTessel, this->tranfo);
          (*aTessel)->properties = this->properties;
        }
      this->needComputeTessels = false;
    }
  return this->tessels;
}

Object *Object::setTransformation(struct transformations transfo)
{
  this->tranfo = transfo;
  this->needComputeTessels = true;
  return this;
}

Object *Object::setColor(Color color)
{
  this->properties.color = color;
  return this;
}