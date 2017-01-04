//
// Benjy Berkowicz - 336182589
// Advanced Programming 2016-2017 Bar Ilan
//

#include "Serializer.h"
#include "StandardTaxi.h"
#include "LuxuryTaxi.h"

using namespace std;

std::string Serializer::serializeDriver(Driver * d) {
    ostringstream buildString;
    buildString << d->getID() << ';' << d->getAge() << ';' << (int)d->getMarital()
                << ';' << d->getYears() << ';' << d->getID();
    return buildString.str();
}

Driver *Serializer::deserializeDriver(std::string input) {
    istringstream parser(input);
    int id, age, years, carID, status;
    char dummy;
    parser >> id >> dummy >> age >> dummy >> status >> dummy >> years >> dummy >> carID;
    Driver* d = new Driver(id, age, (MaritalStatus)status, years, carID);
    return d;
}

std::string Serializer::serializeTaxi(Taxi * t) {
    ostringstream buildString;
    string location = serializePoint(*t->getLocation());
    buildString << t->getPrice() << ';' << t->getID() << ';'
                << (int)t->getManufacturer() << ';' << (int)t->getColor() << ';' << location;
    return buildString.str();
}

Taxi *Serializer::deserializeTaxi(std::string input) {
    int type, id, manu, color;
    char dummy;
    Taxi * returnObj;
    Point * location = new Point();
    istringstream parser(input);
    parser >> type >> dummy >> id >> dummy >> manu >> dummy >> color >> dummy >> location->x >>
            dummy >> location->y;
    if (type == 1) {
        returnObj = new StandardTaxi(id, (CarMaker)manu, (Color)color);
    } else {
        returnObj = new LuxuryTaxi(id, (CarMaker)manu, (Color)color);
    }
    returnObj->setLocation(location);
    return returnObj;
}

std::string Serializer::serializeTrip(TripInfo * t) {
    ostringstream buildString;
    Point next;
    string startP, endP;
    startP = serializePoint(t->getStartPoint());
    endP = serializePoint(t->getEndPoint());
    buildString << t->getRideID() << ';' << startP << ';'
                << endP << ';' << t->getNumPassengers()<< ';'
                << t->getTarrif() << ';' << t->getStartTime()
                << ';' << t->getRoute()->size();
    // We now add the list of points:
    int size = t->getRoute()->size();

    for (int i = 0; i < size; i++) {
        next = t->getRoute()->at(i);
        buildString << ';' << serializePoint(next);
    }
    buildString << ';';

    return buildString.str();
}

TripInfo *Serializer::deserializeTrip(std::string input) {
    int id, numPass, tarr, numELM, startTime;

    Point start, end;
    char dummy;
    TripInfo * returnObj;
    istringstream parser(input);
    parser >> id >> dummy >> start.x >> dummy >> start.y >> dummy >> end.x >> dummy >> end.y >>
            dummy >> numPass >> dummy >> tarr >> dummy >> startTime >> dummy >> numELM >> dummy;

    vector<Point> * route = new vector<Point>();
    for (int i = 0; i < numELM; i++) {

        Point newPoint;
        parser >> newPoint.x >> dummy >> newPoint.y >> dummy;
        route->emplace_back(newPoint);
    }

    returnObj = new TripInfo(id, start, end, numPass, tarr, startTime);
    returnObj->assignRoute(route);

    return returnObj;
}

std::string Serializer::serializePoint(Point p) {
    ostringstream build;
    build << p.x << ';' << p.y;
    return build.str();
}
