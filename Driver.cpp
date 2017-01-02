//
// Benjy Berkowicz - 336182589
// Advanced Programming 2016-2017 Bar Ilan
//

#include "Driver.h"
#include "TripInfo.h"
#include "Taxi.h"

using namespace std;

Driver::Driver(int n_id, int n_age, MaritalStatus n_mStatus, int n_experience, int n_vehicleID) {
    id = n_id;
    age = n_age;
    maritalStatus = n_mStatus;
    yearsExperience = n_experience;
    carID = n_vehicleID;
}

int Driver::getID() {
    return id;
}

int Driver::getAge() {
    return age;
}

MaritalStatus Driver::getMarital() {
    return SINGLE;
}

Taxi* Driver::getTaxi() {
    return 0;
}

int Driver::getYears() {
    return 0;
}

void Driver::setTaxi(Taxi*) {

}



void Driver::notifyListeners() {

}

int Driver::getSatisfaction() {
    return 0;
}

void Driver::addListener(DriverLocationListener * listener) {
    observers.push_back(listener);
}
