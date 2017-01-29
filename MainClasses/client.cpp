//
// Benjy Berkowicz - 336182589
// Advanced Programming 2016-2017 Bar Ilan
//

#include "../DriverTaxiClasses/Driver.h"
#include "../GameControlClasses/Serializer.h"
#include "../DriverTaxiClasses/StandardTaxi.h"
#include "../DriverTaxiClasses/LuxuryTaxi.h"
#include "../GameControlClasses/GameControl.h"
#include "../StructuralClasses/Socket.h"
#include "../StructuralClasses/Udp.h"
#include "../StructuralClasses/Tcp.h"

using namespace std;

int main(int argc, char* argv[]) {
    Clock clock;
    vector<string> tokens;
    GameControl gc;
    int convertedInts[5];
    MaritalStatus mStatus;
    string input, send, receive;
    Serializer serial;
    Taxi * taxi;
    TripInfo * trip;
    stringstream str1;
    bool keepGoing = true;
    char buffer[100000];

    // Get program input (a single driver)
    getline(cin, input);
    // Tokenize the input
    tokens = gc.tokenizeByChar(input, ',');

    // Check that we have received enough input
    if (tokens.size() != 5) {
        return 0;
    }

    for (int i = 0; i < 4; i++) {
        // We skip 2, as the validation is different for a MaritalStatus object
        if (i == 2) { continue; }

        str1 << tokens[i];
        str1 >> convertedInts[i];

        // Validate the ints
        if (str1.fail() || convertedInts[i] < 0 || str1.rdbuf()->in_avail() != 0) {
            // If anything is invalid, we crash the client
            return 0;
        }
        // Clear the stringstream for next round
        str1.clear();
        str1.str("");
    }

    // Special error checking for the marital status
    mStatus = (MaritalStatus) gc.enumFromString(tokens[2], 'M');
    if ((int)mStatus == -1) {
        // We crash the client
        return 0;
    }

    // Generate the driver object
    Driver * d = new Driver(convertedInts[0], convertedInts[1], mStatus, convertedInts[3],
                            convertedInts[4]);

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

        Point taxiLocation = *taxi->getLocation();
        Point tripEndPoint = trip->getEndPoint();
        // We loop through this whole trip until we reach the end, or are told to end
        while (taxiLocation != tripEndPoint) {
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

            taxiLocation = *taxi->getLocation();
            tripEndPoint = trip->getEndPoint();
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