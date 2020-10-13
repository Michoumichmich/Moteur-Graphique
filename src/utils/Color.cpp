#include "Color.h"
Color::Color(enum colors color)
{
  if (color == BLACK)
    {
      red = 0;
      blue = 0;
      green = 0;
      bit = 0;
    }
}
