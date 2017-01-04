//
// Benjy Berkowicz - 336182589
// Advanced Programming 2016-2017 Bar Ilan
//

#include "client.h"
#include "Driver.h"
#include "Serializer.h"
#include "StandardTaxi.h"
#include "LuxuryTaxi.h"
#include "GameControl.h"
#include "Socket.h"
#include "Udp.h"

using namespace std;

int main(int argc, char* argv[]) {
    Clock clock;
    vector<string> tokens;
    GameControl gc;
    int id, age, experience, vehicleID;
    MaritalStatus mStatus;
    string input, send, receive;
    Serializer serial;
    Taxi * taxi;
    TripInfo * trip;
    char buffer[2048];

    // Get program input (a single driver)
    getline(cin, input);

    // Tokenize the input
    tokens = gc.tokenizeByChar(input, ',');

    id = atoi(tokens[0].c_str());
    age = atoi(tokens[1].c_str());
    mStatus = (MaritalStatus) gc.enumFromString(tokens[2], 'M');
    experience = atoi(tokens[3].c_str());
    vehicleID = atoi(tokens[4].c_str());

    // Generate the driver object
    Driver * d = new Driver(id, age, mStatus, experience, vehicleID);

    // Serialize the driver
    send = serial.serializeDriver(d);

    Socket * udp = new Udp(0, atoi(argv[2]), argv[1]);
    udp->initialize();
    // Send the serialized driver
    udp->sendData(send);
    // Receive the taxi
    udp->reciveData(buffer, sizeof(buffer));
    receive = string(buffer);
    taxi = serial.deserializeTaxi(receive);

    while (true) {
        // Wait to receive the trip
        udp->reciveData(buffer, sizeof(buffer));
        if (buffer[0] == 'X') {
            break;
        }
        receive = string(buffer);
        trip = serial.deserializeTrip(receive);
        Point a = *taxi->getLocation();
        Point b = trip->getEndPoint();
        while (a != b) {
            udp->reciveData(buffer, sizeof(buffer));
            if (buffer[0] == '9') {
                clock.time++;
                taxi->move();
                cout << "Taxi Location: " << taxi->getLocation()->toString();
                if (trip->getStartTime() == clock.time) {
                    a = trip->getStartPoint();
                    b = *taxi->getLocation();
                    if (a == b) {
                        taxi->assignTrip(*trip);
                    }
                }
            }
            a = *taxi->getLocation();
            b = trip->getEndPoint();
        }
    }
    delete d;
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