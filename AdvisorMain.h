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

    /** Prompt for user interaction and/or input */
    void userPrompt();

    /** Get user input for further processing */
    static std::string readUserCommand();

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
    void predictProductNextMaxMinOfType(const std::vector<std::string> &cmd);

    /** C8: time - state current time in dataset, i.e. which timeframe are we looking at */
    void printTime() const;

    /** C9: step - move to next time step */
    void moveToNextTimestep();

    /** (EXTRA COMMAND - MY IMPLEMENTATION) C10: list - list all ask/bid prices that happened in the current time step */
    void printAllCurrentOrdersOfType(const std::string &orderType);

    /** current timestamp along with its index in the OrderBook object assigned to this instance (orderBook) */
    std::pair<std::string, int> currentTime = {"", 0};

    /** container for printing the contents of the help and help <cmd> functions */
    std::map<std::string, std::pair<std::string, std::string>> helpMap = {
            {"help",       {"help",                                  "list all available commands"}},
            {"help <cmd>", {"help <cmd>",                            "output help for the specified command"}},
            {"prod",       {"prod",                                  "list available products"}},
            {"min",        {"min <product> <ask/bid>",               "find the minimum bid or ask for a product in the current time step"}},
            {"max",        {"max <product> <ask/bid>",               "find the maximum bid or ask for a product in the current time step"}},
            {"avg",        {"avg <product> <ask/bid> <timesteps>",   "compute the average ask or bid for a product over a number of time steps"}},
            {"predict",    {"predict <min/max> <product> <ask/bid>", "predict the maximum or minimum ask or bid of a product for the next time step"}},
            {"time",       {"time",                                  "state current time in dataset, i.e. which timeframe are we looking at"}},
            {"step",       {"step",                                  "move to the next time step"}},
            {"list",       {"list <ask/bid>",                        "list all ask/bid prices in the current time step"}}
    };

    OrderBook orderBook{CSVDATAFILE};
};


#endif //ADVISORBOT_ADVISORMAIN_H
