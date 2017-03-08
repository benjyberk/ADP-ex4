//
// Benjy Berkowicz - 336182589
// Advanced Programming 2016-2017 Bar Ilan
//

#ifndef ADVANCED_EX2_LUXURYTAXI_H
#define ADVANCED_EX2_LUXURYTAXI_H


#include "Taxi.h"

class LuxuryTaxi : public Taxi {
public:
    LuxuryTaxi(int id, CarMaker manu, Color color);
    int move();
};


#endif //ADVANCED_EX2_LUXURYTAXI_H
