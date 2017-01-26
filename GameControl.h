//
// Benjy Berkowicz - 336182589
// Advanced Programming 2016-2017 Bar Ilan
//

#ifndef ADVANCED_EX2_GAMECONTROL_H
#define ADVANCED_EX2_GAMECONTROL_H


#include <map>
#include "TaxiDispatch.h"
#include "Clock.h"

/**
 * The Game Control class handles all input and directs the creation
 * of the objects needed for the game.
 */
class GameControl {
private:
    std::vector<Point> obstacles;
    GridMap * gridmap;
    TaxiDispatch * dispatcher;
    Clock clock;
    vector<pthread_t> threadDB;
    pthread_mutex_t lock;
public:
    // Used for threading to create a thread for every taxi
    typedef struct params {
        TaxiDispatch* dispatcher;
        int * id;
    } sendTaxiParams;

    // Used for threading to create a thread for every input trip
    typedef struct params2 {
        TaxiDispatch* dispatcher;
        TripInfo * trip;
    } sendTripParams;

    // Converts the input string into the enumeration based on type
    int enumFromString(std::string raw, char type);
    // Tokenizes a string and returns the vector
    std::vector<std::string> tokenizeByChar(std::string, char);
    GameControl();
    // Parses a driver from input and adds it to the Taxi Dispatcher
    void addDriver(std::string, char* args[]);
    // Parses a taxi from input and adds it to the Taxi Dispatcher
    void addTaxi(std::string input);
    // Parses the dimensions of the game, creates the gridmap and obstacles elements
    void getGeneralInput();
    // Adds a new trip to the taxi dispatcher
    void addRide(std::string);
    // Outputs the location of a taxi
    void printTaxiLocation(std::string);
    // Moves all taxis assigned on trips
    void moveOneStep();
    // Close all sockets, release data
    void closingOperations();
    // Finish getting driver inputs
    void finishInput(vector<pthread_t> * input);
    // Used for threading to create multiple clients
    static void * clientCreationHelper(void *);
    // Used for threading to create multiple trips
    static void * tripCreationHelper(void *);
    // Check if a number is in a given range
    bool inRange(int check, int lowerBound, int upperBound);
    void resetstreams(stringstream *a, stringstream *b);
    ~GameControl();
};


#endif //ADVANCED_EX2_GAMECONTROL_H
