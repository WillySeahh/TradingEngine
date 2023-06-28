//
// Created by Willy Seah on 18/6/23.
//

#ifndef RETRIEVING_HISOTRICAL_DATA_SPOT_HPP
#define RETRIEVING_HISOTRICAL_DATA_SPOT_HPP

#include <string>



class Spot {

public:
    /**
     * Overloading the constructor of Spot
     * @param data
     * @param open
     * @param high
     * @param low
     * @param close
     */
    Spot(std::time_t date, double open, double high, double low, double close);

    Spot(std::string date, double open, double high, double low, double close);

    Spot(std::time_t date, double price);

    Spot(std::string date, double price);

    ~Spot();


    /**
     * The getters for the fields in spot
     * @return
     */
    std::time_t getDate();

    double getOpen();

    double getHigh();

    double getLow();

    double getClose();

    /**
     * Useful other functions for Spot class
     */
    std::string getDateToString();

    std::string toString();

    void printSpot();


private:

    /**
     * @brief Spot date in epoch format
     */
    std::time_t date;

    /**
     * @brief Price at opening
     */
    double open;

    /**
     * @brief Highest price value at this date
     */
    double high;

    /**
     * @brief Lowest price value at this date
     */
    double low;

    /**
     * @brief Price at closing
     */
    double close;

};


#endif //RETRIEVING_HISOTRICAL_DATA_SPOT_HPP
