#include "OrderBook.h"
#include "CSVReader.h"
#include <map>
#include <algorithm>

OrderBook::OrderBook(std::string filename) {
    orders = CSVReader::readCSV(filename);
}

std::vector<std::string> OrderBook::getKnownProducts() {
    std::vector<std::string> products;
    std::map<std::string, bool> prodMap;
    for (const OrderBookEntry &e: orders) {
        prodMap[e.product] = true;
    }
    for (auto const &e: prodMap) {
        products.push_back(e.first);
    }
    return products;
}

std::vector<OrderBookEntry> OrderBook::getOrders(OrderBookType type, std::string product, std::string timestamp) {
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

std::string OrderBook::getNextTime(std::string timestamp) {
    std::string nextTimestamp = "";
    for (const OrderBookEntry &e: orders) {
        if (e.timestamp > timestamp) {
            nextTimestamp = e.timestamp;
            break;
        }
    }
    if (nextTimestamp == "")
        nextTimestamp = orders[0].timestamp;
    return nextTimestamp;
}

void OrderBook::insertOrder(OrderBookEntry &order) {
    orders.push_back(order);
    std::sort(orders.begin(), orders.end(), OrderBookEntry::compareByTimestamp);
}

std::vector<OrderBookEntry> OrderBook::matchAsksToBids(std::string product, std::string timestamp) {
    std::vector<OrderBookEntry> asks = getOrders(OrderBookType::ask, product, timestamp);
    std::vector<OrderBookEntry> bids = getOrders(OrderBookType::bid, product, timestamp);
    std::vector<OrderBookEntry> sales;

    std::sort(asks.begin(), asks.end(), OrderBookEntry::compareByPriceAsc);
    std::sort(bids.begin(), bids.end(), OrderBookEntry::compareByPriceDesc);

    for (OrderBookEntry &ask: asks) {
        for (OrderBookEntry &bid: bids) {
            if (bid.price >= ask.price) {
                OrderBookEntry sale{ask.price, 0, timestamp, product, OrderBookType::asksale};
                if (bid.username == "simuser") {
                    sale.username = "simuser";
                    sale.orderType = OrderBookType::bidsale;
                }
                if (ask.username == "simuser") {
                    sale.username = "simuser";
                    sale.orderType = OrderBookType::asksale;
                }
                if (bid.amount == ask.amount) {
                    sale.amount = ask.amount;
                    sales.push_back(sale);
                    bid.amount = 0;
                    break;
                }
                if (bid.amount > ask.amount) {
                    sale.amount = ask.amount;
                    sales.push_back(sale);
                    bid.amount = bid.amount - ask.amount;
                    break;
                }
                if (bid.amount < ask.amount && bid.amount > 0) {
                    sale.amount = bid.amount;
                    sales.push_back(sale);
                    ask.amount = ask.amount - bid.amount;
                    bid.amount = 0;
                    continue;
                }
            }
        }
    }
    return sales;
}
