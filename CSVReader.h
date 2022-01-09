#pragma once
#ifndef ADVISORBOT_CSVREADER_H
#define ADVISORBOT_CSVREADER_H

#include "OrderBookEntry.h"
#include <vector>
#include <string>

/*
DISCLAIMER:
I took the liberty of reusing some of the code introduced with the CSVReader module during the course i.e. merklerex
While some parts are left unchanged, some of the code has been rewritten or adapted by myself for advisorbot.
*/

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
