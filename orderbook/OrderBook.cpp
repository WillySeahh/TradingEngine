//
// Created by Willy Seah on 27/6/23.
//

#include "OrderBook.hpp"
#include <iostream>


bool OrderBook::isEmpty(){
    return bids.empty() && asks.empty();
}

void OrderBook::add_bid(int price, int amount) {
    add(price, amount, true);
}

void OrderBook::add_ask(int price, int amount) {
    add(price, amount, false);
}

void OrderBook::remove_bid(int price, int amount) {
    remove(price, amount, true);
}

void OrderBook::remove_ask(int price, int amount) {
    remove(price, amount, false);
}



void OrderBook::add(int price, int amount, bool bid) {

    if (bid) {
        //this is bid map, how much buyer want to buy for
        bids[price] += amount;
    } else {
        //this is seller want to sell more
        asks[price] += amount;
    }
}


void OrderBook::remove(int price, int amount, bool bid) {

    //TIP: need to get reference to table.
  //  std::map<int,int>&table = bid? bids : asks;

    if (bid) {
        //this is remove bid. means someone want to sell
        //we should remove the highest bid first
        auto it = bids.rbegin();

        while (it != bids.rend()) {

            if (it->first >= price) {
                //can remove bid since bid price is  >= price

                if (it->second >= amount) {
                    //this bid can fulfil the entire order
                    it->second -= amount;
                    if (it->second == 0) {
                        bids.erase(it->first); //remove the key
                    }
                    return; //order already fulfilled
                } else {
                    //this bid cannot fulfil order

                    amount -= it->second;

                    it->second = 0;
                    if (it->second == 0) {
                        bids.erase(it->first); //remove the key
                    }
                    //TIP: after erase key dont need to it++;
                    continue;
                }

            } else {
                //this sell order is not entirely fulfilled
                add_ask(price, amount);
                return;
            }
        }

        if (amount > 0) {
            add_ask(price, amount);
        }


    } else {
        //this is remove sell. means someone want to buy
        //we should sell the cheapest one to him first

        auto it = asks.begin();

        while (it != asks.end()) {

            std::cout << it->first << std::endl;

            if (it->first <= price) {
                //this person buying price is more than or equal to
                //the current ASK

                if (it->second >= amount) {
                    //this current ASK can fulfil entire buy order
                    it->second -= amount;
                    if (it->second == 0) {
                        asks.erase(it->first);
                    }
                    return; //order is fulfilled

                } else {
                    //this current ask cannot fulfil entire buy order

                    amount = amount - it->second;

                    it->second = 0;

                    if (it->second == 0) {
                       asks.erase(it++); //remove the key
                    }

                    continue;
                }


            } else {
                //the cheapest ASK price is more than what this buyer is buying for
                //cannot buy anything so add to bid
                add_bid(price, amount);
                return;
            }
        }

        if (amount > 0) {
            add_bid(price, amount);
            return;
        }
    }
}





std::ostream& operator<<(std::ostream &os, OrderBook &book) {

    if (book.isEmpty()) {
        os << "Order book empty";
        return os;
    }
    //want to print the orderbook from highest price to lowest
    os << "Start of Order Book, highest price to lowest" << std::endl;
    os << "Starting with ASKS" << std::endl;
    for(auto it = book.asks.rbegin(); it != book.asks.rend(); ++it) {
        os << "Price is: " << it->first << "\t" << "Amount is: " << it->second << std::endl;
    }
    os << std::endl;
    os << "Spread between lowest ask and highest bid" << std::endl;
    os << std::endl;

    os << "Starting with BIDS" << std::endl;

    for(auto it = book.bids.rbegin(); it != book.bids.rend(); ++it) {
        os << "Price is: " << it->first << "\t" << "Amount is: " << it->second << std::endl;
    }

    os << "End of Order Book" << std::endl << std::endl;
    return os;

}

OrderBook::BidAsk OrderBook::getBidAsk() {
    BidAsk result;

    auto best_bid = bids.rbegin();
    if (best_bid != bids.rend()) {
        result.bid = *best_bid;
    }

    auto best_ask = asks.begin();
    if (best_ask != asks.end()) {
        result.ask = *best_ask;
    }
    return result;
}






