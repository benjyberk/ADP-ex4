//
// Benjy Berkowicz - 336182589
// Advanced Programming 2016-2017 Bar Ilan
//

#include <unistd.h>
#include "TaxiDispatch.h"
#include "../MapClasses/FindPath.h"
#include "../GameControlClasses/Serializer.h"
#include "../StructuralClasses/Tcp.h"

using namespace std;

void TaxiDispatch::addTaxi(Taxi * newTaxi) {
    Serializer s;
    // If the taxi ID doesn't appear, we initialize it
    if (database.count(newTaxi->getID()) == 0) {
        database[newTaxi->getID()] = new DriverTaxiContainer();
    }
    newTaxi->setLocation(database[newTaxi->getID()]->location);
    database[newTaxi->getID()]->setTaxi(newTaxi);
    string serial = s.serializeTaxi(newTaxi);
}

void TaxiDispatch::addDriver(Driver * newDriver, int tcp) {
    // If the driver id doesn't appear, we initialize it
    if (database.count(newDriver->getID()) == 0) {
        database[newDriver->getID()] = new DriverTaxiContainer();
    }

    // We generate the listener, and attune it to the location of the driver
    Point * start = database[newDriver->getID()]->location;
    DriverLocationListener * l = new DriverLocationListener(start, newDriver->getID());
    listeners.push_back(l);
    database[newDriver->getID()]->setDriver(newDriver);
    database[newDriver->getID()]->assignSocketNum(tcp);
}

void TaxiDispatch::sendTaxi(int * refID) {
    //serialize the taxi
    string buffer;
    int id = *refID;
    Serializer serializer;
    Taxi *taxiToSend = database[id]->getTaxi();

    // We load the serialized taxi into the buffer
    buffer = serializer.serializeTaxi(taxiToSend);
    string send(buffer);
    // The taxi is sent
   tcp->sendData(send, database[id]->getSocketNum());
}

void TaxiDispatch::addTrip(TripInfo * getTrip) {
    // We lock the thread to avoid race conditions (for the bfsRouting algorithm)
    pthread_mutex_lock(&lock);
    TripInfo * newTrip = getTrip;

    // We calculate the route for the taxi to take
    vector<Point> * r = router.bfsRoute(gridMap, newTrip->getStartPoint(), newTrip->getEndPoint());

    // If the route is 'unpathable' we stop the process here (the trip isn't entered)
    Point empty = Point(-1,-1);
    if (r->at(0) != empty) {
        // Otherwise the calculated route is assigned to the taxi
        newTrip->assignRoute(r);

        // We add the trip to the list of trips
        trips.push_back(newTrip);
    }
    else {
        // If the route is un-pathable we free allocated memory
        delete r;
        delete getTrip;
    }

    // We inform the main thread that another trip has been processed
    pendingTrips--;
    // The thread is finished and thus unlocks
    pthread_mutex_unlock(&lock);
    return;
}

Point *TaxiDispatch::getDriverLocation(int id) {
    // We search the listeners for the correct ID
    for (int i = 0; i < listeners.size(); i++) {
        if (listeners[i]->id == id) {
            return listeners[i]->getLocation();
        }
    }
    // If we got to this point, the requested ID was not present, thus we return an error
    return 0;
}

TaxiDispatch::TaxiDispatch(GridMap * grid, Clock newClock) {
    gridMap = grid;
    clock = newClock;
    pendingTrips = 0;

    if (pthread_mutex_init(&lock, NULL) != 0) {
        //"Mutex initialization failed"
    }
}

TaxiDispatch::~TaxiDispatch() {
    for (int i = 0; i < listeners.size(); i++) {
        delete listeners[i];
    }
    for (int i = 0; i < trips.size(); i++) {
        delete trips[i]->getRoute();
        delete trips[i];
    }

    for (taxi_driver_iterator iterator = database.begin(); iterator != database.end(); iterator++) {
        delete iterator->second;
    }
    // Destroy the mutex lock
    pthread_mutex_destroy(&lock);
}

void TaxiDispatch::sendTrip() {
    //assign trips based on their starting point if its the same as a driver.
}

void TaxiDispatch::moveOneStep() {
    // We increase the time by one
    clock.time++;
    TripInfo *current;
    DriverLocationListener *foundListener;
    Serializer serializer;
    string buffer;

    // First we move any taxis that need to be moved along their assigned paths
    for(taxi_driver_iterator iterator = database.begin(); iterator != database.end(); iterator++) {
        if (iterator->second->taxi->isAssigned) {
            int id = iterator->second->taxi->getID();
            iterator->second->taxi->move();
            tcp->sendData("M", database[id]->getSocketNum());
        }
    }

    // We wait for any processing to be done on trips that are pending (essentially performing
    // a pthread_join operation except threadpool styled.
    while (pendingTrips != 0) {
        sleep(1);
    }

    // Now we assign any new trips that need to be assigned
    for (int i = 0; i < trips.size(); i++) {
        current = trips[i];

        // If we are at the right time for this  trip to start
        if (clock.time == current->getStartTime()) {
            // We search for a taxi/driver in the correct position
            for (int j = 0; j < listeners.size(); j++) {
                foundListener = listeners[j];
                Point a = *(foundListener->getLocation());
                Point b = current->getStartPoint();
                // If we have found a taxi at the correct location
                if (a == b) {

                    int foundID = foundListener->id;

                    // We assign the trip to the taxi
                    database[foundID]->taxi->assignTrip(*current);
                    listeners.erase(listeners.begin() + j);
                    listeners.push_back(foundListener);

                    // We send the client info on the assigned taxi
                    buffer = serializer.serializeTrip(current);
                    tcp->sendData(buffer, database[foundID]->getSocketNum());

                    break;
                }
            }
        }
    }
}

void TaxiDispatch::assignSocket(Tcp *tcp1) {
    tcp = tcp1;
}

void TaxiDispatch::closingOperations() {
    for(taxi_driver_iterator iterator = database.begin(); iterator != database.end(); iterator++) {
        if (iterator->second->driver != 0) {
            int id = iterator->second->taxi->getID();
            tcp->sendData("X", database[id]->getSocketNum());
        }
    }
    delete tcp;
}


