//
// Created by Willy Seah on 27/6/23.
//

#include "OrderBook.hpp"
#include <iostream>


void OrderBook::match(std::string side, Order* itr, long* leavesQty, const std::string& clientOrderId) {

    Order* order = itr; //the order that is being matched, meaning should decrease in quantity.
    long orderQuantity = order->quantity;
    long fillQuantity = std::min(*leavesQty, orderQuantity);

    *(leavesQty) -= fillQuantity;
    order->quantity -= fillQuantity;
    std::cout << "TRADE " << symbol << " " << clientOrderId << " " <<  itr->clientOrderId << " " << fillQuantity << " " << itr->price << std::endl;
    if (order->quantity == 0) {
        removeOrder(order); // existing order is completely matched
    }
}

long OrderBook::checkForMatch(const std::string& clientOrderId, const std::string& side, double price, long qty) {

    //parameters here is referring to what is just submitted, if just submitted BUY, side parameter is side
    long leavesQuantity = qty;

    if (side == "BUY") { //newest order is buying = BID, need to see if it can match with ASKS
        while (leavesQuantity && asksByPrice) {
            const auto bestAskIter = asksByPrice->firstOrder;
            if (price < bestAskIter->price) { //my buying price must at least be >= selling price, else break
                break;
            }
            match(side, bestAskIter, &leavesQuantity, clientOrderId);
        }
    }

    if (side == "SELL") { //newest order is selling = ASKS, need to see if it can match with BIDS
        while (leavesQuantity && bidsByPrice) {
            const auto bestBidIter = bidsByPrice->firstOrder;
            if (price > bestBidIter->price) { //my selling price must be <= what people are buying for, else break
                break;
            }
            match(side, bestBidIter, &leavesQuantity, clientOrderId);
        }
    }

    return leavesQuantity;
}

void OrderBook::add(std::string clientOrderId, std::string side, double price, long quantity, long timestamp) {
    long leavesQuantity = checkForMatch(clientOrderId, side, price, quantity);

    if (leavesQuantity > 0) {
        Order* order = new Order(clientOrderId, price, leavesQuantity, side, nullptr, nullptr, timestamp);
        //this client has more orders now
        addOrder(order);
    }
}






