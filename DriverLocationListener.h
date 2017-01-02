//
// Benjy Berkowicz - 336182589
// Advanced Programming 2016-2017 Bar Ilan
//

#ifndef ADVANCED_EX2_DRIVERLOCATIONLISTENER_H
#define ADVANCED_EX2_DRIVERLOCATIONLISTENER_H


#include "Point.h"

/**
 * The driver-location-listener class provides a notification when a move event
 * has occured.
 */
class DriverLocationListener {
private:
    Point * currentLocation;
public:
    DriverLocationListener(Point *, int);
    void moveEvent(Point *);
    Point * getLocation();
    int id;
};


#endif //ADVANCED_EX2_DRIVERLOCATIONLISTENER_H
