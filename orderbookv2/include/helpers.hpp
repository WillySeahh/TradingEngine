//
// Created by Willy Seah on 28/12/24.
//

#ifndef TRADINGENGINE_HELPERS_HPP
#define TRADINGENGINE_HELPERS_HPP

#pragma once

#include <chrono>

inline u_int64_t unix_time() {
    return std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
}

void print_fill(std::pair<int, double> fill, int quantity, u_int64_t start_time, u_int64_t end_time);

#endif //TRADINGENGINE_HELPERS_HPP
