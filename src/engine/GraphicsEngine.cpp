#include "GraphicsEngine.h"

#include <utility>
#include <iostream>
#include <algorithm>

void GraphicsEngine::launchRender(const std::string &outName) {
    this->currentEnv->tesselate();
    this->renderer->SetEnvironment(this->currentEnv);
    this->renderer->renderScene(outName);
}

void GraphicsEngine::createEnvironment(std::string name) {
    auto *env = new Environment(std::move(name));
    auto *sph = new Sphere(1.0); //TODO tmp
    env->addObject(sph);                //TODO tmp
    this->currentEnv = env;
    this->environments.push_back(env);
}

void GraphicsEngine::switchEnvironment(const std::string &name) {
    bool found = false;
    for (std::list<Environment *>::const_iterator it = environments.begin(); it != environments.end(); ++it) {
        if ((*it)->envName == name) {
            currentEnv = *it;
        }
    }
    if (!found) {
        std::cout << "Environment not found. Please select valid environment \n";
    }
}

void GraphicsEngine::setRenderer(Abstract_Renderer *renderer) {
    this->renderer = renderer;
}

Environment *GraphicsEngine::getCurrentEnvironment() {
    return currentEnv;
}

std::list<Environment *> GraphicsEngine::getEnvironments() {
    return environments;
}

std::vector<std::string> GraphicsEngine::environmentsName() {
    std::vector<std::string> names{};
    for (std::list<Environment *>::const_iterator it = environments.begin(); it != environments.end(); ++it) {
        names.push_back(it.operator*()->envName);
    }
    return names;
}

GraphicsEngine::~GraphicsEngine() {
    environments.clear();
    // delete currentEnv;
}

GraphicsEngine::GraphicsEngine() = default;
