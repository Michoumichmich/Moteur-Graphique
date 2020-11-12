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
  int pixel_width_count = DEFAULT_WIDTH;
  int pixel_height_count = DEFAULT_HEIGHT;
  double pixel_width{};
  double pixel_height{};
  Vector up_unit{};
  Vector right_unit{};
  Vector view{};
  Point3D bottom_left{};

  void InitBasicVectors();

 public:
  std::string cameraName = "Camera unnamed";
    /**
     * Wether the rays are parallel or not
     */
    enum camMode mode = ORTHOGRAPHIC;
    Point3D origin = Point3D(0, 2.01, -2.01);
  Point3D target = Point3D(0, 0, 0);
  double viewportWidth = 4;
  double viewportHeight = 2;
  /**
   * Camera's view up vector.
   * TO obtain the real vector we project it on the view vector and substract that amount to the viewUP. Then we compute the right vector using a scalar
   * product and we norm everything
   */
  Vector viewUp = Vector(0, 1, 0);

  Camera();

  Camera(Point3D origin, Point3D target);

  Camera(Point3D origin, Point3D target, std::string name, enum camMode);

  Camera(Point3D origin, Point3D target, std::string name, enum camMode mode, double width, double height, Vector up);

  [[nodiscard]] Vector getCamViewCenter() const;

  Point3D getPixelTargetInEnv(int x, int y);

  void ModifyViewport(double width, double height);

  void PositionCamera(Point3D origin, Point3D target);
};

#endif //GRAPHIC_ENGINE_CAMERA_H
