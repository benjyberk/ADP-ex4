//
// Benjy Berkowicz - 336182589
// Advanced Programming 2016-2017 Bar Ilan
//

#include "DriverLocationListener.h"


void DriverLocationListener::moveEvent(Point * newP) {
    currentLocation = newP;
}

Point *DriverLocationListener::getLocation() {
    return currentLocation;
}

DriverLocationListener::DriverLocationListener(Point * begin, int driverID) {
    currentLocation = begin;
    id = driverID;
}
