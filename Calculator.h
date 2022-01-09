#pragma once
#ifndef ADVISORBOT_CALCULATOR_H
#define ADVISORBOT_CALCULATOR_H


#include <string>
#include <vector>
#include <map>
#include "OrderBookEntry.h"
#include "CSVReader.h"

class Calculator {

public:
/** compare two timestamp strings (for sorting and the like) */
    static bool compareTimestamps(const std::string &t1, const std::string &t2);

/** get maximal price in vector of orders */
    static double getHighPrice(std::vector<OrderBookEntry> &orders);

/** get minimal price in vector of orders */
    static double getLowPrice(std::vector<OrderBookEntry> &orders);

/** given a vector of orders, calculate and return the average price */
    static double calculateAveragePriceOfOrders(const std::vector<OrderBookEntry> &orders);
};


#endif //ADVISORBOT_CALCULATOR_H
