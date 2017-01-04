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
    string lineInput;
    int getChoice;
    bool leaveLoop = false;
    char dummy;
    GameControl * gc = new GameControl();
    gc->getGeneralInput();

    getline(cin, lineInput);
    getChoice = atoi(lineInput.c_str());
    while (!leaveLoop) {
        if (getChoice < 6) {
            getline(cin, lineInput);
        }
        switch (getChoice) {
            case 1:
                gc->addDriver(lineInput, argv);
                break;
            case 2:
                gc->addRide(lineInput);
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
            case 9:
                gc->moveOneStep();
                break;
            default:
                break;
        }
        if (!leaveLoop) {
            getline(cin, lineInput);
            getChoice = atoi(lineInput.c_str());
        }
    }

    delete gc;

    return 0;
}
