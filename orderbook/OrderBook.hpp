//
// Created by Willy Seah on 27/6/23.
//
#include <map>
#include <iostream>
#include <boost/optional.hpp>

#ifndef ORDER_BOOK2_ORDERBOOK_HPP
#define ORDER_BOOK2_ORDERBOOK_HPP

class OrderBook {

public:

    struct BidAsk {
        typedef boost::optional<std::pair<int,int>> Entry; //use optional because bid ask map may be empty
        Entry bid, ask;

        boost::optional<int> spread();
    };


    bool isEmpty();

    void add_bid(int price, int amount);
    void add_ask(int price, int amount);

    void remove_bid(int price, int amount);
    void remove_ask(int price, int amount);

    BidAsk getBidAsk();

    friend std::ostream& operator<<(std::ostream& os, OrderBook&);


private:
    std::map<int, int> bids, asks;
    void add(int price, int amount, bool bid);
    void remove(int price, int amount, bool bid);

};

#endif //ORDER_BOOK2_ORDERBOOK_HPP
