#pragma once
#ifndef ADVISORBOT_ADVISORMAIN_H
#define ADVISORBOT_ADVISORMAIN_H

#define CSVDATAFILE "20200601.csv"
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
    /** Terminate the program gracefully upon user signal */
    static void terminateGracefully();

    /** Get user input for further processing */
    std::string readUserCommand();

    /** Trigger commands based on user input */
    void handleUserCommand(std::string &userCommand);

    /** C1: help - List all available commands */
    void printHelp();

    /** C2: help cmd - Output help for the specified command */
    void printHelpForCmd(const std::string &cmd);

    /** C3: prod - List available products */
    void printAvailableProducts();

    /** C4 + C5: min/max - Find minimum/maximum bid or ask for product in current time step */
    void printProductMinMaxOfType(const std::vector<std::string> &cmd);

    /** C6: avg - compute average ask or bid for the sent product over the sent number of time steps  */
    void printProductAvgOfTypeOverTimesteps(const std::vector<std::string> &cmd);

    /** C7: predict - predict max or min ask or bid for the sent product for the next time step */
    // TODO: use Enum for type and perhaps also max or min
    double predictProductNextMaxMinOfType(bool max_or_min, std::string product, std::string type);

    /** C8: time - state current time in dataset, i.e. which timeframe are we looking at */
    void printTime();

    /** C9: step - move to next time step */
    void moveToNextTimestep();

    /** current timestamp along with its index in the OrderBook object assigned to this instance (orderBook) */
    std::pair<std::string, int> currentTime;

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

    OrderBook orderBook{CSVDATAFILE};
};


#endif //ADVISORBOT_ADVISORMAIN_H
