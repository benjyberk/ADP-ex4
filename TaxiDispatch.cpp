//
// Benjy Berkowicz - 336182589
// Advanced Programming 2016-2017 Bar Ilan
//

#include "TaxiDispatch.h"
#include "findPath.h"

using namespace std;

void TaxiDispatch::provideTaxi() {
    // We loop through all the trips, assigning them/running them if possible
    while (!trips.empty()) {
        // We take the first trip
        TripInfo current = trips[0];

        // We search for a taxi/driver in the correct position
        for (int i = 0; i < listeners.size(); i++) {
            DriverLocationListener *foundListener = listeners[i];
            Point a = *(foundListener->getLocation());
            Point b = current.getStartPoint();
            int foundID = foundListener->id;
            // If we have found a taxi at the correct location
            if (a == b) {
                if (clock.time == current.getStartTime()) {
                    // We assign the trip to the taxi
                    database[foundID]->taxi->assignTrip(current);
                    clock.time++;
                    listeners.erase(listeners.begin() + i);
                    listeners.push_back(foundListener);
                    break;
                }
            }
        }

        //delete trips.front();
        //trips.pop_front();
    }
}

void TaxiDispatch::addTaxi(Taxi * newTaxi) {
    // If the taxi ID doesn't appear, we initialize it
    if (database.count(newTaxi->getID()) == 0) {
        database[newTaxi->getID()] = new DriverTaxiContainer();
    }
    newTaxi->setLocation(database[newTaxi->getID()]->location);
    database[newTaxi->getID()]->setTaxi(newTaxi);
}

void TaxiDispatch::addDriver(Driver * newDriver) {
    // If the driver id doesn't appear, we initialize it
    if (database.count(newDriver->getID()) == 0) {
        database[newDriver->getID()] = new DriverTaxiContainer();
    }

    // We generate the listener, and attune it to the location of the driver
    Point * start = database[newDriver->getID()]->location;
    DriverLocationListener * l = new DriverLocationListener(start, newDriver->getID());
    listeners.push_back(l);
    newDriver->addListener(l);
    database[newDriver->getID()]->setDriver(newDriver);
}

void TaxiDispatch::addTrip(TripInfo * newTrip) {
    stack<Point> * r = router.bfsRoute(gridMap, newTrip->getStartPoint(), newTrip->getEndPoint());

    newTrip->assignRoute(r);
    // We add the trip to the list of trips
    trips.push_back(*newTrip);
}

Point *TaxiDispatch::getDriverLocation(int id) {
    // We search the listeners for the correct ID
    for (int i = 0; i < listeners.size(); i++) {
        if (listeners[i]->id == id) {
            return listeners[i]->getLocation();
        }
    }
}

TaxiDispatch::TaxiDispatch(GridMap * grid, Clock newClock) {
    gridMap = grid;
    clock = newClock;
}

TaxiDispatch::~TaxiDispatch() {
    for (int i = 0; i < listeners.size(); i++) {
        delete listeners[i];
    }
    for (int i = 0; i < trips.size(); i++) {
        //delete trips[i];
    }

    for(taxi_driver_iterator iterator = database.begin(); iterator != database.end(); iterator++) {
        delete iterator->second;
    }

}

void TaxiDispatch::moveOneStep() {
    // We increase the time by one
    clock.time++;
    TripInfo current;
    DriverLocationListener *foundListener;

    // First we move any taxis that need to be moved
    for(taxi_driver_iterator iterator = database.begin(); iterator != database.end(); iterator++) {
        iterator->second->taxi->move();
    }

    // Now we assign any new trips that need to be assigned
    for (int i = 0; i < trips.size(); i++) {
        current = trips[i];

        // If we are at the right time for this  trip to start
        if (clock.time == current.getStartTime()) {
            // We search for a taxi/driver in the correct position
            for (int i = 0; i < listeners.size(); i++) {
                foundListener = listeners[i];
                Point a = *(foundListener->getLocation());
                Point b = current.getStartPoint();
                // If we have found a taxi at the correct location
                if (a == b) {
                    cout << "Assigning taxi to trip ID " << current.getRideID() << endl;
                    int foundID = foundListener->id;
                    // We assign the trip to the taxi
                    database[foundID]->taxi->assignTrip(current);
                    listeners.erase(listeners.begin() + i);
                    listeners.push_back(foundListener);
                    break;
                }
            }
        }
    }
}
