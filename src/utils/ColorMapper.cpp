#include "ColorMapper.h"

ColorMapper::ColorMapper(enum coloringMethods method, double param1, double param2) : method(method), param1(param1), param2(param2) {
}

Color ColorMapper::Map(double val) {
    switch (method) {
        case LINEAR:
            return Color(1 - ((val - param1) / (param2 - param1)));
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
