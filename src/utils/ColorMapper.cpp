#include "ColorMapper.h"
#include <cmath>
#include <ctime>
#include <cstdlib>

ColorMapper::ColorMapper(enum colorMappingMethods method, double param1, double param2) : method(method), param1(param1), param2(param2) {
    srand((unsigned) time(nullptr));
    rand = std::rand() % 1000;
}

Color ColorMapper::Map(double val, Color refColor) {
    double fracpart, intpart, param;
    double tmp;
    switch (method) {
        case LINEAR:
            tmp = 1 - (param1 - val) / (param1 - param2);
            if (tmp < 0)return Color(0);
            else if (tmp > 1) return Color(1);
            else return Color(tmp * refColor.red, tmp * refColor.green, tmp * refColor.blue);
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
