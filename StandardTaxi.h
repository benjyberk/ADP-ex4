//
// Benjy Berkowicz - 336182589
// Advanced Programming 2016-2017 Bar Ilan
//

#ifndef ADVANCED_EX2_STANDARDTAXI_H
#define ADVANCED_EX2_STANDARDTAXI_H


#include "Taxi.h"
#include "CarMaker.h"

class StandardTaxi : public Taxi {
public:
    StandardTaxi(int id, CarMaker manu, Color color);
    int move();
};


#endif //ADVANCED_EX2_STANDARDTAXI_H
