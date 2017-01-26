//
// Benjy Berkowicz - 336182589
// Advanced Programming 2016-2017 Bar Ilan
//

#include <pthread.h>
#include <cstring>
#include "GameControl.h"
#include "LuxuryTaxi.h"
#include "StandardTaxi.h"
#include "Socket.h"
#include "Udp.h"
#include "Serializer.h"
#include "Tcp.h"
using namespace std;

GameControl::GameControl() {
    gridmap = 0;
    dispatcher = 0;
}


void GameControl::addTaxi(std::string input) {
    int id, type;
    CarMaker manufacturer;
    Color color;
    Taxi * t;
    stringstream str1,str2;
    // Parse and tokenize the input
    vector<string> tokens = tokenizeByChar(input, ',');

    // Check to see the input was valid
    if (tokens.size() != 4) {
        cout << -1 << endl;
        return;
    }

    // We begin generating the input required to build our taxi
    str1 << tokens[0];
    str2 << tokens[1];
    // Stringstreams are used for later validation
    str1 >> id;
    str2 >> type;

    manufacturer = (CarMaker)enumFromString(tokens[2], 'T');
    color = (Color)enumFromString(tokens[3], 'C');

    if (manufacturer < 0 || color < 0 || str1.fail() || str2.fail() || !inRange(id, -1, 32767) ||
            !inRange(type, 0, 3) || str1.rdbuf()->in_avail() != 0 || str2.rdbuf()->in_avail() != 0) {
        cout << -1 << endl;
        return;
    }

    // The taxi is generated and added to the dispatcher
    if (type == 1) {
        t = new StandardTaxi(id, manufacturer, color);
    } else {
        t = new LuxuryTaxi(id, manufacturer, color);
    }
    dispatcher->addTaxi(t);
    cout << "Valid Taxi Submitted" << endl;
}

void GameControl::getGeneralInput() {
    Point dimensions;
    int numOfObstacles;
    string input;
    int valid = 0;
    int xParam, yParam;
    vector<string> tokens;
    stringstream str1, str2;

    // Perform error checking
    while (valid < 2) {
        valid = 0;
        // We get the first line required for general input
        getline(cin, input);
        // The line is tokenized
        tokens = tokenizeByChar(input, ' ');

        resetstreams(&str1, &str2);

        // Check to see if we have received enough tokens (sufficient input)
        if (tokens.size() == 2) {
            // Put the tokens in to stringstreams to check for non-digit characters
            str1 << tokens[0];
            str1 >> xParam;

            str2 << tokens[1];
            str2 >> yParam;
            // Check to see that the values are valid
            if ((!inRange(xParam, 0, 32767)) || (!inRange(yParam, 0, 32767))
                || (str1.fail()) || (str2.fail())
                || str1.rdbuf()->in_avail() != 0 || str2.rdbuf()->in_avail() != 0) {
                // If we have invalid input, begin the loop again (dont set valid to true)
                cout << -1 << endl;
                continue;
            } else {
                // Otherwise, assign the parameters, set valid to true
                dimensions.x = xParam;
                dimensions.y = yParam;
                valid++;
            }
        } else {
            cout << -1 << endl;
            continue;
        }

        resetstreams(&str1, &str2);

        // The number of obstacles is tokenized
        getline(cin, input);
        str1 << input;
        str1 >> numOfObstacles;
        tokens = tokenizeByChar(input, ' ');
        if (str1.fail() || !inRange(numOfObstacles, -1, xParam * yParam) || tokens.size() > 1
                || str1.rdbuf()->in_avail() != 0) {
            cout << -1 << endl;
            continue;
        }
        else {
            valid++;
        }

        // We loop through, gathering the obstacles and adding them to a vector
        for (int i = 0; i < numOfObstacles; i++) {
            resetstreams(&str1, &str2);
            getline(cin, input);
            tokens = tokenizeByChar(input, ',');
            Point temp;

            // Validate that enough tokens have been input
            if (tokens.size() != 2) {
                cout << -1 << endl;
                valid = 0;
                obstacles.clear();
                break;
            }

            // Put the tokens into the stringstream for validation checking
            str1 << tokens[0];
            str2 << tokens[1];

            str1 >> temp.x;
            str2 >> temp.y;

            // If the input is not a number, or is not in the valid range, we print -1 and restart
            if (str1.fail() || str2.fail() || !inRange(temp.x, -1, dimensions.x) ||
                    !inRange(temp.y, -1, dimensions.y)
                || str1.rdbuf()->in_avail() != 0 || str2.rdbuf()->in_avail() != 0) {
                cout << -1 << endl;
                valid = 0;
                obstacles.clear();
                break;
            }

            obstacles.push_back(temp);
        }
    }

    cout << "Passed stage 1" << endl;
    // The obstacles are put in the gridmap
    gridmap = new GridMap(dimensions.x, dimensions.y, obstacles);
    // The gridmap is used by the dispatcher
    dispatcher = new TaxiDispatch(gridmap, clock);
}

void GameControl::addRide(string input) {
    int id, num_passengers, tariff, startTime, x, y;
    int convertedInts[4];
    Point tripPoints[2];
    Point dims;
    stringstream str1, str2;
    pthread_t oneThread;

    vector<string> tokens = tokenizeByChar(input, ',');
    if (tokens.size() != 8) {
        cout << -1 << endl;
        return;
    }

    dims = gridmap->getDimensions();
    x = y = 0;
    for (int i = 0; i < 4; i+= 2) {
        // The input is tokenized and parsed into Points
        str1 << tokens[i+1];
        str2 << tokens[i+2];

        str1 >> x;
        str2 >> y;

        // Validation for the Point
        if (str1.fail() || str2.fail() || !inRange(x, -1, dims.x) || !inRange(y, -1, dims.y)
            || str1.rdbuf()->in_avail() != 0 || str2.rdbuf()->in_avail() != 0) {
            cout << -1 << endl;
            return;
        }
        // This will only result in positions 0 and 1, because the loop only runs twice
        tripPoints[i / 2] = Point(x, y);
        resetstreams(&str1, &str2);
    }

    // We overwrite position 4 in the array of tokens for ease of looping:
    tokens[4] = tokens[0];
    for (int i = 0; i < 4; i++) {
        str1 << tokens[i + 4];
        str1 >> convertedInts[i];

        // Validation on the int
        if (str1.fail() || !inRange(convertedInts[i], -1, 32767) || str1.rdbuf()->in_avail() != 0) {
            cout << -1 << endl;
            return;
        }

        str1.str("");
        str1.clear();
    }

    // An addition check is performed on the start-time, as it cannot be equal to 0
    if (convertedInts[3] == 0) {
        cout << -1 << endl;
        return;
    }

    TripInfo* t = new TripInfo(convertedInts[0], tripPoints[0], tripPoints[1], convertedInts[1],
                               convertedInts[2], convertedInts[3]);

    sendTripParams * p = new sendTripParams;
    p->trip = t;
    p->dispatcher = dispatcher;

    // The trip is generated based on input
    // We create a thread to handle the processing of the trip
    if (pthread_create(&oneThread, NULL, tripCreationHelper, (void *) p) != 0) {
        //"Error creating thread";
    }
    // We add our thread id to the list for later 'joining' when necessary
    threadDB.push_back(oneThread);
}

void GameControl::printTaxiLocation(string input) {
    // Parses the input and prints the taxi location from the dispatcher
    vector<string> tokens = tokenizeByChar(input, ',');
    int id = atoi(tokens[0].c_str());
    Point * location = dispatcher->getDriverLocation(id);
    cout << location->toString() << endl;
}

void GameControl::addDriver(string input, char* argv[]) {
    vector<pthread_t> threadIDs;
    char buffer[100000];
    Serializer serializer;

    //Create the socket to receive the driver
    Tcp * tcp = new Tcp(1, atoi(argv[1]), "127.0.0.1");
    tcp->initialize();
    dispatcher->assignSocket(tcp);

    // Loop through all clients, receiving their info
    for(int i = 0; i < atoi(input.c_str()); i++){
        pthread_t oneThread;
        tcp->acceptSock();

        //Gets the driver from the client using the socket based on what the tcp socket is up to
        tcp->reciveData(buffer, sizeof(buffer), tcp->upto - 1);
        string receive(buffer);

        //deserialize the driver from client
        Driver * d = serializer.deserializeDriver(receive);
        dispatcher->addDriver(d, tcp->upto - 1);

        // Create the thread to communicate with client (to send back the taxi)
        int id = d->getID();
        sendTaxiParams p;
        p.id = &id;
        p.dispatcher = dispatcher;

        if (pthread_create(&oneThread, NULL, clientCreationHelper, (void *) &p) != 0) {
            //"Error creating thread";
        }
        // Add the thread to our list for later joining
        threadIDs.push_back(oneThread);
    }
    finishInput(&threadIDs);
}

int GameControl::enumFromString(string raw, char type) {
    int returnVal;
    // Given the input type we could be parsing a MarriageStatus, Color, or TypeofCar
    switch (type) {
        case 'M':
            if (!raw.compare("S")) {
                returnVal = SINGLE;
            }
            else if (!raw.compare("M")) {
                returnVal = MARRIED;
            }
            else if (!raw.compare("D")) {
                returnVal = DIVORCED;
            }
            else if (!raw.compare("W")) {
                returnVal = WIDOWED;
            }
            else {
                returnVal = -1;
            }
            break;
        case 'C':
            if (!raw.compare("R")) {
                returnVal = RED;
            }
            else if (!raw.compare("B")) {
                returnVal = BLUE;
            }
            else if (!raw.compare("G")) {
                returnVal = GREEN;
            }
            else if (!raw.compare("P")) {
                returnVal = PINK;
            }
            else if (!raw.compare("W")) {
                returnVal = WHITE;
            }
            else {
                returnVal = -1;
            }
            break;
        case 'T':
            if (!raw.compare("H")) {
                returnVal = HONDA;
            }
            else if (!raw.compare("S")) {
                returnVal = SUBARU;
            }
            else if (!raw.compare("T")) {
                returnVal = TESLA;
            }
            else if (!raw.compare("F")) {
                returnVal = FIAT;
            }
            else {
                returnVal = -1;
            }
            break;
        default:
            returnVal = -1;
            break;
    }
    return returnVal;
}

vector<string> GameControl::tokenizeByChar(string input, char delim) {
    vector<string> tokens;
    istringstream iss(input);
    string oneToken;

    // We use a stringstream to tokenize our output
    while(getline(iss, oneToken, delim)) {
        tokens.push_back(oneToken);
    }

    return tokens;
}

GameControl::~GameControl() {
    if (gridmap != 0) {
        delete gridmap;
    }
    if (dispatcher != 0) {
        delete dispatcher;
    }
}

void GameControl::finishInput(vector<pthread_t> * input) {
    for (int i = 0; i < input->size(); i++) {
        pthread_join(input->at(i), NULL);
    }
}

void GameControl::moveOneStep() {
    if(!threadDB.empty()){
        for(int i = 0; i < threadDB.size(); ++i){
            pthread_join(threadDB.at(i), NULL);
        }
        threadDB.clear();
    }
    dispatcher->moveOneStep();
}

void GameControl::closingOperations() {
    dispatcher->closingOperations();
}

void * GameControl::clientCreationHelper(void *generic) {
    sendTaxiParams * p = (sendTaxiParams *)generic;
    p->dispatcher->sendTaxi(p->id);
    return 0;
}

void * GameControl::tripCreationHelper(void * generic) {
    sendTripParams * p = (sendTripParams *)generic;
    p->dispatcher->addTrip(p->trip);
    delete p;
    return 0;
}

bool GameControl::inRange(int check, int lowerBound, int upperBound) {
    return (check < upperBound) && (check > lowerBound);
}

void GameControl::resetstreams(stringstream *a, stringstream *b) {
    a->str("");
    a->clear();
    b->str("");
    b->clear();
}
