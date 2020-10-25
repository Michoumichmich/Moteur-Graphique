#include "Environment.h"

#include <sstream>

Environment::Environment(std::string name) {
    currentCam = new Camera();
    cameras.push_back(currentCam);
    this->envName = std::move(name);
}

Camera *Environment::getCurrentCam() {
    return currentCam;
}

std::list<Tessel *> *Environment::getTessels() {
    return &this->allTessels;
}

void Environment::addObject(Object *obj) {
    this->allObjects.push_back(obj);
}

std::list<std::string> Environment::listCameras() {
    //TODO
    return std::list<std::string>();
}

void Environment::tesselate() {
    for (std::list<Object *>::const_iterator it = allObjects.begin(); it != allObjects.end(); ++it) {
        (*it)->Tesselate();
        auto tmp = (*it)->getTessels();
        copy(tmp.rbegin(), tmp.rend(), front_inserter(allTessels));
    }
}

Environment::~Environment() {
    allTessels.clear();
    allObjects.clear();
    cameras.clear();
    allTMapped.clear();
    delete currentCam;
}

Environment::Environment() {
    currentCam = new Camera();
    cameras.push_back(currentCam);
};
