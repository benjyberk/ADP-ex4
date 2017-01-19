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
#include "Tcp.h"

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
    bool keepGoing = true;
    char buffer[100000];

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

    Tcp * tcp = new Tcp(0, atoi(argv[2]), "127.0.0.1");
    tcp->initialize();

    // Send the serialized driver
    tcp->sendData(send, 0);

    // Receive the taxi
    tcp->reciveData(buffer, sizeof(buffer), 0);
    // Deserialize the taxi
    receive = string(buffer);
    taxi = serial.deserializeTaxi(receive);

    while (keepGoing) {
        // Wait to receive the trip details (or the ending signal)
        tcp->reciveData(buffer, sizeof(buffer), 0);
        receive = string(buffer);

        if (receive.compare(0,1,"X") == 0) {
            // If, instead of receiving a trip, we receive an "end", end the program
            break;
        }

        // Deserialize the trip and assign it to our taxi
        receive = string(buffer);
        trip = serial.deserializeTrip(receive);
        taxi->assignTrip(*trip);

        Point a = *taxi->getLocation();
        Point b = trip->getEndPoint();
        // We loop through this whole trip until we reach the end, or are told to end
        while (a != b) {
            tcp->reciveData(buffer, sizeof(buffer), 0);
            receive = string(buffer);

            // When we receive a 9 from the server, we know to move the taxi by one
            if (receive.compare(0,1,"M") == 0) {
                taxi->move();
            }
            // When we receive an X from the server, we leave our loop entirely
            if (receive.compare(0,1,"X") == 0) {
                keepGoing = false;
                break;
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
    delete tcp;
}