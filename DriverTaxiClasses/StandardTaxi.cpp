//
// Benjy Berkowicz - 336182589
// Advanced Programming 2016-2017 Bar Ilan
//

#include "StandardTaxi.h"

using namespace std;

StandardTaxi::StandardTaxi(int id, CarMaker manu, Color color) : Taxi(
        id, manu, color) {
    tariff = 1;
}

int StandardTaxi::move() {
    if (isAssigned) {
        location->x = (currentTrip.getRoute())->at(upto).x;
        location->y = (currentTrip.getRoute())->at(upto).y;
        upto--;
        if (upto < 0) {
            isAssigned = false;
        }
        // Returns 0 if there are no more moves to perform, otherwise 1.
        return upto >= 0;
    }
    return 0;
}
