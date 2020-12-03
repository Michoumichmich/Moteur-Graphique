#define free_ptr_list(list) while(!list.empty()) delete list.front(), list.pop_front()


#include "Environment.h"
#include <sstream>

Environment::Environment(std::string name) {
    currentCam = std::make_shared<Camera>("Default");
    cameras.push_back(currentCam);
    this->envName = std::move(name);
}

std::shared_ptr<Camera> Environment::currCam() {
    return currentCam;
}

std::list<Tessel *> *Environment::getTessels() {
    return &this->allTessels;
}

std::list<std::shared_ptr<Object>> Environment::getObjects() {
    return this->allObjects;
}

std::list<std::shared_ptr<Camera>> Environment::getCameras() {
    return this->cameras;
}

void Environment::addObject(const std::shared_ptr<Object>& obj) {
    this->allObjects.push_back(obj);
}


std::list<std::string> Environment::listCameras() {
    std::list<std::string> out;
    for (auto const &it : cameras) {
        out.push_back(it->getName());
    }
    return out;
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
}

Environment::Environment() {
    currentCam = std::make_shared<Camera>("Default");
    cameras.push_back(currentCam);
}

void Environment::setResolution(int n) {
    tesselResolution = n >= 20 ? n : 20;
}

int Environment::getResolution() const {
    return tesselResolution;
}

void Environment::serialize(std::stringstream &stream) {
    Serialize_Serializable_List(stream, "Environment", allObjects);
}

void Environment::deserialize(std::istream &stream) {

}

void Environment::addCamera(const std::shared_ptr<Camera>& cam) {
    cameras.push_back(cam);
}

void Environment::addLight(Light *light) {
    allLights.push_back(light);
}

bool Environment::switchCamera(const std::string &camName) {
    for (auto const &it : cameras) {
        if (it->getName() == camName) {
            this->currentCam = it;
            return true;
        }
    }
    return false;
}

void Environment::reset() {
    cameras.clear();
    allTessels = std::list<Tessel *>{};
    allObjects.clear();
    allTMapped.clear();
    currentCam = std::make_shared<Camera>("Default");
    cameras.push_back(currentCam);
    int tesselResolution = 30;
    envName = std::string{};
    backgroundColor = Color(24, 179, 220);
    allLights = std::list<Light *>{};
}
