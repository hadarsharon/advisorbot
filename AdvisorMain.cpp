#include "AdvisorMain.h"
#include "CSVReader.h"
#include <iostream>
#include <vector>
#include <algorithm>

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
    if (cmd.empty()) {  // TODO: move to a different block?
        std::cout << BOTPROMPT << "Empty input! Please enter a command: " << std::endl;
        printHelp();
        return;
    }
    if (cmd[0] == "help") {
        if (cmd.size() == 1)
            printHelp();
        else if (helpMap.count(cmd[1]))
            printHelpForCmd(cmd[1]);
        else
            std::cout << BOTPROMPT << "Invalid argument to 'help': " << cmd[1] << " (unknown command)" << std::endl;
    } else if (cmd[0] == "prod") {
        printAvailableProducts();
    } else if (cmd[0] == "min" || cmd[0] == "max") {
        printProductMinMaxOfType(cmd);
    } else if (cmd[0] == "time") {
        printTime();
    } else if (cmd[0] == "step") {
        moveToNextTimestep();
    } else if (cmd[0] == "exit") {
        terminateGracefully();
    } else {
        std::cout << BOTPROMPT << "Invalid command." << std::endl;
        printHelp();
        throw std::invalid_argument("Invalid command"); // TODO: catch
    }
}

void AdvisorMain::init() {
    currentTime = orderBook.getEarliestTime();
    products = orderBook.getKnownProducts();
    std::string userCommand;
    do {
        std::cout << std::endl;
        std::cout << BOTPROMPT << "Please enter a command, or help for a list of commands (to exit simply type 'exit')"
                  << std::endl;
        userCommand = readUserCommand();
        handleUserCommand(userCommand);
    } while (userCommand != "exit");
}

void AdvisorMain::printHelp() {
    std::cout << BOTPROMPT << "The available commands are:" << std::endl;
    std::cout << "---------------------------" << std::endl;
    for (const auto &e: helpMap) {
        std::cout << e.first << std::endl;
    }
    std::cout << "---------------------------" << std::endl;
}

void AdvisorMain::printHelpForCmd(const std::string &cmd) {
    std::pair<std::string, std::string> cmdHelp = helpMap[cmd];
    std::cout << cmdHelp.first << " -> " << cmdHelp.second << std::endl;
}

void AdvisorMain::printAvailableProducts() {
    bool first = true;
    for (const std::string &p: products) {
        if (!first) {
            std::cout << ',';
        } else {
            std::cout << BOTPROMPT;
            first = false;
        }
        std::cout << p;
    }
    std::cout << std::endl;
}

void AdvisorMain::printProductMinMaxOfType(const std::vector<std::string> &cmd) {
    if (cmd.size() < 3) // must be something like '<min/max> <product> <bid/ask>'
        throw std::invalid_argument("Invalid arguments to 'min'/'max'");

    std::string min_or_max = cmd[0];
    std::string product = cmd[1];
    std::string orderType = cmd[2];

    OrderBookType orderBookType;
    if (!std::any_of(products.begin(), products.end(), [&product](const std::string &p) { return p == product; })) {
        std::cout << "Unknown product: " << product << std::endl;
        throw std::invalid_argument("Unknown product");
    }

    if (orderBookTypes.count(orderType) > 0) {
        orderBookType = orderBookTypes[orderType];
    } else {
        std::cout << "Invalid argument for <bid/ask>: " << orderType << std::endl;
        throw std::invalid_argument("Invalid argument for <bid/ask>");
    }

    std::vector<OrderBookEntry> orders = orderBook.getOrders(orderBookType, product, currentTime);

    double price;
    if (min_or_max == "min")
        price = OrderBook::getLowPrice(orders);
    else if (min_or_max == "max")
        price = OrderBook::getHighPrice(orders);
    else
        throw std::invalid_argument("Invalid argument for <min/max>");

    std::cout << BOTPROMPT << "The " << min_or_max << " " << orderType << " for " << product << " is " << price
              << std::endl;
}

double AdvisorMain::getProductAvgOfTypeOverTimesteps(std::string product, std::string type, int timesteps) {
    return 0;
}

double AdvisorMain::predictProductNextMaxMinOfType(bool max_or_min, std::string product, std::string type) {
    return 0;
}

void AdvisorMain::printTime() {
    std::cout << BOTPROMPT << currentTime << std::endl;
}

void AdvisorMain::moveToNextTimestep() {
    currentTime = orderBook.getNextTime(currentTime);
    std::cout << BOTPROMPT << "now at " << currentTime << std::endl;
}

void AdvisorMain::terminateGracefully() {
    std::cout << "Exiting..." << std::endl;
    exit(0);
}
