#include "UglySphere.h"

/**
 * @return Random double between -1 and 1.
 */
static inline double get_rand_float() {
    return 2 * (static_cast<double>(rand()) / RAND_MAX) - 1;
}


UglySphere::UglySphere(double radius, int n_summit, int n_tessels)
        : radius(radius), n_summit(n_summit), n_tessels(n_tessels) {}

void UglySphere::Tesselate(int resolution) {
    std::vector<Point3D> summits(n_summit);
    /* First let's construct random points on a sphere */
    for (int i(0); i < n_summit; i++) {
        Point3D pt(get_rand_float(), get_rand_float(), get_rand_float());
        summits[i] = pt.normalize() * radius;
    }

    /* Then we create random tessels with those points */
    for (int i(0); i < n_tessels; i++) {
        tessels->emplace_back(summits[rand() % n_summit], summits[rand() % n_summit], summits[rand() % n_summit]);
    }
}


std::ostream &UglySphere::print(std::ostream &str) {
    return str << "UglySphere(" << transformations.pt << ", " << radius << ")";
}

void UglySphere::serialize(std::stringstream &stream) {}

void UglySphere::deserialize(std::istream &stream) {}