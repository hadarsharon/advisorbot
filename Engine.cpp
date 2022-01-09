#include "CSVReader.h"
#include "Engine.h"

bool Engine::compareTimestamps(const std::string &t1, const std::string &t2) {
    return t1 < t2;
}

double Engine::getHighPrice(std::vector<OrderBookEntry> &orders) {
    double max = orders[0].price;
    for (const OrderBookEntry &e: orders) {
        if (e.price > max) max = e.price;
    }
    return max;
}

double Engine::getLowPrice(std::vector<OrderBookEntry> &orders) {
    double min = orders[0].price;
    for (const OrderBookEntry &e: orders) {
        if (e.price < min) min = e.price;
    }
    return min;
}

double Engine::calculateAveragePriceOfOrders(const std::vector<OrderBookEntry> &orders) {
    if (orders.empty())
        return 0;

    double acc = 0;
    for (const OrderBookEntry &e: orders) {
        acc += e.price;
    }

    return acc / (double) orders.size();
}