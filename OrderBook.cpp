#include "OrderBook.h"
#include "CSVReader.h"
#include <map>
#include <utility>
#include <algorithm>

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

bool OrderBook::compareTimestamps(const std::string &t1, const std::string &t2) {
    return t1 < t2;
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
    std::sort(timestamps.begin(), timestamps.end(), compareTimestamps);
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
    return timestamps[0];
}

std::pair<std::string, int> OrderBook::getNextTime(const std::string &timestamp) {
    std::string nextTimestamp;
    int timestampIndex;
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

bool OrderBook::isValidOrderType(const std::string &orderType) {
    return orderBookTypes.count(orderType) > 0;
}

double OrderBook::calculateAveragePriceOfOrders(const std::vector<OrderBookEntry> &orders) {
    if (orders.empty())
        return 0;

    double acc = 0;
    for (const OrderBookEntry &e: orders) {
        acc += e.price;
    }

    return acc / (double) orders.size();
}
