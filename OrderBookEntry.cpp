#include "OrderBookEntry.h"

OrderBookType OrderBookEntry::stringToOrderBookType(std::string s) {
    if (s == "ask")
        return OrderBookType::ask;
    if (s == "bid")
        return OrderBookType::bid;
    return OrderBookType::unknown;
}

bool OrderBookEntry::compareByTimestamp(OrderBookEntry &e1, OrderBookEntry &e2) {
    return e1.timestamp < e2.timestamp;
}

bool OrderBookEntry::compareByPriceAsc(OrderBookEntry &e1, OrderBookEntry &e2) {
    return e1.price < e2.price;
}

bool OrderBookEntry::compareByPriceDesc(OrderBookEntry &e1, OrderBookEntry &e2) {
    return e1.price > e2.price;
}