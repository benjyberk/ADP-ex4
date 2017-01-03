//
// Benjy Berkowicz - 336182589
// Advanced Programming 2016-2017 Bar Ilan
//

#include "client.h"
#include "Driver.h"
#include "Serializer.h"
#include "StandardTaxi.h"
#include "LuxuryTaxi.h"
#include <boost/iostreams/device/back_inserter.hpp>
#include <boost/iostreams/stream.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
using namespace std;

void client::run() {
    vector<string> tokens;

    int id, age, experience, vehicleID;
    MaritalStatus mStatus;

    // Tokenize the input
    tokens = tokenizeByChar(input, ',');

    id = atoi(tokens[0].c_str());
    age = atoi(tokens[1].c_str());
    mStatus = (MaritalStatus) enumFromString(tokens[2], 'M');
    experience = atoi(tokens[3].c_str());
    vehicleID = atoi(tokens[4].c_str());

    // Generate the driver and add it to the dispatcher
    Driver * d = new Driver(id, age, mStatus, experience, vehicleID);

}

/*Driver d(1,1,SINGLE,1,1);
string serial;
boost::iostreams::back_insert_device<std::string> inserter(serial);
boost::iostreams::stream<boost::iostreams::back_insert_device<std::string> > s(inserter);
boost::archive::binary_oarchive oa(s);
oa << d;
s.flush();

cout << serial << endl;
Driver *d2;
size_t len = serial.size();
char * begin = (char *)serial.c_str();
char * end = begin + serial.size();
boost::iostreams::basic_array_source<char> device(begin, end);
boost::iostreams::stream<boost::iostreams::basic_array_source<char> > s2(device);
boost::archive::binary_iarchive ia(s2);
ia >> d2;*/

/*
 *
    Serializer serial;
    string returnString;
    findPath find;
    vector<Point> v;
    GridMap g(4, 4, v);

    Driver d(1,21,DIVORCED,3,1);
    cout << d.getID() << ":" << d.getYears() << ":" << d.getMarital() << ":" << d.getAge() << ":" <<endl;
    returnString = serial.serializeDriver(&d);
    //cout << returnString;

    Driver *k;
    k = serial.deserializeDriver(returnString);
    cout << k->getID() << ":" << k->getYears() << ":" << k->getMarital() << ":" << k->getAge() << ":"<<endl;
    cout << "@@@@@@@@@@@@@@@@@@@@" << endl;

    LuxuryTaxi t(1,HONDA,RED);
    returnString = serial.serializeTaxi(&t);
    cout << returnString << endl;

    Taxi* r;
    r = serial.deserializeTaxi(returnString);
    cout << r->getID() << ":" << r->getPrice() << endl;
    cout << "@@@@@@@@@@@@@@@@@@@@" << endl;

    TripInfo ti(5, Point(0,0), Point(3,2), 5, 5, 7);
    vector<Point> * st = find.bfsRoute(&g, Point(0,0), Point(3,2));
    ti.assignRoute(st);

    returnString = serial.serializeTrip(&ti);
    cout << returnString << endl;
    for (int i = 0; i < ti.getRoute()->size(); i++) {
        cout << ti.getRoute()->at(i).toString();
    }
    cout << endl;
    TripInfo* rti;
    rti = serial.deserializeTrip(returnString);
    cout << rti->getRoute()->size() << endl;
    for (int i = 0; i < rti->getRoute()->size(); i++) {
        cout << rti->getRoute()->at(i).toString();
    }
    cout << endl;

 */