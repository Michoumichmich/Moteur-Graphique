#include "Camera.h"

#include <utility>

Camera::Camera(Point3D origin, Point3D target) : origin(origin), target(target)
{
}

Camera::Camera(Point3D origin, Point3D target, std::string name, enum camMode mode) : cameraName(std::move(name)), mode(mode), origin(origin), target(target)
{
}

Camera::Camera(Point3D origin, Point3D target, std::string name, enum camMode mode, double width, double height, Vector up) : cameraName(std::move(name)),
                                                                                                                              mode(mode), origin(origin),
                                                                                                                              target(target),
                                                                                                                              viewportWidth(width),
                                                                                                                              viewportHeight(height),
                                                                                                                              viewUp(up)
{

}

Camera::Camera() = default;
