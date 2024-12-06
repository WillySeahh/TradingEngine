//
// Created by Willy Seah on 27/6/23.
//
#include <map>
#include <iostream>
#include <boost/optional.hpp>
#include <utility>
#include "orders.hpp"

#ifndef ORDER_BOOK2_ORDERBOOK_HPP
#define ORDER_BOOK2_ORDERBOOK_HPP

/**
 * Header to ensure that main.cpp only needs to be exposed to this file, and not the source file.
 */
class OrderBook {

public:

    void add(const std::string& orderId, const std::string& side, double price, long quantity, long timestamp);

    // Explicit is important to ensure whatever function takes an OrderBook as a parameter, is really receiving an Orderbook.
    explicit OrderBook(std::string  symbol): symbol(std::move(symbol)){};

private:
    std::string symbol;
    OrdersAtPrice *bidsByPrice = nullptr;
    OrdersAtPrice *asksByPrice = nullptr;

    OrdersAtPriceHashMap ordersAtPriceHashMap;

private:

    OrdersAtPrice* getOrdersAtPrice(double price) {
        return ordersAtPriceHashMap[price];
    }

    void addOrdersAtPrice(OrdersAtPrice *newOrderAtPrice) {

        // Place in hashmap
        ordersAtPriceHashMap[newOrderAtPrice->price] = newOrderAtPrice;

        OrdersAtPrice* bestOrdersByPrice = (newOrderAtPrice->side == "BUY" ? bidsByPrice : asksByPrice);

        if (!bestOrdersByPrice) {
            // this side (buy/sell) do not have any orders, no price. meaning the incoming newOrderAtPrice is the best
            if (newOrderAtPrice->side == "BUY") {
                bidsByPrice = newOrderAtPrice;
            } else {
                asksByPrice = newOrderAtPrice;
            }
            // Remember OrdersAtPrice is a double linked list, and the SELL and BUY is not linked together
            newOrderAtPrice->nextEntry = newOrderAtPrice->prevEntry = newOrderAtPrice;
        } else {

            OrdersAtPrice* target = bestOrdersByPrice;

            //If newOrder is SELL, is it higher than lowest sell
            //If is BUY, is it lower than highest buy
            //if this is false meaning this is the lowest sell or highest buy
            bool addAfter = (
                    (newOrderAtPrice->side == "SELL" && newOrderAtPrice->price > target->price) ||
                    (newOrderAtPrice->side == "BUY" && newOrderAtPrice->price < target->price)
                    );

            //It is not the best bid/ask. is it the second?
            //we need to check another time to allow for the while loop below to work
            if (addAfter) {
                target = target->nextEntry;
                addAfter = (
                        (newOrderAtPrice->side == "SELL" && newOrderAtPrice->price > target->price) ||
                        (newOrderAtPrice->side == "BUY" && newOrderAtPrice->price < target->price)
                );
                if (addAfter) {
                    target = target->nextEntry;
                }
            }

            while(addAfter && target != bestOrdersByPrice) {
                addAfter = (
                        (newOrderAtPrice->side == "SELL" && newOrderAtPrice->price > target->price) ||
                        (newOrderAtPrice->side == "BUY" && newOrderAtPrice->price < target->price)
                );
                if (addAfter) {
                    target = target->nextEntry;
                }
            }

            if (addAfter) {
                if (target == bestOrdersByPrice) {
                    //the new order is the worse buy or worse sell
                    target = bestOrdersByPrice->prevEntry;
                }
                newOrderAtPrice->prevEntry = target;
                target->nextEntry->prevEntry = newOrderAtPrice;
                newOrderAtPrice->nextEntry = target->nextEntry;
                target->nextEntry = newOrderAtPrice;
            } else {
                // Add Before
                newOrderAtPrice->prevEntry = target->prevEntry;
                newOrderAtPrice->nextEntry = target;
                target->prevEntry->nextEntry = newOrderAtPrice;
                target->prevEntry = newOrderAtPrice;

                if ((newOrderAtPrice->side == "BUY" && newOrderAtPrice->price > bestOrdersByPrice->price) ||
                    (newOrderAtPrice->side == "SELL" && newOrderAtPrice->price < bestOrdersByPrice->price)) {
                    //found a new best order price on buy or sell side

                    // Handle edge case
                    // when new price for BUY is highest, and the previous highest only has 1 price at that BUY
                    //previous highest, next is pointing to itself, which is wrong, need to point to bestOrdersByPrice

                    // May be redundant because addBefore the bestPrice means that addAfter is never true, and target is pointing to
                    target->nextEntry = (target->nextEntry == bestOrdersByPrice ? newOrderAtPrice : target->nextEntry);

                    (newOrderAtPrice->side == "BUY" ? bidsByPrice : asksByPrice) = newOrderAtPrice;
                }
            }

            // Attempt 2 at simplifying code
//            auto target = bestOrdersByPrice;
//            while (true) {
//                bool isBetterPrice = (newOrderAtPrice->side == "SELL" && newOrderAtPrice->price < target->price) ||
//                                      (newOrderAtPrice->side == "BUY" && newOrderAtPrice->price > target->price);
//                if (isBetterPrice) break;
//                target = target->nextEntry;
//                if (target == bestOrdersByPrice) break;
//            }
//
//            // Insert new_orders_at_price before target.
//            newOrderAtPrice->prevEntry = target->prevEntry;
//            newOrderAtPrice->nextEntry = target;
//            target->prevEntry->nextEntry = newOrderAtPrice;
//            target->prevEntry = newOrderAtPrice;
//
//            // Update best_orders_by_price if necessary.
//            if ((newOrderAtPrice->side == "BUY" && newOrderAtPrice->price > bestOrdersByPrice->price) ||
//                (newOrderAtPrice->side == "SELL" && newOrderAtPrice->price < bestOrdersByPrice->price)) {
//                bestOrdersByPrice = newOrderAtPrice;
//                (newOrderAtPrice->side == "BUY" ? bidsByPrice : asksByPrice) = newOrderAtPrice;
//            }

        }
    }

    void removeOrdersAtPrice(const std::string& side, double price) {
        OrdersAtPrice* bestOrdersByPrice = (side == "BUY" ? bidsByPrice : asksByPrice);

        OrdersAtPrice* ordersAtPrice = getOrdersAtPrice(price);

        if (ordersAtPrice->nextEntry == ordersAtPrice) {
            // only 1 price at the side
            (side == "BUY" ? bidsByPrice : asksByPrice) = nullptr;
        } else {
            ordersAtPrice->prevEntry->nextEntry = ordersAtPrice->nextEntry;
            ordersAtPrice->nextEntry->prevEntry = ordersAtPrice->prevEntry;

            if (ordersAtPrice == bestOrdersByPrice) {
                //shift the best ask and bids
                (side == "BUY" ? bidsByPrice : asksByPrice) = ordersAtPrice->nextEntry;
            }
            ordersAtPrice->prevEntry = ordersAtPrice->nextEntry = nullptr;
        }
        ordersAtPriceHashMap.erase(price);
        delete ordersAtPrice;
    }

    void match(const std::string& side, Order* bidItr, long* leavesQty, const std::string& clientOrderId);

    long checkForMatch(const std::string& clientOrderId, const std::string& side, double price, long qty);

    void removeOrder(Order *order) {
        OrdersAtPrice* ordersAtPrice = getOrdersAtPrice(order->price);

        if (order->prevOrder == order) {
            //only 1 order at that price
            //Orders at price must have at least 1 order else delete it.
            removeOrdersAtPrice(order->side, order->price);
        } else {
            auto orderBefore = order->prevOrder;
            auto orderAfter = order->nextOrder;

            orderBefore->nextOrder = orderAfter;
            orderAfter->prevOrder = orderBefore;

            if (ordersAtPrice->firstOrder == order) {
                ordersAtPrice->firstOrder = orderAfter;
            }
        }
        order->prevOrder = order->nextOrder = nullptr;
        delete order;
    }

    void addOrder(Order *order) {
        OrdersAtPrice* ordersAtPrice = getOrdersAtPrice(order->price);

        if (!ordersAtPrice) {
            order->nextOrder = order->prevOrder = order;

            OrdersAtPrice* newOrdersAtPrice = new OrdersAtPrice(order->side, order->price, order, nullptr, nullptr);
            addOrdersAtPrice(newOrdersAtPrice);
        } else {
            Order* firstOrder = ordersAtPrice->firstOrder; // get first order of this price
            //the latest order that joins this queue should be at the back.
            firstOrder->prevOrder->nextOrder = order;
            order->prevOrder = firstOrder->prevOrder;
            order->nextOrder = firstOrder;
            firstOrder->prevOrder = order;
        }
    }

};

#endif //ORDER_BOOK2_ORDERBOOK_HPP
