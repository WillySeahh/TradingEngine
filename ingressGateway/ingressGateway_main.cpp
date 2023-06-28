//
// Created by Willy Seah on 28/6/23.
//

#include <time_utils.hpp>
#include "Quote.hpp"
#include "math.h"


int main() {

    Quote *appleQuote = new Quote("AAPL");
    //Why need pointer. Common misconception, new means the compiler allocates the required memory then
    // call the constructor to
    //create a new object on the allocated memory.
    //so we return the pointer to that allocated memory

    appleQuote->getHistoricalSpots("2023-05-01", "2023-05-09", "1d");
    appleQuote->printSpots();

    try {
        Spot spot = appleQuote->getSpot("2023-05-02");
        std::cout << "this is price " << '\n';
        spot.printSpot();

    } catch (std::exception &e) {
        std::cerr << e.what() << '\n';
    }


//    Quote *eurusd = new Quote("EURUSD=X");
//    eurusd->getHistoricalSpots("2018-01-01", "2018-01-10", "1d");
//    std::cout << "EUR/USD rates between 2018-01-01 and 2018-01-10" << std::endl;
//    eurusd->printSpots();

    delete appleQuote;


    return 0;
}