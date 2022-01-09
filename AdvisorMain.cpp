#include "AdvisorMain.h"
#include "CSVReader.h"
#include <iostream>
#include <vector>

AdvisorMain::AdvisorMain() {

}

std::string AdvisorMain::readUserCommand() {
    std::string line;

    std::cout << USERPROMPT;
    std::getline(std::cin, line);

    return line;
}

void AdvisorMain::handleUserCommand(std::string &userCommand) {
    std::vector<std::string> cmd = CSVReader::tokenise(userCommand, ' ');
    if (cmd.empty()) {
        std::cout << BOTPROMPT << "Empty input! Please enter a command: " << std::endl;
        printHelp();
        return;
    }
    if (cmd[0] == "help") {
        if (cmd.size() == 1)
            printHelp();
        else if (helpMap.count(cmd[1]))
            helpCmd(cmd[1]);
        else
            std::cout << BOTPROMPT << "Invalid argument to 'help': " << cmd[1] << " (unknown command)" << std::endl;
    } else if (cmd[0] == "prod") {
        listProducts();
    } else if (cmd[0] == "exit") {
        terminateGracefully();
    } else {
        std::cout << BOTPROMPT << "Bad choice man" << std::endl;
    }
}

void AdvisorMain::init() {
    std::string userCommand;
    do {
        std::cout << BOTPROMPT << "Please enter a command, or help for a list of commands (to exit simply type 'exit')"
                  << std::endl;
        userCommand = readUserCommand();
        handleUserCommand(userCommand);
    } while (userCommand != "exit");
}

void AdvisorMain::printMenu() {

}

void AdvisorMain::printHelp() {
    std::cout << BOTPROMPT << "The available commands are:" << std::endl;
    std::cout << "---------------------------" << std::endl;
    for (const auto &e: helpMap) {
        std::cout << e.first << std::endl;
    }
    std::cout << "---------------------------" << std::endl;
}

void AdvisorMain::helpCmd(const std::string &cmd) {
    std::pair<std::string, std::string> cmdHelp = helpMap[cmd];
    std::cout << cmdHelp.first << " -> " << cmdHelp.second << std::endl;
}

void AdvisorMain::listProducts() {
    bool first = true;
    for (const std::string &p: orderBook.getKnownProducts()) {
        if (!first)
            std::cout << ',';
        else
            first = false;
        std::cout << p;
    }
    std::cout << std::endl;
}

double AdvisorMain::getProductMinOfType(std::string product, std::string type) {
    return 0;
}

double AdvisorMain::getProductMaxOfType(std::string product, std::string type) {
    return 0;
}

double AdvisorMain::getProductAvgOfTypeOverTimesteps(std::string product, std::string type, int timesteps) {
    return 0;
}

double AdvisorMain::predictProductNextMaxMinOfType(bool max_or_min, std::string product, std::string type) {
    return 0;
}

void AdvisorMain::printTime() {

}

void AdvisorMain::moveToNextTimestep() {

}

void AdvisorMain::terminateGracefully() {
    exit(0);
}
