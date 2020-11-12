#define free_ptr_list(list) while(!list.empty()) delete list.front(), list.pop_front()


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
    allTessels.clear();
    for (auto &allObject : allObjects) {
        auto tmp = allObject->getTessels(tesselResolution);
        copy(tmp.rbegin(), tmp.rend(), front_inserter(allTessels));
    }
}

Environment::~Environment() {

    free_ptr_list(allTessels);
    free_ptr_list(cameras);
    free_ptr_list(allTMapped);
    free_ptr_list(allObjects);
}

Environment::Environment() {
    currentCam = new Camera();
    cameras.push_back(currentCam);
}

void Environment::setResolution(int n) {
    tesselResolution = n >= 20 ? n : 20;
}

int Environment::getResolution() {
    return tesselResolution;
}

void Environment::serialize(std::ostream &stream) {

    std::list<std::string> serial;
    for (auto const &obj:allObjects)
        obj->serialize(stream);

    // jsonify_serializable_list(stream, allObjects);
}

void Environment::deserialize(std::istream &stream) {

}
