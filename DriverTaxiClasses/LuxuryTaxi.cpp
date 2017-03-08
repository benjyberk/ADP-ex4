//
// Benjy Berkowicz - 336182589
// Advanced Programming 2016-2017 Bar Ilan
//

#include "LuxuryTaxi.h"

using namespace std;

LuxuryTaxi::LuxuryTaxi(int id, CarMaker manu, Color color) : Taxi(id, manu, color) {
    tariff = 2;
}

int LuxuryTaxi::move() {
    if (isAssigned) {
        if (upto >= 1) {
            upto--;
        }
        location->x = currentTrip.getRoute()->at(upto).x;
        location->y = currentTrip.getRoute()->at(upto).y;
        upto--;

        if (upto < 0) {
            isAssigned = false;
        }
    }
    // Returns 0 if there are no more moves to perform, otherwise 1.
    return upto >= 0;
}
