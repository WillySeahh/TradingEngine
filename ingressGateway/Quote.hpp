//
// Created by Willy Seah on 18/6/23.
//
#include <iostream>
#include "Spot.hpp"
#include <vector>


#ifndef RETRIEVING_HISOTRICAL_DATA_QUOTE_HPP
#define RETRIEVING_HISOTRICAL_DATA_QUOTE_HPP


class Quote {

public:

    /**
     * Quote constructor
     * @param symbol
     */
    Quote(std::string symbol);

    /**
     * Quote destructor
     */
    ~Quote();


    /**
     * @brief Spot getter by index
     * @param i spot index
     * @return spots(i)
     */
    Spot getSpot(size_t i);

    /**
     * @brief Spot getter by date
     * @param date Spot date
     * @return spots(date)
     */
    Spot getSpot(std::time_t date);

    /**
     * @brief Spot getter by date
     * @param date Spot date
     * @return spots(date)
     */
    Spot getSpot(std::string date);

    /**
     * @brief Print all the spots
     */
    void printSpots();

    /**
     * @brief Get the historical spot CSV file string
     * @param period1 Begining date (POSIX timestamp)
     * @param period2 Ending date (POSIX timestamp)
     * @param interval Date interval for spots, examples:
     *          daily "1d"
     *          weekly "1wk"
     *          annual "1y"
     * @return string containing the historical csv file
     */
    std::string getHistoricalCsv(std::time_t period1,
                                 std::time_t period2,
                                 std::string interval);

    /**
     * @brief Fill spots vector on a period
     * @param period1 Begining date (POSIX timestamp)
     * @param period2 Ending date (POSIX timestamp)
     * @param interval Date interval for spots, examples:
     *          daily "1d"
     *          weekly "1wk"
     *          annual "1y"
     */
    void getHistoricalSpots(std::time_t period1,
                            std::time_t period2,
                            std::string interval);

    /**
     * @brief Fill spots vector on a period
     * @param period1 Begining date (format yyyy-MM-dd)
     * @param period2 Ending date (format yyyy-MM-dd)
     * @param interval Date interval for spots, examples:
     *          daily "1d"
     *          weekly "1wk"
     *          annual "1y"
     */
    void getHistoricalSpots(std::string period1,
                            std::string period2,
                            std::string interval);









private:
    std::string symbol;

    std::vector<Spot> spots;
};


#endif //RETRIEVING_HISOTRICAL_DATA_QUOTE_HPP
