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

Driver::Driver() {
    id = 0;
    age = 0;
    maritalStatus = SINGLE;
    yearsExperience = 0;
    carID = 0;
}

int Driver::getID() {
    return id;
}

int Driver::getAge() {
    return age;
}

MaritalStatus Driver::getMarital() {
    return maritalStatus;
}

int Driver::getTaxi() {
    return carID;
}

int Driver::getYears() {
    return yearsExperience;
}

int Driver::getSatisfaction() {
    return 0;
}

Driver::Driver(int n_id, int n_age, int n_experience, int n_vehicleID) {
    id = n_id;
    age = n_age;
    maritalStatus = SINGLE;
    yearsExperience = n_experience;
    carID = n_vehicleID;
}
