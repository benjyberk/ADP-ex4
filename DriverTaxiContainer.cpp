//
// Benjy Berkowicz - 336182589
// Advanced Programming 2016-2017 Bar Ilan
//

#include "DriverTaxiContainer.h"

DriverTaxiContainer::DriverTaxiContainer() {
    taxi = 0;
    driver = 0;
    location = new Point(0,0);
}

void DriverTaxiContainer::setDriver(Driver * newDriver) {
    driver = newDriver;
}

void DriverTaxiContainer::setTaxi(Taxi * newTaxi) {
    taxi = newTaxi;
}

void DriverTaxiContainer::setLocation(Point * newLocation) {
    location = newLocation;
}

DriverTaxiContainer::~DriverTaxiContainer() {
    if (taxi) {
        delete taxi;
    }
    if (driver) {
        delete driver;
    }
    delete location;
}
