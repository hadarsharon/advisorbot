#pragma once
#ifndef ADVISORBOT_ADVISORMAIN_H
#define ADVISORBOT_ADVISORMAIN_H

#define BOTPROMPT "advisorbot>"
#define USERPROMPT "user>"

#include <string>

class AdvisorMain {
public:
    AdvisorMain();

    /** Call this to start the program */
    void init();

private:
    void printMenu();

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
};


#endif //ADVISORBOT_ADVISORMAIN_H
