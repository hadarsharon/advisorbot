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

    /** List all available commands */
    void printHelp();

    /** Output help for the specified command */
    void helpCmd(const std::string& cmd);

    /** List available products */
    void listProducts();
};


#endif //ADVISORBOT_ADVISORMAIN_H
