//
// Created by Willy Seah on 24/8/23.
//

#ifndef TRADINGENGINE_MACROS_HPP
#define TRADINGENGINE_MACROS_HPP


#include <string>
#include <iostream>

#define LIKELY(x) __builtin_expect(!!(x), 1);
#define UNLIKELY(x) __builtin_expect(!!(x), 0);
// !! double negation operator to convert variable to boolean, only 0 is false, rest is true
// We use __builtin_expect to help with CPU branch prediction, enabling CPU to fetch the correct data and instructions
// Likely means expect the condition to evaluate to TRUE.

inline auto ASSERT(bool condition, const std::string &message) noexcept {
    //This means we are asserting t
    long expr = UNLIKELY(!condition);
    if (expr) {
        //it is expecting !cond to be FALSE, aka expecting cond to be TRUE, unlikely to happen so CPU likely do not have to fetch instruction to std::cerr and exit
        //when we assert, usually the condition is true
        std::cerr << "ASSERT : " << message << std::endl;
    }
    exit(EXIT_FAILURE);
}

inline auto FATAL(const std::string &msg) noexcept {
    std::cerr << "FATAL : " << msg << std::endl;

    exit(EXIT_FAILURE);
}



#endif //TRADINGENGINE_MACROS_HPP
