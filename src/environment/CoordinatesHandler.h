#ifndef _COORDINATESHANDLER_H_
#define _COORDINATESHANDLER_H_

#include <utils.h>

struct transformations {
    double scale = 1;
    double rotX = 0;
    double rotY = 0;
    double rotZ = 0;
    Point3D pt = Point3D();
};

class CoordinatesHandler {
public:
    Point3D fromLocalToGlobal(Point3D, struct transformations);
};

#endif //_COORDINATESHANDLER_H_
