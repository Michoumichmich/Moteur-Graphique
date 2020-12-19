#ifndef GRAPHICSENGINE_UGLYSPHERE_H
#define GRAPHICSENGINE_UGLYSPHERE_H

#include "MeshObject.h"

/**
 * @class UglySphere
 *
 * Probably shouldn't be even called a sphere.
 */
class UglySphere : public MeshObject {
private:
    double radius;
    int n_summit, n_tessels;

public:
    explicit UglySphere(double radius, int n_summit, int n_tessels);

    void deserialize(std::istream &stream) override;

    void serialize(std::stringstream &stream) override;

    std::ostream &print(std::ostream &str) override;
};


#endif //GRAPHICSENGINE_UGLYSPHERE_H
