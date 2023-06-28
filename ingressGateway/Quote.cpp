//
// Created by Willy Seah on 18/6/23.
//
#include <vector>
#include "Quote.hpp"
#include <iostream>
#include <sstream>
#include "utils/time_utils.hpp"
#include "curl_utils.hpp"
#include <iostream>


Quote::Quote(std::string symbol) {
    this->symbol = symbol;
}

Quote::~Quote() {

}

Spot Quote::getSpot(std::string date) {
    for (std::vector<Spot>::iterator it = this->spots.begin();
         it != this->spots.end();
         ++it) {
        if (it->getDateToString() == date) {
            return *it;
        }
    }
    std::string error = "ERROR getSpot(date) - There is no spot at " + date;
    throw std::invalid_argument(error);
}

void Quote::printSpots() {
    for (std::vector<Spot>::iterator it = this->spots.begin();
         it != this->spots.end();
         ++it) {
        std::cout << it->toString() << std::endl;
    }
}

std::string Quote::getHistoricalCsv(
        std::time_t period1,
        std::time_t period2,
        std::string interval
) {
    return downloadYahooCsv(this->symbol, period1, period2, interval);
}



void Quote::getHistoricalSpots(std::time_t period1,
                               std::time_t period2,
                               std::string interval) {
    // Download the historical prices Csv
    std::string csv = this->getHistoricalCsv(period1, period2, interval);
    //convert a string to a input string stream
    std::istringstream csvStream(csv);
    std::string line;

    // Remove the header line
    std::getline(csvStream, line);

    while (std::getline(csvStream, line)) {

        //line contains: 2023-05-01,169.279999,170.449997,168.639999,169.589996,169.355743,52472900
        //need to split it up
        // Split line delimited by comma separator into a vector
        std::vector<std::string> spotVector;

       // std::cout << line << '\n';

        std::string temp;
        int  i = 0;
        while (line[i] != '\0') {
            if (line[i] != ',') {
                temp += line[i];
            } else {
                spotVector.push_back(temp);
                temp.clear();
            }
            i++;
        }

        if (spotVector[0] != "null" && spotVector[1] != "null") {
            Spot spot = Spot(
                    spotVector[0],                      // date
                    std::stod(spotVector[1]),   // open, string to double, stod
                    std::stod(spotVector[2]),   // high
                    std::stod(spotVector[3]),   // low
                    std::stod(spotVector[4])    // close
            );
            this->spots.push_back(spot); //push each spot into vector
        }
    }
}

void Quote::getHistoricalSpots(const std::string date1,
                               const std::string date2,
                               const std::string interval) {
    std::time_t period1 = dateToEpoch(date1);
    std::time_t period2 = dateToEpoch(date2);

    this->getHistoricalSpots(period1, period2, interval);
}
