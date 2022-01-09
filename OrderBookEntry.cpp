#include "OrderBookEntry.h"

OrderBookType OrderBookEntry::stringToOrderBookType(const std::string &s) {
    if (s == "ask")
        return OrderBookType::ask;
    if (s == "bid")
        return OrderBookType::bid;
    return OrderBookType::unknown;
}

bool OrderBookEntry::compareByTimestampAsc(OrderBookEntry &e1, OrderBookEntry &e2) {
    return e1.timestamp < e2.timestamp;
}