#include "GraphicsEngine.h"

#include <utility>
#include <iostream>
#include <algorithm>
#include <sstream>

void GraphicsEngine::launchRender(const std::string& outName)
{
    this->currentEnv->tesselate();
    this->renderer->renderScene(outName, this->currentEnv);
}

void GraphicsEngine::createEnvironment(std::string name)
{
    auto* env = new Environment(std::move(name));
    this->currentEnv = env;
    this->environments.push_back(env);
}

bool GraphicsEngine::switchEnvironment(const std::string& name)
{
    for (auto& environment : environments) {
        if (environment->envName==name) {
            currentEnv = environment;
            return true;
        }
    }
    return false;
}

void GraphicsEngine::setRenderer(Abstract_Renderer* renderer)
{
    this->renderer = renderer;
}

Environment* GraphicsEngine::currEnv()
{
    return currentEnv;
}

std::list<Environment*> GraphicsEngine::getEnvironments()
{
    return environments;
}

std::vector<std::string> GraphicsEngine::environmentsName()
{
    std::vector<std::string> names{};
    for (auto it = environments.begin(); it!=environments.end(); ++it) {
        names.push_back(it.operator*()->envName);
    }
    return names;
}

GraphicsEngine::~GraphicsEngine()
{
    delete renderer;
    while (!environments.empty()) delete environments.front(), environments.pop_front();
}

void GraphicsEngine::addObjInEnv(const std::shared_ptr<Object>& obj)
{
    this->currentEnv->addObject(obj);
}

void GraphicsEngine::deserialize(std::istream& stream)
{

}

void GraphicsEngine::serialize(std::stringstream& stream)
{
    //  Serialize_Atrubutes_List(stream, "GraphicsEngine", environments)
    Serialize_Serializable_List(stream, "Environments", environments)
}

GraphicsEngine::GraphicsEngine() = default;
