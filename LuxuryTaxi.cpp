//
// Benjy Berkowicz - 336182589
// Advanced Programming 2016-2017 Bar Ilan
//

#include "LuxuryTaxi.h"

using namespace std;

LuxuryTaxi::LuxuryTaxi(int id, CarMaker manu, Color color) : Taxi(id, manu, color) {

}

int LuxuryTaxi::move() {
    if (isAssigned) {
        if (currentTrip.getRoute()->size() >= 2) {
            currentTrip.getRoute()->pop();
        }
        location->x = currentTrip.getRoute()->top().x;
        location->y = currentTrip.getRoute()->top().y;
        currentTrip.getRoute()->pop();

        if (currentTrip.getRoute()->empty()) {
            isAssigned = false;
        }
    }
    // Returns 0 if there are no more moves to perform, otherwise 1.
    return !currentTrip.getRoute()->empty();
}
