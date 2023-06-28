#include "time_utils.hpp"

#include <sstream>
#include <cstring>
#include <iostream>


//only accepts format YYYY-mm-dd
std::time_t dateToEpoch(std::string date) {
    //cpp try to use std::string, do not use array
    std::string year;
    year = date.substr(0,4);

    std::string month;
    month = date.substr(5, 8);

    std::string day;
    day = date.substr(8, 10);

    //create a struct time, to convert it into epoch time.
    struct tm time = {};
    time.tm_year = std::stoi(year) - 1900; //year must start since 1900
    time.tm_mon = std::stoi(month) - 1; //month is from 0-11, so need -1
    time.tm_mday = std::stoi(day);

    return timegm(&time);
}

std::string epochToDate(std::time_t epoch) {
    struct std::tm *ptm = std::gmtime(&epoch);

    std::stringstream osYear;
    osYear << ptm->tm_year + 1900;

    std::stringstream osMonth;
    if (ptm->tm_mon < 9) {
        osMonth << 0 << ptm->tm_mon + 1; //if its 0-9, append a 0 so august is 08
    } else {
        osMonth << ptm->tm_mon + 1;
    }

    std::stringstream osDay;
    if (ptm->tm_mday < 10) {
        osDay << 0 << ptm->tm_mday; //so day is 9 -> 09
    } else {
        osDay << ptm->tm_mday;
    }

    std::string date = osYear.str() + "-" + osMonth.str() + "-" + osDay.str();
    return date;
}

bool before(std::string date1, std::string date2) {
    std::time_t epoch1 = dateToEpoch(date1);
    std::time_t epoch2 = dateToEpoch(date2);

    return epoch1 < epoch2;
}

bool after(std::string date1, std::string date2) {
    return !before(date1, date2);
}

