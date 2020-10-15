#ifndef GRAPHIC_ENGINE_POINT3D_H
#define GRAPHIC_ENGINE_POINT3D_H

class Point3D {
public:
    double x{};
    double y{};
    double z{};
public :

    Point3D();

    Point3D(double, double, double);

    static double distance(Point3D &a, Point3D &b);

};

#endif //GRAPHIC_ENGINE_POINT3D_H
