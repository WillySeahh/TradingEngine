//
// Created by Willy Seah on 28/12/24.
//
#include "../include/helpers.hpp"
#include <fstream>
#include <iostream>
#include <utility>

using std::cout;
using std::cerr;

void print_fill(std::pair<int, double> fill, int quantity, u_int64_t start_time, u_int64_t end_time){
    cout << "\033[33mFilled " << fill.first << "/" << quantity << " units @ $"
         << fill.second/fill.first << " average price. Time taken: "
         << (end_time-start_time) << " nano seconds\033[0m" << "\n";
}