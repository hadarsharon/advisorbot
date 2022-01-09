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

std::string OrderBookEntry::orderBookTypeToString(OrderBookType t) {
    if (t == OrderBookType::ask)
        return "ask";
    if (t == OrderBookType::bid)
        return "bid";
    return "unknown";
}

std::string OrderBookEntry::toString() const {
    std::string s;
    s += timestamp + " | " + product + " | " + orderBookTypeToString(orderType) + " | " + std::to_string(price);
    return s;
}
