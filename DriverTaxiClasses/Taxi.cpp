//
// Benjy Berkowicz - 336182589
// Advanced Programming 2016-2017 Bar Ilan
//

#include "Taxi.h"
using namespace std;

Taxi::Taxi(int newId, CarMaker manu, Color newCol) {
    id = newId;
    color = newCol;
    manufacturer = manu;
    isAssigned = false;
}

Color Taxi::getColor() {
    return color;
}

CarMaker Taxi::getManufacturer() {
    return manufacturer;
}

int Taxi::getOdom() {
    return odometer;
}

int Taxi::getID() {
    return id;
}

int Taxi::getPrice() {
    return tariff;
}

Passenger *Taxi::getPassenger() {
    return 0;
}

void Taxi::setPassenger(Passenger) {

}

void Taxi::addListener(Listener *) {

}

void Taxi::removeListener(Listener *) {

}

void Taxi::setLocation(Point * newPoint) {
    location = newPoint;
}

void Taxi::setDriver(Driver * newDriver) {
    driver = newDriver;
}

void Taxi::assignTrip(TripInfo assign) {
    currentTrip = assign;
    upto = assign.getRoute()->size() - 2;
    isAssigned = true;
}

Point * Taxi::getLocation() {
    return location;
}
