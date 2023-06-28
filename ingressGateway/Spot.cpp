//
// Created by Willy Seah on 18/6/23.
//

#include "Spot.hpp"
#include "utils/time_utils.hpp"

#include <iostream>
#include <sstream>

Spot::Spot(std::time_t date, double open, double high, double low, double close) {
    this->date = date; //this is how we are referring to assigning the current date as parameter
    this->open = open;
    this->high = high;
    this->low = low;
    this->close = close;
}

Spot::Spot(std::string date, double open, double high, double low, double close) {
    this->date = dateToEpoch(date.c_str());
    this->open = open;
    this->high = high;
    this->low = low;
    this->close = close;
}

Spot::Spot(std::time_t date, double price){
    this->date = date;
    this->close = price;
    this->open = price;
    this->high = price;
    this->low = price;
}

Spot::Spot(std::string date, double price){
    this->date = dateToEpoch(date.c_str());
    this->close = price;
    this->open = price;
    this->high = price;
    this->low = price;
}

//define the destructor
Spot::~Spot() {
}


std::time_t Spot::getDate() {
    return this->date;
}

std::string Spot::getDateToString() {
    return epochToDate(this->date);
}

double Spot::getOpen() {
    return this->open;
}

double Spot::getHigh() {
    return this->high;
}

double Spot::getLow() {
    return this->low;
}

double Spot::getClose() {
    return this->close;
}


std::string Spot::toString() {
    std::ostringstream osOpen;
    osOpen << this->open;
    std::ostringstream osHigh; //convert double to string to be printed out, using outputstringstream
    osHigh << this->high;
    std::ostringstream osLow;
    osLow << this->low;
    std::ostringstream osClose;
    osClose << this->close;
    return "{ date: " + this->getDateToString()
           + " open: " + osOpen.str()
           + " high: " + osHigh.str()
           + " low: " + osLow.str()
           + " close: " + osClose.str()
           + " }";
}

void Spot::printSpot() {
    std::cout << this->toString() << std::endl;
}


