#include "CommandLineInterface.h"
#include<string>
void CommandLineInterface::main_loop()
{
  enum command_exec_status status = SUCCESS;
  std::string input;
  std::cout << "Welcome in the rendering engine CLI \n For a list of available commands type \'help \'  \n";
  while (status != STOP_EXEC)
    {
      getline(std::cin, input);
      auto tokens = ParseToArray(input, status);
      if (status != NO_COMMAND)
        {
          ExecuteArray(tokens, status);
        }
      ErrorHandler(status);
      std::cout << std::endl;
    }
}

constexpr unsigned int str2int(const char *str, int h = 0)
{
  return !str[h] ? 5381 : (str2int(str, h + 1) * 33) ^ str[h];
}

std::vector<std::string> CommandLineInterface::ParseToArray(const std::string &input, enum command_exec_status &status)
{
  if (input.empty())
    {
      status = NO_COMMAND;
      return std::vector<std::string>();
    }
  else
    {
      status = SUCCESS;
      std::istringstream iss(input);
      std::vector<std::string> results((std::istream_iterator<std::string>(iss)), std::istream_iterator<std::string>());
      return results;
    }
}

void CommandLineInterface::ExecuteArray(const std::vector<std::string> &tokens, enum command_exec_status &status)
{
  // TODO Replace if/else cascade by a switch

  switch (str2int(tokens[0].c_str()))
    {
      case str2int("stop"):
        status = STOP_EXEC;
      break;

      case str2int("help"):
        std::cout << "Supported commands : \n help \n stop \n init ge \n init env <environment name> \n list env \n set resolution <resolution> \n add <object> <x> <y> <z> <size> \n";
      status = SUCCESS;
      break;

      case str2int("init"):
        if (tokens.size() >= 2)
          {
            switch (str2int(tokens[1].c_str()))
              {
                case str2int("ge"):
                  this->graphicEngine = new GraphicsEngine();
                std::cout << "Initialization of the graphic engine \n";
                status = SUCCESS;
                break;
                case str2int("env"):
                  if (this->graphicEngine == NULL)
                    {
                      std::cout << "No graphic engine set. Initialize with `init ge` \n";
                      status = FAIL;
                    }
                  else
                    {
                      if (tokens.size() >= 3)
                        {
                          std::list<Environment *> env = this->graphicEngine->getEnvironments();
                          bool unique = true;
                          for (std::list<Environment *>::iterator it = env.begin(); it != env.end(); ++it)
                            {
                              if ((*it)->envName == tokens[2])
                                {
                                  unique = false;
                                  break;
                                }
                            }
                          if (unique)
                            {
                              this->graphicEngine->createEnvironment(tokens[2]);
                              std::cout << "Initialization of " << tokens[2] << " environment \n";
                              status = SUCCESS;
                            }
                          else
                            {
                              std::cout << "Environment with such name already exists. \n";
                              status = FAIL;
                            }
                        }
                      else
                        {
                          this->graphicEngine->createEnvironment("default");
                          std::cout << "Initialization of default environment \n";
                          status = SUCCESS;
                        }
                    }
                break;
                default :
                  status = UNKNOWN_COMMAND;
                break;
              }
          }
        else
          {
            status = MISSING_ARGS;
          }
      break;

      case str2int("list"):
        if (tokens.size() >= 2)
          {
            if (this->graphicEngine == NULL)
              {
                std::cout << "No graphic engine set. Initialize with init ge \n";
                status = FAIL;
              }
            else if (tokens[1] == "env")
              {
                std::vector<std::string> names = this->graphicEngine->environmentsName();
                for (std::vector<std::string>::const_iterator it = names.begin(); it != names.end(); ++it)
                  {
                    std::cout << *it << std::endl;
                  }
                status = SUCCESS;
              }
            else {
                status = MISSING_ARGS;
            }
          } else {
            status = MISSING_ARGS;
        }
            break;

        case str2int("set"):
            if (tokens.size() >= 2) {
                if (this->graphicEngine == NULL) {
                    std::cout << "No graphic engine set. Initialize with init ge \n";
                    status = FAIL;
                } else if (this->graphicEngine->getEnvironments().empty()) {
                    std::cout << "No environment set. Initialize with init env <environment name> \n";
                    status = FAIL;
                } else if (tokens.size() >= 3) {
                    if (tokens[1] == "resolution") {
                        int res = std::stoi(tokens[2]);
                        this->graphicEngine->getCurrentEnvironment()->setResolution(res);
                        std::cout << "Tesselation resolution set to " << (res < 20 ? 20 : res) << std::endl;
                        status = SUCCESS;
                    }
                } else {
                    status = MISSING_ARGS;
                }
            }
            break;

        case str2int("add"):
            if (tokens.size() >= 6) {
                double x = stod(tokens[2]);
                double y = stod(tokens[3]);
                double z = stod(tokens[4]);
                switch (str2int(tokens[1].c_str())) {
                    case str2int("sphere"): {
                        Sphere* sphere = new Sphere(stod(tokens[5]));
                        sphere->setCenter(Point3D(x, y, z));
                        this->graphicEngine->getCurrentEnvironment()->addObject(sphere);
                        break;
                    }
                    case str2int("cube"): {
                        Cube *cube = new Cube(stod(tokens[5]));
                        cube->setCenter(Point3D(x, y, z));
                        this->graphicEngine->getCurrentEnvironment()->addObject(cube);
                        break;
                    }
                    default:
                        std::cout << "The object " << tokens[1] << " doesn't exist" << std::endl;
                        status = FAIL;
                        break;
                }
            } else
                status = MISSING_ARGS;
            break;

        // TODO Add object to environment
        // else if () {
        //  }
        // TODO Add command for setting renderer
        // TODO Add command for setting current environment
        default :
            status = UNKNOWN_COMMAND;
            break;
    }
}

void CommandLineInterface::ErrorHandler(enum command_exec_status &status)
{
  if (status == UNRECOVERABLE_ERROR)
    {
      //TODO dump memory
      status = STOP_EXEC;
    }
  if (status == UNKNOWN_COMMAND)
    {
      std::cout << "Unknown command \n";
    }
  if (status == FAIL)
    {
      std::cout << "Command fail \n";
    }
  if (status == MISSING_ARGS)
    {
      std::cout << "Missing argument \n";
    }
}

CommandLineInterface::CommandLineInterface() = default;
