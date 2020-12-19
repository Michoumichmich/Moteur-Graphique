#include "UglySphere.h"

/**
 * @return Random double between -1 and 1.
 */
static inline double get_rand_float() {
    return 2 * (static_cast<double>(rand()) / RAND_MAX) - 1;
}


UglySphere::UglySphere(double radius, int n_summit, int n_tessels)
        : radius(radius), n_summit(n_summit), n_tessels(n_tessels) {

    all_nodes.reserve(n_summit);
    /* First let's construct random points on a sphere */
    for (int i(0); i < n_summit; i++) {
        Point3D pt(get_rand_float(), get_rand_float(), get_rand_float());
        all_nodes.emplace_back(pt.normalize() * radius, this);
    }
    /* Then we create random tessels with those points */
    all_mesh_tessels.reserve(n_tessels);
    for (int i(0); i < n_tessels; i++) {
        unsigned long int0 = rand() % n_summit;
        unsigned long int1 = rand() % n_summit;
        unsigned long int2 = rand() % n_summit;
        this->add_mesh_tessel({int0, int1, int2});
    }
}


std::ostream &UglySphere::print(std::ostream &str) {
    return str << "UglySphere(" << transformations.pt << ", " << radius << ")";
}

void UglySphere::serialize(std::stringstream &stream) {}

void UglySphere::deserialize(std::istream &stream) {}
