//
// Benjy Berkowicz - 336182589
// Advanced Programming 2016-2017 Bar Ilan
//

#include "StandardTaxi.h"

using namespace std;

StandardTaxi::StandardTaxi(int id, CarMaker manu, Color color) : Taxi(
        id, manu, color) {

}

int StandardTaxi::move() {
    if (isAssigned) {
        location->x = currentTrip.getRoute()->top().x;
        location->y = currentTrip.getRoute()->top().y;
        cout << "New pos: " << location->toString() << endl;
        currentTrip.getRoute()->pop();
        if (currentTrip.getRoute()->empty()) {
            isAssigned = false;
        }
        // Returns 0 if there are no more moves to perform, otherwise 1.
        return !currentTrip.getRoute()->empty();
    }
    return 0;
}
