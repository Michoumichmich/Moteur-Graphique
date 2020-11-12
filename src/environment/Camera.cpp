#include "Camera.h"

#include <utility>

Camera::Camera(Point3D origin, Point3D target) : origin(origin), target(target)
{
  InitBasicVectors();
}

Camera::Camera(Point3D origin, Point3D target, std::string name, enum camMode mode) : cameraName(std::move(name)), mode(mode), origin(origin), target(target)
{
  InitBasicVectors();
}

Camera::Camera(Point3D origin, Point3D target, std::string name, enum camMode mode, double width, double height, Vector up) : cameraName(std::move(name)),
                                                                                                                              mode(mode), origin(origin),
                                                                                                                              target(target),
                                                                                                                              viewportWidth(width),
                                                                                                                              viewportHeight(height),
                                                                                                                              viewUp(up)
{
  InitBasicVectors();
}
Vector Camera::getCamViewCenter() const
{
  return view;
}
void Camera::InitBasicVectors()
{
  pixel_width = viewportWidth / pixel_width_count;
  pixel_height = viewportHeight / pixel_height_count;
    view = Vector(origin, target);
    up_unit = -(viewUp - view.normalize() * (view.normalize().dot(viewUp))).normalize();
    right_unit = -up_unit.cross(view).normalize();
  bottom_left = target - up_unit * (viewportHeight / 2.0) - right_unit * (viewportWidth / 2.0);
}
Point3D Camera::getPixelTargetInEnv(int x, int y)
{
  return (bottom_left) + (up_unit * (y * pixel_height)) + (right_unit * (x * pixel_width));
}

Camera::Camera()
{
  InitBasicVectors();
}
