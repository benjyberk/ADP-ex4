//
// Benjy Berkowicz - 336182589
// Advanced Programming 2016-2017 Bar Ilan
//

#ifndef ADVANCED_EX2_DRIVER_H
#define ADVANCED_EX2_DRIVER_H

class Taxi;
class DriverLocationListener;

#include <cstdlib>
#include <vector>
#include "MaritalStatus.h"
#include "Taxi.h"
#include "DriverLocationListener.h"
#include "TripInfo.h"

/**
 * The driver is essentially a container class for information. His only (cureent)
 * method of note is add listener - which simply adds a listener
 */
class Driver {
private:
    int id;
    int age;
    MaritalStatus maritalStatus;
    int yearsExperience;
    int averageSatisfaction;
    int passengers;
    int carID;
public:
    Driver(int, int, MaritalStatus, int, int);
    Driver(int, int, int, int);
    Driver();
    int getID();
    int getAge();
    MaritalStatus getMarital();
    int getTaxi();
    int getSatisfaction();
    int getYears();
};


#endif //ADVANCED_EX2_DRIVER_H
