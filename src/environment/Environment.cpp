#include "Environment.h"

#include <utility>
#include "RegularObjects/Sphere.h"

Environment::Environment(std::string name) {
    this->envName = std::move(name);
    /*
    Vector tes0 = Vector(-1, -1, 1);
    Vector tes1 = Vector(1, -1, 1);
    Vector tes2 = Vector(0, 1, 1);
    Tessel tessel = Tessel();
    tessel.summmits[0] = tes0;
    tessel.summmits[1] = tes1;
    tessel.summmits[2] = tes2;
    this->allTessels.push_back(tessel);

    Vector tes3 = Vector(-1, -1, 2);
    Vector tes4 = Vector(1, -1, 2);
    Vector tes5 = Vector(0, 1, 2);
    Tessel tessel2 = Tessel();
    tessel2.summmits[0] = tes3;
    tessel2.summmits[1] = tes4;
    tessel2.summmits[2] = tes5;
    this->allTessels.push_back(tessel2);
    */

    /*
    Object *sph = new  Sphere();
    this->allOjects.push_back(sph);
    sph->Tesselate();
    */
}

Camera *Environment::getCurrentCam() {
    return currentCam;
}

std::list<Tessel> Environment::getTessels() {
    return this->allTessels;
}

Environment::Environment() = default;
