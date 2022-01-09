#pragma once
#ifndef ADVISORBOT_ORDERBOOK_H
#define ADVISORBOT_ORDERBOOK_H


#include "OrderBookEntry.h"
#include "CSVReader.h"
#include <string>
#include <vector>

class OrderBook {
public:
    /** construct, reading a csv data file */
    explicit OrderBook(std::string filename);

    /** return vector of all known products in the dataset */
    std::vector<std::string> getKnownProducts();

    /** return vector of Orders according to the sent filters */
    std::vector<OrderBookEntry> getOrders(OrderBookType type, std::string product, std::string timestamp);

    /** returns the earliest time in the orderbook */
    std::string getEarliestTime();

    /** returns the next time after the sent time in the orderbook. If there is no next timestamp, wraps around to the start */
    std::string getNextTime(std::string timestamp);

    void insertOrder(OrderBookEntry &order);

    std::vector<OrderBookEntry> matchAsksToBids(std::string product, std::string timestamp);

    static double getHighPrice(std::vector<OrderBookEntry> &orders);

    static double getLowPrice(std::vector<OrderBookEntry> &orders);

private:
    std::vector<OrderBookEntry> orders;
};


#endif //ADVISORBOT_ORDERBOOK_H
