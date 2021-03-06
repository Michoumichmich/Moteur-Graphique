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
    std::string cameraName;
    Point3D origin = Point3D(0, 2.01, -2.01);
    Point3D target = Point3D(0, 0, 0);
    enum camMode mode = PERSPECTIVE;
    double viewportWidth = 4;
    double viewportHeight = 2;
    /**
     * Camera's view up vector.
     * TO obtain the real vector we project it on the view vector and substract that amount to the viewUP. Then we compute the right vector using a scalar
     * product and we norm everything
     */
    Vector viewUp = Vector(0, 1, 0);
    int pixel_height_count = DEFAULT_HEIGHT;
    int pixel_width_count = DEFAULT_WIDTH;
    double pixel_width{};
    double pixel_height{};
    Vector up_unit{};
    Vector right_unit{};
    Vector view{};
    Point3D bottom_left{};

    void UpdateBasicVectors();

public:
    int down_sampling = 1;

    /* Scales down the final image by that factor */
    void setDownSamplingFactor(int down);

    explicit Camera(std::string name);

    Camera(std::string name, Point3D origin, Point3D target);

    Camera(std::string name, Point3D origin, Point3D target, enum camMode);

    Camera(std::string name, Point3D origin, Point3D target, enum camMode mode, double width, double height, Vector up);

    [[nodiscard]] Vector getCamViewCenter() const;

    Point3D translatePixelCoordinates(int x, int y);

    void setViewDimensions(double width, double height);

    void setDirection(Point3D ori, Point3D trgt);

    void setMode(enum camMode);

    void setResolution(int width, int height);

    void setName(std::string name);

    [[nodiscard]] Point3D getTarget() const;

    [[nodiscard]] Point3D getOrigin() const;

    std::string getName();

    enum camMode getMode();

    [[nodiscard]] int pxWidthCount() const;

    [[nodiscard]] int pxHeightCount() const;

    void setPixelWidthCount(int pixelWidthCount);

    void setPixelHeightCount(int pixelHeightCount);

    friend std::ostream &operator<<(std::ostream &, const Camera &);
};

#endif //GRAPHIC_ENGINE_CAMERA_H
