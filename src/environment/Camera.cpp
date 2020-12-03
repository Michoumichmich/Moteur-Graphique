#include "Camera.h"

#include <utility>

Camera::Camera(std::string str, Point3D origin, Point3D target)
        :cameraName(std::move(str)), origin(origin), target(target)
{
    UpdateBasicVectors();
}

Camera::Camera(std::string name, Point3D origin, Point3D target, enum camMode mode)
        :cameraName(std::move(name)), origin(origin), target(target), mode(mode)
{
    UpdateBasicVectors();
}

Camera::Camera(std::string name, Point3D origin, Point3D target, enum camMode mode, double width, double height, Vector up)
        :
        cameraName(std::move(name)), origin(origin), target(target), mode(mode), viewportWidth(width), viewportHeight(height), viewUp(up)
{
    UpdateBasicVectors();
}

Vector Camera::getCamViewCenter() const
{
    return view;
}

void Camera::UpdateBasicVectors()
{
    pixel_width = viewportWidth/pixel_width_count;
    pixel_height = viewportHeight/pixel_height_count;
    view = Vector(origin, target);
    up_unit = -(viewUp-view.normalize()*(view.normalize().dot(viewUp))).normalize();
    right_unit = -up_unit.cross(view).normalize();
    bottom_left = target-up_unit*(viewportHeight/2.0)-right_unit*(viewportWidth/2.0);
}

Point3D Camera::translatePixelCoordinates(int x, int y)
{
    return (bottom_left)+(up_unit*(y*pixel_height))+(right_unit*(x*pixel_width));
}

Camera::Camera(std::string str)
        :cameraName(std::move(str))
{
    UpdateBasicVectors();
}

void Camera::setViewDimensions(double width, double height)
{
    this->viewportHeight = height;
    this->viewportWidth = width;
    UpdateBasicVectors();
}

void Camera::setDirection(Point3D origin, Point3D target)
{
    this->origin = origin;
    this->target = target;
    UpdateBasicVectors();
}

void Camera::setMode(enum camMode mode)
{
    this->mode = mode;
}

void Camera::setName(std::string name)
{
    this->cameraName = std::move(name);
}

void Camera::setResolution(int width, int height)
{
    this->pixel_width_count = width;
    this->pixel_height_count = height;
}

Point3D Camera::getTarget() const
{
    return this->target;
}

Point3D Camera::getOrigin() const
{
    return this->origin;
}

std::string Camera::getName()
{
    return this->cameraName;
}

enum camMode Camera::getMode()
{
    return this->mode;
}

int Camera::pxWidthCount() const
{
    return pixel_width_count;
}

void Camera::setPixelWidthCount(int pixelWidthCount)
{
    pixel_width_count = pixelWidthCount;
}

int Camera::pxHeightCount() const
{
    return pixel_height_count;
}

void Camera::setPixelHeightCount(int pixelHeightCount)
{
    pixel_height_count = pixelHeightCount;
}

std::ostream& operator<<(std::ostream& out, const Camera& cam)
{
    out << "Camera(" << cam.cameraName << ", " << cam.origin << ", " << cam.target << ")";
    return out;
}