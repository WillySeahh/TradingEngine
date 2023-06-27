//
// Created by Willy Seah on 27/6/23.
//
#include <iostream>
#include "OrderBook.hpp"

int main()
{
    OrderBook ob;

    ob.add_ask(105,5);
    ob.add_ask(104, 10);
    ob.add_ask(104, 20);

    ob.add_bid(100, 100);
    ob.add_bid(99, 100);
    ob.add_bid(98, 100);


    //someone want to buy price 105 amount 3
    ob.remove_bid(98, 301);
    //should have ask 105, 3 left

    std::cout << ob;


    OrderBook::BidAsk bidAsk = ob.getBidAsk();
    std::cout << "Highest Bid (if present)" << std::endl;
    if (bidAsk.bid.has_value()) {
        std::cout << bidAsk.bid.get().second << std::endl;
    } else {
        std::cout << "NIL" << std::endl;
    }
    std::cout << "Lowest Ask Price (if present)" << std::endl;

    if (bidAsk.ask.has_value()) {
        std::cout << bidAsk.ask.get().second << std::endl;
    } else {
        std::cout << "NIL" << std::endl;
    }



    return 0;
}
