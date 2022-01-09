#include "CSVReader.h"
#include <iostream>
#include <fstream>
#include "OrderBookEntry.h"

CSVReader::CSVReader() = default;

std::vector<OrderBookEntry> CSVReader::readCSV(const std::string &csvFilename) {
    std::vector<OrderBookEntry> entries;
    FILE *fp;
    char line_buffer[1024];
    fp = fopen(csvFilename.c_str(), "r");
    if (fp == nullptr) {
        std::cout << "Couldn't open CSV File: " << csvFilename << std::endl;
        throw std::runtime_error("Couldn't open CSV File!");
    }
    while (fgets(line_buffer, 1024, fp) != nullptr) {
        try {
            OrderBookEntry obe = stringsToOBE(tokenise(line_buffer, ','));
            entries.push_back(obe);
        } catch (const std::exception &e) {
            std::cout << "CSVReader::readCSV bad data - " << e.what() << std::endl;
        }
    }
    fclose(fp);
    std::cout << "CSVReader::readCSV read " << entries.size() << " entries" << std::endl;
    return entries;
}

std::vector<std::string> CSVReader::tokenise(const std::string &csvLine, char separator) {
    std::vector<std::string> tokens;
    signed int start, end;
    std::string token;
    start = csvLine.find_first_not_of(separator, 0);
    do {
        end = csvLine.find_first_of(separator, start);
        if (start == csvLine.length() || start == end) break;
        if (end >= 0) token = csvLine.substr(start, end - start);
        else token = csvLine.substr(start, csvLine.length() - start);
        tokens.push_back(token);
        start = end + 1;
    } while (end > 0);
    return tokens;
}

OrderBookEntry CSVReader::stringsToOBE(std::vector<std::string> tokens) {
    double price;
    if (tokens.size() != 5) { // bad
        std::cout << "Bad line, expected 5 tokens, got: " << tokens.size() << std::endl;
        throw std::exception{};
    }
    // we have 5 tokens
    try {
        price = std::stod(tokens[3]);
    } catch (std::exception &e) {
        std::cout << "CSVReader::stringsToOBE Bad float! " << tokens[3] << std::endl;
        std::cout << "CSVReader::stringsToOBE Bad float! " << tokens[4] << std::endl;
        throw;
    }
    OrderBookEntry obe{price, tokens[0], tokens[1], OrderBookEntry::stringToOrderBookType(tokens[2])};
    return obe;
}