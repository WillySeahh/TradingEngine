//
// Created by Willy Seah on 19/11/24.
//
#include <iostream>
#include <map>
#include <utility>

#ifndef TRADINGENGINE_ORDERS_HPP
#define TRADINGENGINE_ORDERS_HPP

/**
 * Chose to use struct instead of class as I am not planning to perform polymorphism / inheritance.
 * Mostly the same but for default class variables is private for class and public for struct.
 * Chose to use struct as class variables are public and easy to access.
 *
 * Order is a doubly linked list.
 */
struct Order {
    std::string clientOrderId;
    double price;
    long quantity;
    std::string side;

    Order *prevOrder = nullptr;
    Order *nextOrder = nullptr;
    long timestamp;

    Order() = default;

    ~Order(){
        //std::cout << "Deleting Order " << this->clientOrderId << " " << this->price << " " << std::endl;
    }

    // Use move semantics here to prevent unnecessary copying.
    Order(std::string clientOrderId, double price, long quantity, std::string side, Order *prevOrder, Order *nextOrder,
          long timestamp) :
        clientOrderId(std::move(clientOrderId)), price(price), quantity(quantity), side(std::move(side)), prevOrder(prevOrder),
        nextOrder(nextOrder), timestamp(timestamp) {}

    /**
     * For the const in the parameter:
     * Choose to pass  by reference to prevent copying, we do not need an additional copy for simply printing.
     * const in the parameter is important,
     * What const refers to:
     * The reference itself: The const keyword prevents the function from reassigning the reference to point to a different string.
     * The content of the string: The const keyword also prevents the function from modifying the characters within the string.
     * @param symbol
     *
     * For the const outside the parameter, it promises that this function does not modify any class variables.
     * For a print statement it should not edit that hence its safer to add it.
     */
    void toString(const std::string& symbol) const {
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

    ~OrdersAtPrice() {
        //std::cout << "Deleting OrdersAtPrice " << this->side << " " << this->price << " " << std::endl;
    }

    // Move semantics to ensure unnecessary copying.
    OrdersAtPrice(std::string side, double price, Order *firstOrder, OrdersAtPrice *prevEntry, OrdersAtPrice *nextEntry)
        : side(std::move(side)), price(price), firstOrder(firstOrder), prevEntry(prevEntry), nextEntry(nextEntry) {}

    void toString(const std::string& symbol) const {
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
