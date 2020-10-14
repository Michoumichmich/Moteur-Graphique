#ifndef GRAPHIC_ENGINE_POINT3D_H
#define GRAPHIC_ENGINE_POINT3D_H

class Point3D {
public:
    double x{};
    double y{};
    double z{};
public :
    double getX() const;

    double getY() const;

    double getZ() const;

    Point3D setX(double x);

    Point3D setY(double y);

    Point3D setZ(double z);

    Point3D();

    Point3D(double, double, double);

    static double distance(Point3D, Point3D);

};

#endif //GRAPHIC_ENGINE_POINT3D_H