#include "OrderBook.h"
#include "CSVReader.h"
#include <map>
#include <utility>

OrderBook::OrderBook(std::string filename) {
    orders = CSVReader::readCSV(std::move(filename));
    products = populateProducts();
    timestamps = populateTimestamps();
}

std::vector<std::string> OrderBook::populateProducts() {
    std::map<std::string, bool> prodMap;
    for (const OrderBookEntry &e: orders) {
        prodMap[e.product] = true;
    }
    products.reserve(prodMap.size());
    for (auto const &e: prodMap) {
        products.push_back(e.first);
    }
    return products;
}

std::vector<std::string> OrderBook::populateTimestamps() {
    std::map<std::string, bool> timeMap;
    for (const OrderBookEntry &e: orders) {
        timeMap[e.timestamp] = true;
    }
    timestamps.reserve(timeMap.size());
    for (auto const &e: timeMap) {
        timestamps.push_back(e.first);
    }
    return timestamps;
}

std::vector<OrderBookEntry>
OrderBook::getOrders(OrderBookType type, const std::string &product, const std::string &timestamp) {
    std::vector<OrderBookEntry> orders_sub;
    for (const OrderBookEntry &e: orders) {
        if (e.orderType == type && e.product == product && e.timestamp == timestamp)
            orders_sub.push_back(e);
    }
    return orders_sub;
}

double OrderBook::getHighPrice(std::vector<OrderBookEntry> &orders) {
    double max = orders[0].price;
    for (const OrderBookEntry &e: orders) {
        if (e.price > max) max = e.price;
    }
    return max;
}

double OrderBook::getLowPrice(std::vector<OrderBookEntry> &orders) {
    double min = orders[0].price;
    for (const OrderBookEntry &e: orders) {
        if (e.price < min) min = e.price;
    }
    return min;
}

std::string OrderBook::getEarliestTime() {
    return orders[0].timestamp;
}

std::string OrderBook::getNextTime(const std::string &timestamp) {
    std::string nextTimestamp;
    for (const std::string &t: timestamps) {
        if (t > timestamp) {
            nextTimestamp = t;
            break;
        }
    }
    if (nextTimestamp.empty())
        nextTimestamp = timestamps[0];
    return nextTimestamp;
}

const std::vector<std::string> &OrderBook::getProducts() const {
    return products;
}
