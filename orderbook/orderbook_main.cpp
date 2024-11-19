//
// Created by Willy Seah on 27/6/23.
//
#include <iostream>
#include <chrono>
#include <sstream>
#include <memory>
#include <map>
#include <fstream>
#include <filesystem>

#include "OrderBook.hpp"

struct Input {
    std::string orderId;
    std::string side;
    std::string symbol;
    long quantity;
    double price;
};

Input parseInput(const std::string& inputString) {
    std::istringstream iss(inputString);
    Input input;
    iss >> input.orderId >> input.side >> input.symbol >> input.quantity >> input.price;
    return input;
}

int main()
{
    std::map<std::string, std::unique_ptr<OrderBook> > getBookFromSymbol;
    std::string line;

    long time = 0;

    std::ifstream input_file("sample_input.txt");

//    if (std::ifstream("sample_input.txt").good()) {
//        // File exists, proceed with opening
//    } else {
//        std::cout << "File not found: " << "/orderbook/sample_input.txt" << std::endl;
//    }

    while (getline(input_file, line)) {
    //while (getline(std::cin, line) && line != "exit") {
        Input parsedInput = parseInput(line);
        OrderBook* book;
        if (getBookFromSymbol.find(parsedInput.symbol) == getBookFromSymbol.end()) {
            getBookFromSymbol[parsedInput.symbol] = std::make_unique<OrderBook>(parsedInput.symbol);
        }
        book = getBookFromSymbol[parsedInput.symbol].get();
        book->add(parsedInput.orderId, parsedInput.side, parsedInput.price, parsedInput.quantity, time);
        time ++;
    }
    std::cout << std::endl;

//    for(const auto& [symbol,book] : getBookFromSymbol) {
//        book->toStringWithArrivalTime();
//    }


    return 0;
}
