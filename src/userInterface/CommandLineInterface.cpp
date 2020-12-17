#include "CommandLineInterface.h"
#include <string>
#include <fstream>

void CommandLineInterface::main_loop()
{
    enum command_exec_status status = SUCCESS;
    std::string input;
    std::cout << "Welcome in the rendering engine CLI \n For a list of available commands type \'help\'  \n";
    while (status!=STOP_EXEC) {
        getline(std::cin, input);
        auto tokens = ParseToArray(input, status);
        if (status!=NO_COMMAND) {
            ExecuteArray(tokens, status);
        }
        ErrorHandler(status);
        std::cout.flush();
    }
}

constexpr unsigned int str2int(const char* str, int h = 0)
{
    return !str[h] ? 5381 : (str2int(str, h+1)*33) ^ str[h];
}

std::vector<std::string> CommandLineInterface::ParseToArray(const std::string& input, enum command_exec_status& status)
{
    if (input.empty()) {
        status = NO_COMMAND;
        return std::vector<std::string>();
    }
    else {
        status = SUCCESS;
        std::istringstream iss(input);
        std::vector<std::string> results((std::istream_iterator<std::string>(iss)), std::istream_iterator<std::string>());
        return results;
    }
}

void CommandLineInterface::ExecuteArray(const std::vector<std::string>& tokens, enum command_exec_status& status)
{
    // TODO Replace if/else cascade by a switch

    switch (str2int(tokens[0].c_str())) {
        case str2int("quit"):
        case str2int("exit"):
        case str2int("stop"):
            status = STOP_EXEC;
            break;

        case str2int("help"): {
            std::ifstream manCLI;
            manCLI.open("../src/manCLI");
            std::string line;
            if (manCLI.is_open()) {
                while (getline(manCLI, line)) {
                    std::cout << line << "\n";
                }
                status = SUCCESS;
            }
            else {
                std::cout << "Unable to find man";
                status = FAIL;
            }
            manCLI.close();
            break;
        }

        case str2int("init"):
            if (tokens.size() == 1) {;
                this->graphicEngine = new GraphicsEngine();
                this->graphicEngine->setRenderer(new RT_RayTracer());
                this->graphicEngine->createEnvironment("default");
                std::cout << "Initialization successful \n";
            }
            else if (tokens.size()>=2) {
                switch (str2int(tokens[1].c_str())) {
                case str2int("ge"):
                    this->graphicEngine = new GraphicsEngine();
                    this->graphicEngine->setRenderer(new RT_RayTracer());
                    std::cout << "Initialization of the graphic engine \n";
                    status = SUCCESS;
                    break;
                case str2int("env"):
                    if (this->graphicEngine==nullptr) {
                        std::cout << "No graphic engine set. Initialize with `init ge` \n";
                        status = FAIL;
                    }
                    else {
                        if (tokens.size()>=3) {
                            std::list<Environment*> env = this->graphicEngine->getEnvironments();
                            bool unique = true;
                            for (auto& it : env) {
                                if (it->envName==tokens[2]) {
                                    unique = false;
                                    break;
                                }
                            }
                            if (unique) {
                                this->graphicEngine->createEnvironment(tokens[2]);
                                std::cout << "Initialization of " << tokens[2] << " environment \n";
                                status = SUCCESS;
                            }
                            else {
                                std::cout << "Environment with such name already exists. \n";
                                status = FAIL;
                            }
                        }
                        else {
                            this->graphicEngine->createEnvironment("default");
                            std::cout << "Initialization of default environment \n";
                            status = SUCCESS;
                        }
                    }
                    break;
                default :status = UNKNOWN_COMMAND;
                    break;
                }
            }
            else {
                status = MISSING_ARGS;
            }
            break;

        case str2int("list"):
            if (tokens.size()>=2) {
                if (this->graphicEngine==nullptr) {
                    std::cout << "No graphic engine set. Initialize with init ge \n";
                    status = FAIL;
                }
                else if (tokens[1]=="env") {
                    std::vector<std::string> names = this->graphicEngine->environmentsName();
                    for (const auto& name : names) {
                        std::cout << name << std::endl;
                    }
                    status = SUCCESS;
                }
                else if (tokens[1]=="objects") {
                    std::list<std::shared_ptr<Object>> objects = this->graphicEngine->currEnv()->getObjects();
                    int i = 0;
                    for (const auto& object : objects) {
                        std::cout << i << ": " << *object << std::endl;
                        i++;
                    }
                    if (i == 0)
                        std::cout << "No object in current environment" << std::endl;
                    status = SUCCESS;
                }
                else if (tokens[1]=="cameras") {
                    std::list<std::shared_ptr<Camera>> cameras = this->graphicEngine->currEnv()->getCameras();
                    for (const auto& camera : cameras) {
                        std::cout << *camera << std::endl;
                    }
                    status = SUCCESS;
                }
                else if (tokens[1]=="lights") {
                    std::list<Light*> lights = this->graphicEngine->currEnv()->allLights;
                    for (auto light : lights) {
                        std::cout << *light << std::endl;
                    }
                    status = SUCCESS;
                }
                else {
                    status = UNKNOWN_COMMAND;
                }
            }
            else {
                status = MISSING_ARGS;
            }
            break;

        case str2int("set"):
            if (tokens.size()>=2) {
                if (this->graphicEngine==nullptr) {
                    std::cout << "No graphic engine set. Initialize with init ge \n";
                    status = FAIL;
                }
                else if (this->graphicEngine->getEnvironments().empty()) {
                    std::cout << "No environment set. Initialize with init env <environment name> \n";
                    status = FAIL;
                }
                else if (tokens.size()>=3) {
                    if (tokens[1]=="resolution") {
                        int res = std::stoi(tokens[2]);
                        this->graphicEngine->currEnv()->setResolution(res);
                        std::cout << "Tesselation resolution set to " << (res<20 ? 20 : res) << std::endl;
                        status = SUCCESS;
                    }
                    else if (tokens[1]=="env") {
                        if (this->graphicEngine->switchEnvironment(tokens[2])) { // returns false if environment is not found
                            std::cout << "Switched to environment " << tokens[2] << std::endl;
                            status = SUCCESS;
                        }
                        else {
                            std::cout << "Environment not found. Please select valid environment." << std::endl;
                            status = FAIL;
                        }
                    }
                    else if (tokens[1]=="camera") {
                        if (graphicEngine->currEnv()->switchCamera(tokens[2])) {
                            std::cout << "Successfully changed to " << tokens[2] << " camera\n";
                            status = SUCCESS;
                        }
                        else {
                            std::cout << "Camera not found \n";
                            status = FAIL;
                        }
                    }
                    else if (tokens[1] == "reflexion") {
                        if (tokens[2] == "on") {
                            this->graphicEngine->getRenderer()->enableReflexions();
                            std::cout << "Enabled reflexion" << std::endl;
                            status = SUCCESS;
                        } else if (tokens[2] == "off") {
                            this->graphicEngine->getRenderer()->disableReflexions();
                            std::cout << "Disabled reflexion" << std::endl;
                            status = SUCCESS;
                        } else {
                            status = MISSING_ARGS;
                        }
                    }
                    else if (tokens[1] == "render_mode") {
                        if (tokens[2] == "bitmap") {
                            ((RT_RayTracer*)graphicEngine->getRenderer())->setMode(RT_RayRenderMode::RT_BITMAP);
                            std::cout << "Render mode set to bitmap \n";
                            status = SUCCESS;
                        }
                        else if (tokens[2] == "depthmap") {
                            ((RT_RayTracer*)graphicEngine->getRenderer())->setMode(RT_RayRenderMode::RT_DEPTHMAP);
                            std::cout << "Render mode set to depth map\n";
                            status = SUCCESS;
                        }
                        else if (tokens[2] == "standard") {
                            ((RT_RayTracer*)graphicEngine->getRenderer())->setMode(RT_RayRenderMode::RT_STANDARD);
                            std::cout << "Render mode set to standard \n";
                            status = SUCCESS;
                        }
                        else
                            status = UNKNOWN_COMMAND;
                    }
                    else if (tokens[1] == "background") {
                        if (tokens[2] == "on") {
                            graphicEngine->currEnv()->setBackgroundAppearence(true);
                            std::cout << "Background is now on\n";
                        }
                        else if (tokens[2] == "off") {
                            graphicEngine->currEnv()->setBackgroundAppearence(false);
                            std::cout << "Background is now off\n";
                        }
                        else
                            status = UNKNOWN_COMMAND;
                    }
                    else if (tokens[1] == "haze") {
                        double intensity = stod(tokens[2]);
                        if (0 <= intensity && intensity <= 1) {
                            graphicEngine->currEnv()->setHazeIntensity(stod(tokens[2]));
                            std::cout << "Haze intensity set to " << tokens[2] << std::endl;
                            status = SUCCESS;
                        }
                        else
                            status = FAIL;
                    }
                    else if (tokens[1] == "object") {
                        if (tokens.size() >= 5) {
                            std::cout << stoi(tokens[2]);
                            if (0 <= stoi(tokens[2]) && stoi(tokens[2]) <= graphicEngine->currEnv()->getObjects().size()) {
                                if (tokens[3] == "reflexivity") {
                                    if (0 <= stod(tokens[4]) <= 1) {
                                        auto obj = graphicEngine->currEnv()->getObjects().begin();
                                        std::advance(obj, stod(tokens[2]));
                                        (*obj)->setReflexivity(stod(tokens[4]));
                                        status = SUCCESS;
                                    }
                                    else {
                                        std::cout << "Object reflexivity must be between 0 and 1\n";
                                        status = FAIL;
                                    }
                                }
                                else
                                    status = UNKNOWN_COMMAND;
                            }
                            else {
                                std::cout << "Object index out of range. Try list objects to see objects indices\n";
                                status = FAIL;
                            }
                        }
                        else
                            status = MISSING_ARGS;
                    }
                }
            }
            else {
                status = MISSING_ARGS;
            }
            break;

        case str2int("add"):
            if (tokens.size()>=6) {
                if (this->graphicEngine == nullptr) {
                    std::cout << "No graphic engine set. Initialize with init ge\n";
                    status = FAIL;
                }
                else if (this->graphicEngine->getEnvironments().empty()) {
                    std::cout << "No environment set. Initialize with init env <environment name>\n";
                    status = FAIL;
                }
                else {
                    double x = stod(tokens[2]);
                    double y = stod(tokens[3]);
                    double z = stod(tokens[4]);
                    switch (str2int(tokens[1].c_str())) {
                        case str2int("sphere"): {
                            auto sphere = std::make_shared<Sphere>(stod(tokens[5]));
                            sphere->setCenter(Point3D(x, y, z));
                            if (tokens.size() >= 9) {
                                Color color((int) stod(tokens[6]), (int) stod(tokens[7]), (int) stod(tokens[8]));
                                sphere->setColor(color);
                            }
                            this->graphicEngine->currEnv()->addObject(sphere);
                            std::cout << "Added sphere of center (" << x << ", " << y << ", " << z << ") and radius "
                                      << tokens[5] << " to current environment"
                                      << std::endl;
                            break;
                        }
                        case str2int("cube"): {
                            auto cube = std::make_shared<Cube>(stod(tokens[5]));
                            cube->setCenter(Point3D(x, y, z));
                            if (tokens.size() >= 9) {
                                Color color((int) stol(tokens[6]), (int) stol(tokens[7]), (int) stol(tokens[8]));
                                cube->setColor(color);
                            }
                            this->graphicEngine->currEnv()->addObject(cube);
                            std::cout << "Added cube of center (" << x << ", " << y << ", " << z << ") and size "
                                      << tokens[5] << " to current environment"
                                      << std::endl;
                            break;
                        }
                        case str2int("camera") : {
                            if (tokens.size() >= 9) {
                                bool found = false;
                                for (const std::string &camName : graphicEngine->currEnv()->listCameras()) {
                                    if (camName == tokens[5]) {
                                        std::cout << "Camera already exists \n";
                                        found = true;
                                        status = FAIL;
                                    }
                                }
                                if (!found) {
                                    auto camera = std::make_shared<Camera>(tokens[5]);
                                    camera->setDirection(Point3D(x, y, z),
                                                         Point3D(stod(tokens[6]), stod(tokens[7]), stod(tokens[8])));
                                    graphicEngine->currEnv()->addCamera(camera);
                                    std::cout << tokens[5] << " camera added \n";
                                    status = SUCCESS;
                                }
                            } else
                                status = MISSING_ARGS;
                            break;
                        }
                        case str2int("light") : {
                            Light *light = new Light(Vector(x, y, z), stod(tokens[5]));
                            this->graphicEngine->currEnv()->addLight(light);
                            std::cout << "Added light in position (" << x << ", " << y << ", " << z
                                      << ") and intensity "
                                      << tokens[5] << " to current environment" << std::endl;
                            break;
                        }
                        default:
                            std::cout << "The object " << tokens[1] << " doesn't exist" << std::endl;
                            status = FAIL;
                            break;
                    }
                }
            }
            else
                status = MISSING_ARGS;
            break;

        case str2int("reset"):
            if (tokens.size()>=2) {
                bool found = false;
                for (Environment* env : graphicEngine->getEnvironments()) {
                    if (env->envName==tokens[1]) {
                        std::string envName = env->envName;
                        env->reset();
                        env->envName = envName;
                        found = true;
                        std::cout << tokens[1] << " successfully reset\n";
                        status = SUCCESS;
                        break;
                    }
                }
                if (!found) {
                    status = FAIL;
                    std::cout << "No environment with given name \n";
                }
            }
            else {
                status = MISSING_ARGS;
            }
            break;

        case str2int("render"):
            if (tokens.size()>=2) {
                this->graphicEngine->launchRender(tokens[1]);
                std::cout << "Rendered file " << tokens[1] << std::endl;
            }
            else
                status = MISSING_ARGS;
            break;

        default :
            status = UNKNOWN_COMMAND;
            break;
    }
}

void CommandLineInterface::ErrorHandler(enum command_exec_status& status)
{
    if (status==UNRECOVERABLE_ERROR) {
        //TODO dump memory
        status = STOP_EXEC;
    }
    if (status==UNKNOWN_COMMAND) {
        std::cout << "Unknown command \n";
    }
    if (status==FAIL) {
        std::cout << "Command fail \n";
    }
    if (status==MISSING_ARGS) {
        std::cout << "Missing argument \n";
    }
}

CommandLineInterface::CommandLineInterface() = default;
