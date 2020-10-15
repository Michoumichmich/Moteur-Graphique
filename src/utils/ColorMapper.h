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
    double param1;
    double param2;
public :
    /**
     * Constructor for the color mapper. The parameter's signification depends on the context.
     * @param param1
     * @param param2
     */
    explicit ColorMapper(enum coloringMethods method, double param1 = 0.1, double param2 = 0);

    Color Map(double);

};


#endif //_COLORINGMETHODS_H_