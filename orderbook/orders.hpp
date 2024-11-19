//
// Created by Willy Seah on 19/11/24.
//
#include <iostream>
#include <map>

#ifndef TRADINGENGINE_ORDERS_HPP
#define TRADINGENGINE_ORDERS_HPP

struct Order {
    std::string clientOrderId;
    double price;
    long quantity;
    std::string side;

    Order *prevOrder = nullptr;
    Order *nextOrder = nullptr;
    long timestamp;

    Order() = default;

    Order(std::string clientOrderId, double price, long quantity, std::string side, Order *prevOrder, Order *nextOrder,
          long timestamp) :
        clientOrderId(clientOrderId), price(price), quantity(quantity), side(side), prevOrder(prevOrder),
        nextOrder(nextOrder), timestamp(timestamp) {}


    void toString(std::string symbol) {
        std::cout << clientOrderId << " " << side << " " << symbol  << " " << quantity << " " << price << std::endl;
    }
};

struct OrdersAtPrice {
    std::string side;
    double price;

    Order *firstOrder = nullptr;

    OrdersAtPrice *prevEntry = nullptr;
    OrdersAtPrice *nextEntry = nullptr;

    OrdersAtPrice() = default;

    OrdersAtPrice(std::string side, double price, Order *firstOrder, OrdersAtPrice *prevEntry, OrdersAtPrice *nextEntry)
        : side(side), price(price), firstOrder(firstOrder), prevEntry(prevEntry), nextEntry(nextEntry) {}

    void toString(std::string symbol) {
        Order* curr = firstOrder;
        curr->toString(symbol);
        curr = curr->nextOrder;
        while (curr != firstOrder) {
            curr->toString(symbol);
            curr = curr->nextOrder;
        }
    }
};

typedef std::map<double, OrdersAtPrice*> OrdersAtPriceHashMap;

#endif //TRADINGENGINE_ORDERS_HPP
