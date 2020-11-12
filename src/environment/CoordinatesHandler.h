#ifndef _COORDINATESHANDLER_H_
#define _COORDINATESHANDLER_H_

#include <utils.h>
#include "Tessel.h"

/**
 * Structure that holds the different transformations that can be applied to a point, an objet or a tessel
 * The angle is defined in degrees (easier to work with for an end used I think).
 */
struct transformations {
    double scale = 1;
    int rotX = 0;
    int rotY = 0;
    int rotZ = 0;
    Point3D pt = Point3D();
};

class CoordinatesHandler {
public:
    static Point3D fromLocalToGlobal(Point3D, struct transformations);

    static Tessel fromLocalToGlobal(const Tessel &, struct transformations);

    static void rotate(float *x, float *y, float deg);
};

#endif //_COORDINATESHANDLER_H_
