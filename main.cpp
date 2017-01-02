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

int main() {
    string lineInput;
    int getChoice;
    char dummy;
    GameControl * gc = new GameControl();
    gc->getGeneralInput();

    getline(cin, lineInput);
    getChoice = atoi(lineInput.c_str());
    while (getChoice != 7) {
        if (getChoice < 6) {
            getline(cin, lineInput);
        }
        switch (getChoice) {
            case 1:
                cout << "Entering case " << getChoice << endl;
                gc->addDriver(lineInput);
                break;
            case 2:
                cout << "Entering case " << getChoice << endl;
                gc->addRide(lineInput);
                break;
            case 3:
                cout << "Entering case " << getChoice << endl;
                gc->addTaxi(lineInput);
                break;
            case 4:
                cout << "Entering case " << getChoice << endl;
                gc->printTaxiLocation(lineInput);
                break;
            case 6:
                cout << "Entering case " << getChoice << endl;
                gc->assignTaxiTrips();
                break;
            case 9:
                cout << "Entering case " << getChoice << endl;
                gc->moveOneStep();
                break;
            default:
                break;
        }
        getline(cin, lineInput);
        getChoice = atoi(lineInput.c_str());
    }

    delete gc;

    return 0;
}
