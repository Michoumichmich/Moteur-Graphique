#include "GraphicsEngine.h"

#include <utils.h>
#include <iostream>
#include <algorithm>
#include <sstream>

void GraphicsEngine::launchRender(const std::string &outName, int frame_num) {
    Chrono local("Rendering " + outName);
    this->currentEnv->tesselate();
    this->currEnv()->set_time_frame(frame_num);
    this->renderer->renderScene(outName, this->currentEnv);
}

void GraphicsEngine::launchRender(const std::string &outName, int frame_start, int frame_end) {
    for (int frame = frame_start; frame < frame_end; frame++) {
        char suffix[14];
        std::snprintf(suffix, 14, "_%04d", frame);
        std::string curr_name = outName;
        curr_name.append(suffix);
        this->currEnv()->set_time_frame(frame);
        launchRender(curr_name);
    }
}


void GraphicsEngine::createEnvironment(std::string name) {
    auto *env = new Environment(std::move(name));
    this->currentEnv = env;
    this->environments.push_back(env);
}

bool GraphicsEngine::switchEnvironment(const std::string &name) {
    for (auto &environment : environments) {
        if (environment->envName == name) {
            currentEnv = environment;
            return true;
        }
    }
    return false;
}

Abstract_Renderer *GraphicsEngine::getRenderer() {
    return this->renderer;
}

void GraphicsEngine::setRenderer(Abstract_Renderer *abstract_renderer) {
    this->renderer = abstract_renderer;
}

Environment *GraphicsEngine::currEnv() {
    return currentEnv;
}

std::list<Environment *> GraphicsEngine::getEnvironments() {
    return environments;
}

std::vector<std::string> GraphicsEngine::environmentsName() {
    std::vector<std::string> names{};
    for (auto it = environments.begin(); it != environments.end(); ++it) {
        names.push_back(it.operator*()->envName);
    }
    return names;
}

GraphicsEngine::~GraphicsEngine() {
    delete renderer;
    while (!environments.empty()) delete environments.front(), environments.pop_front();
}

void GraphicsEngine::addObjInEnv(const std::shared_ptr<Object> &obj) {
    this->currentEnv->addObject(obj);
}

void GraphicsEngine::deserialize(std::istream &stream) {

}

void GraphicsEngine::serialize(std::stringstream &stream) {
    //  Serialize_Atrubutes_List(stream, "GraphicsEngine", environments)
    Serialize_Serializable_List(stream, "Environments", environments)
}


GraphicsEngine::GraphicsEngine() = default;
