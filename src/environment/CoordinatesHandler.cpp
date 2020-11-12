#include "CoordinatesHandler.h"
#include <cmath>

Point3D CoordinatesHandler::fromLocalToGlobal(Point3D local, struct transformations transformations) {
    /**
     * Scaling of the point. Makes sense given that the figure's center is in 0.0.0
     */
    Vector vec = local * transformations.scale;

    /**
     * Now the rotations : their order is important
     */
    rotate(&vec.y, &vec.z, transformations.rotX);
    rotate(&vec.x, &vec.z, transformations.rotY);
    rotate(&vec.x, &vec.y, transformations.rotZ);

    /**
     * Translation in the world
     */
    vec += transformations.pt;
    return vec;
}

void CoordinatesHandler::rotate(float *x, float *y, float deg) {
    float theta = PI * deg / 180.0;
    float x_tmp = *x;
    float y_tmp = *y;
    *x = x_tmp * cos(theta) - y_tmp * sin(theta);
    *y = x_tmp * sin(theta) + y_tmp * cos(theta);
}

Tessel CoordinatesHandler::fromLocalToGlobal(const Tessel &tessel, struct transformations transformations) {
    Tessel out = Tessel(tessel);
    out.summmits[0] = fromLocalToGlobal(out.summmits[0], transformations);
    out.summmits[1] = fromLocalToGlobal(out.summmits[1], transformations);
    out.summmits[2] = fromLocalToGlobal(out.summmits[2], transformations);
    return out;
}
