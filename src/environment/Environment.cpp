#include "Environment.h"

#include <utility>
#include "RegularObjects/Sphere.h"

Environment::Environment(std::string name) {
    this->envName = std::move(name);
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
