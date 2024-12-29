//
// Created by Willy Seah on 28/12/24.
//

#ifndef TRADINGENGINE_ORDER_HPP
#define TRADINGENGINE_ORDER_HPP

#pragma once

#include <cstdint>
#include <sstream>
#include "enums.hpp"
#include "helpers.hpp"

struct Order{
    int quantity; // 4
    BookSide side; // 4
    double price; // 8
    uint64_t timestamp; //8

    Order(int q, double p, BookSide s, uint64_t t = unix_time())
            : quantity {q}, price {p}, side {s}, timestamp {t} {}

    std::string to_string() const {
        std::stringstream ss;
        ss << "Order{"
           << "quantity: " << quantity << ", "
           << "timestamp: " << timestamp
           << "}";
        return ss.str();
    }

};

#endif //TRADINGENGINE_ORDER_HPP
