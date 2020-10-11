#include "GraphicsEngine.h"

#include <utility>

void GraphicsEngine::launchRender(const std::string &outName) {
}

void GraphicsEngine::createEnvironment(std::string name) {
    auto *env = new Environment(std::move(name));
    this->currentEnv = env;
    this->environments.push_back(env);
}

void GraphicsEngine::switchEnvironment(std::string name) {
    //TODO
}

void GraphicsEngine::setRenderer(enum renderer_type type) {
    this->renderer = new Renderer(type);
}

GraphicsEngine::GraphicsEngine() = default;
