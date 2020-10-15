#ifndef GRAPHIC_ENGINE_CAMERA_H
#define GRAPHIC_ENGINE_CAMERA_H

#include <utils.h>
#include <string>
enum camMode{
    PERSPECTIVE,
    ORTHOGRAPHIC
};

class Camera {
private:

public:
    double viewportWidth;
    double viewportHeight;

    /**
     * Camera's view up vector.
     * TO obtain the real vector we project it on the view vector and substract that amount to the viewUP. Then we compute the right vector using a scalar
     * product and we norm everything
     */
    Vector viewUp;

    /**
     * Wether the rays are parallel or not
     */
    enum camMode mode;
    Point3D origin;
    Point3D target;
    std::string cameraName;

    explicit Camera(std::string Name);

    Camera(Point3D origin, Point3D target);

    void ModifyViewport(double width, double height);

    void PositionCamera(Point3D origin, Point3D target);
};

#endif //GRAPHIC_ENGINE_CAMERA_H
