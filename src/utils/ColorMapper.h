#ifndef _COLORINGMETHODS_H_
#define _COLORINGMETHODS_H_

#include "Color.h"


/**
 * Method used to convert a double to a color
 */
enum colorMappingMethods {
    /** The closer the lighter, the further the darker. Param1 min distance, Param2 maxdistance */
    LINEAR,
    /** Random stuff  */
    NONSENSE,
    /** Black and white strips with Param1 thickness */
    STRIPS,
    /** Black lines with param1 spacing, param2 line thickness */
    TOPO_LINES,
};

/**
 * @class can be attached to the OutputPictureManager and when called with writePixel, but with a double, the
 * selected mapping will be made.
 */
class ColorMapper {
private :
    enum colorMappingMethods method;
    double param1;
    double param2;
    int rand;
public :
    /**
     * Constructor for the color mapper. The parameter's signification depends on the context.
     * @param param1
     * @param param2
     */
    explicit ColorMapper(enum colorMappingMethods method, double param1 = 0.1, double param2 = 0);

    /**
     * Takes a double and returns the right color
     * accorging the the selected method and pressets
     * @return
     */
    Color Map(double);

};


#endif //_COLORINGMETHODS_H_