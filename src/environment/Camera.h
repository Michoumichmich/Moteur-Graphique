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
    Point3D origin;
    Point3D target;
    double viewportWidth;
    double viewportHeight;
    enum camMode mode;

public:
    std::string cameraName;
    Camera CreateCamera();
    Camera CreateCamera(Point3D origin, Point3D target);
    void ModifyViewport(double width,double height);
    void PositionCamera(Point3D origin,Point3D target);
};

#endif //GRAPHIC_ENGINE_CAMERA_H
