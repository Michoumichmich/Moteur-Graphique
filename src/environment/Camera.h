#ifndef GRAPHIC_ENGINE_CAMERA_H
#define GRAPHIC_ENGINE_CAMERA_H

#include <utils.h>
#include <string>
enum camMode{
    PERSPECTIVE,
    ORTHOGONAL
};
class Camera {
private:

public:
    double viewportWidth;
    double viewportHeight;
    enum camMode mode;
    Point3D origin;
    Point3D target;
    std::string cameraName;
    Camera CreateCamera(std::string Name);
    Camera CreateCamera(Point3D origin, Point3D target);
    void ModifyViewport(double width,double height);
    void PositionCamera(Point3D origin,Point3D target);
};

#endif //GRAPHIC_ENGINE_CAMERA_H
