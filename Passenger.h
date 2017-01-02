//
// Benjy Berkowicz - 336182589
// Advanced Programming 2016-2017 Bar Ilan
//

#ifndef ADVANCED_EX2_PASSENGER_H
#define ADVANCED_EX2_PASSENGER_H

class TaxiDispatch;

#include "Point.h"
#include "Taxi.h"
#include "TaxiDispatch.h"

class Passenger {
private:
    int id;
    Point startPoint;
    Point endPoint;
    TaxiDispatch* dispatcher;
public:
    int generateScore();
    Taxi* orderTaxi();
};


#endif //ADVANCED_EX2_PASSENGER_H
