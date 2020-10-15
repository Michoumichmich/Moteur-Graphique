#include "ColorMapper.h"

ColorMapper::ColorMapper(enum coloringMethods method, double spacing): method(method), param(spacing)
{
}
Color ColorMapper::Map(double val)
{
  switch (method)
    {
      case LINEAR:
        return Color(val/param);
        break;
      case NONSENSE:

        break;
      case STRIPS:
        break;
      case TOPO_LINES:
        break;
    }
    return Color(0);
}
