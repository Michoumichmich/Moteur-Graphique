/**
 * @file CommandLineInferface.h
 */
#ifndef GRAPHIC_ENGINE_COMMANDLINEINTERFACE_H
#define GRAPHIC_ENGINE_COMMANDLINEINTERFACE_H

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <iterator>

#include "../engine/GraphicsEngine.h"

/**
 * Various exec status that could appear during execution
 */
enum command_exec_status {
    STOP_EXEC = 0,
    SUCCESS = 1,
    FAIL = 2,
    UNRECOVERABLE_ERROR = 3,
    UNKNOWN_COMMAND = 4,
    NO_COMMAND = 5,
    MISSING_ARGS = 6
};

/**
 * @class CommandLineInterface
 * A sorte of shell used to interact with the game engine;
 */
class CommandLineInterface {
 private:
  GraphicsEngine *graphicEngine;

  static std::vector<std::string> ParseToArray(const std::string &input, enum command_exec_status &status);

  void ExecuteArray(const std::vector<std::string> &tokens, enum command_exec_status &status);

  static void ErrorHandler(enum command_exec_status &);

 public:
  CommandLineInterface();

  void main_loop();
};

#endif //GRAPHIC_ENGINE_COMMANDLINEINTERFACE_H
