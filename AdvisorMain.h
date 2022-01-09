#pragma once
#ifndef ADVISORBOT_ADVISORMAIN_H
#define ADVISORBOT_ADVISORMAIN_H

#define BOTPROMPT "advisorbot> "
#define USERPROMPT "user>"

#include "OrderBook.h"
#include <string>
#include <map>

class AdvisorMain {
public:
    AdvisorMain();

    /** Call this to start the program */
    void init();

private:
    void printMenu();

    static void terminateGracefully();

    std::string readUserCommand();

    void handleUserCommand(std::string &userCommand);

    /** C1: help - List all available commands */
    void printHelp();

    /** C2: help cmd - Output help for the specified command */
    void helpCmd(const std::string &cmd);

    /** C3: prod - List available products */
    void listProducts();

    /** C4: min - Find minimum bid or ask for product in current time step */
    double getProductMinOfType(std::string product, std::string type);  // TODO: use Enum for type

    /** C5: max - Find maximum bid or ask for product in current time step */
    double getProductMaxOfType(std::string product, std::string type);  // TODO: use Enum for type

    /** C6: avg - compute average ask or bid for the sent product over the sent number of time steps  */
    // TODO: verify type of timesteps, use Enum for type
    double getProductAvgOfTypeOverTimesteps(std::string product, std::string type, int timesteps);

    /** C7: predict - predict max or min ask or bid for the sent product for the next time step */
    // TODO: use Enum for type and perhaps also max or min
    double predictProductNextMaxMinOfType(bool max_or_min, std::string product, std::string type);

    /** C8: time - state current time in dataset, i.e. which timeframe are we looking at */
    void printTime();

    /** C9: step - move to next time step */
    void moveToNextTimestep();

    std::map<std::string, std::pair<std::string, std::string>> helpMap = {
            {"help",       {"help",                                  "list all available commands"}},
            {"help <cmd>", {"help <cmd>",                            "output help for the specified command"}},
            {"prod",       {"prod",                                  "list available products"}},
            {"min",        {"min <product> <ask/bid>",               ""}},
            {"max",        {"max <product> <ask/bid>",               ""}},
            {"avg",        {"avg <product> <ask/bid> <timesteps>",   ""}},
            {"predict",    {"predict <min/max> <product> <ask/bid>", ""}},
            {"time",       {"time",                                  "state current time in dataset, i.e. which timeframe are we looking at"}},
            {"step",       {"step",                                  "move to the next time step"}}
    };

    OrderBook orderBook{"20200601.csv"};


};


#endif //ADVISORBOT_ADVISORMAIN_H
