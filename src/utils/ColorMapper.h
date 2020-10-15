#ifndef _COLORINGMETHODS_H_
#define _COLORINGMETHODS_H_


#include "Color.h"


enum coloringMethods {
    LINEAR,
    NONSENSE,
    STRIPS,
    TOPO_LINES,
};

class ColorMapper {
private :
    enum coloringMethods method;
    double param;
public :
    explicit ColorMapper(enum coloringMethods, double param = 0.1);

    Color Map(double);

};


#endif //_COLORINGMETHODS_H_