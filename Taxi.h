//
// Benjy Berkowicz - 336182589
// Advanced Programming 2016-2017 Bar Ilan
//

#ifndef ADVANCED_EX2_TAXI_H
#define ADVANCED_EX2_TAXI_H

class Passenger;
class Listener;
class Driver;

#include <stack>
#include "Color.h"
#include "Passenger.h"
#include "CarMaker.h"
#include "Driver.h"

class Taxi {
private:
    int id;
    int odometer;
    CarMaker manufacturer;
    Color color;
    Driver* driver;
    Listener** listeners;
protected:
    bool isAssigned;
    Passenger* passengers;
    Point* location;
    int tariff;
    int upto;
    TripInfo currentTrip;
public:
    Taxi(int, CarMaker, Color);
    Color getColor();
    CarMaker getManufacturer();
    int getOdom();
    int getID();
    int getPrice();
    Passenger* getPassenger();
    Point * getLocation();
    void setPassenger(Passenger);
    void setLocation(Point *);
    virtual int move() = 0;
    void addListener(Listener*);
    void removeListener(Listener*);
    void setDriver(Driver *);
    void assignTrip(TripInfo);
};


#endif //ADVANCED_EX2_TAXI_H
