//
// Benjy Berkowicz - 336182589
// Advanced Programming 2016-2017 Bar Ilan
//

#include <cstdlib>
#include <string.h>
#include "Point.h"
#include "GridMap.h"
#include "GameControl.h"

using namespace std;

int main(int argc, char* argv[]) {

    //create new socket for the server to communicate
    Tcp * tcp = new Tcp(1, atoi(argv[1]), "127.0.0.1");
    tcp->initialize();

    string lineInput;
    stringstream stream;
    int getChoice;
    bool leaveLoop = false;
    char dummy;
    GameControl * gc = new GameControl(tcp);
    gc->getGeneralInput();

    getline(cin, lineInput);
    stream << lineInput;
    stream >> getChoice;
    while (!leaveLoop) {
        // If we couldn't read in the stream or if there was more in the line then we fail
        if (stream.fail() || stream.rdbuf()->in_avail() != 0) {
            // If invalid input was received, go into case default
            getChoice = 999;
        }
        if (getChoice < 6) {
            getline(cin, lineInput);
        }
        switch (getChoice) {
            case 1:
                gc->addDriver(lineInput);
                break;
            case 2:
                gc->addTrip(lineInput);
                break;
            case 3:
                gc->addTaxi(lineInput);
                break;
            case 4:
                gc->printTaxiLocation(lineInput);
                break;
            case 7:
                gc->closingOperations();
                leaveLoop = true;
                break;
            case 9:
                gc->moveOneStep();
                break;
            default:
                cout << -1 << endl;
                break;
        }
        if (!leaveLoop) {
            stream.str("");
            stream.clear();

            getline(cin, lineInput);
            stream << lineInput;
            stream >> getChoice;
        }
    }

    delete gc;
    delete tcp;
    return 0;
}
