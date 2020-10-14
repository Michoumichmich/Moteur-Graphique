#include "GraphicsEngine.h"

#include <utility>

void GraphicsEngine::launchRender(const std::string &outName) {
    this->picManager->outFile = outName;
    this->renderer->renderScene();
}

void GraphicsEngine::createEnvironment(std::string name) {
    auto *env = new Environment(std::move(name));
    this->currentEnv = env;
    this->environments.push_back(env);
}

void GraphicsEngine::switchEnvironment(std::string name) {
    //TODO
}

void GraphicsEngine::setRenderer(Abstract_Renderer *renderer) {
    this->renderer = renderer;
}

Environment *GraphicsEngine::getCurrentEnvironment() {
    return currentEnv;
}

OutputPictureManager *GraphicsEngine::getPicManager() {
    return this->picManager;
}

GraphicsEngine::GraphicsEngine() = default;
