#include "AdvisorMain.h"
#include <iostream>

AdvisorMain::AdvisorMain() {

}

void AdvisorMain::init() {

}

void AdvisorMain::printMenu() {

}

void AdvisorMain::printHelp() {
    std::cout << BOTPROMPT << "The available commands are help, help <cmd>, avg, time, ..." << std::endl;
}

void AdvisorMain::helpCmd(const std::string &cmd) {

}

void AdvisorMain::listProducts() {

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
