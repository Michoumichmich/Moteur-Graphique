#include "ColorMapper.h"
#include <cmath>
#include <ctime>
#include <cstdlib>

ColorMapper::ColorMapper(enum colorMappingMethods method, double param1, double param2) : method(method), param1(param1), param2(param2) {
    srand((unsigned)time(nullptr));
    rand = std::rand() % 1000;
}

Color ColorMapper::Map(double val) {
    double fracpart, intpart, param;
    switch (method) {
        case LINEAR:
            return Color(1 - ((val - param1) / (param2 - param1)));
        case NONSENSE:
            param = val * rand;
            fracpart = modf(param, &intpart);
            return {(int) pow(intpart, 1) % 256, (int) pow(intpart, 2) % 256, (int) pow(intpart, 3) % 256, 256};
        case STRIPS:
            break;
        case TOPO_LINES:
            break;
    }
    return Color(0);
}
