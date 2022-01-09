#pragma once
#ifndef ADVISORBOT_CSVREADER_H
#define ADVISORBOT_CSVREADER_H

#include "OrderBookEntry.h"
#include <vector>
#include <string>

class CSVReader {
public:
    CSVReader();

    /** Given a CSV data file, read the data and convert the records into a vector of OrderBookEntry objects */
    static std::vector<OrderBookEntry> readCSV(const std::string &csvFile);

    /** Function to tokenise each CSV line (i.e. record) into a vector */
    static std::vector<std::string> tokenise(const std::string &csvLine, char separator);

private:
    /** private utility function to aid in the conversion of raw CSV rows to OrderBookEntry objects */
    static OrderBookEntry stringsToOBE(std::vector<std::string> tokens);
};


#endif //ADVISORBOT_CSVREADER_H
