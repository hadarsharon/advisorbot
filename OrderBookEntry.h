#pragma once
#ifndef ADVISORBOT_ORDERBOOKENTRY_H
#define ADVISORBOT_ORDERBOOKENTRY_H


#include <string>
#include <utility>

enum class OrderBookType {
    bid,
    ask,
    unknown
};

class OrderBookEntry {
public:

    OrderBookEntry(
            double _price,
            std::string _timestamp,
            std::string _product,
            OrderBookType _orderType
    ) : price(_price),
        timestamp(std::move(_timestamp)),
        product(std::move(_product)),
        orderType(_orderType) {
    }

    /** maps string values to Enum type */
    static OrderBookType stringToOrderBookType(const std::string &s);

    /** reverts Enum type to string representation */
    static std::string orderBookTypeToString(OrderBookType t);

    /** helper method to compare two entries by their Timestamp values */
    static bool compareByTimestampAsc(OrderBookEntry &e1, OrderBookEntry &e2);

    /** generate a string representation of the OrderBookEntry */
    std::string toString() const;

    double price;
    std::string timestamp;
    std::string product;
    OrderBookType orderType;
};


#endif //ADVISORBOT_ORDERBOOKENTRY_H
