#pragma once
#ifndef ADVISORBOT_ORDERBOOKENTRY_H
#define ADVISORBOT_ORDERBOOKENTRY_H


#include <string>

enum class OrderBookType {
    bid,
    ask,
    asksale,
    bidsale,
    unknown
};

class OrderBookEntry {
public:

    OrderBookEntry(
            double _price,
            double _amount,
            std::string _timestamp,
            std::string _product,
            OrderBookType _orderType,
            std::string _username = "dataset"
    ) : price(_price),
        amount(_amount),
        timestamp(_timestamp),
        product(_product),
        orderType(_orderType),
        username(_username) {
    }

    static OrderBookType stringToOrderBookType(std::string s);

    static bool compareByTimestamp(OrderBookEntry &e1, OrderBookEntry &e2);

    static bool compareByPriceAsc(OrderBookEntry &e1, OrderBookEntry &e2);

    static bool compareByPriceDesc(OrderBookEntry &e1, OrderBookEntry &e2);

    double price;
    double amount;
    std::string timestamp;
    std::string product;
    OrderBookType orderType;
    std::string username;
};


#endif //ADVISORBOT_ORDERBOOKENTRY_H
