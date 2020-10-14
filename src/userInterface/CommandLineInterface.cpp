#include "CommandLineInterface.h"

void CommandLineInterface::main_loop() {
    enum command_exec_status status = SUCCESS;
    std::string input;
    std::cout << "Welcome in the rendering engine CLI \n For a list of available commands type \'help \'  \n";
    while (status != STOP_EXEC) {
        getline(std::cin, input);
        auto tokens = ParseToArray(input, status);
        if (status != NO_COMMAND) {
            ExecuteArray(tokens, status);
        }
        ErrorHandler(status);
    }
}

std::vector<std::string> CommandLineInterface::ParseToArray(const std::string &input, enum command_exec_status &status) {
    if (input.empty()) {
        status = NO_COMMAND;
        return std::vector<std::string>();
    } else {
        status = SUCCESS;
        std::istringstream iss(input);
        std::vector<std::string> results((std::istream_iterator<std::string>(iss)), std::istream_iterator<std::string>());
        return results;
    }
}

void CommandLineInterface::ExecuteArray(const std::vector<std::string> &tokens, enum command_exec_status &status) {
    if (tokens[0] == "stop") {
        status = STOP_EXEC;
    } else if (tokens[0] == "help") {
        std::cout << "Supported commands : \n help \n stop \n init ge \n";
        status = SUCCESS;
    } else if (tokens[0] == "init") {
        if (tokens[1] == "ge") {
            this->graphicEngine = new GraphicsEngine();
            std::cout << "Initialization of the graphic engine \n";
            status = SUCCESS;
        } else {
            status = UNKNOWN_COMMAND;
        }
    } else {
        status = UNKNOWN_COMMAND;
    }
}

void CommandLineInterface::ErrorHandler(enum command_exec_status &status) {
    if (status == UNRECOVERABLE_ERROR) {
        //TODO dump memory
        status = STOP_EXEC;
    }
    if (status == UNKNOWN_COMMAND) {
        std::cout << "Unknown command \n";
    }
}

CommandLineInterface::CommandLineInterface() = default;
