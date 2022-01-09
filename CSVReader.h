#pragma once
#ifndef ADVISORBOT_CSVREADER_H
#define ADVISORBOT_CSVREADER_H

#include "OrderBookEntry.h"
#include <vector>
#include <string>

class CSVReader {
public:
    CSVReader();

    static std::vector<OrderBookEntry> readCSV(const std::string& csvFile);

    static std::vector<std::string> tokenise(const std::string& csvLine, char separator);

    static OrderBookEntry
    stringsToOBE(const std::string& priceString, std::string timestamp, std::string product, OrderBookType OrderType);

private:
    static OrderBookEntry stringsToOBE(std::vector<std::string> tokens);
};


#endif //ADVISORBOT_CSVREADER_H
