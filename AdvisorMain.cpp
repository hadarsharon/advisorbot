#include "AdvisorMain.h"
#include "CSVReader.h"
#include "Engine.h"
#include <iostream>
#include <vector>
#include <algorithm>

AdvisorMain::AdvisorMain() = default;

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
    } else if (cmd[0] == "avg") {
        printProductAvgOfTypeOverTimesteps(cmd);
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
    currentTime = {orderBook.getEarliestTime(), 0}; // program is always initialized at the earliest time step
    std::string userCommand;
    do { // keep asking for user input until user chooses to exit
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
    for (const auto &e: helpMap) {  // print all available commands line by line
        std::cout << e.first << std::endl;
    }
    std::cout << "---------------------------" << std::endl;
}

void AdvisorMain::printHelpForCmd(const std::string &cmd) {
    std::pair<std::string, std::string> cmdHelp = helpMap[cmd];
    std::cout << cmdHelp.first << " -> " << cmdHelp.second << std::endl;
}

void AdvisorMain::printAvailableProducts() {
    bool first = true; // flag to aid in comma printing logic (no comma before first product etc.)
    for (const std::string &p: orderBook.getProducts()) {
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

    // verify product passed by user actually exists
    auto products = orderBook.getProducts();
    if (!orderBook.checkProductExists(product)) {
        std::cout << "Unknown product: " << product << std::endl;
        throw std::invalid_argument("Unknown product");
    }

    // verify order type passed by user is a valid one
    OrderBookType orderBookType;
    if (orderBook.isValidOrderType(orderType)) {
        orderBookType = orderBook.orderBookTypes[orderType];
    } else {
        std::cout << "Invalid argument for <bid/ask>: " << orderType << std::endl;
        throw std::invalid_argument("Invalid argument for <bid/ask>");
    }

    std::vector<OrderBookEntry> orders = orderBook.getOrders(orderBookType, product, currentTime.first);

    double price;
    if (min_or_max == "min")
        price = Engine::getLowPrice(orders);
    else if (min_or_max == "max")
        price = Engine::getHighPrice(orders);
    else
        throw std::invalid_argument("Invalid argument for <min/max>");

    std::cout << BOTPROMPT << "The " << min_or_max << " " << orderType << " for " << product << " is " << price
              << std::endl;
}

void AdvisorMain::printProductAvgOfTypeOverTimesteps(const std::vector<std::string> &cmd) {
    if (cmd.size() < 4) // must be something like 'avg <product> <ask/bid> <timesteps>'
        throw std::invalid_argument("Invalid arguments to 'avg'");

    std::string product = cmd[1];
    std::string orderType = cmd[2];
    int timeSteps;
    try {
        timeSteps = std::stoi(cmd[3]);
    } catch (const std::exception &e) {
        std::cout << "Bad value for 'timesteps' when calling 'avg': " << cmd[3] << std::endl;
        throw;
    }

    if (!orderBook.checkProductExists(product)) {
        std::cout << "Unknown product: " << product << std::endl;
        throw std::invalid_argument("Unknown product");
    }
    OrderBookType orderBookType;
    if (orderBook.isValidOrderType(orderType)) {
        orderBookType = orderBook.orderBookTypes[orderType];
    } else {
        std::cout << "Invalid argument for <bid/ask>: " << orderType << std::endl;
        throw std::invalid_argument("Invalid argument for <bid/ask>");
    }

    std::vector<OrderBookEntry> orders = orderBook.getOrders(orderBookType, product);
    std::sort(orders.begin(), orders.end(), OrderBookEntry::compareByTimestampAsc);

    int timeStepsBack, timeStepsSkip;
    if (timeSteps > currentTime.second) {
        timeStepsBack = std::max(currentTime.second, 1);
        timeStepsSkip = 0;
        std::cout << BOTPROMPT << "number of timesteps (" << timeSteps << ") is too far back." << std::endl;
        std::cout << BOTPROMPT << "current step is " << timeStepsBack << ", therefore the maximum amount of "
                  << timeStepsBack << " timesteps will be used." << std::endl;
    } else {
        timeStepsBack = timeSteps;
        timeStepsSkip = std::max(currentTime.second - timeSteps, 0);
    }

    std::vector<OrderBookEntry> ordersBack;
    ordersBack = std::vector<OrderBookEntry>(orders.begin() + timeStepsSkip, orders.begin() + timeStepsBack);

    double calculatedAvg = Engine::calculateAveragePriceOfOrders(ordersBack);
    std::cout << BOTPROMPT << "The average " << product << " " << orderType << " price over the last " << timeStepsBack
              << " timesteps was " << calculatedAvg << std::endl;
}

double AdvisorMain::predictProductNextMaxMinOfType(bool max_or_min, std::string product, std::string type) {
    return 0;
}

void AdvisorMain::printTime() {
    std::cout << BOTPROMPT << currentTime.first << std::endl;
}

void AdvisorMain::moveToNextTimestep() {
    currentTime = orderBook.getNextTime(currentTime.first);
    std::cout << BOTPROMPT << "now at " << currentTime.first << std::endl;
}

void AdvisorMain::terminateGracefully() {
    std::cout << "Exiting..." << std::endl;
    exit(0);
}

void AdvisorMain::printAllCurrentOrdersOfType(std::string orderType) {
    if (!orderBook.isValidOrderType(orderType)) {
        std::cout << "Invalid argument for <bid/ask>: " << orderType << std::endl;
        throw std::invalid_argument("Invalid argument for <bid/ask>");
    }
    std::vector<OrderBookEntry> orders;
    orders = orderBook.getOrders(OrderBookEntry::stringToOrderBookType(orderType), "", currentTime.first);
    if (orders.empty()) {
        std::cout << BOTPROMPT << "No orders of type " << orderType << " found for current time step: "
                  << currentTime.first << std::endl;
    } else {
        for (const OrderBookEntry &e: orders) {

        }
    }
}