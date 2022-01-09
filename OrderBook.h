#pragma once
#ifndef ADVISORBOT_ORDERBOOK_H
#define ADVISORBOT_ORDERBOOK_H


#include "OrderBookEntry.h"
#include "CSVReader.h"
#include <string>
#include <vector>
#include <map>

class OrderBook {
public:
    /** construct, reading a csv data file */
    explicit OrderBook(std::string filename);

    /** return vector of Orders according to the sent filters */
    std::vector<OrderBookEntry> getOrders(OrderBookType type, const std::string &product, const std::string &timestamp);

    /** returns the earliest time in the orderbook */
    std::string getEarliestTime();

    /** returns the next time after the sent time in the orderbook. If there is no next timestamp, wraps around to the start */
    std::string getNextTime(const std::string &timestamp);

    /** given a certain product name, check if it exists in the dataset (for validity checks etc.) */
    bool checkProductExists(std::string product);

    /** given a certain order type (string value), check if it is a valid one based on the Enum */
    bool isValidOrderType(const std::string &orderType);

    /** get maximal price in vector of orders */
    static double getHighPrice(std::vector<OrderBookEntry> &orders);

    /** get minimal price in vector of orders */
    static double getLowPrice(std::vector<OrderBookEntry> &orders);

    /** getter for the products vector */
    const std::vector<std::string> &getProducts() const;

    /** getter for the timestamps vector */
    const std::vector<std::string> &getTimestamps() const;

    /** mapping of valid order book types string values to their respective Enum value */
    std::map<std::string, OrderBookType> orderBookTypes = {
            {"ask", OrderBookType::ask},
            {"bid", OrderBookType::bid}
    };

private:
    /** populate vector of all known products in the dataset */
    std::vector<std::string> populateProducts();

    /** populate vector of all timestamps in the dataset */
    std::vector<std::string> populateTimestamps();

    std::vector<OrderBookEntry> orders;
    std::vector<std::string> products;
    std::vector<std::string> timestamps;
};

#endif //ADVISORBOT_ORDERBOOK_H
