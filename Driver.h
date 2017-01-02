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
    Taxi* taxi;
    std::vector<DriverLocationListener *> observers;
public:
    Driver(int, int, MaritalStatus, int, int);
    int getID();
    int getAge();
    MaritalStatus getMarital();
    Taxi* getTaxi();
    int getSatisfaction();
    int getYears();
    void setTaxi(Taxi*);
    void notifyListeners();
    // Add a listener for the driver position
    void addListener(DriverLocationListener *);
};


#endif //ADVANCED_EX2_DRIVER_H
