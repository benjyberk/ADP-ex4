//
// Benjy Berkowicz - 336182589
// Advanced Programming 2016-2017 Bar Ilan
//

#include <cstring>
#include "GameControl.h"
#include "LuxuryTaxi.h"
#include "StandardTaxi.h"
#include "Socket.h"
#include "Udp.h"
#include "Serializer.h"

using namespace std;

GameControl::GameControl() {
}


void GameControl::addTaxi(std::string input) {
    int id, type;
    CarMaker manufacturer;
    Color color;

    // Parse and tokenize the input
    vector<string> tokens = tokenizeByChar(input, ',');

    Taxi * t;

    // We begin generating the input required to build our taxi
    id = atoi(tokens[0].c_str());
    type = atoi(tokens[1].c_str());
    manufacturer = (CarMaker)enumFromString(tokens[2], 'T');
    color = (Color)enumFromString(tokens[3], 'C');

    // The taxi is generated and added to the dispatcher
    if (type == 1) {
        t = new StandardTaxi(id, manufacturer, color);
    } else {
        t = new LuxuryTaxi(id, manufacturer, color);
    }
    dispatcher->addTaxi(t);
}

void GameControl::getGeneralInput() {
    Point dimensions;
    int numOfObstacles;
    string input;
    char dummy;

    // We get the first line required for general input
    getline(cin, input);
    // The line is tokenized
    vector<string> tokens = tokenizeByChar(input, ' ');

    dimensions.x = atoi(tokens[0].c_str());
    dimensions.y = atoi(tokens[1].c_str());

    // The number of obstacles is tokenized
    getline(cin, input);
    tokens = tokenizeByChar(input, ' ');
    numOfObstacles = atoi(input.c_str());

    // We loop through, gathering the obstacles and adding them to a vector
    for (int i = 0; i < numOfObstacles; i++) {
        getline(cin, input);
        tokens = tokenizeByChar(input, ',');
        Point temp;

        temp.x = atoi(tokens[0].c_str());
        temp.y = atoi(tokens[1].c_str());

        obstacles.push_back(temp);
    }

    // The obstacles are put in the gridmap
    gridmap = new GridMap(dimensions.x, dimensions.y, obstacles);
    // The gridmap is used by the dispatcher
    dispatcher = new TaxiDispatch(gridmap, clock);
}

void GameControl::addRide(string input) {
    int id, num_passengers, tariff, startTime;
    Point start, end;
    vector<string> tokens = tokenizeByChar(input, ',');

    // The input is tokenized and parsed into Points
    start = Point(atoi(tokens[1].c_str()), atoi(tokens[2].c_str()));
    end = Point(atoi(tokens[3].c_str()), atoi(tokens[4].c_str()));

    id = atoi(tokens[0].c_str());
    num_passengers = atoi(tokens[5].c_str());
    tariff = atoi(tokens[6].c_str());
    startTime = atoi(tokens[7].c_str());

    // The trip is generated based on input
    TripInfo* t = new TripInfo(id, start, end, num_passengers, tariff, startTime);
    dispatcher->addTrip(t);
}

void GameControl::printTaxiLocation(string input) {
    // Parses the input and prints the taxi location from the dispatcher
    vector<string> tokens = tokenizeByChar(input, ',');
    int id = atoi(tokens[0].c_str());
    Point * location = dispatcher->getDriverLocation(id);
    cout << location->toString() << endl;
}

void GameControl::addDriver(string input, char* argv[]) {
    char buffer[2048];
    Serializer serializer;

    //create socket
    Socket * udp = new Udp(1, atoi(argv[1]), "127.0.0.1");
    udp->initialize();
    cout << "Socket created on port " << argv[1] << "value " << udp << endl;
    for(int i = 0; i < atoi(input.c_str()); i++){
        //gets the driver from the client
        udp->reciveData(buffer, sizeof(buffer));
        string receive(buffer);
        cout << "Received: " << receive << endl;
        //deserialize the driver from client
        Driver * d = serializer.deserializeDriver(receive);
        dispatcher->addDriver(d, udp);
        dispatcher->sendTaxi(d->getID());
    }
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
            break;
        default:
            returnVal = 0;
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

void GameControl::assignTaxiTrips() {
    dispatcher->provideTaxi();
}

GameControl::~GameControl() {
    delete gridmap;
    delete dispatcher;
}

void GameControl::moveOneStep() {
    dispatcher->moveOneStep();
}

void GameControl::closingOperations() {
    dispatcher->closingOperations();
}

