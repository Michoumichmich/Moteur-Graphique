#ifndef GRAPHIC_ENGINE_CAMERA_H
#define GRAPHIC_ENGINE_CAMERA_H

#include <utils.h>
#include <string>

class Camera {
private:
    Point3D origin;
    Point3D target;
    double viewportWidth;
    double viewportHeight;
    double viewPortDistance;

public:
    std::string cameraName;
};

#endif //GRAPHIC_ENGINE_CAMERA_H
