//
// Benjy Berkowicz - 336182589
// Advanced Programming 2016-2017 Bar Ilan
//

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

    Socket * udp = new Udp(0, atoi(argv[2]), "127.0.0.1");
    udp->initialize();

    // Send the serialized driver
    udp->sendData(send);
    cout << "i, the client, sent a driver" << endl;
    // Receive the taxi
    udp->reciveData(buffer, sizeof(buffer));
    cout << "i, the client, recived a taxi" << endl;
    // Deserialize the taxi
    receive = string(buffer);
    taxi = serial.deserializeTaxi(receive);

    while (true) {
        // Wait to receive the trip
        udp->reciveData(buffer, sizeof(buffer));
        cout << "got the trip"<<endl;
        receive = string(buffer);

        if (receive.compare("X") == 0) {
            // If, instead of receiving a trip, we receive an "end", end the program
            break;
        }
        receive = string(buffer);
        trip = serial.deserializeTrip(receive);
        cout << "our trip is" << trip->getRideID() << endl;
        taxi->assignTrip(*trip);
        Point a = *taxi->getLocation();
        Point b = trip->getEndPoint();
        // We loop through this whole trip
        while (a != b) {
            udp->reciveData(buffer, sizeof(buffer));
            receive = string(buffer);
            cout << "recived" << buffer << endl;
            // When we receive a 9 from the server, we know to move the taxi by one
            if (receive.compare("9") == 0) {
                taxi->move();
            }
            a = *taxi->getLocation();
            b = trip->getEndPoint();
        }
        // We have completed one trip, we free the allocated memory
        delete trip->getRoute();
        delete trip;
    }
    delete taxi->getLocation();
    delete taxi;
    delete d;
    delete udp;
}