#include "OrderBook.h"
#include "CSVReader.h"
#include "Calculator.h"
#include <map>
#include <utility>
#include <algorithm>

OrderBook::OrderBook(const std::string &filename) {
    orders = CSVReader::readCSV(filename);
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
    std::sort(timestamps.begin(), timestamps.end(), Calculator::compareTimestamps);
    return timestamps;
}

std::vector<OrderBookEntry>
OrderBook::getOrders(OrderBookType type, const std::string &product, const std::string &timestamp) {
    std::vector<OrderBookEntry> orders_sub;
    for (const OrderBookEntry &e: orders) {
        if (
                e.orderType == type &&
                (product.empty() || e.product == product) &&  // only filter by product if given, else get all products
                (timestamp.empty() || e.timestamp == timestamp) // ditto for timestamp
                )
            orders_sub.push_back(e);
    }
    return orders_sub;
}

std::string OrderBook::getEarliestTime() {
    return timestamps[0];
}

std::pair<std::string, int> OrderBook::getNextTime(const std::string &timestamp) {
    std::string nextTimestamp;
    unsigned int timestampIndex;
    for (int i = 0; i < timestamps.size(); ++i) {
        if (timestamps[i] > timestamp) {
            nextTimestamp = timestamps[i];
            timestampIndex = i;
            break;
        }
    }
    if (nextTimestamp.empty()) {
        nextTimestamp = timestamps[0];
        timestampIndex = 0;
    }
    return {nextTimestamp, timestampIndex};
}

const std::vector<std::string> &OrderBook::getProducts() const {
    return products;
}

const std::vector<std::string> &OrderBook::getTimestamps() const {
    return timestamps;
}

bool OrderBook::checkProductExists(std::string product) {
    return std::any_of(products.begin(), products.end(), [&product](const std::string &p) { return p == product; });
}

bool OrderBook::isValidOrderType(const std::string &orderType) const {
    return orderBookTypes.count(orderType) > 0;
}

