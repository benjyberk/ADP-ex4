//
// Benjy Berkowicz - 336182589
// Advanced Programming 2016-2017 Bar Ilan
//

#include "TaxiDispatch.h"
#include "findPath.h"
#include "Serializer.h"

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

void TaxiDispatch::addDriver(Driver * newDriver, Socket* sock) {
    // If the driver id doesn't appear, we initialize it
    if (database.count(newDriver->getID()) == 0) {
        database[newDriver->getID()] = new DriverTaxiContainer();
    }

    // We generate the listener, and attune it to the location of the driver
    Point * start = database[newDriver->getID()]->location;
    DriverLocationListener * l = new DriverLocationListener(start, newDriver->getID());
    listeners.push_back(l);
    database[newDriver->getID()]->setDriver(newDriver);
    database[newDriver->getID()]->setSocket(sock);
}

void TaxiDispatch::sendTaxi(int id) {
    //serialize the taxi
    string buffer;

    Serializer serializer;
    Taxi *taxiToSend = database[id]->getTaxi();
    buffer = serializer.serializeTaxi(taxiToSend);
    Socket *sock = database[id]->getSocket();
    sock->sendData(buffer);
}

void TaxiDispatch::addTrip(TripInfo * newTrip) {
    vector<Point> * r = router.bfsRoute(gridMap, newTrip->getStartPoint(), newTrip->getEndPoint());

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

void TaxiDispatch::sendTrip() {
    //assign trips based on their starting point if its the same as a driver.
}

void TaxiDispatch::moveOneStep() {
    // We increase the time by one
    clock.time++;
    TripInfo current;
    DriverLocationListener *foundListener;
    Serializer serializer;
    string buffer;



    // First we move any taxis that need to be moved
    for(taxi_driver_iterator iterator = database.begin(); iterator != database.end(); iterator++) {
        if (iterator->second->taxi->isAssigned) {
            int id = iterator->second->taxi->getID();
            iterator->second->taxi->move();
            Socket *sock = database[id]->getSocket();
            sock->sendData("9");
        }
    }

    // Now we assign any new trips that need to be assigned
    for (int i = 0; i < trips.size(); i++) {
        current = trips[i];

        // If we are at the right time for this  trip to start
        if (clock.time == current.getStartTime()) {
            // We search for a taxi/driver in the correct position
            for (int j = 0; j < listeners.size(); j++) {
                foundListener = listeners[j];
                Point a = *(foundListener->getLocation());
                Point b = current.getStartPoint();
                // If we have found a taxi at the correct location
                if (a == b) {
                    cout << "Assigning taxi to trip ID " << current.getRideID() << endl;
                    int foundID = foundListener->id;
                    // We assign the trip to the taxi
                    database[foundID]->taxi->assignTrip(current);
                    listeners.erase(listeners.begin() + j);
                    listeners.push_back(foundListener);

                    ///////////
                    buffer = serializer.serializeTrip(&current);
                    Socket *sock = database[foundID]->getSocket();
                    sock->sendData(buffer);

                    break;
                }
            }
        }
    }
}

void TaxiDispatch::closingOperations() {
    for(taxi_driver_iterator iterator = database.begin(); iterator != database.end(); iterator++) {
        if (iterator->second->driver != 0) {
            int id = iterator->second->taxi->getID();
            Socket *sock = database[id]->getSocket();
            sock->sendData("X");
            delete sock;
        }
    }
}
