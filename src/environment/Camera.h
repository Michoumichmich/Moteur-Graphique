#ifndef GRAPHIC_ENGINE_CAMERA_H
#define GRAPHIC_ENGINE_CAMERA_H

#include <utils.h>
#include <string>

enum camMode {
    PERSPECTIVE,
    ORTHOGRAPHIC
};

class Camera {
private:
    Point3D origin = Point3D(-1, 2.01, -2.01);
    Point3D target = Point3D(0, 0, 0);
    std::string cameraName = "Camera unnamed";
    enum camMode mode = PERSPECTIVE;
    double viewportWidth = 4;
    double viewportHeight = 2;
    /**
     * Camera's view up vector.
     * TO obtain the real vector we project it on the view vector and substract that amount to the viewUP. Then we compute the right vector using a scalar
     * product and we norm everything
     */
    Vector viewUp = Vector(0, 1, 0);


    int pixel_width_count = DEFAULT_WIDTH;
public:
    int pxWidthCount() const;

    void setPixelWidthCount(int pixelWidthCount);

    int pxHeightCount() const;

    void setPixelHeightCount(int pixelHeightCount);

private:
    int pixel_height_count = DEFAULT_HEIGHT;
    double pixel_width{};
    double pixel_height{};
    Vector up_unit{};
    Vector right_unit{};
    Vector view{};
    Point3D bottom_left{};

    void UpdateBasicVectors();

public:


    Camera();

    Camera(Point3D origin, Point3D target);

    Camera(Point3D origin, Point3D target, std::string name, enum camMode);

    Camera(Point3D origin, Point3D target, std::string name, enum camMode mode, double width, double height, Vector up);

    [[nodiscard]] Vector getCamViewCenter() const;

    Point3D translatePixelCoordinates(int x, int y);

    void setViewDimensions(double width, double height);

    void setCameraPosition(Point3D origin, Point3D target);

    void setCameraMode(enum camMode);

    void setCamScreenResolution(int width, int height);

    void setCamName(std::string name);

    [[nodiscard]] Point3D getTarget() const;

    [[nodiscard]] Point3D getOrigin() const;

    std::string getName();

    enum camMode getMode();
};

#endif //GRAPHIC_ENGINE_CAMERA_H
